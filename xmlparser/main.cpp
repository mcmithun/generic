#include <QCoreApplication>
#include "xmlparser.h"
#include "resources.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string data;
    data.append(data1);

    XmlParser *xmlParse = new XmlParser;
    auto roots = xmlParse->CreateXMLDoc(data);
    // Just to print and see the nodes
    xmlParse->PrintListOftags(roots);

    // get the query

    // parse and print the query output from roots.
    return a.exec();
}
