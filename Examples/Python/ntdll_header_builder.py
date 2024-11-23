import argparse
import os
import sys
from typing import Iterator, Iterable
from collections import defaultdict, deque

# Must be after!
sys.path.append(os.path.abspath(os.curdir))
import pydia
from pydia import DataSource, Struct, Union, Enum

INVALID_NAMES = ["__m64", "_iobuf", "__m128"]


def topological_sort(objects, dependencies):
    """
    Topologically sorts the given objects based on their dependencies.

    :param objects: List of all objects.
    :param dependencies: Dict where key is an object and value is a list of objects it depends on.
    :return: List of objects in topologically sorted order.
    """
    # Build the graph
    graph = defaultdict(list)
    in_degree = {obj: 0 for obj in objects}  # Initialize in-degrees

    for obj, deps in dependencies.items():
        for dep in deps:
            graph[dep].append(obj)  # Add a directed edge dep -> obj
            in_degree[obj] += 1  # Increment in-degree for obj

    # Initialize queue with nodes having in-degree 0
    queue = deque([obj for obj in objects if in_degree[obj] == 0])
    sorted_order = []

    while queue:
        current = queue.popleft()
        sorted_order.append(current)

        # Process neighbors
        for neighbor in graph[current]:
            in_degree[neighbor] -= 1  # Decrement in-degree
            if in_degree[neighbor] == 0:
                queue.append(neighbor)

    # Check for cyclic dependency (should not happen here by assumption)
    if len(sorted_order) != len(objects):
        raise ValueError("Cyclic dependency detected")

    return sorted_order


def detect_and_print_cycle(objects, dependencies):
    """
    Detects and prints a cyclic dependency in the graph, if it exists.

    :param objects: List of all objects.
    :param dependencies: Dict where key is an object and value is a list of objects it depends on.
    """

    def dfs(node, visited, path):
        visited[node] = 1  # Mark as visiting
        path.append(node)  # Add to current path

        for neighbor in dependencies.get(node, []):  # Safe access to dependencies
            if visited[neighbor] == 0:  # Not visited
                if dfs(neighbor, visited, path):  # Recurse
                    return True
            elif visited[neighbor] == 1:  # Cycle detected
                # Extract and print the cycle
                cycle_start_index = path.index(neighbor)
                print(
                    "Cycle detected:",
                    " -> ".join(path[cycle_start_index:] + [neighbor]),
                )
                return True

        visited[node] = 2  # Mark as fully visited
        path.pop()  # Remove from current path
        return False

    # Initialize visited dictionary
    visited = {obj: 0 for obj in objects}

    for obj in objects:
        if visited[obj] == 0:  # Not visited
            if dfs(obj, visited, []):
                return True  # Stop after finding one cycle

    return False


def enum_values_to_dict(enum_values: Iterable[pydia.Data]):
    values: dict[str, int] = {}
    for entry in enum_values:
        values[entry.get_name()] = entry.get_value()
    return values


def assert_no_conflict_and_update_values(old_enum_values: dict, new_enum_values: dict):
    combined_values = dict(old_enum_values)
    for new_value in new_enum_values:
        assert (new_value not in combined_values) or (
            combined_values[new_value] == new_enum_values[new_value]
        )
        combined_values[new_value] = new_enum_values[new_value]
    return combined_values


def signed_to_unsigned(size: int, value: int) -> str:
    """
    Converts a signed integer to its unsigned equivalent of the same byte length.
    For negative values, return the result as a hexadecimal string.
    For non-negative values, return the result as a decimal string.

    :param size: The size in bytes (1, 2, 4, or 8).
    :param value: The signed integer value to convert.
    :return: A string representing the unsigned integer value.
    """
    if size not in (1, 2, 4, 8):
        raise ValueError("Size must be 1, 2, 4, or 8 bytes.")

    # Calculate the maximum value for the unsigned integer of the given size.
    max_unsigned_value = (1 << (size * 8)) - 1

    # Convert the signed value to its unsigned equivalent.
    unsigned_value = value & max_unsigned_value

    # Return hex if the initial value is negative, else return decimal.
    if value < 0:
        return hex(unsigned_value)
    return str(unsigned_value)


