#include "flowdefine.h"
#include <QModelIndex>
#include <QVariant>

flowDefine::flowDefine(QWidget *p):QDialog(p)
{
    ui.setupUi(this);
    init();
}
flowDefine::~flowDefine()
{

} 
void flowDefine::setText(int row,QString &t,QString &n, QString &v)
{
    model->setData(model->index(row,0,QModelIndex()),t);
    model->setData(model->index(row,1,QModelIndex()),n);
    model->setData(model->index(row,2,QModelIndex()),v);
}
void flowDefine::getText(int row,QString &t,QString &n ,QString &v)
{
    QVariant vq;
    vq  = model->data(model->index(row,0,QModelIndex()));
    t = vq.toString();
    vq  = model->data(model->index(row,1,QModelIndex()));
    n = vq.toString();
    vq = model->data(model->index(row,2,QModelIndex()));
    v = vq.toString();

} 
void flowDefine::init()
{
    QString str;
    QStringList liststr;
    model = new QStandardItemModel(4,3);
    liststr << "type" << "name" << "value";
    model->setHorizontalHeaderLabels(liststr);
    //horizontalHeader()->setStretchLastSection(true);
    dlg = new tableDlg();
    ui.tableView->setItemDelegateForColumn(0,dlg);
   // str = "&table";
    
    for (int row = 0; row < MAX_DEFINES; ++row) 
    {
        for (int column = 0; column < 1; ++column) 
        {
             if(row == 3 ) str = "&define";
             else str= "&table";
             QModelIndex index = model->index(row, column, QModelIndex());
             model->setData(index, QVariant(str));
        }
    }
 
    ui.tableView->setModel(model);


    connect(ui.tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(slotSelect(QModelIndex)));
    //connect(ui.tableView, SIGNAL(clicked(QModelIndex )),  this, SLOT(accept()));
   // connect(ui.tableView, SIGNAL(clicked(QModelIndex )),(flowDefine *) this, SLOT(slotSelect( QModelIndex )));
    connect(ui.buttonBox, SIGNAL(accepted()),this, SLOT(accept()));

 
}
void flowDefine::slotSelect(QModelIndex index)
{
    QString str;
    int row,col;
    QModelIndex idx;
   // qDebug() <<    "slot Select";
     
    row = index.row();
    col = index.column();
    idx = index.sibling(row,1);
    str = idx.data().toString();
    ui.lineEdit->setText(str);
 
}
void flowDefine::accept()
{
    QDialog::accept();
   //qDebug()<< "yes accept";
}
QString flowDefine::getSelect()
{
    return ui.lineEdit->text();
}
