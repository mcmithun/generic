#ifndef XMLDOCQUERY_H
#define XMLDOCQUERY_H
#include <string>

/*
tag1~value            "value"
tag1.tag2.tag3~name   "value"
tag1.tag2.tag3~final  "value"
tags will be connected with "."
attributes will be appended with "~"
 */

class XmlDocQuery
{
public:
    XmlDocQuery(const std::string &queryStr);
};

#endif // XMLDOCQUERY_H
