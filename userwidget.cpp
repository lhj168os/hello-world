#include "userwidget.h"
#include "ui_userwidget.h"
#include "chatdialog.h"

UserWidget::UserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWidget)
{
    ui->setupUi(this);
}

UserWidget::UserWidget(int receivePort,QString sendIp,int sendPort,QString sendAccount,QString loginAccount,QString name,QString myName,QString wisdom,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWidget)
{
    ui->setupUi(this);
    udpReceivePort = receivePort;
    udpSendIp = sendIp;
    udpSendPort = sendPort;
    udpSendAccount = sendAccount;
    loginUserAccount = loginAccount;
    userName = name;
    loginName = myName;
    userWisdom = wisdom;
    ui->label_user->setText(QObject::tr("  %1(%2)").arg(userName).arg(udpSendAccount));
    ui->label_wis->setText(QObject::tr(" 个性签名：%1").arg(userWisdom));
}

UserWidget::~UserWidget()
{
    delete ui;
}

void UserWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        chatDialog *chat = new chatDialog(udpReceivePort,udpSendIp,udpSendPort,udpSendAccount,loginUserAccount,userName,loginName);
        chat->show();
    }
}
