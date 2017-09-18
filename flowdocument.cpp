#include "flowdocument.h"
 
flowDocument::flowDocument()
{
    init();
}
flowDocument::~flowDocument()
{

}
void  flowDocument::init()
{
    m_loadFile = false;
    m_filename = "";
    m_project = "";
    m_line = "";

    m_flowHome = "";
    m_logHome = "";
    m_dataHome = "";

}
string flowDocument::toString(QString str)
{
    string s;
    s = str.toUtf8().data();
    return s;
}
