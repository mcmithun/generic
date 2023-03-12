#include "xmlparser.h"
#include <iostream>
#include <sstream>
#include <unistd.h>

XmlParser::XmlParser()
{

}

void XmlParser::getSpaceWithEqualsRemoved(std::string &tofmt, const std::string &toFindreplace, const std::string &rWith)
{
    // **** " = " and replace with "=" else in parsing attr, will have issues.

    size_t getpos;
    while(getpos != std::string::npos){
        getpos = tofmt.find(toFindreplace);
        if(getpos != std::string::npos){
            tofmt.replace(getpos, toFindreplace.length(), rWith);
        }
    }
}

void XmlParser::LoadFromXml(std::string &xml)
{
    getSpaceWithEqualsRemoved(xml, " = ", "=");
    getSpaceWithEqualsRemoved(xml, " =", "=");
    getSpaceWithEqualsRemoved(xml, "= ", "=");
    // space before = removed

    // find < and > positions
    // find end of tag </
    // push into list of Tags
    // List is something like
    // [0] tag1->tag2-tag3
    // [1] tag2->tag4
    // [2] tag5
    //<tag1 value="HelloWorld"><tag2 name="Name1"></tag2></tag1><tag3 name="abcdef"></tag3>

    std::size_t ipos = 0, lastTagLength = 0;
    decltype (ipos) start=0, tagNameEnd=0, end=0, initialEndPos=0;
    std::string tagNameStr = "";
    std::string endTagName ="</";
    do{
        int count = 0; //means it is a parent tag
        do{
            start = xml.find("<", ipos);

            Tag* tag = new Tag();
            tag->next = nullptr;

            char tagName[16] = "";
            sscanf(xml.substr(ipos).c_str(), "<%[^ >]", tagName);
            tagNameStr = std::string(tagName);
            endTagName += tagNameStr;
            end = xml.find(endTagName.c_str(), ipos); // end of this tag

            // this is start and end of a tag, checking its validity
            if (start != std::string::npos && end != std::string::npos){
                tag->mTagName.append(tagNameStr);

                // find > for the tagName
                tagNameEnd = xml.find_first_of(">", ipos)+1;

                // extract attribute data - get substring till end of line >; just after attributes.
                std::string ltagLine = xml.substr(ipos, tagNameEnd);
                char attributePart[128];
                sscanf(ltagLine.c_str(), std::string("<"+tagNameStr+" %[^>]>").c_str(), attributePart );

                std::stringstream sAttributePart(attributePart);
                std::string segment = "";
                // Using string stream get the data to attributelist.
                while(std::getline(sAttributePart, segment, ' ')){
                    char attribute[10], value[20];
                    sscanf(segment.c_str(), "%[^=]=\"%[^\"]\"", attribute, value);
                    tag->mAttributeValueList.push_back(std::pair<std::string, std::string>(attribute, value));
                }
            }
            ipos = tagNameEnd; // this will push the pointer for start after, '>'.
            lastTagLength = endTagName.length()+1;
            tagNameStr = "";
            endTagName = "</";
            initialEndPos = initialEndPos > end ? initialEndPos : end;
            if(!count){
                mListOfTags.push_back(new Tag(*tag));
            }
            else {
                auto tagObj = mListOfTags.back();
                while(tagObj->next != nullptr){
                    tagObj = tagObj->next;
                }
                if(tagObj->next == nullptr){ // make sure that this is the final tag in the linked list
                    tagObj->next = new Tag(*tag);
                    tagObj->next->next = nullptr;
                }
            }
            delete tag;
            count++;
        } while((end-ipos) > lastTagLength);
        ipos = initialEndPos+lastTagLength;
        tagNameStr = "";
        endTagName ="</";
    } while (ipos+lastTagLength < xml.length()-1);

    PrintListOftags();
}

void XmlParser::PrintListOftags()
{
    for(auto a: mListOfTags){
        std::cout<<a->ToString()<<std::endl;
    }
}
