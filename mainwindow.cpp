 
#include <QtWidgets>
#include <QMessageBox>
#include "mainwindow.h"
#include "modinfo.h"
#include "listview.h"
#include "flowapplication.h"
#include "flownode.h"
#include "geolib_string_utils.h"
#include "csParamManager.h"
#include "csLogWriter.h"
#include "csParamDescription.h"
#include "csParamDef.h"
#define stringList csVector<std::string>

 
#include <QStandardItemModel>
#include <QModelIndex>
#include <QPixmap>
#include <QVBoxLayout>
#define STARTV 30
static QString flowpath = "./";

using namespace cseis_geolib;
using namespace cseis_system;
 
MainWindow::MainWindow():QMainWindow()
{
    //left dock: up:modules,down:moduleHelp:
//dock
    m_w=m_h = 800;
    
    modDockWidget = new QDockWidget("Module Lists",this );
    QDockWidget *modHelpDockWidget = new QDockWidget("ModuleHelp",this );
 
    addDockWidget(Qt::LeftDockWidgetArea, modDockWidget);
    addDockWidget(Qt::LeftDockWidgetArea, modHelpDockWidget);
//moduleView:
    
    modManager = new  QWidget(this);
    QVBoxLayout *vlayout = new QVBoxLayout(modManager);
    modListView = new modListWin(modManager);
    modFilter = new  QWidget(modManager);
    vlayout->setSpacing(1);
    vlayout->addWidget(modFilter);
    vlayout->addWidget(modListView);

    QHBoxLayout *hlayout = new QHBoxLayout(modFilter);
    labelFilter = new QLabel("Filter:",modFilter) ;
    editFilter = new QLineEdit (modFilter);
    buttonModAll = new QPushButton("All",modFilter);
    hlayout->addWidget(labelFilter);
    hlayout->addWidget(editFilter);
    hlayout->addWidget(buttonModAll);
 
//moduleHelpView:
    modHelpView =new  modHelpWin(this);

    //modDockWidget->setWidget(modListView);
    modDockWidget->setWidget(modManager);
    modHelpDockWidget->setWidget(modHelpView);

 // a split: 
   
    split = new QSplitter();
    setCentralWidget(split);

// left split:  flow view:

    flowView = new flowWin(this); 
    split->addWidget(flowView);
    //flowView->setBackgroundBrush(QPixmap(":/images/flowback.jpg"));
    //flowView->setBackgroundBrush(QPixmap(":/images/flowback1.png"));
   // flowView->setBackgroundBrush(QPixmap(":/images/flowback1.bmp"));
    //flowView->setBackgroundBrush(Qt::blue);
//right dock
    paramDockWidget = new QDockWidget("paramView",this );
    flowTextDockWidget = new QDockWidget("flowLOG",this );
    //flowDefineDockWidget = new QDockWidget("flowDefine",this );
    //QDockWidget *lineDockWidget = new QDockWidget("line",this );

    addDockWidget(Qt::RightDockWidgetArea, paramDockWidget);
    //addDockWidget(Qt::BottomDockWidgetArea, flowTextDockWidget);
    addDockWidget(Qt::RightDockWidgetArea, flowTextDockWidget);
    //addDockWidget(Qt::RightDockWidgetArea, flowDefineDockWidget);
    //addDockWidget(Qt::RightDockWidgetArea, lineDockWidget);


    paramView = new paramWin(this);
    flowTView = new flowTextWin(this);
    defineView = new flowDefine(this);
    //lineView = new lineMenuEdit(this);
    //paramView->setMinimumWidth(100);
   // flowTView->setMinimumWidth(100);

    paramDockWidget->setWidget(paramView);
    flowTextDockWidget->setWidget(flowTView);
//bottom dock
    runDockWidget = new QDockWidget("run result",this );
    addDockWidget(Qt::BottomDockWidgetArea, runDockWidget);
    runView = new runWin(this);
    runDockWidget->setWidget(runView);
    

   // flowDefineDockWidget->setWidget(defineView);
    //lineDockWidget->setWidget(lineView);
    //qDebug() <<"11111";
    setCorner(Qt::BottomRightCorner,Qt::RightDockWidgetArea);
    setCorner(Qt::BottomLeftCorner,Qt::LeftDockWidgetArea);
    //setWindowTitle(QObject::tr("GeoSeis Flow Pad 1.0"));
    
    //initMod();
//connect:
//filter:
//textChanged ( const QString & text )
    connect(editFilter,SIGNAL(textChanged(QString )),modListView,SLOT(slotFilter(QString)));
    connect(buttonModAll,SIGNAL(clicked ()),modListView,SLOT(slotFilterAll()));

//modListView:   
    connect(modListView,SIGNAL(sigSelect(QString)),modHelpView,SLOT(slotHelp(QString)));
    //connect(modListView,SIGNAL(sigSelect(QString)),this,SLOT(slotCreateParam(QString)));
    //double clidk:
    connect(modListView,SIGNAL(sigAddModule(QString)),flowView,SLOT(slotAddNode(QString)));
//flowView:
    //mouse pressed show modhelp:  
    connect(flowView,SIGNAL(sigModHelp(QString)),modHelpView,SLOT(slotHelp(QString)));
     //mouse pressed show param:   
    connect(flowView,SIGNAL(sigShowParam(flowNode *)),this,SLOT(slotShowParam(flowNode*)));
    //double click modlistView cause to create:
    connect(flowView,SIGNAL(sigAddNode(flowNode *)),this,SLOT(slotCreateParam(flowNode*)));
    //shift + <-- to remove 
    connect(flowView,SIGNAL(sigRemoveParam(flowNode *)),this,SLOT(slotRemoveParam(flowNode*)));
//run win:sigDBClick(s)
//   
    connect(runView,SIGNAL(sigSelect(QString)),modHelpView,SLOT(slotHelp(QString)));
    connect(runView,SIGNAL(sigDBClick(QString)),this,SLOT(slotShowLog(QString)));

    //setWindowTitle("flowPad 1.0");
 
    createActions();
    
    createMenus();
    createToolBars();
    createStatusBar();
    setWindowModified(false);//init
    flowMode();
    if ( theApp->m_doc->m_filename != "") 
    {
        loadFile(theApp->m_doc->m_filename);
    }
    else
    {
        readSettings();
        if ( theApp->m_doc->m_filename != "") 
            loadFile(theApp->m_doc->m_filename);

    }
    setTitle();
    return; 
   
    //connect(textEdit->document(), SIGNAL(contentsChanged()),
    //        this, SLOT(documentWasModified()));

    setCurrentFile("");
    setUnifiedTitleAndToolBarOnMac(true);
}
void MainWindow::setTitle()
{
  
    QString str;
    str = "";
    str = str + APP_NAME + "-"+APP_VERSION +"-"+ __DATE__+"-";
    str = str + theApp->m_doc->m_filename + ":" + theApp->m_doc->m_project +":" + theApp->m_doc->m_line;

    setWindowTitle(str);
    qDebug() << "title = " << str;

}
void MainWindow::logMode()
{
     
     
    int w,mw;
    mw = 4;
    w = (m_w-m_w/mw)/2;
    paramDockWidget->setMinimumWidth(w);
    modDockWidget->setMinimumWidth(w);
    //paramDockWidget->setMaximumHeight(h);
    tabifyDockWidget(paramDockWidget,flowTextDockWidget);
 
}
 
