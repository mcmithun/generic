#include "xmlparser.h"
#include <iostream>
#include <sstream>
#include <unistd.h>

std::string spacer = " ";
size_t MAXSIZE = 65536;

XmlParser::XmlParser()
{

}

std::string XmlParser::getStringLital(const std::string &str)
{
    std::ostringstream ss;
    ss << str;
    return  ss.str();
}

std::string XmlParser::getTagName(const std::string &xml, size_t &ipos, const std::string &fmt="<%[^ >]")
{
    char tagName[16] = "";
    sscanf(xml.substr(ipos).c_str(), fmt.c_str(), tagName);
    return std::string(tagName);
}

void XmlParser::getAttributesFilledInTag(const std::string &tagline, const std::string &fmt, Tag* &tag)
{
    char attributePart[128];
    sscanf(tagline.c_str(), fmt.c_str(), attributePart);

    std::stringstream sAttributePart(attributePart);
    std::string segment = "";
    // Using string stream get the data to attributelist.
    while(std::getline(sAttributePart, segment, ' ')){
        char attribute[10], value[20];
        sscanf(segment.c_str(), "%[^=]=\"%[^\"]\"", attribute, value);
        tag->mAttributeValueList.push_back(std::pair<std::string, std::string>(attribute, value));
    }
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

void XmlParser::getChildrenFilled(const std::string &xml, Tag* &tag)
{
    if(!tag)
        return;
    //std::cout<<"Going to fetch the data for :"<<tag->mTagName<<std::endl;

    //tag->start, tag->end;
    size_t start = tag->mTagPosition->start;
    size_t end = tag->mTagPosition->end;

    // find > for the current tagName
    size_t ipos = xml.find_first_of(">", start)+1;

    while(ipos < end) { // this condition is difficult
        Tag *child = new Tag;
        // check for children
        // find start and end and assign to tag
        child->mTagPosition->start = xml.find("<", ipos);
        std::string tagName = getTagName(xml, ipos);
        child->mTagName = tagName;
        std::string endTagName = "</";
        endTagName.append(tagName);
        endTagName.append(">");
        child->mTagPosition->end = xml.find(endTagName.c_str(), child->mTagPosition->start);

        if(child->mTagPosition->start == std::string::npos || child->mTagPosition->end == std::string::npos){
            std::cout << "Invalid Child for " << child->mTagName<<" , "<< endTagName<< std::endl;
            return;
        }

        std::string ltagLine = xml.substr(child->mTagPosition->start, child->mTagPosition->end);

        getAttributesFilledInTag(ltagLine, std::string("<"+tagName+" %[^>]>"), child);

        // Check the validity that it comes under this tag
        if(child->mTagPosition->end < end){
            // and add to vector under tag
            child->parentTag = tag;
            getChildrenFilled(xml, child);
            tag->mChildTags.push_back(child);
        }
        // Set position updated, with nth level of child tags
        // Jumping from end of tag 1 to start of tag 2 up to n
        // It will skip all other children of current child tags
        ipos = child->mTagPosition->end + endTagName.length();
        //std::cout   <<" tagNameStr:"<< child->mTagName <<"("<<child->mTagPosition->start <<","<<child->mTagPosition->end<< ")"<<std::endl;
    }

    return;
}

std::vector<Tag*> XmlParser::CreateXMLDoc(std::string &xml)
{
    // Correct the formats in data
    getSpaceWithEqualsRemoved(xml, " = ", "=");
    getSpaceWithEqualsRemoved(xml, " =", "=");
    getSpaceWithEqualsRemoved(xml, "= ", "=");

    //first tag, propably root tag, if its end tag is same as xml length
    size_t ipos = 0;
    decltype (ipos) start=ipos, end=0, tagNameEnd;

    while(ipos < xml.length() || end < xml.length()){ // Most propably there ll be only one tag
        ipos = xml.find_first_of("<", ipos);
        if(ipos == std::string::npos || ipos > MAXSIZE){
            std::cout<<"ipos gone out of boundry."<<std::endl;
            break;
        }
        std::string tagNameStr = "";
        std::string endTagNameStr ="</";

        tagNameStr = getTagName(xml, ipos);
        endTagNameStr.append(tagNameStr);
        endTagNameStr.append(">");
        end = xml.find(endTagNameStr.c_str(), ipos); // end of this tag

        auto tag = new Tag();
        tag->mTagPosition->start = ipos;
        tag->mTagPosition->end = end;

        //std::cout<<"["<<tag->mTagPosition->start<<","<<tag->mTagPosition->end<<"]"<<tagNameStr<<" & "<< endTagNameStr <<std::endl;

        // find > for the current tagName
        tagNameEnd = xml.find_first_of(">", ipos)+1;

        // extract attribute data - get substring till end of line >; just after attributes.
        std::string ltagLine = xml.substr(ipos, tagNameEnd);
        auto isAttrAvailable = ltagLine.find("<"+tagNameStr+">", 0);
        if(isAttrAvailable!=0)
            getAttributesFilledInTag(ltagLine, std::string("<"+tagNameStr+" %[^>]>"), tag);
        tag->mTagName = tagNameStr;
        mRootTags.push_back(tag); // need to pushback a new Tag??

        ipos = end + endTagNameStr.length();
        //std::cout<< ipos<<"[" <<start << ","<< end <<"]"<<xml.length()<<" ->"<<tag->mTagName<<std::endl; // Confirm the positions
    }
    // start parsing the root or parent tags, propably a single time loop.
    // Else it means multiple root tags.
    for(auto &a: mRootTags){
        getChildrenFilled(xml, a);
    }
    return mRootTags;
}

std::vector<Tag*> XmlParser::GetRootTags() const
{
    return mRootTags;
}

void XmlParser::getChildPrinted(Tag* &tag) const
{
    spacer.append(" ");
    if(!tag) return;
    for(auto a: tag->mChildTags){
        std::cout<<spacer<<a->ToString()<<std::endl;
        getChildPrinted(a);
    }
}

void XmlParser::PrintListOftags(std::vector<Tag*> rootTags)
{
    for(auto a: rootTags){
        std::cout<<a->ToString()<<std::endl;
        getChildPrinted(a);
    }
}
