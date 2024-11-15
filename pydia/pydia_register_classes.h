#pragma once
#include "dia_types/pydia_datasource.h"
#include "pydia.h"
#include "pydia_classes.h"
#include "pydia_enum.h"
#include "pydia_other_types.h"
#include <functional>
#include <vector>

using PyClassRegistrationFunction = std::function<PyObject*(PyObject* module)>;

static std::vector<PyClassRegistrationFunction>& getPyClassRegistrationFunctions()
{
    static std::vector<PyClassRegistrationFunction> initializers;
    return initializers;
}

static inline void registerPyClassRegistrationFunction(PyClassRegistrationFunction func) { getPyClassRegistrationFunctions().push_back(func); }

#define REGISTER_PYCLASS_REGISTRATION_FUNCTION(fn)                                                                                                   \
    namespace                                                                                                                                        \
    {                                                                                                                                                \
    struct PyClassRegistration__##fn                                                                                                                 \
    {                                                                                                                                                \
        PyClassRegistration__##fn() { registerPyClassRegistrationFunction(fn); }                                                                     \
    };                                                                                                                                               \
    static PyClassRegistration__##fn pyClassRegistration__##fn;                                                                                      \
    }


#define __REGISTER_PYDIA_CLASS(className)                                                                                                            \
    do                                                                                                                                               \
    {                                                                                                                                                \
        if (PyType_Ready(&(PyDia##className##_Type)) < 0)                                                                                            \
        {                                                                                                                                            \
            return NULL;                                                                                                                             \
        }                                                                                                                                            \
        Py_INCREF(&(PyDia##className##_Type));                                                                                                       \
        PyModule_AddObject(module, #className, (PyObject*)&(PyDia##className##_Type));                                                               \
    } while (0)

static PyObject* pydia_registerClasses(PyObject* module)
{
    XFOR_EACH_PYDIA_CLASS(__REGISTER_PYDIA_CLASS)

    for (const auto& registrationFunction : getPyClassRegistrationFunctions())
    {
        if (NULL == registrationFunction(module))
        {
            return NULL;
        }
    }

    return module;
}