void MainWindow::flowMode()
{
     
    int w,mw;
    //mw = 4;
    mw =3 ;// middle occupy 1/3;
    w = (m_w-m_w/mw)/2;
    paramDockWidget->setMinimumWidth(w);
    modDockWidget->setMinimumWidth(w);
    tabifyDockWidget(flowTextDockWidget,paramDockWidget);
     
}
void MainWindow::slotShowLog(QString log)
{
    QFile file(log);
    if (!file.open(QFile::ReadOnly | QFile::Text)) 
    {
        QMessageBox::warning(this, tr(" "),
                         tr("Cannot read file %1:\n%2.")
                         .arg(log)
                         .arg(file.errorString()));
        return;
    }
    QString str;
    str = file.readAll();
    flowTView->setText(str);
    file.close();

    logMode();
}
void MainWindow::slotTextFlow()
{
    slotParam2Str();
    flowTView->setText(theApp->m_doc->m_flowText);
    logMode();
}
void MainWindow::slotRemoveParam(flowNode *node)
{
    int num,i;
    paramWin *win;
    QString name ;
    name = node->getQName();
    num = m_listParam.size();
    for (i =0; i<num; i++)
    {
        win = m_listParam[i];
        if (win !=NULL) 
        {
            if (win->m_name == name && win->m_node == node) 
            {
                m_listParam.removeAll(win);
                delete win;
                break;
            }
        }

    }
 
}
QMap<QString,QStringList> MainWindow::getModParaDV(QString mname)
{
    QMap<QString,QStringList> mapModP;
    string s;
    s = mname.toUtf8().data();
    DOC->m_modIfo.setModule(s);
    csParamDef *pDef = DOC->m_modIfo.getPDef();
    Q_CHECK_PTR(pDef);

    csParamDef *pdef;
    QString name,vname,pdesc,vdesc,disName,modname,str;
    QStringList strList;
    QVariant vv;
    int nOptions;
    pdef = pDef;

    csParamDescription const* const module = pdef->module();
    if (module == NULL)
    {
        str = QString(" No this module: ") + name;
        QMessageBox::warning(this,"error",str);
        mapModP;
    }

    modname = module->name();
    int nParams = pdef->numParameters();
    qDebug() <<"number of P ="<< nParams;

    csParamDescription const* valueDescriptor;
    csParamDescription const* optionDescriptor;
// loop Param:
    for( int ip = 0; ip < nParams; ip++ ) 
    {
        name = pdef-> param(ip)->name();
        pdesc = pdef-> param(ip)->desc();
        int nValues = pdef->numValues(ip);
        strList.clear();
        //loop of values:
        for( int iv = 0; iv < nValues; iv++ ) 
        {
            vname = "";
            valueDescriptor = pdef->value(ip,iv);
            if( strlen(valueDescriptor->name()) != 0 ) 
                vname = valueDescriptor->name();            
#if 1
            qDebug() << "value name = " <<   valueDescriptor->name();
            qDebug() << "value type = " <<   valueDescriptor->type();
            qDebug() << "value desc = " <<   valueDescriptor->desc();
            qDebug() << "value descE = " <<   valueDescriptor->descExtra(); 
#endif 
            strList << vname;
        }//end of value;
        mapModP[name] = strList;   
    }  // end of param  
    return mapModP;
}
void MainWindow::slotCreateParam(flowNode *node)
{
       //qDebug() << "slot in paramWin,mod= " << s;        
    string s;
    QString name;
    s=node->getName();
    name = s.c_str();
    mapModPV[name] = getModParaDV(name);
    qDebug()<<"moddv = "<<name<<mapModPV[name];

    DOC->m_modIfo.setModule(s);
    csParamDef *pDef = DOC->m_modIfo.getPDef();
    //delete mi;
    Q_CHECK_PTR(pDef);
    paramView = new  paramWin(this);
    paramView->m_name = name;
    paramView->m_node = node;
   // flowTView->setMinimumSize(150,500);
    paramView->setWindowTitle( name);
    paramDockWidget->setWindowTitle("Parm:" + name);

    paramDockWidget->setWidget(paramView);
    paramView->createProperty(pDef);
    m_listParam.append(paramView);
 
}
void MainWindow::slotShowParam(flowNode *node)
{ 
    int num,i;
    QString name; 
    paramWin *win;
    num = m_listParam.size();
    name = node->getQName();
    flowMode();
    //qDebug() << " show slot enter =" <<num;
    for (i =0; i<num; i++)
    {
        win = m_listParam[i];
        //qDebug() << win << win->m_name <<name <<node << win->m_node;
        if (win !=NULL) 
        {
            if (win->m_name == name && win->m_node == node ) 
            {
                paramView =win;
                paramDockWidget->setWindowTitle("Parm:" + name);
                paramDockWidget->setWidget(paramView);
                //qDebug() << " show slot";
                paramView->show();
                break;
            }
        }
    } 

}
void MainWindow::initMod()
{
    int sz,i;
    bool b;
    string s;
    
  
}

