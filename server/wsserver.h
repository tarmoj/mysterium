#ifndef WSSERVER_H
#define WSSERVER_H

#include <QObject>
#include <QtCore/QList>
#include <QTimer>
#include "player.h"


QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

#define FLUTE 0
#define CLARINET 1
#define VIOLIN 2
#define CELLO 3
#define PIANO 4
#define PERCUSSION 5


class Player;


class WsServer : public QObject
{
    Q_OBJECT
public:
    explicit WsServer(quint16 port, QObject *parent = NULL);
    ~WsServer();

	void sendToAll(QString message);
    void resetEventCounters();
	void loadDensities();
	void setDensity(int density);
	QTimer timer;
    int counter;
	int everyNthCommand;
    QList <QWebSocket *> playerSockets;  // used by indexes -  0 FL, 1- CL, etc



Q_SIGNALS:
    void closed();
    void newConnection(int connectionsCount);
    void newCounter(int counter);
    void sendCommand(int playerIndex, QString commandString);
	void newDensity(int density);

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
	QHash <int, int> densityHash;


};



#endif // WSSERVER_H
