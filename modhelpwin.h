#ifndef MODHELPWIN_H 
#define MODHELPWIN_H 

#include <QTextBrowser>
 
#include "sysdefine.h"

class modHelpWin :public QTextBrowser
{
    Q_OBJECT

public:
    modHelpWin(QWidget *p);
    ~modHelpWin();
    void init();
  
protected:
    //gdata *data;
public slots:
    void slotHelp(QString);

   // virtual bool edit(const QModelIndex &index, EditTrigger trigger, QEvent *event);
};



#endif


