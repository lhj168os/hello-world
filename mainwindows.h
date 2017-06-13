#ifndef MAINWINDOWS_H
#define MAINWINDOWS_H

#include <QWidget>
#include <QMouseEvent>
#include <QString>
#include <QDebug>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QPainter>

namespace Ui {
class MainWindows;
}

class MainWindows : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindows(QWidget *parent = 0);
    ~MainWindows();

private:
    Ui::MainWindows *ui;

    QString userAccount;
    QString myName;
    QString userWisdom;
    QString loginAccount;
    int userPort;

    QVBoxLayout *verticalLayout;

    bool createDBConnection();
    void UserFriend();


private slots:
    void getUserAccount(QString account);
    void on_pushButton_2_clicked();
};

#endif // MAINWINDOWS_H
