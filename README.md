# pydia

## The ultimate Python wrapper for the [Microsoft's DIA SDK (Debug Interface Access)](https://learn.microsoft.com/en-us/visualstudio/debugger/debug-interface-access/debug-interface-access-sdk)

---

## Goal

**pydia** aims to ease the manual handling of [PDB](https://en.wikipedia.org/wiki/Program_database) files. No more hacking together some [IDA-Python](https://python.docs.hex-rays.com/) - you can now use your favorite python ditribution and simply install a package!
**pydia** makes all the common functionality used when working with PDB files extremely accessible.

### My future vision

Hopefully, we can make **pydia** so powerful we will be able to accurately recreate header files from PDBs alone.

## How?

The ideaology of **pydia** is as follows:

* Every DIA2 SDK [COM](https://learn.microsoft.com/en-us/windows/win32/com/component-object-model--com--portal) function is wrapped by a neat C++ function which handles all memory allocation/de-allocation and reference count tracking. These C++ wrappers are found in DiaLib.
* Each DIA2 SDK "class" is implemented as a [C-API Python](https://docs.python.org/3/c-api/) class in pydia (the sub-project).
  * The C-Python wrapper will never directly call a COM function - rather it will call a DiaLib method which will wrap the low level memory managment.
* The C-Python wrappings (pydia) must be as user-friendly and safe as possible. It should be actively difficult to missuse pydia's exported Python API.
* The DiaLib wrappings should be 100% responsible for all low-level management - especially memory-wise. Unless the user is a dehydrated donkey they should not be able to cause DiaLib to "[seg-fault](https://en.wikipedia.org/wiki/Segmentation_fault)" (0xC0000005 - `STATUS_ACCESS_VIOLATION`).

## Internals

### Directory structure

* CTests
  * Testing framework for DiaLib based on Microsoft's [CppUnitTestFramework](https://learn.microsoft.com/en-us/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2022).
  * Resources
  * Generally useful binary/misc resources for tests.
* DiaLib
  * Implementation of the C++ wrapper library for the DIA2 SDK.
* PyTests
  * Testing framework for pydia (the C-API Python module) based on [pytest](https://docs.pytest.org/en/stable/).
* pydia
  * Implementation of the C-API Python module which wraps DiaLib (and by transitivity also the DIA2 SDK)
