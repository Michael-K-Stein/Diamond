#include "DiaStruct.h"
#include "DataMember.h"
#include <sstream>
namespace dia
{
DiaSymbolEnumerator Struct::enumerateMembers() const
{
    return enumerate(*this, SymTagData);
}
} // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::Struct& diaStruct)
{
    const auto& structName = diaStruct.getName();
    const auto& structPureName = structName.c_str() + 1;
    os << L"typedef struct " << structName << L" {\n";

    std::wstringstream tmpUnionStream{};

    bool processingBitfield = false;
    LONG previousMemberOffset = -1;
    size_t membersInStringStream = 0;
    size_t indentationLevel = 1;

    for (const dia::DataMember& member : diaStruct.enumerateMembers())
    {
        const auto currentOffset = member.getOffset();
        if (previousMemberOffset != currentOffset)
        {
            if (membersInStringStream > 1)
            {
                for (size_t i = 0; i < indentationLevel; ++i)
                {
                    os << L"\t";
                }
                os << L"union {\n";
                os << tmpUnionStream.str();
                os << L"\t};\n";
            }
            else
            {
                os << tmpUnionStream.str();
            }
            tmpUnionStream = std::wstringstream{}; // New stringstream
            membersInStringStream = 0;
        }
        previousMemberOffset = currentOffset;
        if (member.getLocationType() == LocIsBitField)
        {
            if (!processingBitfield)
            {
                for (size_t i = 0; i < indentationLevel; ++i)
                {
                    tmpUnionStream << L"\t";
                }
                tmpUnionStream << L"/* " << " 0x" << std::hex
                               << member.getOffset() << L" */ \t "
                               << L"struct {\n";
                // Now inside an inner struct
                ++indentationLevel;
            }
            processingBitfield = true;
            for (size_t i = 0; i < indentationLevel; ++i)
            {
                tmpUnionStream << L"\t";
            }
            tmpUnionStream << member << L"\n";
        }
        else
        {
            if (processingBitfield)
            {
                for (size_t i = 0; i < indentationLevel; ++i)
                {
                    tmpUnionStream << L"\t";
                }
                tmpUnionStream << L"};\n";
                // Inner struct finished
                --indentationLevel;
            }
            processingBitfield = false;
            for (size_t i = 0; i < indentationLevel; ++i)
            {
                tmpUnionStream << L"\t";
            }
            tmpUnionStream << member << L"\n";
        }
        ++membersInStringStream;
    }
    os << L"} " << structPureName << L", *P" << structPureName << L";";
    return os;
}
