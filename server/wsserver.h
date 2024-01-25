#ifndef WSSERVER_H
#define WSSERVER_H

#include <QObject>
#include <QtCore/QList>
#include <QTimer>
#include "player.h"


QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

#define JAAN 8  // highest bit in binary code
#define NOORA 7
#define ANDRUS 6
#define INDREK 5
#define HANS 4
#define GERHARD 3
#define KAI 2
#define KENNETH 1
#define KYLLI 0 // lowest bit in binary code


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
    void sendCommandToPlayers(QString command, quint16 players);
    void loadCommandInfo();

    QTimer timer;
    int counter;
	int everyNthCommand;
    QList <QWebSocket *> playerSockets;  // used by indexes -  0 FL, 1- CL, etc

    QStringList const names = QStringList() << "Külli" <<  "Kenneth" <<  "Kai" << "Gerhard" << "Hans" << "Indrek" << "Andrus" << "Noora" << "Jaan";



Q_SIGNALS:
    void closed();
    void newConnection(int connectionsCount);
    void newCounter(int counter);
    void sendCommand(int playerIndex, QString commandString);
    //void newDensity(int density);

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
	//void processBinaryMessage(QByteArray message);
    void socketDisconnected();
    void counterChanged();

private:
    class Event {
    public:
        int time;
        int commandNumber;
        quint16 playerFlags;
    };

    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    QList <Player *> players;
    //QHash <int, int> densityHash;
    QList <Event> events;



};



#endif // WSSERVER_H
