#include "wsserver.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>




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
        //create commmand lists etc in the constructor of Player
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

void WsServer::resetEventCounters()
{
    for (Player * player: players ) {
        player->resetEventCounter();
    }
}


Player::Player(QObject *parent, int _playerIndex ):
    QObject(parent), eventCounter(0), playerIndex(_playerIndex)
{
    server = qobject_cast<WsServer*>(parent);

    events << qMakePair(2,1) << qMakePair(4,2) << qMakePair(6,3) << qMakePair(10,4)
            << qMakePair(12,1) << qMakePair(14,2) << qMakePair(16,3) << qMakePair(20,4)
             << qMakePair(22,1) << qMakePair(24,2) << qMakePair(26,3) << qMakePair(30,4)
             << qMakePair(-1, -1);

    commands << "Hüppa" << "Puhu" << "Seisa" << "Ehita";
}

void Player::checkEvents()
{
    // hm -  kui mainwindow seab counteri, kas uus aeg on juba seatud, kui see siin käivitub?
    // karta on, et see varem, kui counter uueks seatud...
    // võibolla siiski ainult üks ühendus timerist ühe sloti külge, mis käivitab kõigi playerite checkEvendid...
    // kõige õigem, kui taimeri SLOT jookseb serveri threadis, mitte UI threadis... aga võibolla pole vahet.
    //
    if ( eventCounter<events.size()-1 ) { // last one not fired?
        while (server->counter == events[eventCounter].first) { // since there can be several command on one beat
            // first -  time, second, command
            //emit sendCommand(playerIndex, events[eventCounter].second, commands[events[eventCounter].second]);
            int time = events[eventCounter].first, command =  events[eventCounter].second;
            qDebug()<<QString("Saadan koodi %1 mängijale %2").arg(events[eventCounter].second).arg(playerIndex);
            if (server) {
                if (server->playerSockets[playerIndex]) {
                    server->playerSockets[playerIndex]->sendTextMessage(
                                "command " + QString::number(events[eventCounter].second));

                }

            }
            eventCounter++;
        }
    }

}
