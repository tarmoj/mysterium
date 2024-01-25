import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2
import QtMultimedia 5.5
import QtWebSockets 1.1
import Qt.labs.settings 1.0
import Qt.labs.platform 1.0


ApplicationWindow {
    id: window
    visible: true
    width: 500
    height: 400
    title: qsTr("Sürrealism 100")
    property string language: "est"  // "est" | "eng"

    function getSoundUrl(command) {
        var url =  "qrc:///commands/syrr/" + command + ".mp3";
        console.log("getSoundUrl: ", url);
        return url;
    }

    function playOnFirstFreeAudio(file) {
        var player = sound;
        if (sound.playbackState === Audio.PlayingState ) {
            console.log("sound playing")
            player = sound2
            if (sound2.playbackState === Audio.PlayingState ) {
                console.log("sound2 playing")
                player = sound3
                if (sound3.playbackState === Audio.PlayingState) {
                    console.log("sound3 playing too, no free audio object...")
                    return
                }
            }

        } else {
            console.log("sound not playing")
        }
        console.log("to play: ", file);
        player.source =file
        player.play()
    }


    Settings {
        id: settings
        property alias serverIP: socket.serverIP
        property alias language: window.language
        //property alias lastFile: sound.source
        //property alias lastFolder: fileDialog.folder
        property alias delay: page.delay
        property alias playerIndex: page.playerIndex
    }

    Component.onCompleted: {
        page.serverAddressField.text = socket.serverIP
        page.fileNameField.text = sound.source
        page.delaySpinbox.value = page.delay
        page.playerComboBox.currentIndex = page.playerIndex
        page.languageComboBox.currentIndex = page.languageComboBox.model.indexOf(window.language) //  (window.language=="est") ? 0 : 1 // should use somehow indexOf model // not certain if this is correct ...
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
                var command =messageParts[1];
                console.log(command)
                page.commandLabel.text = command;
                playOnFirstFreeAudio(getSoundUrl(command))
            }
        }


        onStatusChanged: if (socket.status == WebSocket.Error) {
                             console.log("Error: " + socket.errorString)
                             socket.active = false;

                         } else if (socket.status == WebSocket.Open) {
                             console.log("Socket open")
                             socket.sendTextMessage("here,"+page.playerComboBox.currentText )
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



    Audio {
        id: sound
        property int seekPosition: 0 // in ms
        source: getSoundUrl("01");
        //autoPlay: true
    }

    Audio {
        id: sound2
        source:getSoundUrl("02");
    }

    Audio {
        id: sound3
        //source: "qrc:///commands/YLD_05.mp3"
    }
    SwipeView {
        anchors.fill:parent
        currentIndex: 1

        Page {
            MainForm {
                id: page;
                property string playerIndex: playerComboBox.currentIndex
                property int delay: delaySpinbox.value

                anchors.fill: parent

                playButton.onClicked: {
                    playOnFirstFreeAudio(getSoundUrl("01"))
                }

                stopButton.onClicked: {
                    playOnFirstFreeAudio(getSoundUrl("02"))
                }

                updateButton.onClicked: {
                    socket.sendTextMessage("here,"+page.playerComboBox.currentText )
                }

                languageComboBox.onCurrentTextChanged: {
                    window.language = page.languageComboBox.currentText
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

        Page {
            Rectangle {
                anchors.fill: parent
                color:
                    "#304d4b"
            }

            Label {
                id: connectedLabel2
                text: (socket.status == WebSocket.Open) ? qsTr("Connected") : qsTr("Not connected")
            }

            Label {
                anchors.centerIn: parent
                text: page.commandLabel.text
                font.pointSize: 32
            }

        }
    }

}