class EnumData:
    name: str
    size: int
    values: dict[str, int]

    def __init__(self, name, size, values):
        self.name = name
        self.size = size
        self.values = values

    def __repr__(self):
        return f"EnumData({self.name}, {self.size}, {self.values.__repr__()})"

    def format_value(self, value: int):
        return signed_to_unsigned(self.size, value)

    def __str__(self):
        return f"""
enum {self.name} : uint{self.size * 8}_t {{
    {"\n\t".join(list(str(f"{x} = { self.format_value(self.values[x])},") for x in self.values))}
}};
""".strip()

    def forward_decleration(self):
        return f"""enum {self.name} : uint{self.size * 8}_t;"""


class DataData:
    name: str
    data: pydia.Data

    def __init__(self, data):
        self.data = data
        self.name = self.data.get_name()

    @staticmethod
    def safe_type_name_resolution(type: pydia.Symbol):
        type_name = pydia.resolve_type_name(type)
        if type_name[0 : len("<unnamed-")] != "<unnamed-":
            return type_name

        # This is an unnamed enum/union/struct/...
        if type.get_sym_tag() == pydia.SymTag.Enum:
            values = enum_values_to_dict(type.get_values())
            return f"""
enum {{
\t{"\n\t".join(list(str(f"{x} = { values[x]},") for x in values))}
}}
""".strip()
        elif type.get_sym_tag() == pydia.SymTag.UDT:
            unnamed_tag_udt_data = UdtData(type)
            return f"""{unnamed_tag_udt_data.modifiers()}{unnamed_tag_udt_data.kind_name} {{\n\t{unnamed_tag_udt_data.members()}\n\t}}"""
        else:
            assert False, f"Invalid unnamed tag {type.get_sym_tag()}"

    def __str__(self):
        type = self.data.get_type()
        # if type.get_sym_tag() == pydia.SymTag.ArrayType:
        #     element_type = type.get_type()
        #     element_count = type.get_count()
        #     return f"""{DataData.safe_type_name_resolution(element_type)} {self.name}[{element_count}];"""
        return f"""{DataData.safe_type_name_resolution(type)} {self.name};"""


class UdtData:
    name: str
    data: pydia.Udt
    kind: pydia.UdtKind
    kind_name: str

    def __init__(self, data: pydia.Udt):
        self.data = data
        self.name = self.data.get_name()
        self.kind = self.data.get_udt_kind()
        assert (self.kind is pydia.UdtKind.Struct) or (self.kind is pydia.UdtKind.Union)
        self.kind_name = "struct" if (self.kind is pydia.UdtKind.Struct) else "union"

    def typedefs(self):
        if self.name == "<unnamed-tag>":
            return ""
        if self.name[0] != "_":
            return ""
        pure_name = self.name[1:]
        pointer_name = f"P{pure_name}"
        return f"using {pure_name} = {self.kind_name} {self.name};\nusing {pointer_name} = {self.kind_name} {self.name}*;"

    def members(self):
        return f"{'\n\t'.join(str(DataData(raw_member)) for raw_member in self.data.enumerate_members())}"

    def modifiers(self):
        return ""
        return f"""{"const " if self.data.is_const() else ""}{"volatile " if self.data.is_volatile() else ""}{"__unaligned " if self.data.is_unaligned() else ""}"""

    def forward_decleration(self):
        return f"""{self.modifiers()}{self.kind_name} {self.name};"""

    def __repr__(self):
        return (
            f"UdtData({self.name}, {self.data}, {list(self.data.enumerate_members())})"
        )

    def __str__(self):
        return f"""
{"#pragma pack(push, 1)" if self.data.is_packed() else ""}
{self.modifiers()}{self.kind_name} {self.name} {{
\t{self.members()}
}};
{"#pragma pack(pop)\n" if self.data.is_packed() else ""}{self.typedefs()}
""".strip()


