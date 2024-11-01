#include <stdint.h>

typedef struct FirstStruct_s
{
    char Member1;
    uint16_t Member2;
} FirstStruct;

typedef struct SecondStruct_s
{
    char Member1[5];
    struct SecondStruct_s* Member2;
} SecondStruct;

int main()
{
    FirstStruct s;
    SecondStruct v;
    s.Member1 = v.Member1[0] = 2;
    return s.Member1;
}
