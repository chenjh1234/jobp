#ifndef MODLISTWIN_H 
#define MODLISTWIN_H 
#include <QStringList>
#include "listview.h"
#include "sysdefine.h"
//#include "flowapplication.h"

class modListWin :public listView
{
    Q_OBJECT

public:
    modListWin(QWidget *p);
    ~modListWin();
    void init();

protected:
     
   void selectionChanged ( const QItemSelection & selected, const QItemSelection & deselected );
   void	mouseDoubleClickEvent ( QMouseEvent * event );
public slots:
    void slotFilter(const QString &s);
    void slotFilterAll();
signals:

    void sigSelect(QString);
    void sigAddModule(QString);
private:
    QString m_selectedMod ;
    QStringList m_listMods;
    void viewList(QStringList  s);
    void clear();
    void setHeader();

   // virtual bool edit(const QModelIndex &index, EditTrigger trigger, QEvent *event);
};



#endif