void MainWindow::closeEvent(QCloseEvent *event)

{
 
    //if (maybeSave()) {
        writeSettings();
        event->accept();
    //} else {
    //    event->ignore();
    //}
}
 
void MainWindow::newFile()
{
    if (maybeSave()) {
        flowView->clear();
        setWindowModified(false);//new
        setCurrentFile("");
    }
}

void MainWindow::open()
{
    int i;
    QString strt,strd,strf,str;
    strf = "*.flow";
    strt = "Open flow file";
    strd = theApp->m_doc->m_flowHome;
    if (strd.isEmpty()) 
    {
        strd = flowpath;
    }
    //qDebug() << "flowpath=" <<flowpath;
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this,strt,strd,strf);
        if (!fileName.isEmpty())
            loadFile(fileName);

        QFileInfo fi(fileName);
        i = fileName.lastIndexOf(SLASH);
        str = fileName.left(i+1);
        flowpath = str;// remember the last set
        qDebug() << "flowpath=" <<flowpath << str;
    }
    setTitle();
}

bool MainWindow::save()

{
    

    //return true;
    if (theApp->m_doc->m_filename.isEmpty()) 
    {
        return saveAs();
    } else 
    {
        return saveFile(theApp->m_doc->m_filename);
    }
}

bool MainWindow::saveAs()
{
    QString strt,strd,strf,str;
    strf = "*.flow";
    strt = "save flow file";
    strd = theApp->m_doc->m_flowHome;
    //qDebug() << "flowHome = " << strd;
    if (strd.isEmpty()) 
    {
        strd = flowpath;
    }

    QString fileName = QFileDialog::getSaveFileName(this,strt,strd,strf);
    if (fileName.isEmpty())
        return false;
    QFileInfo fi(fileName);

    QString ext = "flow";
    if (fi.suffix() != ext) 
    {
        fileName = fileName +"."+ext;
    }
    return saveFile(fileName);
}

void MainWindow::slotSubmit()
{
    slotRun();
}

