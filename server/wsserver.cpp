#include "wsserver.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>
//#include "player.h"
#include <QFile>
#include <QtMath>



QT_USE_NAMESPACE



WsServer::WsServer(quint16 port, QObject *parent) :
    QObject(parent),
	counter(-10),
	everyNthCommand(1),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("MysteriumServer"),
                                            QWebSocketServer::NonSecureMode, this)),
    m_clients()
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        qDebug() << "WsServer listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &WsServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &WsServer::closed);
	}

    connect(&timer, SIGNAL(timeout()), this, SLOT(counterChanged()) );

    for (int i = 0; i < names.count(); i++) {
        playerSockets.append(nullptr);
    }

    loadCommandInfo();


}



WsServer::~WsServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}


void WsServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &WsServer::processTextMessage);
	//connect(pSocket, &QWebSocket::binaryMessageReceived, this, &WsServer::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &WsServer::socketDisconnected);

    m_clients << pSocket;

    emit newConnection(m_clients.count());
}

void WsServer::processTextMessage(QString message) // message must be an array of numbers (8bit), separated with colons
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (!pClient) {
        return;
    }

	qDebug()<<"Message received: "<<message;
	QStringList messageParts = message.split(",");

    if (messageParts[0].toLower()=="here" && messageParts.count()>1) {
        QString name = messageParts[1];
        int index = names.indexOf(name);
        if (index>=0) {
            // check if that socket was assigned to another player before (if changed from the menu)
            int playerIndex = playerSockets.indexOf(pClient);
            if (playerIndex>=0) { // remove the old one if player changed the name
                playerSockets[playerIndex] = nullptr;
            }
            qDebug() << name << " connected.";
            playerSockets[index] = pClient;
        } else {
            qDebug() << "Unknown player " << name;
        }

    }

}


void WsServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient) {
        int index = playerSockets.indexOf(pClient);
        if (index>=0) {
            playerSockets[index] = nullptr; // probably crash if it disconnects exatly when message is being sent. Not likely
        }
        m_clients.removeAll(pClient);
        emit newConnection(m_clients.count());
        pClient->deleteLater();
    }
}

void WsServer::counterChanged() // timer timeOut slot
{
    counter++;
    emit newCounter(counter);
    for (Event const &event: events) {
        if (event.time == counter) {
            sendCommandToPlayers(event.command, event.playerFlags);
        }
    }




}


void WsServer::sendToAll(QString message )
{

	foreach(QWebSocket *socket, m_clients) {
		if (socket)
		{
			socket->sendTextMessage(message);
		}
	}
}


void WsServer::sendCommandToPlayers(QString command, quint16 players)
{
    for (int i=0; i<names.count(); i++) {
        quint16 bitmask = 1 << i;
        if (players & bitmask) { // check if the according bit is set
          qDebug() << "Player " << names[i] << "gets command: " << command;
          emit sendCommand(i, command); // for UI
          if (playerSockets[i]) {
            playerSockets[i]->sendTextMessage("command "+command);
          } else {
            qDebug() << names[i] << " seems not to be conncted";
          }

        }
    }
}

void WsServer::loadCommandInfo()
{
    QString fileName = ":/command-files/syrr.commands";
    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        events.clear();
        QTextStream in(&inputFile);
        int counter = 0;
        while (!in.atEnd())
        {
          QString line = in.readLine();
          QStringList fields = line.split(QRegExp("\\s+"), Qt::SkipEmptyParts);

          if (fields.count()>=3) {
            bool ok1, ok2, ok3;
            int commandNumber = fields[0].toInt(&ok1);
            int time = fields[1].toInt(&ok2);
            quint16 playerFlags = static_cast<quint16>(fields[2].toInt(&ok3, 2));
            if (ok1 && ok2 && ok3) {
                Event event;
                event.command = QString::number(commandNumber).rightJustified(2, '0'); ;
                event.time = time;
                event.playerFlags = playerFlags;
                events.append(event);
                counter++;
            }
          }
        }
        qDebug()<<"Added " << counter << "commands";
        inputFile.close();
    } else {
        qDebug()<<"Could not open file " <<fileName;
    }
}


