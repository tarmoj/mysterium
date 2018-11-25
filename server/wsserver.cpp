#include "wsserver.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>
#include "player.h"



QT_USE_NAMESPACE



WsServer::WsServer(quint16 port, QObject *parent) :
    QObject(parent),
    counter(0),
	m_pWebSocketServer(new QWebSocketServer(QStringLiteral("BreathServer"),
                                            QWebSocketServer::NonSecureMode, this)),
    m_clients()
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        qDebug() << "WsServer listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &WsServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &WsServer::closed);
	}

    playerSockets << nullptr << nullptr << nullptr << nullptr << nullptr << nullptr;
    connect(&timer, SIGNAL(timeout()), this, SLOT(counterChanged()) );
    for (int i=0;i<6;i++) {
        players << new Player(this, i);
        connect(players[i], SIGNAL(sendCommand(int, QString)), this, SIGNAL(sendCommand(int, QString)));
    }


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
    if (messageParts[0].toLower()=="tarmo") {
        playerSockets[TARMO] = pClient;
    }
    if (messageParts[0].toLower()=="helena") {
        playerSockets[HELENA] = pClient;
    }
    if (messageParts[0].toLower()=="merje") {
        playerSockets[MERJE] = pClient;
    }
    if (messageParts[0].toLower()=="levi") {
        playerSockets[LEVI] = pClient;
    }
    if (messageParts[0].toLower()=="taavi") {
        playerSockets[TAAVI] = pClient;
    }
    if (messageParts[0].toLower()=="vambola") {
        playerSockets[VAMBOLA] = pClient;
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

void WsServer::counterChanged()
{
   counter++;
   emit newCounter(counter);
   for (int i=0;i<players.count();i++) {
       players[i]->checkEvents();
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


