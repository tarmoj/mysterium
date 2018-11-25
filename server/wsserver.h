#ifndef WSSERVER_H
#define WSSERVER_H

#include <QObject>
#include <QtCore/QList>
#include <QTimer>
#include "player.h"

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

#define TARMO 0
#define HELENA 1
#define MERJE 1
#define LEVI 1
#define TAAVI 5
#define VAMBOLA 6


class Player;


class WsServer : public QObject
{
    Q_OBJECT
public:
    explicit WsServer(quint16 port, QObject *parent = NULL);
    ~WsServer();

	void sendToAll(QString message);
    void resetEventCounters();
    QTimer timer;
    int counter;
    QList <QWebSocket *> playerSockets;  // used by indexes -  0 FL, 1- CL, etc



Q_SIGNALS:
    void closed();
    void newConnection(int connectionsCount);
    void newCounter(int counter);
    void sendCommand(int playerIndex, QString commandString);

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
	//void processBinaryMessage(QByteArray message);
    void socketDisconnected();
    void counterChanged();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    QList <Player *> players;


};



#endif // WSSERVER_H
