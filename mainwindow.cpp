#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>
#include <QSqlRelationalDelegate>
#include "IdAttachmentDelegat.h"
#include "NoEditColumnDelegate.h"
#include "AuthorizationDialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    db(QSqlDatabase::addDatabase(DRIVER))
{
    ui->setupUi(this);
    if(connect_db()){
        ui->statusBar->showMessage(db.userName());
    }
    else
        ui->statusBar->showMessage(db.lastError().text());

    setAddresseeModel();
    setItemModel();
    setAttachmentModel();
    setMailModel();
    setTypeModel();
    setOfficeModel();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete addresseeModel;
    delete itemModel;
    delete attachmentModel;
    delete mailModel;
    delete officeModel;
    delete typeModel;
}

void MainWindow::setAddresseeModel()
{
   addresseeModel = new QSqlTableModel(this,db);
   addresseeModel->setTable("\"Адресат\"");
   addresseeModel->setEditStrategy(QSqlTableModel::OnRowChange);
   addresseeModel->select();

   ui->addresseeView->setModel(addresseeModel);
   //ui->addresseeView->setItemDelegateForColumn(0,new NoEditColumnDelegate(ui->addresseeView));
   ui->addresseeView->setEditTriggers(QAbstractItemView::DoubleClicked);
   ui->addresseeView->setSelectionBehavior(QAbstractItemView::SelectRows);
   ui->addresseeView->verticalHeader()->setVisible(false);
   ui->addresseeView->resizeColumnsToContents();
}

void MainWindow::setItemModel()
{
    itemModel = new QSqlRelationalTableModel(this,db);
    itemModel->setTable("\"Предмет\"");
    itemModel->setRelation(1,QSqlRelation("\"Вложение\"","\"ИД_Вложение\"","\"ИД_Вложение\""));
    itemModel->setEditStrategy(QSqlTableModel::OnRowChange);
    itemModel->select();

    ui->itemView->setModel(itemModel);
    ui->itemView->setItemDelegate(new QSqlRelationalDelegate(ui->itemView));
    //ui->itemView->setItemDelegateForColumn(0,new NoEditColumnDelegate(ui->itemView));
    ui->itemView->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->itemView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->itemView->verticalHeader()->setVisible(false);
    ui->itemView->resizeColumnsToContents();
}

void MainWindow::setAttachmentModel()
{
    attachmentModel = new QSqlRelationalTableModel(this,db);
    attachmentModel->setTable("\"Вложение\"");
    attachmentModel->setRelation(1,QSqlRelation("\"Адресат\"","\"ИД_Адресат\"","\"ИД_Адресат\""));
    attachmentModel->setEditStrategy(QSqlTableModel::OnRowChange);
    attachmentModel->select();

    ui->attachmentView->setModel(attachmentModel);
    ui->attachmentView->setItemDelegate(new QSqlRelationalDelegate(ui->attachmentView));
    //ui->attachmentView->setItemDelegateForColumn(0,new NoEditColumnDelegate(ui->attachmentView));
    ui->attachmentView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->attachmentView->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->attachmentView->verticalHeader()->setVisible(false);
    ui->attachmentView->resizeColumnsToContents();
}

void MainWindow::setMailModel()
{
    mailModel = new QSqlRelationalTableModel(this,db);
    mailModel->setTable("\"Почтовое_отправление\"");
    mailModel->setRelation(1,QSqlRelation("\"Адресат\"","\"ИД_Адресат\"","\"ИД_Адресат\""));
    mailModel->setRelation(2,QSqlRelation("\"Тип_отправления\"","\"ИД_Тип\"","\"Название\""));
    mailModel->setRelation(3,QSqlRelation("\"Вложение\"","\"ИД_Вложение\"","\"ИД_Вложение\""));
    mailModel->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    mailModel->setEditStrategy(QSqlTableModel::OnRowChange);
    mailModel->select();

    ui->mailView->setModel(mailModel);
    ui->mailView->setItemDelegate(new QSqlRelationalDelegate(ui->mailView));
    //ui->mailView->setItemDelegateForColumn(0,new NoEditColumnDelegate(ui->mailView));
    ui->mailView->setItemDelegateForColumn(3,new IdAttachmentDelegat(ui->mailView));
    ui->mailView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->mailView->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->mailView->verticalHeader()->setVisible(false);
    ui->mailView->resizeColumnsToContents();
}

void MainWindow::setTypeModel()
{
    typeModel = new SqlTypeModel(this,db);
    typeModel->setTable("\"Тип_отправления\"");
    typeModel->setEditStrategy(QSqlTableModel::OnRowChange);
    typeModel->select();

    ui->typeView->setModel(typeModel);
    //ui->typeView->setItemDelegateForColumn(0,new NoEditColumnDelegate(ui->typeView));
    ui->typeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->typeView->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->typeView->verticalHeader()->setVisible(false);
    ui->typeView->resizeColumnsToContents();
}

void MainWindow::setOfficeModel()
{
    officeModel = new QSqlRelationalTableModel(this,db);
    officeModel->setTable("\"Почтовое_отделение\"");
    officeModel->setRelation(1,QSqlRelation("\"Почтовое_отправление\"","\"ИД_Отправление\"","\"ИД_Отправление\""));
    officeModel->setEditStrategy(QSqlTableModel::OnRowChange);
    officeModel->select();

    ui->officeView->setModel(officeModel);
    ui->officeView->setItemDelegate(new QSqlRelationalDelegate(ui->officeView));
    ui->officeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->officeView->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->officeView->verticalHeader()->setVisible(false);
    ui->officeView->resizeColumnsToContents();
}