void MainWindow::slotRun()
{
    QProcess *job;
    run *runflow;
    QString cmd,name,logname,fullname;
    if (!maybeSave()) return;

    //cmd = RUNJOB  + theApp->m_doc->m_filename + " " + theApp->m_doc->m_project +" " + theApp->m_doc->m_line;
    cmd = QString(RUNJOB)  + "\"" +theApp->m_doc->m_filename + "\"" + " " + theApp->m_doc->m_project +" " + theApp->m_doc->m_line;

    //cmd = editFilter->text();
    qDebug() << "runflow cmd = "<< cmd;
    name = QFileInfo(theApp->m_doc->m_filename).baseName();
    fullname = theApp->m_doc->m_filename;

    if (theApp->m_doc->m_project.isEmpty()) 
    {
        //same dir
        logname = QFileInfo(theApp->m_doc->m_filename).absolutePath() + SLASH + name + ".log"; 
    }
    else
    {
        logname = theApp->m_doc->m_logHome + SLASH + name + ".log";

    }
    
    runflow = new run();

    job = new QProcess();
    runflow->name = name;
    runflow->logname = logname;
    runflow->fullname = fullname;
    runflow->inputData = theApp->m_doc->m_inputData;
    runflow->outputData = theApp->m_doc->m_outputData;
    runflow->pro = job;

    m_listRun.insert(0,runflow);

    //job->setObjectName(theApp->m_doc->m_filename);

    qDebug() << "workdir = "<< job->workingDirectory();
    qDebug() << "QProcess = "<< job;
    QDateTime tm;
    tm = tm.currentDateTime();
    QStringList lists;
    lists << runflow->name << tm.toString("hh:mm:ss") << "  " << "Running" ;
    runView->addRow(lists);
    runView->updateRowTip(job,theApp->m_doc->m_filename);

    job->start(cmd);
    connect(job,SIGNAL(error( QProcess::ProcessError)),this,SLOT(slotJobErr( QProcess::ProcessError)));
    //connect(job,SIGNAL(started()),this,SLOT(about()));
    //connect(job,SIGNAL(stateChanged(QProcess::ProcessState)),this,SLOT(about()));
    connect(job,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(slotJobOK(int,QProcess::ExitStatus)));
    qDebug() << "exit from runflow";


}
void MainWindow::slotJobErr(  QProcess::ProcessError ii)
{
    int ee,num;
    QString st,stm;
    st = "ERR";
    ee =ii;
    qDebug() << "================== ";
    qDebug() << "JObERR code = " << ii << ee;
    //num = m_listRun.size();
    //qDebug() <<"cmd = " <<  m_listJob.at(num-1)->objectName();
 
    QProcess *p;

    p = (QProcess *)sender();
    qDebug() <<"err = " <<  p->readAllStandardError();
    qDebug() <<"out = " <<  p->readAllStandardOutput();


    QDateTime tm;
    tm = tm.currentDateTime();
    stm = tm.toString("hh:mm:ss");
    runView->updateRow(p,stm,st);
}
void MainWindow::slotJobOK( int ie , QProcess::ExitStatus ii)
{
    int ee,num;
    ee =ii;
    qDebug() << "================== ";
    qDebug() << "JOBOK sender = " << sender();
    qDebug() << "exit code = " << ii << ee;

    //num = m_listJob.size();
    //qDebug() <<"cmd = " <<  m_listJob.at(num-1)->objectName();
    //qDebug() <<"err = " <<  m_listJob.at(num-1)->readAllStandardError();
    //qDebug() <<"out = " <<  m_listJob.at(num-1)->readAllStandardOutput();

    QProcess *p;
    QString st,stm;
    st = "OK";

    p = (QProcess *)sender();
    qDebug() <<"err = " <<  p->readAllStandardError();
    qDebug() <<"out = " <<  p->readAllStandardOutput();
    QDateTime tm;
    tm = tm.currentDateTime();
    stm = tm.toString("hh:mm:ss");
    runView->updateRow(p,stm,st);

}
void MainWindow::slotDel()
{
    int i,id;
    QString str1,str;
    qDebug("del slot");
    str1 = "Question";
    i = flowView->findSelectedIndex();
    if (i <0)
    {
        str = "No selected Node";
        QMessageBox::warning(this,str1,str);
        return;
    }

    str = "Remove The node:" + str.setNum(i)+ ":"+flowView->getSelected()->getQName();
    id = QMessageBox::question(this,str1,str);
    if (id ==QMessageBox::Yes) 
    {
        //qDebug() << "yes=",id;
        flowView->removeNode(i);
    }
    else
    {
         //qDebug() << "NO=",id;
    }
  
}
void MainWindow::slotUp()
{
    int i;
    QString str1,str;
    qDebug("Up slot");
    str1 = "warning";
    i = flowView->findSelectedIndex();
    if (i <0)
    {
        str = "No selected Node";
        QMessageBox::warning(this,str1,str);
        return;
    }
    else if (i ==0) 
    {
        str = "selected Node is at Top";
        QMessageBox::warning(this,str1,str);
        return;
    }

    flowView->moveNode(i, i-1);

}
void MainWindow::slotDown()
{
    int i,num;
    QString str1,str;
    qDebug("down slot");
    str1 = "warning";
    num = flowView->numNodes();
    i = flowView->findSelectedIndex();
    if (i <0)
    {
        str = "No selected Node";
        QMessageBox::warning(this,str1,str);
        return;
    }
    else if (i == num-1) 
    {
        str = "selected Node is at Bottom";
        QMessageBox::warning(this,str1,str);
        return;
    }

    flowView->moveNode(i, i+1);


}
void MainWindow::slotConstant()
{
    int i;

    i = defineView->exec();

}
void MainWindow::about()
//! [13] //! [14]
{
    QString title,str,str1;
    title = ORG_NAME;
    str1 = __DATE__;
    str = QString("   App name : ") +QString(APP_NAME) + "\n" +
          QString("App version : ") +QString(APP_VERSION) + "\n" +
          QString("       Date : ") +str1;
   QMessageBox::about(this, title,str);
}
//! [14]

//! [15]
void MainWindow::documentWasModified()
//! [15] //! [16]
{
    //setWindowModified(textEdit->document()->isModified());
}
//! [16]

//! [17]
void MainWindow::createActions()
{
    //open
    newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));
 
    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
 

    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    textFlowAct = new QAction(QIcon(":/images/textflow.png"),tr("&TextFlow"), this);
    //saveAsAct->setShortcuts(QKeySequence::SaveAs);
    textFlowAct->setStatusTip(tr("Convert to text flow"));
    connect(textFlowAct, SIGNAL(triggered()), this, SLOT(slotTextFlow()));

//qDebug() << "file action";
    //closeAct = new QAction(QIcon(":/images/close.png"), tr("&Close"), this);
    //closeAct->setShortcuts(QKeySequence::Close);
    //closeAct->setStatusTip(tr("close the flow"));
    //connect(closeAct, SIGNAL(triggered()), this, SLOT(slotClose()));
//qDebug() << "close action";
    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
 
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    //qDebug() << "exit action";
    //===============================
//run 
    constantAct = new QAction(QIcon(":/images/constant.png"), tr("&Constant"), this);
    //constantAct->setShortcuts(QKeySequence::Cut);
    constantAct->setStatusTip(tr("constant Select"));
    connect(constantAct, SIGNAL(triggered()), this, SLOT(slotConstant()));

    runAct = new QAction(QIcon(":/images/run.png"), tr("&Run"), this);
    //runAct->setShortcuts(QKeySequence::Cut);
    runAct->setStatusTip(tr("Run"));
    connect(runAct, SIGNAL(triggered()), this, SLOT(slotRun()));


    submitAct = new QAction(QIcon(":/images/submit.png"), tr("&Submit"), this);
    //runAct->setShortcuts(QKeySequence::Cut);
    submitAct->setStatusTip(tr("Submit"));
    connect(submitAct, SIGNAL(triggered()), this, SLOT(slotSubmit()));
