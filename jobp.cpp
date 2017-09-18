#include <iostream>

using namespace std;
#include "csHelp.h"
#include "gsysinfo.h"
#include "modinfo.h"
using namespace cseis_system;
void testGsys()
{
    string modname;
    modname = "bin";
   gsysInfo mm;
     cout << "====start test gsysInfo \n";
    ///stardard system headers:
    MPR2("%s",mm.getStdHeader().c_str());

     ///stardard system headers:html
    MPR2("%s",mm.getStdHtmlHeader().c_str());

    /// print all modules of the system:

    stringList l;
    l = mm.modules();
    int i;
 
    for (i = 0 ; i <l.size(); i++) 
    {
        cout << "mod " <<i << " =  " << l[i]<<endl;
    }



}
void testMod()
{
    string modname;
    modname = "bin";
    modMng mm;
     cout << "====start test modMng\n";
    ///stardard system headers:
   // MPR2("%s",mm.getStdHeader().c_str());

     ///stardard system headers:html
   // MPR2("%s",mm.getStdHtmlHeader().c_str());

    /// print all modules of the system:

    stringList l;
    l = mm.modules();
    int i;
 
    for (i = 0 ; i <l.size(); i++) 
    {
        cout << "mod " <<i << " =  " << l[i]<<endl;
    }
//modinfo:
      cout << "====start test modInfo\n";
    modInfo mod;
    i = mod.setModule(modname);
    MPR2("setmod ret = %d\n",i);
    mod.getParam();





}
#include "qtpropertybrowser.h"
#include "qtvariantproperty.h"
void testProperty()
{
    cout << "====start test property\n";
    QtVariantPropertyManager pm;
    QtVariantProperty *p;
    p = pm.addProperty(QVariant::Int,"v1");


}
#include <iostream>
#include <QString>

#include "flowapplication.h"
#include "flowdocument.h"
#include "mainwindow.h"
#include <QDebug>

using namespace std;


int main (int argc, char *argv[])
{
 
   // cout << "start test\n";
   // testProperty();


    //Q_INIT_RESOURCE(jobp);
    string str;
    QString qstr;
    flowApplication app(argc, argv);
    app.setOrganizationName(ORG_NAME);
    app.setApplicationName(APP_NAME);
 
    flowDocument doc;
    app.m_doc =&doc;
    qstr = QString(doc.m_projectMng.getProjectHome());

    if (argc >1) 
    {
        qDebug() << "flow file =" << argv[1];
        doc.m_filename = argv[1];
    }
    if (argc >2) 
    {
        qDebug() << "project = ";argv[2];
        doc.m_project = argv[2];
        doc.m_projectMng.setProject(argv[2]);
        doc.m_flowHome = qstr + SLASH + doc.m_project +SLASH +"flow";
        doc.m_dataHome = qstr + SLASH + doc.m_project +SLASH +"data";
        doc.m_logHome = qstr + SLASH + doc.m_project +SLASH + "log";
    }
    if (argc >3) 
    {
        qDebug() << "line = ";argv[3];
        doc.m_line = argv[3];
        doc.m_projectMng.setLine(argv[3]);
        doc.m_flowHome = qstr + SLASH + doc.m_project +SLASH + argv[3] +SLASH +"flow";
        doc.m_dataHome = qstr + SLASH + doc.m_project +SLASH + argv[3] +SLASH +"data";
        doc.m_logHome = qstr + SLASH + doc.m_project +SLASH + argv[3] +SLASH +"log";
    }
    
    MainWindow mainWin;
 
    app.m_win = &mainWin;
    //qDebug() << "t = " << mainWin.windowTitle();
    //mainWin.setWindowTitle(APP_NAME);
     //qDebug() << "t1 = " << mainWin.windowTitle();
     //qDebug() << "type= " << mainWin.windowFlags();

    mainWin.show();
    return app.exec();
 
}

