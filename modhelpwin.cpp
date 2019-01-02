#include "modhelpwin.h"
#include "flowapplication.h"
modHelpWin::modHelpWin(QWidget *p):QTextBrowser(p)
{
    init();
}
//=======================
modHelpWin::~modHelpWin()
{

}

//=======================
void modHelpWin::init()
{   
}
void modHelpWin::slotHelp(QString str)
{
    qDebug() << "slot in help = mod = "<< str;
    string s;
    s=DOC->toString(str);

    DOC->m_modIfo.setModule(s);
    s = DOC->m_modIfo.getHelp();

   qDebug() << "help size = " << s.size(); 
                 
    QString qs;
     qs = s.c_str();
    //clear();
    setHtml(qs);
//qDebug() << qs;
   //setText(qs);
       qDebug() << "after set html";
}
 