def build_enum_header(data_sources: list[DataSource]):
    all_enums: dict[str, EnumData] = {}
    for data_source in data_sources:
        new_enums: dict[str, EnumData] = {}
        for enum in data_source.get_symbols(pydia.SymTag.Enum):
            if enum.get_name()[: len("<unnamed-enum-")] == "<unnamed-enum-":
                continue
            new_enums[enum.get_name()] = EnumData(
                enum.get_name(),
                enum.get_length(),
                enum_values_to_dict(enum.get_values()),
            )

        for new_enum in new_enums:
            if new_enum not in all_enums:
                all_enums[new_enum] = new_enums[new_enum]
                continue
            all_enums[new_enum].values = assert_no_conflict_and_update_values(
                all_enums[new_enum].values, new_enums[new_enum].values
            )

    return all_enums


def build_struct_header(data_sources: list[DataSource]):
    all_structs: dict[str, UdtData] = {}
    for data_source in data_sources:
        new_structs: dict[str, UdtData] = {}
        for struct in data_source.get_symbols(pydia.SymTag.UDT):
            a = UdtData(struct)
            if a.name == "<unnamed-tag>":
                continue
            new_structs[a.name] = a

        for new_struct in new_structs:
            if new_struct not in all_structs:
                all_structs[new_struct] = new_structs[new_struct]
                continue

    all_enums = build_enum_header(data_sources)

    all_definitions = {}
    all_definitions.update(all_enums)
    all_definitions.update(all_structs)

    # Build dependency graph
    dependencies = {
        struct.name: list(x.get_name() for x in struct.data.get_dependencies())
        for struct in all_structs.values()
        if struct.name != "<unnamed-tag>"
    }
    for k, v in dependencies.items():
        continue
        while "<unnamed-tag>" in v:
            print("UNNAMED", k)
            return
            v.remove("<unnamed-tag>")
        to_remove = []
        for x in v:
            if x[: len("<unnamed-")] == "<unnamed-":
                to_remove.append(x)
        for x in to_remove:
            v.remove(x)

    for enum_name in all_enums:
        assert enum_name not in dependencies
        dependencies[enum_name] = []

    for definition_name in all_definitions:
        assert (
            definition_name in dependencies
        ), f"Name {definition_name} missing from dependencies dictionary!"
    for k, dependecy_list in dependencies.items():
        assert all(
            d in all_definitions for d in dependecy_list
        ), f"Dependency list contains names not in definitions set! {k} {dependecy_list}"

    all_definition_names = list(dependencies.keys())
    assert not detect_and_print_cycle(all_definition_names, dependencies)
    sorted_definitions = topological_sort(all_definition_names, dependencies)

    for name in sorted_definitions:
        print(all_definitions[name].forward_decleration())
    for name in sorted_definitions:
        print(str(all_definitions[name]))


def build_header_for_file(file_paths: str):
    data_sources: list[DataSource] = []

    for file_path in file_paths:
        if not os.path.exists(file_path):
            raise ValueError(f'Path "{file_path}" does not exist!')
        if not os.path.isfile(file_path):
            raise ValueError(f'Path "{file_path}" is not a file!')
        data_sources.append(DataSource(file_path))

    print("#include <cstdint>")
    print("#include <functional>")
    print("#include <array>")
    print("")
    print("namespace windows {")
    print("using HRESULT = uint32_t;")
    # print(build_enum_header(data_sources))
    build_struct_header(data_sources)
    print("}")


def main():
    parser = argparse.ArgumentParser()

    parser.add_argument(
        "-f",
        "--files",
        help="Input dlls or pdbs from which to build the header",
        nargs="+",
    )

    args = parser.parse_args()

    if args.files is None:
        parser.print_help()
        return -1
    build_header_for_file(args.files)


if __name__ == "__main__":
    main()