//edit:
    upAct = new QAction(QIcon(":/images/up.png"), tr("&Up"), this);
    //constantAct->setShortcuts(QKeySequence::Cut);
    upAct->setStatusTip(tr("Move Up"));
    connect(upAct, SIGNAL(triggered()), this, SLOT(slotUp()));
    //qDebug() << "up action";

    downAct = new QAction(QIcon(":/images/down.png"), tr("&Down"), this);
    //constantAct->setShortcuts(QKeySequence::Cut);
    downAct->setStatusTip(tr("Move Down"));
    connect(downAct, SIGNAL(triggered()), this, SLOT(slotDown()));
//qDebug() << "down action";
    delAct = new QAction(QIcon(":/images/del.png"), tr("&Del"), this);
    //constantAct->setShortcuts(QKeySequence::Cut);
    delAct->setStatusTip(tr("remove"));
    connect(delAct, SIGNAL(triggered()), this, SLOT(slotDel()));
//qDebug() << "del action";
//help

    helpAct = new QAction(QIcon(":/images/help.png"), tr("&Help"), this);
    helpAct->setStatusTip(tr("User manual of flowPad"));
    connect(helpAct, SIGNAL(triggered()), this, SLOT(slotHelp()));
    //qDebug() << "create action OK";


//about

    aboutAct = new QAction(QIcon(":/images/about.png"), tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    //qDebug() << "create action OK";
    return;
   
}
 void MainWindow::createMenus()
{
   // open
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(textFlowAct);
    //fileMenu->addAction(closeAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
  
//-----------------------------------------
    //run
    runMenu = menuBar()->addMenu(tr("&Run"));
    runMenu->addAction(runAct);
    runMenu->addAction(submitAct);
    //edit
    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(upAct);
    editMenu->addAction(downAct);
    editMenu->addAction(delAct);
    
    //constant
    constantMenu = menuBar()->addMenu(tr("&Constant"));
    constantMenu->addAction(constantAct);
   
 
//help
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(helpAct);
    helpMenu->addAction(aboutAct);
    qDebug() << "create menu OK";
    return;
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(textFlowAct);
    //run
    runToolBar = addToolBar(tr("Run"));
    runToolBar->addAction(runAct);
    runToolBar->addAction(submitAct);
    runToolBar->addAction(constantAct);
//-----------------------------------------
    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(upAct);
    editToolBar->addAction(downAct);
    editToolBar->addAction(delAct);
    helpToolBar = addToolBar(tr("Help"));
    helpToolBar->addAction(helpAct);
    qDebug() << "create toolbar OK";
    return;
}

void MainWindow::createStatusBar()

{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readSettings()
{
    QSettings settings(ORG_NAME, APP_NAME);
    QString str = settings.value("flow").toString();
    theApp->m_doc->m_filename =str; 
 
}
void MainWindow::writeSettings()
{
    QString str;
    QSettings settings(ORG_NAME,APP_NAME);
    str = QString("\"") + theApp->m_doc->m_filename + QString("\"");
    settings.setValue("flow", theApp->m_doc->m_filename);
 
}

bool MainWindow::maybeSave()
{ 
    if ( isWindowModified ()) 
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("You will New your flow"),
                     tr("The current flow has been modified.\n"
                        "Do you want to save your changes?"),
                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    } 
    return true;
}
void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    flowView->clear();

 
    FILE *f_flow;
    char fname[256];
    char line[1024];

    //#define pmList csVector<PMList>
    csVector<std::string> tokenList;
    csVector< stringList > defineList;
    csVector< csUserParam * > paramList;
    //map<string,csVector<csUserParam *> > mapParam;




    string   moduleName,lastName,sidx;
    QString str;
    int icMod = 0;
    theApp->m_doc->m_filename = fileName;
    theApp->m_doc->m_loadFile = true;// avoid to modify:
    //strcpy(fname,"e:\\openseaseis_v2.03\\example_flows\\t01_create_pseudo_data.flow");
    strcpy(fname,fileName.toUtf8().data());
    f_flow = fopen(fname,"r");
    if (!f_flow)
    {
        qDebug() << "open flow error\n";
    }
    qDebug() << "openfloe ok\n";
    int counterLines;
    counterLines = 0;

    while( fgets( line, MAX_LINE_LENGTH, f_flow ) != NULL ) 
    {
        tokenList.clear();
        counterLines++;
        int counterChars = strlen(line)-1;
        while( counterChars >= 0 && (line[counterChars] == NEW_LINE || line[counterChars] == CARRIAGE_RETURN) ) 
        {
            line[counterChars] = '\0';
            counterChars -= 1;
        }
        char c;
        if( ! firstNonBlankChar( line, c ) || c ==  '#' ) 
        {   // This line is empty or a comment -> Skip to next line
            //myLog->line( "%s", line );
            qDebug() << "comment = " << line << endl;
            continue;
        }
       //std::string tmpStr = replaceUserConstants( line, userConstantList );
        std::string tmpStr = line;
        //myLog->line( "%s", tmpStr.c_str() );  // Print input line to log file
        tokenize( tmpStr.c_str(), tokenList );
        if( tokenList.size() == 0 ) continue;   // Comment or empty line (this case should have been caught already)
    // DEFINE & TABLE statements have already been processed -> Skip to next line
        //if( c == csUserConstant::LETTER_DEFINE && (!tokenList.at(0).compare(csUserConstant::defineWord()) || !tokenList.at(0).compare(csUserConstant::tableWord())) )
        if( c == '&' && (!tokenList.at(0).compare("&define") || !tokenList.at(0).compare("&table")) )
        {
            qDebug() << "define = " << line <<endl;
            // add to defineList
            defineList.insertEnd(tokenList);
            continue;
        }
        if( tokenList.at(0)[0] == LETTER_MODULE ) 
        {  // This token is a module because it starts with the 'module letter'
            
            lastName = moduleName;
            moduleName = tokenList.at(0).substr(1,tokenList.at(0).length()-1);   // substr() in order to skip leading 'module letter'

      //--------------- CREATE MODULE ---------------------
            qDebug() <<" modname = " <<  moduleName.c_str() << endl;
            str = moduleName.c_str();
            // add node:
            flowView->slotAddNode(str);
            if (icMod >0)
            {
                //end of the parameters of the last module;
                //mapParam(lastName.c_str()) =  paramList;
                str.setNum(icMod-1);
                sidx =str.toUtf8().data();

                mapParam.insert( make_pair(sidx,paramList ));
            }
            
            paramList.clear();
            icMod ++ ;
        }
        else 
        {  // This line contains user parameters. Save to user parameter list of the current module
            csUserParam *userParam = new csUserParam( tokenList );
           // userParamList[moduleIndexCurr]->push_back( userParam );
            qDebug() << "param = " <<userParam->getName().c_str() <<endl;
            qDebug() << "v0 = " <<userParam->getValue(0).c_str();
            //cout << "param 1= " << tokenList <<endl;
            paramList.insertEnd(userParam);
        }
    }

    fclose( f_flow );  // DO NOT CLOSE FILE
   // last module:
    str.setNum(icMod-1);
    sidx =str.toUtf8().data();
    mapParam.insert( make_pair(sidx  ,paramList ));
    
    setParamData();
    theApp->m_doc->m_loadFile = false;
