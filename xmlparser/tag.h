#ifndef TAG_H
#define TAG_H
#include <string>
#include <vector>
#include <algorithm>

class Tag
{
public:
    Tag();
    Tag(const Tag &obj);
    Tag &operator=(const Tag &obj);
    Tag* next;              // the pointer to the next tag in the current one
    std::string mTagName;   // the name of the tag it could be any
    std::vector<std::pair<std::string, std::string>> mAttributeValueList; //list of unknown attributes found with values
    std::string ToString(); // convert to string, especially to print
};

#endif // TAG_H
