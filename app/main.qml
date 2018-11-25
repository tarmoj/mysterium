import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2
import QtMultimedia 5.5
import QtWebSockets 1.1
import Qt.labs.settings 1.0
import Qt.labs.platform 1.0


ApplicationWindow {
    visible: true
    width: 500
    height: 400
    title: qsTr("Šamaani surm")


    Settings {
        id: settings
        property alias serverIP: socket.serverIP
        //property alias lastFile: sound.source
        //property alias lastFolder: fileDialog.folder
        property alias delay: page.delay
        property alias playerIndex: page.playerIndex
    }

    Component.onCompleted: {
        page.serverAddressField.text = socket.serverIP
        page.fileNameField.text = sound.source
        page.delaySpinbox.value = page.delay
        page.nameCombobox.currentIndex = page.playerIndex
        if (!socket.active) {
            if (page.serverAddressField.text==socket.serverIP) {
                socket.active = true
            } else {
                socket.serverIP = page.serverAddressField.text // this should activate the socket as well, since server.url is bound to serverIP
            }
        }
    }

    WebSocket {
        id: socket
        property string serverIP: "192.168.1.199"
        url: "ws://"+serverIP+":7007/ws"

        onTextMessageReceived: {
            console.log(message)
            var messageParts = message.split(" ");
            if (messageParts[0]==="command") {
                sound.source = "qrc:///commands/"+messageParts[1]+".mp3"
                console.log(sound.source)
                page.commandLabel.text = messageParts[1];
                //playTimer.start();
                sound.play()
            }
        }


        onStatusChanged: if (socket.status == WebSocket.Error) {
                             console.log("Error: " + socket.errorString)
                             socket.active = false;

                         } else if (socket.status == WebSocket.Open) {
                             console.log("Socket open")
                             socket.sendTextMessage(page.nameCombobox.currentText )
                             page.connectButton.text = "Connected"
                             page.connectButton.enabled = false
                         } else if (socket.status == WebSocket.Closed) {
                             console.log("Socket closed")
                             socket.active = false;
                             page.connectButton.text = "Connect"
                             page.connectButton.enabled = true
                         }
                         else if (socket.status == WebSocket.Connecting) {
                             console.log("Socket connecting")
                             page.connectButton.text = "Connecting"
                             //page.connectButton.enabled = false
                         }

            active: false

    }

    Timer {
        id: playTimer
        interval: page.delay
        repeat: false
        onTriggered: {console.log("Delay: ", interval); sound.play() }
    }


    Audio {
        id: sound
        property int seekPosition: 0 // in ms
        source: "qrc:///commands/YLD_01.mp3" //StandardPaths.writableLocation(7) + "/track1.mp3";  // 7- TempLocaton, see QStandardPaths must be copied there in main.cpp //
        onStatusChanged: {
            console.log("sound status: ",status)
            if (status == Audio.Loading || status == Audio.Buffering) {
                console.log("Loading")
                page.statusLabel.text = "Loading";
            }
            if (status == Audio.Loaded) {
                console.log("Loaded")
                page.statusLabel.text = "Loaded";
            }

            if (status == Audio.EndOfMedia) {
                console.log("End of Media")
                page.statusLabel.text = "End of media";
            }

        }

        onPlaybackStateChanged:  {
            if (playbackState==Audio.PlayingState)
                page.statusLabel.text = "Playing"
            if (playbackState==Audio.PausedState)
                page.statusLabel.text = "Paused"
            if (playbackState==Audio.StoppedState)
                page.statusLabel.text = "Stopped"
        }

    }

    MainForm {
        id: page;
        property string playerIndex: nameCombobox.currentIndex
        property int delay: delaySpinbox.value
        anchors.fill: parent

        playButton.onClicked: {
            sound.play()
        }
        stopButton.onClicked: {
            sound.stop()
        }

        updateButton.onClicked: {
            socket.sendTextMessage(page.nameCombobox.currentText )
        }

        connectButton.onClicked: {
            if (!socket.active) {
                if (page.serverAddressField.text==socket.serverIP) {
                    socket.active = true
                } else {
                    socket.serverIP = page.serverAddressField.text // this should activate the socket as well, since server.url is bound to serverIP
                }
                //console.log("Connecting to ",serverAddress.text, "Socket status: ", socket.status)
            }
        }
    }

}
