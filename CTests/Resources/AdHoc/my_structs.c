#include <stdint.h>

typedef struct MyCoolStruct_s
{
    uint8_t MyUint8;
    uint16_t MyUint16;
    uint32_t MyUint32;
    uint64_t MyUint64;

} MyCoolStruct;

typedef struct MyVolatileStruct_s
{
    volatile char Member1;
    volatile uint64_t Member2;
    wchar_t* volatile Member3;
    volatile int Member4[4];

} MyVolatileStruct;

#pragma pack(push, 1)

typedef struct MyPackedStruct_s
{
    char Member1;
    char Member2;
    char Member3;
    uint32_t Member4;
    uint64_t Member5;
    uint16_t Member6;
    int8_t Member7;

} MyPackedStruct;

#pragma pack(pop)

int fakeFunc()
{
    MyCoolStruct s;
    MyVolatileStruct s2;
    MyPackedStruct s3;
    s.MyUint8 = s2.Member1 = s3.Member1 = 0;
    return s.MyUint8;
}
