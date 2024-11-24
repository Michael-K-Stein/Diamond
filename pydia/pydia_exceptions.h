#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else

#include <Exceptions.h>

#define PYDIA_SAFE_TRIVIAL_ERROR_HANDLER()                                                                                                           \
    do                                                                                                                                               \
    {                                                                                                                                                \
        PyErr_SetString(PyDiaError, e.what());                                                                                                       \
        return NULL;                                                                                                                                 \
    } while (0)

#define PYDIA_SAFE_TRIVIAL_PROPERTY_NOT_AVAILABLE_ERROR_HANDLER()                                                                                    \
    do                                                                                                                                               \
    {                                                                                                                                                \
        PyErr_SetString(PyDiaPropertyNotAvailableError, e.what());                                                                                   \
        return NULL;                                                                                                                                 \
    } while (0)

#define PYDIA_SAFE_TRY_EXCEPT(unsafeCode, exceptionHandler)                                                                                          \
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE(unsafeCode, PYDIA_SAFE_TRIVIAL_PROPERTY_NOT_AVAILABLE_ERROR_HANDLER(), exceptionHandler)

#define PYDIA_SAFE_TRY(unsafeCode) PYDIA_SAFE_TRY_EXCEPT(unsafeCode, PYDIA_SAFE_TRIVIAL_ERROR_HANDLER())

#define PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE(unsafeCode, notAvailableHandler, exceptionHandler)                                                       \
    do                                                                                                                                               \
    {                                                                                                                                                \
        try                                                                                                                                          \
        {                                                                                                                                            \
            do                                                                                                                                       \
            {                                                                                                                                        \
                unsafeCode;                                                                                                                          \
            } while (0);                                                                                                                             \
        }                                                                                                                                            \
        catch ([[maybe_unused]] const dia::PropertyNotAvailableException& e)                                                                         \
        {                                                                                                                                            \
            do                                                                                                                                       \
            {                                                                                                                                        \
                notAvailableHandler;                                                                                                                 \
            } while (0);                                                                                                                             \
        }                                                                                                                                            \
        catch ([[maybe_unused]] const std::exception& e) /* The exception handler has no obligation of using the exception itself */                 \
        {                                                                                                                                            \
            do                                                                                                                                       \
            {                                                                                                                                        \
                exceptionHandler;                                                                                                                    \
            } while (0);                                                                                                                             \
        }                                                                                                                                            \
    } while (0)


#define XFOR_TRIVIAL_PYDIA_ERRORS(opperation)                                                                                                        \
    opperation(PropertyNotAvailable);                                                                                                                \
    opperation(InvalidUsage);                                                                                                                        \
    opperation(NotFound);

#define __DECLARE_TRIVIAL_PYDIA_ERROR(pureName) extern PyObject* PyDia##pureName##Error;


extern PyObject* PyDiaError;
XFOR_TRIVIAL_PYDIA_ERRORS(__DECLARE_TRIVIAL_PYDIA_ERROR);

PyObject* pydia_initializeErrors(PyObject* module);
