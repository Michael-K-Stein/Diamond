# pydia

## The ultimate Python wrapper for the Microsoft DIA SDK (Debug Interface Access)

---

## Goal

**pydia** aims to ease the manual handling of PDB files. No more hacking together some IDA-Python - you can now use your favorite python ditribution and simply install a package!
**pydia** makes all the common functionality used when working with PDB files extremely accessible.

### My future vision

Hopefully, we can make **pydia** so powerful we will be able to accurately recreate header files from PDBs alone.

## How?

The structure of **pydia** is as follows:

* Every DIA2 SDK COM function is wrapped by a neat C++ function which handles all memory allocation/de-allocation and reference count tracking. These C++ wrappers are found in DiaLib.
* Each DIA2 SDK "class" is implemented as a C-API Python class in pydia (the sub-project).
  * The C-Python wrapper will never directly call a COM function - rather it will call a DiaLib method which will wrap the low level memory managment.
* The C-Python wrappings (pydia) must be as user-friendly and safe as possible. It should be actively difficult to missuse pydia's exported Python API.
* The DiaLib wrappings should be 100% responsible for all low-level management - especially memory-wise. Unless the user is a dehydrated donkey they should not be able to cause DiaLib to "seg-fault" (0xC0000005 - `STATUS_ACCESS_VIOLATION`).
