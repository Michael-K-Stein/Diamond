#include <Windows.h>

typedef struct FirstStruct_s
{
    CHAR Member1;
    USHORT Member2;
} FirstStruct;

typedef struct SecondStruct_s SecondStruct;

struct SecondStruct_s
{
    CHAR Member1[sizeof(ULONG32) + 1];
    SecondStruct* Member2;
};

int main()
{
    FirstStruct s;
    SecondStruct v;
    s.Member1 = v.Member1[0] = 2;
    return s.Member1;
}
