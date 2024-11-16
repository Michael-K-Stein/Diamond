import argparse
import os
import sys
from typing import Iterator, Iterable

# Must be after!
sys.path.append(os.path.abspath(os.curdir))
from pydia import DataSource, Struct, Union, Enum
import pydia


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

    def __str__(self):
        return f"""
enum {self.name} : uint{self.size * 8}_t {{
    {"\n    ".join(list(str(f"{x} = { self.values[x]},") for x in self.values))}
}};
""".strip()


def build_header_for_file(file_paths: str):
    all_enums: dict[str, EnumData] = {}

    for file_path in file_paths:
        if not os.path.exists(file_path):
            raise ValueError(f'Path "{file_path}" does not exist!')
        if not os.path.isfile(file_path):
            raise ValueError(f'Path "{file_path}" is not a file!')

        data_source = DataSource(file_path)
        types_to_look_for = (Struct, Union, Enum)
        new_enums: dict[str, EnumData] = {}
        for enum in data_source.get_symbols(pydia.SymTag.Enum):
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
    for x in all_enums:
        print(str(all_enums[x]))


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
