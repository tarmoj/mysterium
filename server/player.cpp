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
    QStringList filenames = QStringList()<<"fl.commands"<< "cl.commands" << "vl.commands"
                                        << "vlc.commands" << "pf.commands" << "perc.commands";
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
				  EventClass event;
				  event.index = counter;
				  event.code = code; event.command = command;
				  commandHash.insert(time, event);
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
	QMultiHash< int,  EventClass >::const_iterator foundHash = commandHash.find(server->counter);
	int sendNthEvent = server->everyNthCommand;
	while (foundHash != commandHash.end() && foundHash.key() && foundHash.key() == server->counter) {
		  EventClass event = foundHash.value();
		  if ( !event.code.isEmpty() && !event.command.isEmpty() && (server->counter <2 || (event.index % sendNthEvent)==0 || event.code == "YLD_40" || event.code == "PERC_12")  || event.index == 0 ) { // if less than 0 -  countdown, if over 0, send only every nth event
			  qDebug()<<QString("Saadan koodi %1 mängijale %2 löögil %3 index %4").arg(event.code).arg(playerIndex).arg(server->counter).arg(event.index);
			  emit sendCommand(playerIndex, event.command);
			  if (server) {
				  if (server->playerSockets[playerIndex]) {
					  server->playerSockets[playerIndex]->sendTextMessage(
								  "command " + event.code); // send the code. filename is code + ".mp3"
				  }
			  }
		  }
		  ++foundHash;
	  }
}

