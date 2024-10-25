"""
"""

import os
from pickletools import pyset
import sys
import pytest
import pydia


def main():
    print(f"Python Version: {sys.version}")

    data_source = pydia.DataSource(
        R"C:\Users\mkupe\source\repos\pydia\CTests\Resources\ntdll.pdb"
    )
    print(data_source)


if __name__ == "__main__":
    pyset.main()
    os.system("pause")
