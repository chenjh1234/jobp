
#ifndef FLOWTEXTWIN_H 
#define FLOWTEXTWIN_H 
 
#include <QTextBrowser>
 
#include "sysdefine.h"
#include <QDebug>
#include <QMouseEvent>
#include <QTextCursor>
#include <QTextCharFormat>

class flowTextWin :public QTextBrowser
{
    Q_OBJECT

public:
    flowTextWin(QWidget *p);
    ~flowTextWin();
    void init();
  
protected:
    //gdata *data;
    QTextCursor lastCursor ;
    QTextCharFormat lastFmt;

   // virtual bool edit(const QModelIndex &index, EditTrigger trigger, QEvent *event);
   void mousePressEvent(QMouseEvent *e);
};



#endif
