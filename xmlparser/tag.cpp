#include "tag.h"
#include <iostream>

template<typename T, typename Y>
auto operator<<(std::ostream& stream, std::pair<T,Y> const& p) -> std::ostream&
{
    stream << p.first << ' ' << p.second;
    return stream;
}

auto operator<<(std::ostream& stream, std::vector<Tag*> const& p) -> std::ostream&
{
    for(auto a : p)
        stream <<'<' << a->mTagPosition->start <<","<< a->mTagPosition->end << "; " << a->mTagName << '>';
    return stream;
}

Tag::Tag(): mTagPosition(std::make_shared<TagPos>()), mTagName("")
{

}

Tag::Tag(const Tag& obj): mTagPosition(std::make_shared<TagPos>())
                        , mTagName("")
{
    mTagName = obj.mTagName;
    mAttributeValueList = obj.mAttributeValueList;

}
Tag& Tag::operator=(const Tag &obj)
{
    mTagName = "";
    if (this != &obj) {
        mTagName = obj.mTagName;
        mAttributeValueList = obj.mAttributeValueList;
        mChildTags = obj.mChildTags;
    }
    return *this;
}
std::string Tag::ToString()
{
    std::string buffer ="";
    for(auto a : mAttributeValueList){
        buffer.append(" attr("+a.first + " : "+ a.second+");");
    }
    return std::string(""+mTagName+": "+buffer+"\n");
}
