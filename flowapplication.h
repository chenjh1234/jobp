#ifndef FLOWAPPLICATION_H
#define FLOWAPPLICATION_H

#include <QApplication>
#include "mainwindow.h"
#include "flowdocument.h"
class flowApplication;
class MainWindow;
#include <iostream>

#define DOC theApp->m_doc

using namespace std;
extern flowApplication *theApp;
 
class flowApplication :public QApplication  
{
public:
    flowApplication( int & argc, char ** argv );
    ~flowApplication();
    flowDocument *m_doc;
    MainWindow *m_win;


private:

    void init();

};
#endif
