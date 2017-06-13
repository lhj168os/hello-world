#include "logwindows.h"
#include "ui_logwindows.h"

Logwindows::Logwindows(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Logwindows)
{
    ui->setupUi(this);
    ui->lineEdit_pw->setEchoMode(QLineEdit::Password);
    this->setWindowTitle(QObject::tr("登录界面"));

    if(createDBConnection())
    {
        qDebug()<<QObject::tr("Connect successful!");
    }
    createUserTable();
}

Logwindows::~Logwindows()
{
    delete ui;
}

void Logwindows::on_pushButton_clicked()
{
    QString account = ui->lineEdit_id->text();
    QString password = ui->lineEdit_pw->text();
    if(userVerify(account,password))
    {
        accept();
        emit userSignal(account);
    }
    else{
        QDialog *dialog = new QDialog(this);
        QFont font("Microsoft YaHei", 15, 25);
        dialog->setWindowTitle(QObject::tr("警告！"));
        dialog->resize(200,50);
        dialog->setModal(true);
        QLabel *label = new QLabel(dialog);
        label->setText(QObject::tr("账号或密码错误!!!\n"));
        label->setFont(font);
        dialog->show();
        ui->lineEdit_id->clear();
        ui->lineEdit_pw->clear();
    }

}

bool Logwindows::createDBConnection()
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

void Logwindows::createUserTable()
{
    QSqlQuery query;
    query.exec("create table user (account varchar(8) primary key,password varchar(8),ip varchar(16),port int,name varchar(24),wisdom varchar(56))");
    query.exec("insert into user values('0123','123','127.0.0.1',1111,'马云','你穷,是因为你没野心！')");
    query.exec("insert into user values('1234','123','127.0.0.1',2222,'马化腾','世间一切皆可山寨！')");
    query.exec("insert into user values('2345','123','127.0.0.1',3333,'李宏彦','价高者靠前！')");
    query.exec("insert into user values('3456','123','127.0.0.1',4444,'董明珠','好空调,格力造！')");
    query.exec("insert into user values('4567','123','127.0.0.1',5555,'王建林','清华北大,不如胆子大！')");
    query.exec("insert into user values('5678','123','127.0.0.1',6666,'奥巴马','No Money No Talk！')");
    query.exec("insert into user values('6789','123','127.0.0.1',7777,'习大大','功崇惟志,业广惟勤')");
    query.exec("insert into user values('7890','123','127.0.0.1',8888,'刘强东','京东奶茶,你值得拥有！')");
    query.exec("insert into user values('8901','123','127.0.0.1',9999,'毛泽东','见马克思不如来见我！')");
}

bool Logwindows::userVerify(const QString &strAccount, const QString &strPwd)
{
    QSqlQuery query;
    query.exec(QString("select * from user where account = '%1' and password = '%2'").arg(strAccount, strPwd));
    return query.next();














































}

