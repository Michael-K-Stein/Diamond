#include "DiaStruct.h"
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
    for (const auto& member : diaStruct.enumerateMembers())
    {
        const auto currentOffset = member.getOffset();
        if (previousMemberOffset != currentOffset)
        {
            if (membersInStringStream > 1)
            {
                os << L"\tunion {\n";
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
                tmpUnionStream << L"\t/* " << " 0x" << std::hex
                               << member.getOffset() << L" * / \t "
                               << L"struct {\n";
            }
            processingBitfield = true;
            tmpUnionStream << L"\t\t/* " << " 0x" << std::hex
                           << member.getBitPosition() << L" * / \t ";
            tmpUnionStream << member << L" : " << std::dec
                           << member.getLength();
            tmpUnionStream << L";\n";
        }
        else
        {
            if (processingBitfield)
            {
                tmpUnionStream << L"\t\t};\n";
            }
            processingBitfield = false;
            tmpUnionStream << L"\t/* " << " 0x" << std::hex
                           << member.getOffset() << L" * / \t ";
            tmpUnionStream << member;
            tmpUnionStream << L";\n";
        }
        ++membersInStringStream;
    }
    os << L"} " << structPureName << L", *P" << structPureName << L";";
    return os;
}
