#ifndef TAG_H
#define TAG_H
#include <string>
#include <vector>
#include <algorithm>
#include <memory>


class Tag
{
public:
    Tag();
    Tag(const Tag &obj);
    Tag &operator=(const Tag &obj);
    friend std::ostream& operator<<(std::ostream& stream, std::vector<Tag*> const& p);
    using AttributeList = std::vector<std::pair<std::string, std::string>>;

    struct TagPos{
        size_t start;
        size_t end;
        TagPos():start(0), end(0){}
    };

    std::shared_ptr<TagPos> mTagPosition;                           //used to mark the start and end of tag in the xml
    std::vector<Tag*> mChildTags;                                   // List of Child tags
    Tag* parentTag;                                                 // assign parent tag
    [[deprecated("Deprecated, not to use.")]]bool hasChild;         // Do this tag has child or children
    std::string mTagName;                                           // the name of the tag it could be any
    AttributeList mAttributeValueList; //list of unknown attributes found with values
    std::string ToString();                                         // convert to string, especially to print
};

#endif // TAG_H
