#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include "Database.h"
#include "SqlTypeModel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setAddresseeModel();
    void setItemModel();
    void setAttachmentModel();
    void setMailModel();
    void setTypeModel();
    void setOfficeModel();

protected:
    void updateRelation(QSqlRelationalTableModel *model);

private slots:
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
    Database *db;
    QSqlTableModel *addresseeModel;
    QSqlRelationalTableModel *itemModel, *attachmentModel, *mailModel, *officeModel;
    SqlTypeModel *typeModel;
};

#endif // MAINWINDOW_H
