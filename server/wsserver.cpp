#include "wsserver.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>
#include "player.h"
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

//    for (int i=0;i<6;i++) {
//        players << new Player(this, i);
//        connect(players[i], SIGNAL(sendCommand(int, QString)), this, SIGNAL(sendCommand(int, QString)));
//    }
//	loadDensities();

    //TEST
//    sendCommandToPlayers("01", (quint16) 0b100000000);
//    sendCommandToPlayers("02", (quint16) 0b111111111);
//    sendCommandToPlayers("03", (quint16) 0b1);

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
   for (int i=0;i<players.count();i++) {
       players[i]->checkEvents();
   }
   //TODO: check density
   QHash< int,  int >::const_iterator foundHash = densityHash.find(counter);
   if (foundHash != densityHash.end() && foundHash.key() == counter) {
	   setDensity(foundHash.value());
	   emit newDensity(foundHash.value());
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

void WsServer::loadDensities()
{

	QString fileName = ":/command-files/density";
	QFile inputFile(fileName);
	if (inputFile.open(QIODevice::ReadOnly|QIODevice::Text))
	{
	   QTextStream in(&inputFile);
	   int counter = 0;
	   while (!in.atEnd())
	   {
		  QString line = in.readLine();
		  QStringList fields = line.split("\t");

		  if (fields.count()>=2) {
			  bool timeOk, densityOk;
			  int time = fields[0].toInt(&timeOk);
			  int density = fields[1].toInt(&densityOk);
			  if (timeOk && densityOk) {
				  densityHash.insert(time, density);
				  counter++;
			  }
		  }
	   }
	   qDebug()<<"Added " << counter << "densities";
	   inputFile.close();
	} else {
		qDebug()<<"Could not open file " <<fileName;
   }
}

void WsServer::setDensity(int density)
{
	if (density>0 && density <= 12) {
		everyNthCommand = density;
		qDebug() << "Setting density to " << everyNthCommand;
	} else {
		qDebug() << "Illegal density value: " << density;
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


