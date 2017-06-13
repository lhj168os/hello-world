#include "chatdialog.h"
#include "ui_chatdialog.h"

chatDialog::chatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatDialog)
{
    ui->setupUi(this);
}

chatDialog::chatDialog(int receivePort, QString sendIp, int sendPort, QString sendAccount,QString loginAccount,QString name,QString myName,QWidget *parent):
    QDialog(parent),
    ui(new Ui::chatDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(QObject::tr("聊天界面"));
    this->setFixedSize(400,410);          //设置刚开始的聊天界面大小,以隐藏聊天记录页面
    receiver = new QUdpSocket(this);
                                                                 udpReceivePort = receivePort;
    receiver->bind(udpReceivePort, QUdpSocket::ShareAddress);
    connect(receiver, &QUdpSocket::readyRead, this, &chatDialog::processPendingDatagram);

    sender = new QUdpSocket(this);
    udpSendIp = sendIp;
    udpSendPort = sendPort;
    udpSendAccount = sendAccount;
    loginUserAccount = loginAccount;
    userName = name;
    loginName = myName;
    ui->label_name->setText(QObject::tr("%1").arg(userName));
}

chatDialog::~chatDialog()
{
    delete ui;
}

void chatDialog::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier)
    {
        if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        {
            if(event->isAutoRepeat()) return;
            on_pushButton_send_clicked();
        }
    }
}

void chatDialog::on_pushButton_send_clicked()
{
    if(!QString(ui->textEdit->toPlainText()).isEmpty()){
        QDateTime currentTime = QDateTime::currentDateTime();
        QString strData = currentTime.toString("【%1】：（yyyy-MM-dd hh:mm:ss）\n").arg(loginName).arg(loginUserAccount);

        QByteArray datagram = strData.toUtf8();
        datagram += ui->textEdit->toPlainText().toUtf8();
        datagram += "\n";
        ui->listWidget->addItem(datagram);
        ui->listWidget->setCurrentRow(ui->listWidget->count()-1);

        sender->writeDatagram(datagram.data(), datagram.size(),
                              QHostAddress(udpSendIp), udpSendPort);


        QDir userDir(QDir::currentPath());
        userDir.mkdir(QString("logDir%1").arg(loginUserAccount));
        userDir.cd(QString("logDir%1").arg(loginUserAccount));
        QFile file(userDir.absolutePath() + QString("/%1.txt").arg(udpSendAccount));
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
            qDebug() << file.errorString();
        file.write(datagram);
        file.close();
        ui->textEdit->setText("");
    }else{
        QDialog *dialog = new QDialog(this);
        QFont font("Microsoft YaHei", 15, 25);
        dialog->setWindowTitle(QObject::tr("提示！"));
        dialog->resize(200,50);
        dialog->setModal(true);
        QLabel *label = new QLabel(dialog);
        label->setText(QObject::tr("发送消息不能为空!!!\n"));
        label->setFont(font);
        dialog->show();
    }
}

void chatDialog::on_pushButton_close_clicked()
{
    close();
}


void chatDialog::processPendingDatagram()
{
    // 拥有等待的数据报
    while(receiver->hasPendingDatagrams())
    {
        QByteArray datagram;

        // 让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
        datagram.resize(receiver->pendingDatagramSize());

        // datagram用于接收数据报
        receiver->readDatagram(datagram.data(), datagram.size());
        ui->listWidget->addItem(datagram);
        ui->listWidget->setCurrentRow(ui->listWidget->count()-1);

        QDir userDir(QDir::currentPath());
        userDir.mkdir(QString("logDir%1").arg(loginUserAccount));
        userDir.cd(QString("logDir%1").arg(loginUserAccount));
        QFile file(userDir.absolutePath() + QString("/%1.txt").arg(udpSendAccount));
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
            qDebug() << file.errorString();
        file.write(datagram);
        file.close();
    }
}


void chatDialog::on_pushButton_chatlog_toggled(bool checked)
{
    ui->textEdit_2->setVisible(checked);
    if(checked)
    {
        this->setFixedSize(688,410);
        QDir userDir(QDir::currentPath());
        userDir.mkdir(QString("logDir%1").arg(loginUserAccount));
        userDir.cd(QString("logDir%1").arg(loginUserAccount));
        QFile file(userDir.absolutePath() + QObject::tr("/%1.txt").arg(udpSendAccount));
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
          qDebug() << file.errorString();

        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QByteArray line = file.readAll();
        QString temp = codec->toUnicode(line);
        ui->textEdit_2->setText(temp);
        file.close();
    }
    else{
        this->setFixedSize(400,410);
    }
}
