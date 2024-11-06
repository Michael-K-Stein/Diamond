#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else

#define PYDIA_SAFE_TRY_EXCEPT(unsafeCode, exceptionHandler)                                                                                          \
    do                                                                                                                                               \
    {                                                                                                                                                \
        try                                                                                                                                          \
        {                                                                                                                                            \
            do                                                                                                                                       \
            {                                                                                                                                        \
                unsafeCode;                                                                                                                          \
            } while (0);                                                                                                                             \
        }                                                                                                                                            \
        catch ([[maybe_unused]] const std::exception& e) /* The exception handler has no obligation of using the exception itself */                 \
        {                                                                                                                                            \
            exceptionHandler;                                                                                                                        \
        }                                                                                                                                            \
    } while (0)

#define PYDIA_SAFE_TRY(unsafeCode)                                                                                                                   \
    PYDIA_SAFE_TRY_EXCEPT(unsafeCode, {                                                                                                              \
        do                                                                                                                                           \
        {                                                                                                                                            \
            PyErr_SetString(PyDiaError, e.what());                                                                                                   \
            return NULL;                                                                                                                             \
        } while (0);                                                                                                                                 \
    })

#define PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE(unsafeCode, notAvailableHandler)                                                                         \
    do                                                                                                                                               \
    {                                                                                                                                                \
        const auto __safeTryCode = [&]()                                                                                                             \
        {                                                                                                                                            \
            try                                                                                                                                      \
            {                                                                                                                                        \
                do                                                                                                                                   \
                {                                                                                                                                    \
                    unsafeCode;                                                                                                                      \
                } while (0);                                                                                                                         \
            }                                                                                                                                        \
            catch ([[maybe_unused]] const dia::PropertyNotAvailableException& e)                                                                     \
            {                                                                                                                                        \
                notAvailableHandler;                                                                                                                 \
            }                                                                                                                                        \
        };                                                                                                                                           \
        PYDIA_SAFE_TRY({ return __safeTryCode(); });                                                                                                 \
    } while (0)


#define XFOR_TRIVIAL_PYDIA_ERRORS(opperation)                                                                                                        \
    opperation(InvalidUsage);                                                                                                                        \
    opperation(NotFound);

#define __DECLARE_TRIVIAL_PYDIA_ERROR(pureName) extern PyObject* PyDia##pureName##Error;


extern PyObject* PyDiaError;
XFOR_TRIVIAL_PYDIA_ERRORS(__DECLARE_TRIVIAL_PYDIA_ERROR);

int pydia_initialize_pydiaerrors(PyObject* module);
