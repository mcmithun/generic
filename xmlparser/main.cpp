#include <QCoreApplication>
#include "xmlparser.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //std::string data = "<tag1 v1 = \"123\" v2 = \"43.4\" v3 = \"hello\"></tag1><tag2 v4 = \"v2\" name = \"Tag2\"><tag3 v1 = \"Hello\" v2 = \"World!\"></tag3><tag4 v1 = \"Hello\" v2 = \"Universe!\"></tag4></tag2><tag5><tag7 new_val = \"New\"></tag7></tag5><tag6><tag8 intval= \"34\" floatval = \"9.845\"></tag8></tag6>";

    std::string data = "<tag1 value = \"HelloWorld\"><tag2 name = \"Name1\"></tag2></tag1><tag3 name = \"abcdef\"></tag3>";
    XmlParser *xmlParse = new XmlParser;
    xmlParse->LoadFromXml(data);
    return a.exec();
}
