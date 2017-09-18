#ifndef RUNWIN_H 
#define RUNWIN_H 
#include <QStringList>
#include <QProcess>
#include "listview.h"
#include "sysdefine.h"
//#include "flowapplication.h"
/**
 * run result window
 * 
 * @author cjh (7/3/2015)
 */
class runWin :public listView
{
    Q_OBJECT

public:
    runWin(QWidget *p);
    ~runWin();
    void updateRow(QProcess *p,QString stm,QString st);
    void updateRowTip(QProcess *p,QString stm);
   

protected:
     
   void selectionChanged ( const QItemSelection & selected, const QItemSelection & deselected );
   void	mouseDoubleClickEvent ( QMouseEvent * event );
 
signals:

    void sigSelect(QString);
    void sigDBClick(QString);
private:
     void init();
    void setHeader();
    QString m_selectedName;
    int  m_selectedRow;

   // virtual bool edit(const QModelIndex &index, EditTrigger trigger, QEvent *event);
};
#endif
