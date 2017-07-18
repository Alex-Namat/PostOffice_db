#ifndef SQLTYPEMODEL_H
#define SQLTYPEMODEL_H

#include <QSqlTableModel>

class SqlTypeModel : public QSqlTableModel
{
public:
    SqlTypeModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());
    virtual ~SqlTypeModel();
    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
};

#endif // SQLTYPEMODEL_H
