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
    this->setDatabaseName(QString("Driver={%1};Server={%2};Database={%3}")
                          .arg(DRIVER_NAME)
                          .arg(SERVER_NAME)
                          .arg(DATABASE_NAME));
    if(authorizationDlg->exec() == QDialog::Accepted){
        this->setUserName(authorizationDlg->getUser());
        this->setPassword(authorizationDlg->getPassword());
    }
    delete authorizationDlg;

    if(this->open()){
        return true;
    }
    else
        return false;

}
