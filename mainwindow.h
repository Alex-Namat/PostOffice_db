#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include "SqlTypeModel.h"

#define DRIVER  "QPSQL"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void setAddresseeModel();
    void setItemModel();
    void setAttachmentModel();
    void setMailModel();
    void setTypeModel();
    void setOfficeModel();
    bool connect_db();
    void updateRelation(QSqlRelationalTableModel *model);

public slots:
    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_updateButton_clicked();

    void on_connectionButton_clicked();

    void on_caseButton_clicked();

    void on_havingButton_clicked();

    void on_anyButton_clicked();

    void on_viewButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *addresseeModel;
    QSqlRelationalTableModel *itemModel, *attachmentModel, *mailModel, *officeModel;
    SqlTypeModel *typeModel;
};

#endif // MAINWINDOW_H
