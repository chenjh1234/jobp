#include <QtGui>

#include "tabledlg.h"

tableDlg::tableDlg(QObject *parent)
    : QItemDelegate(parent)
{
}

QWidget *tableDlg::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex &/* index */) const
{
    //QSpinBox *editor = new QSpinBox(parent);
    //editor->setMinimum(0);
    //editor->setMaximum(100);
    QComboBox *editor = new QComboBox(parent);
    editor->addItem("&define");
    editor->addItem("&table");
    editor->setCurrentIndex (0);

    return editor;
}

void tableDlg::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    //int value = index.model()->data(index, Qt::EditRole).toInt();
    //QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    //spinBox->setValue(value);

    QString str = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comBox = static_cast<QComboBox*>(editor);
    int v;
    if (str == "&define")  v=0;
    if (str == "&table")  v=1;
    comBox->setCurrentIndex(v); 
}

void tableDlg::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    //QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    //spinBox->interpretText();
    //int value = spinBox->value();
    //model->setData(index, value, Qt::EditRole);

    QComboBox *comBox = static_cast<QComboBox*>(editor);
    //comBox->interpretText();
    int value = comBox->currentIndex();
    QString str;
    str = comBox->currentText();
    model->setData(index, str, Qt::EditRole);
}

void tableDlg::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
