
#ifndef LINEMENUEDIT_H 
#define LINEMENUEDIT_H
 
#include <QWidget>
#include <QDebug>
#include <QLineEdit>
#include <QFileDialog>
#include <QString>

class lineMenuEdit : public QLineEdit
{
    Q_OBJECT
public:
    lineMenuEdit(QWidget *p);
    ~lineMenuEdit();
    void init();
    //static QString flowPath;
protected:
    void contextMenuEvent(QContextMenuEvent *event);
    QAction *acFile,*acDefine;
public slots:
    void slotFile();


};
#endif
