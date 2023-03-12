#ifndef XMLPARSER_H
#define XMLPARSER_H
#include <string>
#include <tag.h>

class XmlParser
{
    void getSpaceWithEqualsRemoved(std::string &tofmt, const std::string &toFindreplace, const std::string &rWith);
    std::vector<Tag*> mListOfTags;
public:
    XmlParser();
    void LoadFromXml(std::string &xml);
protected:
    void PrintListOftags();
};

#endif // XMLPARSER_H
