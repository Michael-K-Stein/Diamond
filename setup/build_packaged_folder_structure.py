import sys
import os
import shutil


def create_init_file(dir_path: str):
    with open(os.path.join(dir_path, "__init__.py"), "w") as f:
        f.write("from .pydia import *\n")


def main():
    pyd_file_path = os.path.abspath(sys.argv[1])
    out_root_dir = sys.argv[2]
    setup_root_dir = os.path.abspath(sys.argv[3])
    project_root_dir = os.path.abspath(sys.argv[4])

    assert os.path.splitext(pyd_file_path)[1] == ".pyd", "File extension must be .pyd !"

    package_dir_path = os.path.abspath(os.path.join(out_root_dir, "package"))
    package_extension_dir_path = os.path.abspath(
        os.path.join(package_dir_path, "pydia")
    )

    os.makedirs(package_dir_path, exist_ok=True)
    os.makedirs(package_extension_dir_path, exist_ok=True)

    create_init_file(dir_path=package_extension_dir_path)

    # Copy the binary to the output tree structure
    shutil.copy(
        pyd_file_path,
        os.path.join(package_extension_dir_path, "pydia.pyd"),
    )

    # Copy setup.py from local setup dir to output package
    shutil.copy(
        os.path.join(setup_root_dir, "setup.py"),
        os.path.join(package_dir_path, "setup.py"),
    )

    shutil.copy(
        os.path.join(setup_root_dir, "MANIFEST.in"),
        os.path.join(package_dir_path, "MANIFEST.in"),
    )

    shutil.copy(
        os.path.join(project_root_dir, "README.md"),
        os.path.join(package_dir_path, "README.md"),
    )


if __name__ == "__main__":
    main()
