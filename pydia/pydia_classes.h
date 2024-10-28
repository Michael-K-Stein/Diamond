#pragma once

#define XFOR_EACH_PYDIA_CLASS(opperation)                                                                                                            \
    opperation(DataSource);                                                                                                                          \
    opperation(Enum);                                                                                                                                \
    opperation(Data);                                                                                                                                \
    opperation(Array);                                                                                                                               \
    opperation(Pointer);                                                                                                                             \
    opperation(Exe);                                                                                                                                 \
    opperation(Null);                                                                                                                                \
    opperation(Udt);                                                                                                                                 \
    opperation(FunctionType);                                                                                                                        \
    opperation(FunctionArgType);                                                                                                                     \
    opperation(Function);                                                                                                                            \
    opperation(Struct);                                                                                                                              \
    opperation(Union);                                                                                                                               \
    opperation(Class);                                                                                                                               \
    opperation(Interface);