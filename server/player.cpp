#include "player.h"
#include "wsserver.h"
#include <QtDebug>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QFile>

QT_USE_NAMESPACE


Player::Player(QObject *parent, int _playerIndex ):
    QObject(parent), playerIndex(_playerIndex)
{
    server = qobject_cast<WsServer*>(parent);
    loadCommands();
}

void Player::loadCommands()
{
    QStringList filenames = QStringList()<<"tarmo.commands"<< "helena.commands" << "merje.commands"
                                        << "levi.commands" << "taavi.commands" << "vambola.commands";
    QString fileName = ":/command-files/"+filenames[playerIndex];
    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
       QTextStream in(&inputFile);
       int counter = 0;
       while (!in.atEnd())
       {
          QString line = in.readLine();
          QStringList fields = line.split("\t");

          if (fields.count()>=3) {
              bool intOk;
              int time = fields[0].toInt(&intOk);
              if (intOk) {
                  QString code = fields[1], command = fields[2];
				  commandHash.insert(time,  QPair <QString, QString>(code, command));
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

void Player::checkEvents()
{
	QMultiHash< int,  QPair <QString,QString> >::const_iterator foundHash = commandHash.find(server->counter);
	while (foundHash != commandHash.end() && foundHash.key() == server->counter) {
		  QPair <QString,QString> event = foundHash.value();
		  if ( !event.first.isEmpty() && !event.second.isEmpty() ) {
			  qDebug()<<QString("Saadan koodi %1 mängijale %2 löögil %3").arg(event.first).arg(playerIndex).arg(server->counter);
			  emit sendCommand(playerIndex, event.second);
			  if (server) {
				  if (server->playerSockets[playerIndex]) {
					  server->playerSockets[playerIndex]->sendTextMessage(
								  "command " + event.first); // send the code. filename is code + ".mp3"
				  }
			  }
		  }
		  ++foundHash;
	  }
/*    if (foundHash == commandHash.end()) {
		//qDebug()<< "On counter " << server->counter << " no event";
    } else {
		//QPair <QString,QString> event = foundHash.value();
		QList <QPair <QString, QString> events = foundHash.va
		if ( !event.first.isEmpty() && !event.second.isEmpty() ) {
            qDebug()<<QString("Saadan koodi %1 mängijale %2").arg(event.first).arg(playerIndex);
            emit sendCommand(playerIndex, event.second);
            if (server) {
                if (server->playerSockets[playerIndex]) {
                    server->playerSockets[playerIndex]->sendTextMessage(
                                "command " + event.first); // send the code. filename is code + ".mp3"
                }
            }
        }
    }
	*/
}

