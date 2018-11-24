#include "player.h"
#include "wsserver.h"
#include <QtDebug>
#include <QWebSocketServer>
#include <QWebSocket>

QT_USE_NAMESPACE


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
   if ( eventCounter<events.size()-1 ) { // last one not fired?
        while (server->counter == events[eventCounter].first) { // since there can be several command on one beat
            // first -  time, second, command
            //emit sendCommand(playerIndex, events[eventCounter].second, commands[events[eventCounter].second]);
            //int time = events[eventCounter].first, command =  events[eventCounter].second;
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

