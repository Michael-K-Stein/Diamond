#pragma once
#include "DiaData.h"
namespace dia
{
class DataMember : public Data
{
public:
    DataMember() = default;
    using Data::Data;
    DataMember(const Data& other);
    DataMember operator=(const Data& other);
    DataMember(Data&& other);
    DataMember operator=(Data&& other);

    std::wstring getFieldName() const;
    const Symbol getFieldCType() const;

protected:
private:
};
} // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::DataMember& member);
