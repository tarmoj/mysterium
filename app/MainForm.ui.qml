import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Rectangle {
    id: ui
    property alias connectButton: connectButton
    property alias serverAddressField: serverAddressField
    property alias fileNameField: fileNameField
    property alias statusLabel: statusLabel
    property alias playButton: playButton
    property alias stopButton: stopButton
    width: 400
    height: 500
    color: "#0e4248"
    property alias commandLabel: commandLabel
    property alias nameCombobox: nameCombobox
    property alias updateButton: updateButton
    property alias delaySpinbox: delaySpinbox

    //    gradient: Gradient {
    //        GradientStop {
    //            position: 1
    //            color: "#ffffff"
    //        }
    //        GradientStop {
    //            position: 0
    //            color: "#45a916"
    //        }
    //    }
    ColumnLayout {
        id: columnLayout
        height: 177
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.topMargin: 10
        spacing: 5
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left

        Row {
            id: nameRow
            spacing: 6

            Label {
                text: "Nimi"
            }
            ComboBox {
                id: nameCombobox
                model: ["Tarmo", "Helena", "Merje", "Levi", "Taavi", "Vambola"]
            }

            Button {
                id: updateButton
                text: "Uuenda"
            }
        }

        Row {
            id: serverRow
            spacing: 6

            Label {
                id: label
                text: qsTr("Server:")
            }

            TextField {
                id: serverAddressField

                //text: qsTr("192.168.1.199")
                z: 1
            }

            Button {
                id: connectButton
                text: qsTr("Connect")
            }
        }

        Row {
            id: delayRow
            visible: false
            spacing: 6

            Label {
                text: qsTr("Delay (ms)")
            }
            ToolTip {
                text: qsTr("Delay to set incoming network calls later (for faster devices)")
            }
            SpinBox {
                id: delaySpinbox
                to: 1000
                editable: true
            }
            Button {
                text: qsTr("Reset")
                onClicked: delaySpinbox.value = 0
            }
        }

        Row {
            id: fileRow
            visible: false
            spacing: 6

            Label {
                id: label1
                text: qsTr("Clicktrack file:")
                anchors.verticalCenter: parent.verticalCenter
            }

            TextField {
                id: fileNameField
                text: qsTr("qrc:/sounds/track1.mp3")
            }
        }

        Row {
            id: playingRow
            spacing: 6

            Button {
                id: playButton
                text: qsTr("Test")
            }

            Button {
                id: stopButton
                text: qsTr("Play2")
                visible: true
            }
        }

        Row {
            id: statusRow
            width: 200
            height: 40
            spacing: 6

            Label {
                id: label2
                text: qsTr("Status:")
            }

            Label {
                id: statusLabel
                text: qsTr("Not loaded")
            }
        }

        Row {
            id: timeRow
            spacing: 6

            Label {
                id: label4
                text: qsTr("Command:")
            }

            Label {
                id: commandLabel
                text: qsTr("0")
                font.bold: true
                font.pointSize: 20
            }
        }
    }
}
