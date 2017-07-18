#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

#define DRIVER          "QODBC3"
#define DRIVER_NAME     "SQL Server"
#define SERVER_NAME     "NAMAT-UB"
#define DATABASE_NAME   "post_office"


class Database : public QSqlDatabase
{
public:
    Database();
    Database(const Database& other) = default;
    Database& operator =(const Database& other) = default;
    virtual ~Database();
    bool connect();
};

#endif // DATABASE_H
