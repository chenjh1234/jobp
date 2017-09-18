#ifndef TABLEDLG_H
#define TABLEDLG_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QSize>
#include <QSpinBox> 
#include <QComboBox>

class tableDlg : public QItemDelegate
{
    Q_OBJECT

public:
    tableDlg(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif
