#include "AuthorizationDialog.h"
#include "ui_authorizationdialog.h"

AuthorizationDialog::AuthorizationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorizationDialog),
    settings(new QSettings("Namat","Database"))
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(clickedOk()));
    ui->userEdit->setText(settings->value("PostOffice/connection/user").toString());
}
void AuthorizationDialog::clickedOk(){
    settings->setValue("PostOffice/connection/user",ui->userEdit->text());
    emit accept();
}

QString AuthorizationDialog::getUser() const{
    return ui->userEdit->text();
}

QString AuthorizationDialog::getPassword() const{
    return ui->passwordEdit->text();
}

AuthorizationDialog::~AuthorizationDialog()
{
    delete settings;
    delete ui;
}
