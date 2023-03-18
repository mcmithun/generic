#include "xmldocquery.h"

XmlDocQuery::XmlDocQuery(const std::string &queryStr) : mQueryStr(queryStr)
{
    char tag[50], tag0[50], tag3[50], tag4[50], value[50];
    // Extract substrings using sscanf
    sscanf(mQueryStr.c_str(), "%[^.].%[^.].%[^.].%[^~]~%s", tag, tag0, tag3, tag4, value);
}
