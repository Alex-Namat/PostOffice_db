#ifndef AUTHORIZATIONDIALOG_H
#define AUTHORIZATIONDIALOG_H

#include <QDialog>
#include <QSettings>
#include "simplecrypt.h"

namespace Ui {
class AuthorizationDialog;
}

class AuthorizationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorizationDialog(QWidget *parent = 0);
    ~AuthorizationDialog();
    QString getDatabaseName() const;
    QString getHost() const;
    int getPort() const;
    QString getUser() const;
    QString getPassword() const;

signals:
    void sendConnectionSetings(QMap<QString, QString> settings);

public slots:
    void clickedOk();

private:
    Ui::AuthorizationDialog *ui;
    QSettings settings;
    SimpleCrypt crypt;
};

#endif // AUTHORIZATIONDIALOG_H
