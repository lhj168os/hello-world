#include "mainwindows.h"
#include "ui_mainwindows.h"
#include "chatdialog.h"
#include "logwindows.h"
#include "userwidget.h"

MainWindows::MainWindows(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindows)
{
    ui->setupUi(this);
    this->setWindowTitle(QObject::tr("极速版QQ"));
   // this->setStyleSheet("QWidget{background-color:green;}");

    Logwindows *login = new Logwindows(this);
    connect(login, SIGNAL(userSignal(QString)), this, SLOT(getUserAccount(QString)));

    if(login->exec() == QDialog::Accepted)
    {
        loginAccount = userAccount;
        this->show();
        verticalLayout = new QVBoxLayout(ui->page_friend);
        UserFriend();
        ui->labelUser->setText(QObject::tr("  %1    ^_^").arg(myName));
        ui->label_wis->setText(QObject::tr("  %1").arg(userWisdom));
        ui->label_wis->setStyleSheet("QWidget{background-color:pink; border-radius:3px;}");
    }

}

MainWindows::~MainWindows()
{
    delete ui;
}

void MainWindows::UserFriend()
{
    if(createDBConnection())
    {
        qDebug()<< QObject::tr("Connect successful!");
    }

    QSqlQuery query;
    query.exec(QString("select account,password,ip,port,name,wisdom from user where account = '%1'").arg(userAccount));
    query.next();
    userPort = query.value(3).toInt();
    myName = query.value(4).toString();
    userWisdom = query.value(5).toString();
    query.exec("select account,password,ip,port,name,wisdom from user");
    while(query.next())
    {
        QString value0 = query.value(0).toString();
        QString value2 = query.value(2).toString();
        int value3 = query.value(3).toInt();
        QString value4 = query.value(4).toString();
        QString value5 = query.value(5).toString();
      //  qDebug()<<QObject::tr("%1\n").arg(value5);

        if(value0 == userAccount) continue;
        UserWidget *user = new UserWidget(userPort,value2,value3,value0, loginAccount, value4,myName,value5);
        user->setStyleSheet("QWidget{background-color:teal; border-radius:8px;}");
        verticalLayout->addWidget(user);
        verticalLayout->addWidget(user);
    }
    verticalLayout->addStretch(0);
}

void MainWindows::getUserAccount(QString account)
{
    userAccount = account;
}

bool MainWindows::createDBConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("UserDB.db");
    if(!db.open())
    {
        qDebug()<<QObject::tr("open database error!");
        return false;
    }
    return true;
}

void MainWindows::on_pushButton_2_clicked()
{
    this->close();
    MainWindows *w = new MainWindows();
}
