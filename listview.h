#ifndef LISTVIEW_H 
#define LISTVIEW_H 

#include <QWidget>
#include <QListView>
#include <QTreeView>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include "sysdefine.h"

class listView :public QTreeView
{
    Q_OBJECT

public:
    listView(QWidget *p);
    ~listView();
    void init();
    int addRow(stringList item);
    int addRow(QStringList item);
    int addRow(string item);
    int addRow(QString item);
    int setHeader(QStringList h);
    int setHeader(stringList h);
    QStringList toQStrList(stringList s);

     
    QStandardItemModel  *model;
    QSortFilterProxyModel *pmodel;
    
protected:
    //gdata *data;

   // virtual bool edit(const QModelIndex &index, EditTrigger trigger, QEvent *event);
};



#endif
