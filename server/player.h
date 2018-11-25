#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QHash>

class WsServer;


QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class Player : public QObject
{
    Q_OBJECT
public:
    Player(QObject *parent , int _playerIndex);
    //~Player();
    void loadCommands();

public slots:
    void checkEvents();

signals:
    void sendCommand(int playerIndex, QString commandString);


private:
    QList <QPair <int,int>>  events;
    int playerIndex;
    WsServer * server;
    QHash <int, QPair<QString, QString> > commandHash;
};

#endif // PLAYER_H
