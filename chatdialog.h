#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include <QtNetwork>
#include <QDateTime>
#include <QString>
#include <QDir>
#include <QFile>
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class chatDialog;
}

class chatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit chatDialog(QWidget *parent = 0);
    explicit chatDialog(int receivePort,QString sendIp,int sendPort,QString sendAccount,QString loginAccount,QString Name,QString myName,QWidget *parent = 0);
    ~chatDialog();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_pushButton_send_clicked();

    void on_pushButton_close_clicked();

    void processPendingDatagram();

    void on_pushButton_chatlog_toggled(bool checked);

private:
    Ui::chatDialog *ui;
    QUdpSocket *receiver;
    QUdpSocket *sender;
    QString udpSendAccount;
    QString loginUserAccount;
    QString userName;
    QString loginName;
    QString udpSendIp;
    int udpSendPort;
    int udpReceivePort;
};

#endif // CHATDIALOG_H