bool MainWindow::connect_db()
{
    AuthorizationDialog *authorizationDlg = new AuthorizationDialog();
    if(authorizationDlg->exec() == QDialog::Accepted){
        db.setDatabaseName(authorizationDlg->getDatabaseName());
        db.setHostName(authorizationDlg->getHost());
        db.setPort(authorizationDlg->getPort());
        db.setUserName(authorizationDlg->getUser());
        db.setPassword(authorizationDlg->getPassword());
    }
    delete authorizationDlg;

    if(db.open()){
        return true;
    }
    else
        return false;
}

void MainWindow::updateRelation(QSqlRelationalTableModel *model)
{
    for(int i = 0; i < model->columnCount(); i++) {
        QSqlTableModel *m = model->relationModel(i);
        if (m){
            m->select();
        }
    }
}

void MainWindow::on_addButton_clicked()
{
    this->on_updateButton_clicked();
    QSqlTableModel *model;
    switch(ui->tabWidget->currentIndex()){
    case 0 :
        model = addresseeModel;
        break;
    case 1 :
        model = itemModel;
        break;
    case 2 :
        model = attachmentModel;
        break;
    case 3 :
        model = mailModel;
        break;
    case 4 :
        model = typeModel;
        break;
    case 5 :
        model = officeModel;
        break;
    default :
        return;
    }
    model->insertRow(model->rowCount());
}

void MainWindow::on_deleteButton_clicked()
{
    QSqlTableModel *model;
    QTableView *view;
    switch(ui->tabWidget->currentIndex()){
    case 0 :
    {
        model = addresseeModel;
        view =ui->addresseeView;
        break;
    }
    case 1 :
    {
        model = itemModel;
        view =ui->itemView;
        break;
    }
    case 2 :
    {
        model = attachmentModel;
        view =ui->attachmentView;
        break;
    }
    case 3 :
    {
        model = mailModel;
        view =ui->mailView;
        break;
    }
    case 4 :
    {
        model = typeModel;
        view = ui->typeView;
        break;
    }
    case 5 :
    {
        model = officeModel;
        view = ui->officeView;
        break;
    }
    default:
        return;
    }
    auto select = view->selectionModel();
    if(select->hasSelection()){
        auto listSelect = select->selectedRows();
        for(auto i = 0; i < listSelect.size(); ++i){
            model->removeRow(listSelect[0].row());
        }
        model->submitAll();
    }
}

void MainWindow::on_updateButton_clicked()
{
    addresseeModel->submitAll();
    itemModel->submitAll();
    attachmentModel->submitAll();
    mailModel->submitAll();    
    typeModel->submitAll();
    officeModel->submitAll();

    updateRelation(itemModel);
    updateRelation(attachmentModel);
    updateRelation(mailModel);
    updateRelation(officeModel);

    addresseeModel->select();
    itemModel->select();
    attachmentModel->select();
    mailModel->select();
    typeModel->select();
    officeModel->select();
}

void MainWindow::on_connectionButton_clicked()
{
    db.close();
    if(connect_db()){
        ui->statusBar->showMessage(db.userName());}
    else
        ui->statusBar->showMessage(db.lastError().text());

    delete addresseeModel;
    delete itemModel;
    delete attachmentModel;
    delete mailModel;
    delete officeModel;
    delete typeModel;

    setAddresseeModel();
    setItemModel();
    setAttachmentModel();
    setMailModel();
    setTypeModel();
    setOfficeModel();
}

void MainWindow::on_caseButton_clicked()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT "
                    "p.\"ИД_Отправление\","
                    "a.\"ФИО\","
                    "t.\"Название\","
                    "CASE "
                    "WHEN t.\"Ценность\" = true THEN 1 "
                    "WHEN t.\"Ценность\" = false THEN 0 "
                    "END "
                    "\"Ценность\","
                    "p.\"Стоимость\" "
                    "FROM public.\"Почтовое_отправление\" AS p "
                    "INNER JOIN public.\"Тип_отправления\" AS t ON t.\"ИД_Тип\" = p.\"ИД_Тип\" "
                    "INNER JOIN public.\"Адресат\" AS a ON a.\"ИД_Адресат\" = p.\"ИД_Адресат\"");
    QTableView *view = new QTableView;
    view->setModel(model);
    //view->verticalHeader()->setVisible(false);
    view->show();
}

void MainWindow::on_havingButton_clicked()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT a.\"ИД_Вложение\","
                    "COUNT(*) \"Количество\" "
                    "FROM public.\"Вложение\" AS a, public.\"Предмет\" AS i "
                    "WHERE i.\"ИД_Вложение\" = a.\"ИД_Вложение\" "
                    "GROUP BY a.\"ИД_Вложение\" "
                    "HAVING COUNT(*) > 1");
    QTableView *view = new QTableView;
    view->setModel(model);
    view->verticalHeader()->setVisible(false);
    view->show();
}

void MainWindow::on_anyButton_clicked()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT * "
                    "FROM public.\"Почтовое_отделение\" "
                    "WHERE \"Индекс\" = ANY "
                    "(SELECT \"Индекс\" FROM public.\"Адресат\")");
    QTableView *view = new QTableView;
    view->setModel(model);
    view->verticalHeader()->setVisible(false);
    view->show();
}

void MainWindow::on_viewButton_clicked()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery(QString("SELECT * FROM public.po_view ORDER BY \"%1\"")
                    .arg(ui->comboBox->currentText()));
    QTableView *view = new QTableView;
    view->setModel(model);
    view->verticalHeader()->setVisible(false);
    view->show();
}