// set define:
#if 1
    int i,num;
    QString qs1,qs2,qs3;
    stringList slist;
    num = defineList.size();
    for (i = 0; i<num; i ++) 
    {
        slist =  defineList.at(i);
        qs1 = slist.at(0).c_str();
        qs2 = slist.at(1).c_str();
        qs3 = slist.at(2).c_str();
        defineView->setText(i,qs1,qs2,qs3);
    }

  //  defineView->getText(0,qs1,qs2,qs3);
    qDebug() << "get text = "<< qs1<<qs2<<qs3;
#endif
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}
paramWin * MainWindow::findParamView(int idx)
{
    int num,i,ret;
    num = m_listParam.size();
    ret = -1;
    for (i = 0; i < num; i++)
    {
        if (m_listParam.at(i)->m_node->m_id == idx) 
        {
            ret = i;
            break;

        }
    }
    if (ret !=-1) return m_listParam.at(ret);
    else return NULL; 

}

bool MainWindow::saveFile(const QString &fileName)
{
    theApp->m_doc->m_filename = fileName;
    slotParam2Str();

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Flow Save"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    //qDebug()<< "1111="<<theApp->m_doc->m_flowText;
    out <<  theApp->m_doc->m_flowText;
    file.close();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    qDebug() << "saved file = " << fileName << theApp->m_doc->m_flowText.length();
    statusBar()->showMessage(tr( " File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
     
    //textEdit->document()->setModified(false);
    
    setWindowModified(false);

    QString shownName = fileName;
    if (fileName.isEmpty())
        shownName = "untitled.flow";

    theApp->m_doc->m_filename = fileName;
    setWindowFilePath(shownName);
    setTitle();
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::slotParam2Str1()
{
    int i,num,pnum,vnum;
    QString str,param,mod,flow,val,defstr,pname,mname;
    QStringList vlist;
    str = param = mod=flow = "";
    // def:
    i = 0;
    QString q1,q2,q3;
    defstr = "";
    while (i<MAX_DEFINES)
    {
        defineView->getText(i,q1,q2,q3);
        qDebug()<< "q2 = " <<q2;
        i++;
        if (q2.length() == 0) break;
        defstr += q1 + " " + q2 +" " + q3 + "\n";
    }
    qDebug()<< "defstr = " <<defstr;

    flow = defstr;
    paramWin *paramw; 
    QList<QtProperty *> listp,listsp;
    QtProperty *pt,*spt;
    //num: number of modules in flow
    num = m_listParam.size();
    theApp->m_doc->m_inputData = "";
    theApp->m_doc->m_outputData = "";
    // modules loop:
    for (i = 0; i <num ; i++)
    {
         
        //paramw = m_listParam[i];
        paramw = findParamView(i);
        if (paramw == NULL) break;
        listp = paramw->properties ();
        pnum = listp.size();
        qDebug() << "model index =" << i << " modname ="<< paramw->m_name;
        //pnum :number of params in th module;
        //2015.6.24: modname must be uppercase
        mod = "$"+paramw->m_name.toUpper() + "\n";
        mname = paramw->m_name;
        
        for (int pi = 0; pi < pnum ;pi++) 
        {
            pt = listp[pi];
            if (pt ==NULL) break; 
            qDebug() << "param index =" << pi << " paramname =" << pt->propertyName();
            qDebug() << "value 0 = " << pt->valueText();
            val = "";
            pname = pt->propertyName();
            if (pt->propertyName() == "filename") 
            {
                if (i == 0) // first module
                {
                    theApp->m_doc->m_inputData = pt->valueText();
                }
                 if (i == num -1) //last module
                {
                    theApp->m_doc->m_outputData = pt->valueText();
                }
            }



            if (pt->valueText().length() != 0)  val = pt->valueText();

            //vlist  = getParamDV(mnane,pname)

            param = " " + pname; 

            if (param.size() < STARTV -1)  
                param.insert(STARTV, val); 
            else
                param.append(" " + val);


            listsp = pt->subProperties();
            //vnum :number of values in the parameter:
            vnum = listsp.size();
            qDebug() << "num of vnum = "<<vnum;
            for (int vi = 0; vi < vnum; vi ++) 
            {
                spt = listsp[vi];
                if (spt == NULL) break;
                qDebug() << "value " << vi << " =" << spt->valueText();

                if (spt->valueText().length() != 0)  val += spt->valueText();

                if (spt->valueText().length() !=0)  
                    param.append(" " + spt->valueText()); 
            }
            if (val.length()>0) 
            {
                param.append("\n"); 
                mod += param;
            }
            
        }
        //pnum = param->
        flow += mod;
    }
    //flowTView->setText(flow);
    theApp->m_doc->m_flowText = flow;
    return ;
}
 
void MainWindow::slotParam2Str()
{
    int i,num,pnum,vnum;
    QString str,param,mod,flow,val,defstr,pname,mname;
    QStringList vlist,slist;
    str = param = mod=flow = "";
    // def:
    i = 0;
    QString q1,q2,q3;
    defstr = "";
    while (i<MAX_DEFINES)
    {
        defineView->getText(i,q1,q2,q3);
        qDebug()<< "q2 = " <<q2;
        i++;
        if (q2.length() == 0) break;
        defstr += q1 + " " + q2 +" " + q3 + "\n";
    }
    qDebug()<< "defstr = " <<defstr;

    flow = defstr;
    paramWin *paramw; 
    QList<QtProperty *> listp,listsp;
    QtProperty *pt,*spt;
    //num: number of modules in flow
    num = m_listParam.size();
    theApp->m_doc->m_inputData = "";
    theApp->m_doc->m_outputData = "";
    // modules loop:
    
    for (i = 0; i <num ; i++)
    {
         
        //paramw = m_listParam[i];
        paramw = findParamView(i);
        if (paramw == NULL) break;
        listp = paramw->properties ();
        pnum = listp.size();
        qDebug() << "model index =" << i << " modname ="<< paramw->m_name;
        //pnum :number of params in th module;
        //2015.6.24: modname must be uppercase
        mod = "$"+paramw->m_name.toUpper() + "\n";
        mname = paramw->m_name;
       
        
        for (int pi = 0; pi < pnum ;pi++) 
        {
            pt = listp[pi];
            if (pt ==NULL) break; 
            qDebug() << "param index =" << pi << " paramname =" << pt->propertyName();
            qDebug() << "value 0 = " << pt->valueText();
            val = "";
            pname = pt->propertyName();
            if (pt->propertyName() == "filename") 
            {
                if (i == 0) // first module
                {
                    theApp->m_doc->m_inputData = pt->valueText();
                }
                 if (i == num -1) //last module
                {
                    theApp->m_doc->m_outputData = pt->valueText();
                }
            }

            vlist.clear();

            if (pt->valueText().length() != 0)  val = pt->valueText();

            //vlist  = getParamDV(mnane,pname)
            vlist << val;

#if 0
             param = " " + pname; 

             if (param.size() < STARTV -1)  
                param.insert(STARTV, val); 
            else
                param.append(" " + val);
#endif

            listsp = pt->subProperties();
            //vnum :number of values in the parameter:
            vnum = listsp.size();
            qDebug() << "num of vnum = "<<vnum;
            for (int vi = 0; vi < vnum; vi ++) 
            {
                spt = listsp[vi];
                if (spt == NULL) break;
                qDebug() << "value " << vi << " =" << spt->valueText();
                val = spt->valueText();
                vlist << val;
#if 0
                if (spt->valueText().length() != 0)  val += spt->valueText();

                if (spt->valueText().length() !=0)  
                    param.append(" " + spt->valueText()); 
#endif
            }// endof v
            #if 0
            if (val.length()>0) 
            {
                param.append("\n"); 
                mod += param;
            }
            #endif
            slist = mapModPV[mname][pname];
            if (slist == vlist) 
            {
                qDebug()<<"omit param = "<<mname<<pname<<vlist;
                continue;
            }

            param = " " + pname; 
            val = vlist.join(" ");


            if (param.size() < STARTV -1)  
                param.insert(STARTV, val); 
            else
                param.append(" " + val);

            qDebug()<< param;
            mod+= param + "\n";

        }
        //pnum = param->
        flow += mod;
    }
    //flowTView->setText(flow);
    theApp->m_doc->m_flowText = flow;
    return ;
}
void MainWindow::setParamData()
{
  
    int i,num,pnum,vnum,nOptions,io,idx,itype;
    int numLine;
    QString str,param,mod,flow,vname;
    QStringList strList;
    csParamDef *pdef;
    csParamDescription const* valueDescriptor;
    csParamDescription const* optionDescriptor;
    //char *ch;
    string sidx,pname;
    csVector< csUserParam * > paramList;
    csVector< string > vlist,vlist1;
    //FILE *flog;
    //flog = fopen("//tmp//testflow.log","w");
    csLogWriter log;


    str = param = mod=flow = "";
    
    paramWin *paramw;
    QList<QtProperty *> listp,listsp;
    QtProperty *pt,*spt;
    QtVariantProperty *vpt;
    csParamManager *mng;
    //num: number of modules in flow
    num = m_listParam.size();
    for (i = 0; i <num ; i++)
    {
            
        //paramw = m_listParam[i];
        paramw = findParamView(i);  
        if (paramw == NULL) break;
        pdef = paramw->m_node->m_pdf;

        str.setNum(i);
        sidx =str.toUtf8().data();
        paramList =  mapParam[sidx]; 
        mng = new csParamManager(&paramList,&log);


        listp = paramw->properties ();
        pnum = listp.size();
        qDebug() << "model index =" << i << " modname ="<< paramw->m_name << paramw->m_node->m_id;
        //pnum :number of params in th module;
        mod = paramw->m_name;

        for (int pi = 0; pi < pnum; pi++) 
        {
            pt = listp[pi];
            vpt = (QtVariantProperty *)pt;
            if (pt ==NULL) break; 
            param = pt->propertyName();
            qDebug() << "param index =" << pi << " paramname =" << param;
            qDebug() << "value 0 = " << pt->valueText();
            // continue;
            valueDescriptor = pdef->value(pi,0);
            itype = valueDescriptor->type();
             qDebug() << "value type = " << itype;
              

            pname = param.toUtf8().data();
            vlist.clear();//value list of the prameter in all lines
            if (mng->exists(pname.c_str()))  // if this param have data:
            {
                numLine = mng->getNumLines(pname.c_str());
                qDebug() << " numLines = " << numLine;// we assume that only have one line for one parameter;
                for (int il = 0; il < numLine; il++) 
                {
                    vlist1.clear();// value list in one line;
                    mng->getAll(pname.c_str(),&vlist1,il);
                    qDebug()<< "size of vlist1 =" << vlist1.size();
                    for (int ill =0; ill < vlist1.size();ill++) 
                    {
                        vlist.insertEnd(vlist1.at(ill));
                    }
                }
            }
            if (vlist.size() >0) 
            {
                str = vlist.at(0).c_str(); 
                qDebug() << "value 00 = " << str;
                
       // set first value:
                if(valueDescriptor->type()== VALTYPE_OPTION ||valueDescriptor->type()== VALTYPE_HEADER_NUMBER)
                {
                    //qDebug() << "22222 =" << valueDescriptor->type() ; 
                    nOptions = pdef->numOptions(pi,0);
                        //strList.clear();
                    qDebug() << "nOptions  = " << nOptions;
                    idx = 0;
                    for(  io = 0; io < nOptions; io++ )
                    {
                        optionDescriptor = pdef->option(pi,0,io);
                        Q_ASSERT(optionDescriptor->name() !=NULL);
                            //strList.append(optionDescriptor->name());
                        vname = optionDescriptor->name();
                         qDebug() << "nOptions  =" << vname;
                        if (str == vname) idx = io;
                    }
                    qDebug() << "before set idx = " <<idx ;
                    //vpt->setValue(idx); 
                    paramw->m_mngE->setValue(vpt,idx);
                         
                }
                else
                    vpt->setValue(str); 
   
                qDebug() << "value 00 after setvalue "  ;
            }// end of first value;
            
            listsp = pt->subProperties();
            //vnum :number of values -1 in the parameter:
            vnum = listsp.size();
            //continue;
            qDebug() << "number of subProperty =" << vnum;

            if (vlist.size() >1)  // data in user cards;
            for (int vi = 0; vi < vnum; vi ++) 
            {
                spt = listsp[vi];
                vpt = (QtVariantProperty *)spt;
                if (spt == NULL) break;
                qDebug() << "sub value " << vi << " =" << spt->valueText();
                
                if (vlist.size()-1 >vi ) 
                {
                    str = vlist.at(vi+1).c_str();
                    qDebug() << "user value ="  <<str;
           // set other  values:    
                    valueDescriptor = pdef->value(pi,vi+1); 
                    qDebug() << "user pdf ok =";
                    if(valueDescriptor->type()== VALTYPE_OPTION ||valueDescriptor->type()== VALTYPE_HEADER_NUMBER)
                    {
                        nOptions = pdef->numOptions(pi,vi+1);
                        //strList.clear();
                        idx = 0;
                        for(  io = 0; io < nOptions; io++ )
                        {
                            optionDescriptor = pdef->option(pi,vi+1,io);
                            Q_ASSERT(optionDescriptor->name() !=NULL);
                            //strList.append(optionDescriptor->name());
                            vname = optionDescriptor->name();
                            if (str == vname) idx = io;
                        }
                        qDebug() << "user pdf option idx =" << idx;
                        //vpt->setValue(idx);
                        paramw->m_mngE->setValue(vpt,idx);   
                        //qDebug() << "after option vpt =" << vpt;   
                    } 
                    else
                        vpt->setValue(str); 
                    qDebug() << "sub value1 " << vi << " =" << str;
                }
                
            }// end of vlist 
             
        }//end of params in the module
   
    }// end of paramWins(modules)
    //fclose(flog);
    return ;
}
void MainWindow::resizeEvent ( QResizeEvent * event )
{
    int w,h;
    m_w = event->size().width();
    m_h = event->size().height();
    flowMode();
}
void MainWindow::slotHelp()
{
    QString cmd,str;
    char *ch;
    cmd = "showpdf ";
    cmd = cmd+ getDocDir()+ SLASH + "flowpad.pdf";
        //cmd = "ls";
    qDebug() << "cmd=" <<cmd;
    hrun.start(cmd);

}
