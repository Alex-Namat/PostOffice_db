#include "SqlTypeModel.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>


SqlTypeModel::SqlTypeModel(QObject *parent, QSqlDatabase db) :
    QSqlTableModel(parent,db)
{

}

SqlTypeModel::~SqlTypeModel()
{
}

bool SqlTypeModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(count)
    beginInsertRows(parent,row,row);
    bool result = true;
    QSqlQuery query;
    query.prepare("SELECT public.insert_type ("
                  ":name,"
                  ":maxWeight,"
                  ":stdTariff ::money,"
                  ":stdWeight,"
                  ":addTariff ::money,"
                  ":addWeight,"
                  ":value,"
                  ":costTariff ::money,"
                  ":addCost ::money)");
    query.bindValue(":name"," ");
    query.bindValue(":maxWeight",20);
    query.bindValue(":stdTariff",0);
    query.bindValue(":stdWeight",0);
    query.bindValue(":addTariff",0);
    query.bindValue(":addWeight",0);
    query.bindValue(":value",false);
    query.bindValue(":costTariff",0);
    query.bindValue(":addCost",0);

    if(!query.exec()){
        result = false;
    }
    endInsertRows();
    this->select();
    return result;
}

bool SqlTypeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(count)
    beginRemoveRows(parent, row, row);    
    bool result = true;
    QSqlQuery query;
    query.prepare("SELECT public.delete_type (:id)");
    query.bindValue(":id",this->record(row).value(0).toInt());
    if(!query.exec()){
        result = false;
    }
    endRemoveRows();
    this->select();
    return result;
}

bool SqlTypeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role)
    bool result = true;
    QSqlRecord record = this->record(index.row());
    record.setValue(index.column(),value);
    QSqlQuery query(this->database());
    query.prepare("SELECT public.update_type ("
                  ":id,"
                  ":name,"
                  ":maxWeight,"
                  ":stdTariff,"
                  ":stdWeight,"
                  ":addTariff,"
                  ":addWeight,"
                  ":value,"
                  ":costTariff,"
                  ":addCost)");
    query.bindValue(":id",record.value(0));
    query.bindValue(":name",record.value(1));
    query.bindValue(":maxWeight",record.value(2));
    query.bindValue(":stdTariff",record.value(3));
    query.bindValue(":stdWeight",record.value(4));
    query.bindValue(":addTariff",record.value(5));
    query.bindValue(":addWeight",record.value(6));
    query.bindValue(":value",record.value(7));
    query.bindValue(":costTariff",record.value(8));
    query.bindValue(":addCost",record.value(9));
    if(!query.exec()){
        result = false;
    }

    this->select();
    return result;
}
