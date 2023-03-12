#include "tag.h"
#include <iostream>

template<typename T, typename Y>
auto operator<<(std::ostream& stream, std::pair<T,Y> const& p) -> std::ostream&
{
    stream << p.first << ' ' << p.second;
    return stream;
}

Tag::Tag(): next(nullptr), mTagName("")
{

}
Tag::Tag(const Tag& obj): next(nullptr), mTagName("")
{
    mTagName = obj.mTagName;
    mAttributeValueList = obj.mAttributeValueList;
    if (obj.next == nullptr) {
        next = nullptr;
    } else {
        next = new Tag(*(obj.next));
    }
}
Tag& Tag::operator=(const Tag &obj)
{
    next = nullptr;
    mTagName = "";
    if (this != &obj) {
        mTagName = obj.mTagName;
        mAttributeValueList = obj.mAttributeValueList;
        if (obj.next == nullptr) {
            next = nullptr;
        } else {
            if (next == nullptr) {
                next = new Tag();
            }
            *next = *(obj.next);
        }
    }
    return *this;
}
std::string Tag::ToString()
{
    std::string buffer;
    for(auto a : mAttributeValueList){
        buffer.append("("+a.first + " : "+ a.second+")");
    }
    if(next != nullptr){
        buffer.append(next->ToString());
    }

    return std::string(mTagName+":"+buffer);
}
