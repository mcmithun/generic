#ifndef XMLPARSER_H
#define XMLPARSER_H
#include <string>
#include <tag.h>

class XmlParser
{
    std::string getStringLital(const std::string &str);
    std::string getTagName(const std::string &xml, size_t &ipos, const std::string &fmt);
    void getAttributesFilledInTag(const std::string &data, const std::string &fmt, Tag* &tag);
    void getSpaceWithEqualsRemoved(std::string &tofmt, const std::string &toFindreplace, const std::string &rWith);

    void getChildrenFilled(const std::string &xml, Tag *&tag);

    std::vector<Tag*> mRootTags;  // most propably there ll be one tag, else there are multiple parent tags.
public:
    explicit XmlParser();
    std::vector<Tag*> CreateXMLDoc(std::string &xml);
    std::vector<Tag*> GetRootTags() const;
    void PrintListOftags(std::vector<Tag*> rootTags);

protected:
    void getChildPrinted(Tag *&tag) const;
};

#endif // XMLPARSER_H
