#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>

namespace Ui {
class UserWidget;
}

class UserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserWidget(QWidget *parent = 0);
    explicit UserWidget(int receivePort,QString sendIp ,int sendPort,QString sendAccount,QString loginAccount,QString name,QString myName,QString wisdom,QWidget *parent = 0);
    ~UserWidget();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);


private:
    Ui::UserWidget *ui;
    QString udpSendIp;
    int udpSendPort;
    int udpReceivePort;
    QString loginUserAccount;
    QString udpSendAccount;
    QString userName;
    QString loginName;
    QString userWisdom;
};

#endif // USERWIDGET_H
