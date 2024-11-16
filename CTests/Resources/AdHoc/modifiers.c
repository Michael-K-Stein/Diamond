#define _AMD64_
#include <intrin.h>

static int g_isInitialized = 0;

typedef struct FieldsWithModifiers_s
{
    volatile long volatileField;
    const long constField;
    char padding1;
    _UNALIGNED long unalignedField;
    char padding2;
} FieldsWithModifiers;

int main()
{
    FieldsWithModifiers x;
    x.volatileField  = 0;
    x.unalignedField = _InterlockedIncrement(&x.volatileField);
    return g_isInitialized;
}
