#include "listview.h"
#include "flowapplication.h"

listView::listView(QWidget *p):QTreeView(p)
{
    init();
}
//=======================
listView::~listView()
{

}

//=======================
void listView::init()
{    
    setSortingEnabled(true);
    setEditTriggers(0);
    
    model = NULL;  
    //qDebug() <<"00001110";
}
int listView::setHeader(stringList head)
{
    return setHeader(toQStrList(head));
}
int listView::setHeader(QStringList head)
{

    int num,i;
    num = head.size(); 
    if (model == NULL) 
    {
         model = new QStandardItemModel(1,num,parent());
         setModel(model);
         
         
    }
   // Q_CHECK_PTR(model);
    model->setHorizontalHeaderLabels (head);
    
    for (i = 0; i <num ; i++)
    {     
        model->setHeaderData(i, Qt::Horizontal,tr( head[i].toUtf8().data()) );         
    }
    return 0;
}
QStringList listView::toQStrList(stringList l)
{
    QStringList list;
    int num,i;  
    num = l.size();
    for (i =0; i <num ;i++) 
    {
        list.append(l[i].c_str());
    }
    return list;

}
int listView::addRow(string str)
{
    stringList  list;
    list.push_back(str);
    return addRow(list);

}
int listView::addRow(QString str)
{
    QStringList  list;
    list.append(str);
    return addRow(list);

}
int listView::addRow(stringList item)
{
  
    return addRow(toQStrList(item));
}

int listView::addRow(QStringList item)
{

    int num,idx,i;  
    idx = 0;  
    num =item.size(); 
    if (model ==NULL) 
    {
         model = new QStandardItemModel(1,num,parent());
         
    }

  
    model->insertRow(idx,QModelIndex());//insert from index 0;
    for (i = 0; i <num ; i++)
    {
        model->setData(model->index(idx,i,QModelIndex()),item[i]);
    }
    return 0; 
}

/* 
    //return;
    int sz,i;
    bool b;
    string s;
   
    m_file->setProject("myproject","line2");
    fileInfo *fp;
   // if (m_file->m_config != "log")  return;
    sz = m_file->size();

    model = new QStandardItemModel(1,4,parent());
    
    model->setHeaderData(0, Qt::Horizontal, tr("Name"));
    model->setHeaderData(1, Qt::Horizontal, tr("User"));
    model->setHeaderData(2, Qt::Horizontal, tr("Size"));
    model->setHeaderData(3, Qt::Horizontal, tr("Time"));

//    model->removeRows(0, model->rowCount(QModelIndex()), QModelIndex());
  
    for (i = 0 ; i <sz ; i++) 
    {
       fp =  (fileInfo *)(m_file->get(i));
       cout << fp->name <<endl;
       cout << fp->path <<endl;
       cout << fp->size <<endl;
       //cout << fp->time <<endl;
       //cout << fp->user <<endl;
       model->insertRow(i,QModelIndex());
       model->setData(model->index(i,0,QModelIndex()),fp->name.c_str());
       model->setData(model->index(i,1,QModelIndex()),fp->user.c_str());
      //s =flexVar(fp->size).toString(); 
       //model->setData(model->index(i,2,QModelIndex()),s.c_str());
       model->setData(model->index(i,2,QModelIndex()),fp->size);
       model->setData(model->index(i,3,QModelIndex()),fp->time.c_str());

    }
    //pmodel = new QSortFilterProxyModel;
    //pmodel->setDynamicSortFilter(true);
    //pmodel->setSourceModel(model);

    setModel(model);
    setSortingEnabled(true);
    setEditTriggers(0);
   // setModel(model);
   // QItemSelectionModel *selectionModel = new QItemSelectionModel(model);
    //setSelectionModel(selectionModel);


  
}
*/
//=======================
 
  
