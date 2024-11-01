#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_exceptions.h"
#include "pydia_other_types.h"
#include "pydia_symbol_private.h"
#include "pydia_trivial_init.h"


#define __TRIVIAL_PYDIA_SYMBOL_TYPE_DEFINITION(className) PYDIA_SYMBOL_TYPE_DEFINITION(className, 0)

XFOR_TRIVIAL_PYDIA_CLASSES(TRIVIAL_INIT_DEINIT);
XFOR_TRIVIAL_PYDIA_CLASSES(__TRIVIAL_PYDIA_SYMBOL_TYPE_DEFINITION);
XFOR_TRIVIAL_PYDIA_CLASSES(TRIVIAL_C_TO_PYTHON_SYMBOL_CONVERSION);
