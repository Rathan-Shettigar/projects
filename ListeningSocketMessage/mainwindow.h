/*This example is created to send and recieve max last 10 messages sent from server side
 * TCP and UDP is communication protocol is used
 *
 * TCP (Transmission Control Protocol) is a reliable, stream-oriented, connection-oriented transport protocol.
 * TCP is especially well suited for continuous transmission of data.
 *
 *UDP (User Datagram Protocol) is a lightweight, unreliable, datagram-oriented, connectionless protocol.
 *UDP can be used when reliability isn't important.
 *
 * TCP uses Valid IPv4 IP and Port.
 * UDP uses only reciever port. Continuous multiple UDP connection is not possible on same port
 *
 * Tested on Windows 10 pro 64 bit Core-i7-4600U.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QUdpSocket>
#include <QHostInfo>
#include <QMessageBox>
#include <QNetworkDatagram>
#include <QNetworkInterface>
#include <QRegularExpressionValidator>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_sendMessage_clicked();
    void on_pushButton_recieveMessage_clicked();
    void on_lineEdit_port_editingFinished();
    void on_lineEdit_IPAddress_editingFinished();
    void on_comboBox_ProtocolType_currentIndexChanged(const QString &arg1);

    void sendTCPData();
    void readTCPData();
    void readUDPData();
    void saveSentTCPData();

private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket = nullptr;
    QTcpServer *tcpServer = nullptr;
    QUdpSocket *udpSocketSender = nullptr;
    QUdpSocket *udpSocketReceiver= nullptr;
    QTcpSocket *clientConnection = nullptr;

    QString ipAddress;
    quint16 portNumber;
    QString protocolType;
    QVector<QString> messageToSend;
    QDataStream in;

    int messageCounter;
    QStringList udpMessageList;
    QStringList tcpMessageList;
    bool isTcpPreventFirstRun;

    void initUDPConnection();
    void setIPAddressFromNetwork();
    void initTCPConnection();
    void sendUDPData();
};

#endif // MAINWINDOW_H
