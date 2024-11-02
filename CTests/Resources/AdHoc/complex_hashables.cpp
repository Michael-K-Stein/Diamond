#include <atlbase.h>
#include <oaidl.h>
#include <stdint.h>

typedef struct IntHash_s
{
    int8_t Member1;
    int16_t Mmber2;
    int32_t Member3;
    int64_t Member4;
} IntHash;

typedef struct UintHash_s
{
    uint8_t Member1;
    uint16_t Mmber2;
    uint32_t Member3;
    uint64_t Member4;

} UintHash;

typedef struct MixedHash_s
{
    uint8_t Member1;
    int16_t Member2;
    char Member3;
    void* Member4;
    float Member5;
    wchar_t Member6;
    unsigned long long Member7;
    signed long long Member8;
} MixedHash;

typedef struct ComObjHash_s
{
    BSTR Member1;
    HRESULT Member2;
    VARIANT Member3;
    CURRENCY Member4;
    DATE Member5;
} ComObjHash;

typedef struct ParentHash_s
{
    ComObjHash Member1;
    MixedHash Member2;
    UintHash Member3;
    IntHash Member4;
    WCHAR Member5;
} ParentHash;

typedef struct RecursiveHash_s RecursiveHash;

struct RecursiveHash_s
{
    ComObjHash Member1;
    MixedHash Member2;
    UintHash Member3;
    IntHash Member4;
    WCHAR Member5;
    RecursiveHash* Next;
};

int fakeFunc()
{
    IntHash s1;
    UintHash s2;
    MixedHash s3;
    ComObjHash s4;
    RecursiveHash s5;
    ParentHash s6;
    s1.Member1 = s2.Member1 = s3.Member1 = s4.Member2 = s5.Member5 = s6.Member5 = 0;
    return s1.Member1;
}
