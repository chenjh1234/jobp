
#ifndef FLOWDEFINE_H 
#define FLOWDEFINE_H
#include <QDialog>
#include <QWidget>
#include <QDebug>
#include <QString>
#include <QTableView>
#include <QStandardItemModel>
#include <QDialog>
#include <QModelIndex>
#include "tabledlg.h"
#include "ui_flowdefine.h"
#define MAX_DEFINES 10
class flowDefine : public QDialog
{
    Q_OBJECT
public:
    flowDefine(QWidget *p);
    ~flowDefine();
     
 
    void init();
    void setText(int row,QString &t,QString &n, QString &v);
    void getText(int row,QString &t,QString &n, QString &v);
    QString getSelect();
public slots:
    void slotSelect(QModelIndex);
    void accept();

private:
    QStandardItemModel *model;
    tableDlg *dlg;
    Ui::Dialog ui;
 
/*
class flowDefine : public QTableView
{
public:
    flowDefine(QWidget *p);
    ~flowDefine();
    void init();
    void setText(int row,QString &t,QString &n, QString &v);
    void getText(int row,QString &t,QString &n, QString &v);
private:
    QStandardItemModel *model;
    tableDlg *dlg;
*/
};
#endif
