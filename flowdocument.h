#ifndef FLOWDOCUMENT_H
#define FLOWDOCUMENT_H

#include "modinfo.h"
#include "projectmng.h"
#include <iostream>
#define ORG_NAME "GEOSEIS"
#define APP_NAME "flowPad"
#define APP_VERSION "1.01"
#define APP_DATE " 2015.07.3 "
using namespace std;
#define RUNJOB "runflow "
#define SUBMITJOB "runflow "
/**
 * 1.01: 2015.7.3,add command line parameter: flow file name 
 *                 make the title contain flowname ;
 *       2015.7.15: add command line parameter:filename
 *                  projectname linename
 *                  update the runflow commandline script
 *                  parameter: file project line,
 *       2015.8.18: leave the detault to "", match the text
 *       flow.
 * 
 * @author   (7/3/2015)
 */
class flowDocument  
{
public:
    flowDocument();
    ~flowDocument();
    void init();
    modMng m_modMng;
    modInfo m_modIfo;
    QString m_filename;// flow filename;
    QString m_project,m_line; //
    QString m_flowHome,m_logHome,m_dataHome;
    projectMng m_projectMng;

    QString m_inputData,m_outputData;// input output of the flow;
    QString m_flowText;//flow test
    // the procedge of load flow file,we do not set modify flag;
    // othewise if parameter changed we set modify flag;
    bool m_loadFile;

    string toString(QString str);
};
#endif
