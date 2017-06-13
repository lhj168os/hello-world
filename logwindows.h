#ifndef LOGWINDOWS_H
#define LOGWINDOWS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <QCompleter>
#include <QFont>

namespace Ui {
class Logwindows;
}

class Logwindows : public QDialog
{
    Q_OBJECT

public:
    explicit Logwindows(QWidget *parent = 0);
    ~Logwindows();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Logwindows *ui;
    bool createDBConnection();
    void createUserTable();
    bool userVerify(const QString &strAccount, const QString &strPwd);

signals:
    void userSignal(QString account);
};

#endif // LOGWINDOWS_H
