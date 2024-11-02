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

int fakeFunc()
{
    IntHash s1;
    UintHash s2;
    MixedHash s3;
    s1.Member1 = s2.Member1 = s3.Member1 = 0;
    return s1.Member1;
}
