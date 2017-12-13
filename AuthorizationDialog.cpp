#include "AuthorizationDialog.h"
#include "ui_authorizationdialog.h"

AuthorizationDialog::AuthorizationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorizationDialog),
    settings("Namat","PostOffice_db"),
    crypt(Q_UINT64_C(0x19be90ac42c639b3db7e))
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(clickedOk()));
    ui->nameEdit->setText(settings.value("Connection/database_name").toString());
    ui->hostEdit->setText(settings.value("Connection/host").toString());
    ui->portEdit->setText(settings.value("Connection/port").toString());
    ui->userEdit->setText(settings.value("Connection/user").toString());
    ui->passwordEdit->setText(crypt.decryptToString(
                                  settings.value("Connection/password").toString()
                                  ));
    if(settings.value("check").toBool()){
        ui->checkBox->setChecked(true);
    }
}
void AuthorizationDialog::clickedOk(){
    settings.setValue("Connection/database_name",ui->nameEdit->text());
    settings.setValue("Connection/host",ui->hostEdit->text());
    settings.setValue("Connection/port",ui->portEdit->text());
    settings.setValue("Connection/user",ui->userEdit->text());
    if(ui->checkBox->isChecked()){
        settings.setValue("Connection/password",crypt.encryptToString(
                              ui->passwordEdit->text()
                              ));
    }
    else
    {
       settings.setValue("Connection/password","");
    }
    settings.setValue("check",ui->checkBox->isChecked());
    emit accept();
}

AuthorizationDialog::~AuthorizationDialog()
{
    delete ui;
}

QString AuthorizationDialog::getDatabaseName() const
{
    return ui->nameEdit->text();
}

QString AuthorizationDialog::getHost() const
{
    return ui->hostEdit->text();
}

int AuthorizationDialog::getPort() const
{
    return ui->portEdit->text().toInt();
}

QString AuthorizationDialog::getUser() const
{
    return ui->userEdit->text();
}

QString AuthorizationDialog::getPassword() const
{
    return ui->passwordEdit->text();
}
