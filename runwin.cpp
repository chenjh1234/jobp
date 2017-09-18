
#include "flowapplication.h"
#include "runwin.h"
#include "comfun.h"
#include <QStringMatcher>
runWin::runWin(QWidget *p):listView(p)
{
    init();
}
//=======================
runWin::~runWin()
{

}
void runWin::setHeader()
{ 
    QStringList s;
    s <<"name" << "start" << "finish" << "status";   
    listView::setHeader(s);
}
//=======================
void runWin::init()
{   
  
    setHeader();
  
}
void runWin::updateRow(QProcess *p,QString stm,QString st)
{
    int i,num,ip;
    QProcess *myp;
    ip = -1;
    num = theApp->m_win->m_listRun.size();
    for (i = 0; i <num ; i++)
    {
        myp = theApp->m_win->m_listRun.at(i)->pro;
        if (myp == p) //find;
        {
            ip = i;
            break;
        }
    }
    if (ip == -1) return;// not found;
    model->setData(model->index(ip,2,QModelIndex()),stm);
    model->setData(model->index(ip,3,QModelIndex()),st);
}
void runWin::updateRowTip(QProcess *p,QString stm)
{
    int i,num,ip;
    QProcess *myp;
    ip = -1;
    num = theApp->m_win->m_listRun.size();
    for (i = 0; i <num ; i++)
    {
        myp = theApp->m_win->m_listRun.at(i)->pro;
        if (myp == p) //find;
        {
            ip = i;
            break;
        }
    }
    if (ip == -1) return;// not found;
    model->setData(model->index(ip,0,QModelIndex()),stm,Qt::ToolTipRole);
     
}
void runWin::selectionChanged ( const QItemSelection & selected, const QItemSelection & deselected )
{
    QString s;
    QModelIndexList l;
    QModelIndex p;
   
    l = selected.indexes();
 //qDebug() << "select  = " << model->rowCount() << model->columnCount();
    if (l.size()<=0) return;
  
    p = l.at(0) ;//first selected;
    //qDebug() << "select3 = " << l << l.size()<< p;
     
    if (!p.isValid())  return;
    //if (p.data().toStringList().size() == 0) return;
    //s = p.data().toStringList().at(0); // first column
    int i;
    i = p.row();
    //qDebug() << "row = " << i;
    m_selectedRow = i; 
    if (theApp->m_win->m_listRun.size() > i) 
    {
        m_selectedName = theApp->m_win->m_listRun.at(i)->logname; 
    }
    else
        m_selectedName = "";

  
}
void runWin::mouseDoubleClickEvent ( QMouseEvent * event )
{
    QString s;
    s = m_selectedName;
    if (s.length()>0)  
        emit sigDBClick(s);

    listView::mouseDoubleClickEvent(event); 
}
  
 
 
