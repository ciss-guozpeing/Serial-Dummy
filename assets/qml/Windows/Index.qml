import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

//import QtQuick.Controls 1.4
//import QtQuick.Controls.Styles 1.4
Window {
    id: rocket
    width: app.width
    height: app.height
    visible: true
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
    x: app.x
    y: app.y

    signal okClicked()

    Column {
        id: indexPage
        width: 210
        height: 400
        anchors.centerIn: parent
        spacing: app.spacing
        Text {
            id: exper_name
//            anchors {
//                horizontalCenter: indexPage.horizontalCenter
//                top: indexPage.top
//                topMargin: 8
//            }
            font.family: "Microsoft YaHei UI"
            color: Qt.rgba(101 / 255, 1, 1, 1)
            text: qsTr("高压潜水服检测试验")
            font.pointSize: 18
            verticalAlignment: Text.AlignVCenter
        }

        Rectangle {
            id: experSerial
            width: exper_name.width
            height: exper_name.height
//            anchors {
//                topMargin: 18
//                horizontalCenter: indexPage.horizontalCenter
//                top: mainPerson.bottom
//            }
            color: "lightgrey"
            border.color: "grey"
            TextInput {
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
//                anchors.margins: 2
                font.pointSize: 15
                focus: true
                inputMask: "实验编号:99999999"
                Component.onCompleted: text = getDate()
            }
        }

        TextField {
            id: mainPerson
            width: exper_name.width
            height: exper_name.height
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
//            anchors {
//                topMargin: 18
//                horizontalCenter: indexPage.horizontalCenter
//                top: exper_name.bottom
//            }
            font.pointSize: 15
            focus: true
            placeholderText: "实验人员"
            validator: RegExpValidator { regExp: /^[a-zA-Z0-9]+$/ }
        }

        TextField {
            id: waterPressure
            width: exper_name.width
            height: exper_name.height
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
//            anchors {
//                topMargin: 18
//                horizontalCenter: indexPage.horizontalCenter
//                top: experSerial.bottom
//            }
            font.pointSize: 15
            focus: true
            placeholderText: qsTr("实验水压")
        }

        Button {
            id: okbtn
            width: exper_name.width
            height: exper_name.height
//            anchors {
//                topMargin: 18
//                horizontalCenter: indexPage.horizontalCenter
//                top: waterPressure.bottom
//                bottomMargin: indexPage.height * 0.1
//            }
            text: "确认"
            onClicked: {
                // 设置软件名字
//                Cpp_CSV_Save.setSaveFileName(mainPerson.text.toString() + getDate());
                rocket.visible = 0
                rocket.opacity = 0
                app.flags = Qt.Window
                rocket.okClicked()
            }
        }
    }
    function getDate() {
        var date = new Date()
        var month = (date.getMonth() + 1).toString()
        var year = date.getFullYear().toString()
        var day = date.getDate().toString()
        var resdate = year + month + day
        console.log(resdate)
        return resdate
    }
}
