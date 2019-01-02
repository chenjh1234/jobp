
#include "flowapplication.h"
#include "modlistwin.h"
#include "comfun.h"
#include <QStringMatcher>
modListWin::modListWin(QWidget *p):listView(p)
{
    init();
}
//=======================
modListWin::~modListWin()
{

}
void modListWin::setHeader()
{ 
    stringList s;
    s.push_back("modules");     
    listView::setHeader(s);
}
//=======================
void modListWin::init()
{   
    stringList s; 
    setHeader();
    sortByColumn(0);
    s = theApp->m_doc->m_modMng.modules();
    m_listMods = toQStrList(s);
   
    viewList(m_listMods);
  
}
void modListWin::selectionChanged ( const QItemSelection & selected, const QItemSelection & deselected )
{
    QString s;
    QModelIndexList l;
    QModelIndex p;

    l = selected.indexes();
    if (l.size()<=0) return;
    //qDebug() << "size =" << l.size();
    p = l[0] ;//first selected;
    if (p.data().toStringList().size() == 0) return;
    s = p.data().toStringList()[0];// first column
    m_selectedMod =s;
    emit sigSelect(s);
    //qDebug() << "yes emit " << s;
   
}
void	modListWin::mouseDoubleClickEvent ( QMouseEvent * event )
{
    QString s;
    s = m_selectedMod;
    if (s != NULL)  
        emit sigAddModule(s);

    listView::mouseDoubleClickEvent(event); 
}
void modListWin::slotFilter(const QString &s)
{
    QStringMatcher m;
    QString str;
    QStringList lists;
    int i,num;
    //qDebug() << "edit =" << s;

    m.setPattern(s);
    num = m_listMods.size();
    // qDebug() << "edit size =" << num;
    for (i = 0; i < num; i++)
    {
        //qDebug() << "loop=" << i;
        str= m_listMods[i];
        //qDebug() << "loop1=" << i;
        if(m.indexIn(str)!=-1)
        {
            lists.append(str);
        }     
    }
    //qDebug() << "after loop1=" << lists.size()<<num <<model->rowCount();
    viewList(lists);
    
}
void modListWin::slotFilterAll()
{
     viewList(m_listMods);
}
void modListWin::clear()
{
    model->clear();
    return;
}
void modListWin::viewList(QStringList mlist)
{

    int num,i;
    QString str;
    clear();
    setHeader();

    num = mlist.size();
     
    for (i = 0; i < num; i++)
    {
        str= mlist[i];
        addRow(str);
    }
    model->sort(0);
}
