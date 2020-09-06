#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Set IPv4 address from the network. By default it sets one IPv4 from list
    //Else TCP comunication is not possible.
    //Manual setting of IP may fail if it is not in the network IPv4 list
    setIPAddressFromNetwork();

    //Initialise TCP connection
    initTCPConnection();

    //Valid Port validation from 1-65535
    ui->lineEdit_port->setValidator(new QIntValidator(1, 65535, this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::initTCPConnection
 * Initialise TCP Connection
 */
void MainWindow::initTCPConnection()
{
    protocolType = "TCP";
    messageCounter = 0;
    tcpMessageList.clear();
    messageToSend.clear();
    isTcpPreventFirstRun = true;

    tcpSocket = new QTcpSocket(this);
    tcpServer = new QTcpServer(this);
    clientConnection = new  QTcpSocket(this);
    if (!tcpServer->listen())
    {
        QMessageBox::critical(this, tr("TCP"),tr("Unable to start the server: %1.").arg(tcpServer->errorString()));
    }

    //Fetch IP from server for new connection
    if(isTcpPreventFirstRun)
    {
        portNumber = tcpServer->serverPort();
    }
    ui->lineEdit_port->setText(QString::number(portNumber));

    tcpSocket->connectToHost(ipAddress,portNumber);
    connect(tcpServer, &QTcpServer::newConnection, this, &MainWindow::sendTCPData);
    connect(tcpSocket, &QIODevice::readyRead, this, &MainWindow::saveSentTCPData);

    //Data stream initialisation
    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_5_10);

    ui->statusBar->showMessage("TCP Connection Restored",1000);
}

/**
 * @brief MainWindow::initUDPConnection
 * Initialise UDP Connection
 */
void MainWindow::initUDPConnection()
{
    udpMessageList.clear();

    //Multiple UDP multiple connection simultaneously to same port is possible .
    //increment by 1 for every new connection
    portNumber = portNumber + 1;
    ui->lineEdit_port->setText(QString::number(portNumber));
    messageCounter = 0;

    protocolType = "UDP";
    //Socket initialisation
    udpSocketSender = new QUdpSocket(this);
    udpSocketReceiver = new QUdpSocket(this);
    udpSocketReceiver->bind(portNumber,QUdpSocket::ShareAddress);

    ui->statusBar->showMessage("UDP Connection Restored",1000);
}

/**
 * @brief MainWindow::on_pushButton_sendMessage_clicked
 * Send TCP or UDP message
 */
void MainWindow::on_pushButton_sendMessage_clicked()
{
    if(protocolType == "TCP")
    {
        sendTCPData();
    }
    else
    {
        sendUDPData();
    }
}

/**
 * @brief MainWindow::on_pushButton_recieveMessage_clicked
 * Recieve TCP or UDP message
 */
void MainWindow::on_pushButton_recieveMessage_clicked()
{
    if(protocolType == "TCP")
    {
        readTCPData();
    }
    else
    {
        readUDPData();
    }
}

/**
 * @brief MainWindow::sendTCPData
 * Sends TCP Message
 */
void MainWindow::sendTCPData()
{
    //Prepare input data stream
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    //Send message
    if(!ui->lineEdit_messageToSend->text().isEmpty() && !isTcpPreventFirstRun)
    {
        messageToSend << ui->lineEdit_messageToSend->text();
        out << messageToSend[messageCounter];
        messageCounter++;
    }
    else
    {
        if(!isTcpPreventFirstRun)
            QMessageBox::warning(this, tr("TCP"),tr("No Messages to send"));
        isTcpPreventFirstRun = false;
    }

    //check for next pending condition
    if(tcpServer->hasPendingConnections())
    {
        clientConnection = tcpServer->nextPendingConnection();
    }

    //check for valid connection
    if(clientConnection->isValid())
    {
        clientConnection->write(block);
    }
    else
    {
        QMessageBox::warning(this, tr("TCP"),tr("Check the connection"));
    }
}

/**
 * @brief MainWindow::readTCPData
 * Read TCP message
 */
void MainWindow::readTCPData()
{
    QStringList strList ;
    //Display last 10 message
    for (int messageCount = tcpMessageList.count() -1 ; messageCount >= 0; messageCount--)
    {
        if(strList.count() <10)
            strList.append( tcpMessageList.at(messageCount));
    }

    //Parse message to display in message box
    QString str = "";
    for(int i=0; i < strList.count(); i++)
    {
        str.append(strList.at(i) + "\n");
    }
    if(strList.count() > 0)
    {
        QMessageBox::information(this, "TCP Read", str);
    }
    else
    {
        QMessageBox::information(this, "TCP Read", "No messages to show");
    }

    tcpMessageList.clear();
}

/**
 * @brief MainWindow::saveSentTCPData
 * Save read messages
 */
void MainWindow::saveSentTCPData()
{
    in.startTransaction();
    QString inMessage;
    in >> inMessage;
    //Save messages to a list
    if(!inMessage.isEmpty())
    {
        tcpMessageList.append(inMessage);
        QString statusMessage= "Sent message count : " + QString::number(tcpMessageList.count());
        ui->statusBar->showMessage(statusMessage,1000);
    }
}

/**
 * @brief MainWindow::sendUDPData
 * Send UDP message
 */
void MainWindow::sendUDPData()
{
    QByteArray datagram = ui->lineEdit_messageToSend->text().toUtf8();
    udpSocketSender->writeDatagram(datagram, QHostAddress::Broadcast, portNumber);

    messageCounter++;
    QString statusMessage= "Sent message count : " + QString::number(messageCounter);
    ui->statusBar->showMessage(statusMessage,1000);
}

/**
 * @brief MainWindow::readUDPData
 * Read UDP message
 */
void MainWindow::readUDPData()
{
    QByteArray datagram;
    udpMessageList.clear();
    messageCounter = 0 ;

    //Check for any pending datagrams
    while (udpSocketReceiver->hasPendingDatagrams())
    {
        datagram.resize(int(udpSocketReceiver->pendingDatagramSize()));
        udpSocketReceiver->readDatagram(datagram.data(), datagram.size());
        udpMessageList<< datagram.constData();
    }
    //Collect data in a list
    QStringList strList ;
    for (int messageCount = udpMessageList.count() -1 ; messageCount >= 0; messageCount--)
    {
        if(strList.count() <10)
            strList.append( udpMessageList.at(messageCount));
    }

    //Display messages in a list
    QString str = "";
    for(int i=0; i < strList.count(); i++)
    {
        str.append(strList.at(i) + "\n");
    }
    if(strList.count() > 0)
    {
        QMessageBox::information(this, "UDP Read", str);
    }
    else
    {
        QMessageBox::information(this,  "UDP Read", "No messages to show");
    }
}

/**
 * @brief MainWindow::setIPAddressFromNetwork
 * Set the first avaliable IPv4 IP address.
 * If no address then displays error message
 * IP validation is handled
 * If no IPv4 address then TCP communication is not possible
 */
void MainWindow::setIPAddressFromNetwork()
{
    QString locIPAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address())
        {
            locIPAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    if(locIPAddress.isEmpty())
    {
        QMessageBox::critical(this, tr("Communication"),tr("Unable to fetch IP address."));
    }

    //IP validation on line edit
    QString IpRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegularExpression IpRegex ("^" + IpRange
                                + "(\\." + IpRange + ")"
                                + "(\\." + IpRange + ")"
                                + "(\\." + IpRange + ")$");
    QRegularExpressionValidator *ipValidator = new QRegularExpressionValidator(IpRegex, this);
    ui->lineEdit_IPAddress->setValidator(ipValidator);

    ui->lineEdit_IPAddress->setText(locIPAddress);
    ipAddress = ui->lineEdit_IPAddress->text();
}

/**
 * @brief MainWindow::on_lineEdit_port_editingFinished
 * Reset the connection with new port number
 */
void MainWindow::on_lineEdit_port_editingFinished()
{
    portNumber = static_cast<quint16>(ui->lineEdit_port->text().toUInt());
    if(protocolType == "TCP")
    {
        isTcpPreventFirstRun = false;
        tcpSocket->disconnectFromHost();
        tcpSocket->abort();
        tcpSocket->deleteLater();
        tcpServer->deleteLater();
        initTCPConnection();

        QString statusMessage= "Resetting to TCP Server port else TCP connection fails" ;
        QMessageBox::warning(this, tr("TCP"),statusMessage);
    }
    else
    {
        udpSocketSender->disconnectFromHost();
        udpSocketSender->abort();
        udpSocketSender->deleteLater();

        udpSocketReceiver->disconnectFromHost();
        udpSocketReceiver->abort();
        udpSocketReceiver->deleteLater();

        initUDPConnection();
    }
}

/**
 * @brief MainWindow::on_lineEdit_IPAddress_editingFinished
 *  Reset the connection with new IP Address
 */
void MainWindow::on_lineEdit_IPAddress_editingFinished()
{
    ipAddress = ui->lineEdit_IPAddress->text();
    if(protocolType == "TCP")
    {
        isTcpPreventFirstRun = false;
        tcpSocket->disconnectFromHost();
        tcpSocket->abort();
        tcpSocket->deleteLater();
        tcpServer->deleteLater();
        initTCPConnection();
    }
    else
    {
        udpSocketSender->disconnectFromHost();
        udpSocketSender->abort();
        udpSocketSender->deleteLater();

        udpSocketReceiver->disconnectFromHost();
        udpSocketReceiver->abort();
        udpSocketReceiver->deleteLater();
        initUDPConnection();
    }
}

/**
 * @brief MainWindow::on_comboBox_ProtocolType_currentIndexChanged
 * @param arg1 - String of selection
 */
void MainWindow::on_comboBox_ProtocolType_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "TCP")
    {
        initTCPConnection();
    }
    else
    {
        initUDPConnection();
    }
}


