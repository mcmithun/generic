#include <QCoreApplication>
#include "xmlparser.h"
#include "resources.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string data;
    data.append(data2);

    XmlParser *xmlParse = new XmlParser;
    auto roots = xmlParse->CreateXMLDoc(data);
    xmlParse->PrintListOftags(roots);
    return a.exec();
}
