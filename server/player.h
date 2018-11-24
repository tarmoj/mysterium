#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class WsServer;


QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class Player : public QObject
{
    Q_OBJECT
public:
    Player(QObject *parent , int _playerIndex);
    //~Player();

public slots:
    void checkEvents();
    void resetEventCounter() { eventCounter = 0; }

signals:
    void sendCommand(int playerIndex, int commandNumber, QString commandString);


private:
    QList <QPair <int,int>>  events;
    int eventCounter;
    int playerIndex;
    WsServer * server;
    QStringList commands;
};

#endif // PLAYER_H
