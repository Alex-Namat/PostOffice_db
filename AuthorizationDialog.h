#ifndef AUTHORIZATIONDIALOG_H
#define AUTHORIZATIONDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class AuthorizationDialog;
}

class AuthorizationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorizationDialog(QWidget *parent = 0);
    QString getUser() const;
    QString getPassword() const;
    virtual ~AuthorizationDialog();

public slots:
    void clickedOk();

private:
    Ui::AuthorizationDialog *ui;
    QSettings *settings;
};

#endif // AUTHORIZATIONDIALOG_H
