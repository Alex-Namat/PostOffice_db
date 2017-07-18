#include "IdAttachmentDelegat.h"
#include <QComboBox>
#include <QSqlRelationalTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

IdAttachmentDelegat::IdAttachmentDelegat(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

QWidget *IdAttachmentDelegat::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    QSqlRelationalTableModel* model = (QSqlRelationalTableModel*) index.model();
    QComboBox* combo = new QComboBox(parent);
    combo->setModel(model->relationModel(index.column()));
    combo->setModelColumn(0);
    combo->addItem("NULL");
    return combo;
}

void IdAttachmentDelegat::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox * combo = (QComboBox *)editor;
    QSqlRelationalTableModel* m = (QSqlRelationalTableModel*) model;
    QVariant tmp = combo->currentText();
    if(tmp == QString("NULL")){
        QSqlQuery query;
        query.prepare("UPDATE [dbo].[Почтовое_отправление] "
                      "SET [ИД_Тип] = "
                        "(SELECT [ИД_Тип] "
                        "FROM [dbo].[Тип_отправления] "
                        "WHERE [Название] LIKE :type),"
                      "[ИД_Вложение] = NULL "
                      "WHERE [ИД_Отправление] = :id");
        qDebug() << index.sibling(index.row(),0).data() << index.sibling(index.row(),2).data();
        query.bindValue(":id",index.sibling(index.row(),0).data().toInt());
        query.bindValue(":type",index.sibling(index.row(),2).data().toString());
        query.exec();
        m->submitAll();
        return;
    }
    model->setData(index,tmp);
}





