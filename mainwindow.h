#ifndef FLOWMAINWINDOW_H
#define FLOWMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
//class QPlainTextEdit;
QT_END_NAMESPACE
#include <QSplitter>
#include <QTabWidget>
#include <QDockWidget>
#include <QTextBrowser>
#include <QGraphicsView>
#include <QLabel>
#include <QPushButton>
#include <QProcess>
#include "csVector.h"
#include "csUserParam.h"

#include "listview.h"
#include "modhelpwin.h"
#include "modlistwin.h"
#include "paramwin.h"
#include "flowtextwin.h"
#include "flowwin.h"
#include "runwin.h"
#include "flowdefine.h"
#include "linemenuedit.h"
#include "iostream"
//#include <QtTreePropertyBrowser>
#include "flowapplication.h"

#define pmList csVector<csUserParam *>
using namespace std;
using namespace cseis_geolib;
 
class MainWindow : public QMainWindow
{
    Q_OBJECT
public: 
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void about();
    void documentWasModified();

private:
    void initMod();
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    void setTitle();

   // QPlainTextEdit *textEdit;
    QSplitter *split;
    QTabWidget *tabWidget;
    QDockWidget *modDockWidget,*infoDockWidget;
    QDockWidget *paramDockWidget ,*flowTextDockWidget,*flowDefineDockWidget  ;
    QDockWidget *runDockWidget;
    QWidget *modManager;
    QWidget *modFilter;
    QPushButton *buttonModAll;
    QLineEdit *editFilter;
    QLabel *labelFilter;
    modListWin *modListView; 
    runWin *runView; 
    QProcess hrun;
    class run//run information;
    {
    public:
        run(){};
        QString name,logname,fullname;
        QProcess *pro;
        QString inputData,outputData;
    };

    //lineMenuEdit *lineView;

  
    //QString curFile;
    //csVector<csUserParam *> *modParam;

    map<string,csVector<csUserParam *> > mapParam;
 
    
    QMenu *fileMenu;
    QMenu *editMenu,*runMenu,*constantMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;
    QToolBar *editToolBar,*runToolBar,*helpToolBar;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *textFlowAct;

    QAction *closeAct;
    QAction *exitAct;

    QAction *upAct;
    QAction *downAct;
    QAction *delAct;
  
    
    QAction *runAct;
    QAction *submitAct;
    QAction *constantAct;

    QAction *aboutAct;
    QAction *helpAct;
public:
    modHelpWin *modHelpView;
    paramWin *paramView;
    flowTextWin *flowTView;
    flowWin *flowView;
    flowDefine *defineView;
    //QProcess job;
    void logMode();
    void flowMode();

public slots:
    void slotCreateParam(flowNode*);
    void slotShowParam(flowNode*);
    void slotRemoveParam(flowNode*);
    void slotParam2Str();
    void slotRun();
    void slotSubmit();
    void slotConstant();
    void slotUp();
    void slotDown();
    void slotDel();
    void slotHelp();
    void slotTextFlow();
    void slotJobOK(int, QProcess::ExitStatus);
    void slotJobErr(QProcess::ProcessError);
    void slotShowLog(QString log);
    void resizeEvent ( QResizeEvent * event );
public:
    QList<run *> m_listRun;
private:
    QList<paramWin *> m_listParam;
    
    void param2Str();
    paramWin * findParamView(int idx);
    void setParamData();
    int m_w,m_h;
    //bool isflowMode();
 
};
//! [0]

#endif
