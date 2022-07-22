import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

import "../Widgets" as Widgets
import "../Widgets/Table" as Table

import SerialStudio 1.0

Control {
    id: root
    property int tempIndex: 0
    property var oldTempArray: []

    background: Rectangle {
        color: app.windowBackgroundColor
    }

    Component.onCompleted: {
        constPower.visible = false
    }

    Connections {
        target: Cpp_UI_DrawCurve
        function onSendCurTableTemp() {
            var temps = Cpp_UI_DrawCurve.curTableTemp
            curTemp.setTableData(temps)
        }
    }
    Connections {
        target: Cpp_UI_DrawCurve
        function onSendLeakageDetection() {
            var leakageDetections = Cpp_UI_DrawCurve.leakageDetection
            leakageDetection.setTableData(leakageDetections)
        }
    }

    RowLayout {
        x: 2 * app.spacing
        spacing: app.spacing
        Layout.fillWidth: true
        Layout.fillHeight: true
        anchors.fill: parent
        anchors.margins: app.spacing * 1.5
        Widgets.Window {
            id: view
            gradient: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: curTemp.width + 2 * (app.spacing * 1.5)
            Layout.maximumWidth: curTemp.width + 2 * (app.spacing * 1.5)
            backgroundColor: "#121218"
            headerDoubleClickEnabled: false
            icon.source: "qrc:/icons/scatter-plot.svg"
            title: qsTr("数据")
            Column {
                anchors.fill: parent
                spacing: app.spacing / 2
                anchors.margins: app.spacing * 1.5
                Layout.fillHeight: true
                Layout.fillWidth: true

                Row {
                    height: 30
                    Layout.fillWidth: true
                    TabBar {
                        id: tab
                        height: 30
                        Layout.fillWidth: true
                        onCurrentIndexChanged: {

                        }
                        TabButton {
                            text: qsTr("温度控制模式")
                            height: tab.height + 3
                            width: implicitWidth + 2 * app.spacing
                            onClicked: {
                                destTemp.visible = true
                                constPower.visible = false
                            }
                        }

                        TabButton {
                            text: qsTr("恒功率模式")
                            height: tab.height + 3
                            width: implicitWidth + 2 * app.spacing
                            onClicked: {
                                constPower.visible = true
                                destTemp.visible = false
                            }
                        }
                    }
                    Rectangle {
                        id: allRect
                        Layout.fillWidth: true
                        height: 40
                        width: 100
                        color: app.windowBackgroundColor
                        Button {
                            id: allSelectBtn
                            anchors.right: parent.right
                            text: "全选"
                            onClicked: {
                                let data = []
                                let tableData = destTemp.getTableData()
                                for (var x = 0; x < tableData.length; x++) {
                                    for (var j = 0; j < tableData[x].length; j++) {
                                        data.push(tableData[x][j])
                                    }
                                }
                                var diffArray = allRect.getArrDifference(root.oldTempArray,data)

                                let allSelArr= []
                                for(let i=0; i<29; i++){
                                    allSelArr.push(diffArray[0])
                                }

                                destTemp.setTableData(allSelArr)
                                root.oldTempArray = data
                            }
                        }
                        function getArrDifference(arr1, arr2) {
                            return arr1.concat(arr2).filter(function(v, i, arr) {
                              return arr.indexOf(v) === arr.lastIndexOf(v);
                            });
                          }
                    }

                    Rectangle {
                        id: btnrect
                        Layout.fillWidth: true
                        height: 40
                        width: 100
                        color: app.windowBackgroundColor
                        Button {
                            id: okbtn
                            anchors.right: parent.right
                            text: "确认"
                            onClicked: {
                                if (constPower.visible) {
                                    var data = getConstPowerData()
                                    var constPowerValue = 'ConstantPower:' + data
                                    console.log(constPowerValue)
                                    Cpp_UI_FormData.sendTemps(constPowerValue)
                                }
                                if (destTemp.visible) {
                                    let tempData = getDestTempData()
                                    console.log(tempData)
                                    Cpp_UI_FormData.sendTemps(tempData)
                                }
                            }
                        }
                    }
                }

                ScrollView {
                    width: parent.width
                    height: parent.height - tab.height
                    clip: true
                    RegExpValidator {
                        id: regExpValue1
                        regExp: /[0-9][0-9].[0-9]/
                    }
                    RegExpValidator {
                        id: regExpValue2
                        regExp: /[0-9][0-9][0-9][0-9]/
                    }
                    Column {
                        width: curTemp.width + 2 * (app.spacing * 1.5)
                        spacing: app.spacing
                        Table.Table {
                            id: curTemp
                            title: "当前温度"
                            Component.onCompleted: {
                                createDefaultTable()
                            }
                        }
                        Table.Table {
                            id: leakageDetection
                            title: "漏水状态"
                            Component.onCompleted: {
                                createTable(1, 9)
                                setTableTitle(
                                            [["头部", "左肩部", "右肩部", "左胯部", "右胯部", "左膝盖", "右膝盖", "左肘部", "右肘部"]])
                            }
                        }
                        Table.Table {
                            id: destTemp
                            title: "目标温度"
                            Component.onCompleted: {
                                createDefaultTable(30.5)
                                setValidator(regExpValue1)
                                let data = []
                                let tableData = destTemp.getTableData()
                                for (var x = 0; x < tableData.length; x++) {
                                    for (var j = 0; j < tableData[x].length; j++) {
                                        data.push(tableData[x][j])
                                    }
                                }
                                root.oldTempArray = data
                            }
                        }
                        Table.Table {
                            id: constPower
                            title: "恒功率"
                            Component.onCompleted: {
                                createTable(1, 1)
                                setValidator(regExpValue2)
                            }
                        }
                    }
                }
            }
        }

        Widgets.Window {
            id: view2
            gradient: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 600
            Layout.minimumHeight: 600
            backgroundColor: "#121218"
            headerDoubleClickEnabled: false
            icon.source: "qrc:/icons/scatter-plot.svg"
            title: qsTr("人体模型")

            DummyView {
                id: dummy
                width: 400
                height: 600
                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton
                    property real originX: 0
                    property real originY: 0
                    onPressed: {
                        originX = mouse.x
                        originY = mouse.y
                        dummy.areaClicked(originX.valueOf(), originY.valueOf())
                    }
                    onPositionChanged: {
                        var width = mouse.x - originX
                        var height = mouse.y - originY
                    }
                    onScaleChanged: {
                        console.log("1111")
                        dummy.scale = 2
                    }
                }
                onImplicitHeightChanged: {
                    dummy.width = 400
                }
                Component.onCompleted: {
                    console.log("dfadfasdfasdfasdfasdf")
                }
            }
            onWidthChanged: {
                dummy.x = view2.width / 2 - (dummy.width / 2)
                dummy.y = view2.height / 2 - (dummy.height / 2)
                dummy.y = 15
            }
        }
    }

    function getConstPowerData() {
        var data = constPower.getTableData()
        data = "/*ConstantPower:" + data[0] + "*/"
        return data
    }

    function getDestTempData() {
        let data = []
        let tableData = destTemp.getTableData()
        for (var x = 0; x < tableData.length; x++) {
            for (var j = 0; j < tableData[x].length; j++) {
                data.push(tableData[x][j])
            }
        }
        let start_str = "/*SET T: "
        let end_str = "*/"
        for (var i = 0; i < Cpp_UI_DrawCurve.tempCurveNum; i++) {
            if (data[i].toString() === "") {
                Cpp_UI_FormData.sendWarningMess()
                break
            }
            if (i < (Cpp_UI_DrawCurve.tempCurveNum - 1)) {
                let channel_num = (i + 1) < 10 ? ('0' + (i + 1).toString(
                                                      )) : (i + 1).toString()
                let channel_str = (channel_num + " " + data[(i)].toString(
                                       ) + ",")
                start_str = start_str + channel_str
            }

            if (i === (Cpp_UI_DrawCurve.tempCurveNum - 1)) {
                let channel_str = ((i + 1).toString(
                                       ) + " " + data[(i)].toString())
                start_str = start_str + channel_str
            }
        }
        let tempData = start_str + end_str
        return tempData
    }

        Timer{
            id: refreshTemp
            interval: 1000
            running: true
            repeat: true
            onTriggered: {
                if (Cpp_UI_FormData.connectBt && root.tempIndex < Cpp_UI_FormData.timeControl().length){
                        Cpp_UI_FormData.connectBt = false
                        setTimeout(sendTempControl,Cpp_UI_FormData.timeControl()[root.tempIndex])
                }
            }
        }

        function setTimeout(callback, timeout){
                let timer = Qt.createQmlObject("import QtQuick 2.14; Timer {}", root);
                timer.interval = timeout * 1000;
                timer.repeat = false;
                timer.triggered.connect(callback);
                timer.start();
            }

        function sendTempControl(){
            var tempList = Cpp_UI_FormData.tempControl(root.tempIndex)
            destTemp.setTableData(tempList)
            // 加热
            Cpp_UI_FormData.sendTemps(getDestTempData())
            //
            root.tempIndex += 1
            Cpp_UI_FormData.connectBt = true
        }
}
