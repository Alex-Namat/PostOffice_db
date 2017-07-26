#include "Database.h"
#include "AuthorizationDialog.h"


Database::Database() :
    QSqlDatabase(QSqlDatabase::addDatabase(DRIVER))
{
}

Database::~Database()
{
    this->close();
}

bool Database::connect()
{
    AuthorizationDialog *authorizationDlg = new AuthorizationDialog();
    this->setHostName(HOST_NAME);
    this->setPort(PORT);
    this->setDatabaseName(DATABASE_NAME);
    if(authorizationDlg->exec() == QDialog::Accepted){
        this->setUserName("postgres");
        this->setPassword("admin");
    }
    delete authorizationDlg;

    if(this->open()){
        return true;
    }
    else
        return false;

}
