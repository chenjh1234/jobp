
#include "linemenuedit.h"
#include <QMenu>
#include <QCursor>
static QString flowPath;
lineMenuEdit::lineMenuEdit(QWidget *p):QLineEdit(p)
{
    init();
}
lineMenuEdit::~lineMenuEdit()
{

}
void lineMenuEdit::init()
{
    flowPath = "";
}
void lineMenuEdit::contextMenuEvent(QContextMenuEvent *event)
{
    
    
    QMenu *menu = createStandardContextMenu();
    //qDebug() << menu->size();
    acFile = menu->addAction(tr("File select"));
    //acDefine = menu->addAction(tr("Define select"));
    connect(acFile, SIGNAL(triggered()), this, SLOT(slotFile()));
    //connect(acDefine, SIGNAL(triggered()), parent(), SLOT(slotDefine()));
    //...
    //menu->exec(event->globalPos());
    menu->exec(QCursor::pos());
    delete menu;
 //QLineEdit::contextMenuEvent(event);
 //QLineEdit::contextMenuEvent(event);
   //QLineEdit::contextMenuEvent(event);
}
void lineMenuEdit::slotFile()
{
    QString fileName,str;
    int i;

    fileName = QFileDialog::getOpenFileName(this,
    tr("Open File"), flowPath, tr("data Files (*.*)"));
    QFileInfo fi(fileName);
    i = fileName.lastIndexOf(SLASH);
    str = fileName.left(i+1);
    flowPath = str;
    //qDebug() << "flowPath = " << flowPath <<str <<i;
    setText(fileName);
}
