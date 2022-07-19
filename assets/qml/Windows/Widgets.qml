
/*
 * Copyright (c) 2020-2021 Alex Spataru <https://github.com/alex-spataru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls 1.5 as QC15
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.12 as QtWindow

import "../Widgets" as Widgets

Control {
    id: root
    property int channelCount: 29
    property int avgTemCount: 3
    property int tempCount: 29
    property int heatPowerCount: 29
    property var groups: []
    property var swChecked: [[],[],[],[]]

    property int avgtemp_min
    property int avgtemp_max
    property int hp_min
    property int hp_max
    property int temp_min
    property int temp_max

    RowLayout {
        anchors.fill: parent
        spacing: app.spacing * 2
        anchors.margins: app.spacing * 1.5
        Widgets.Window {
            id: viewOptions
            gradient: true
            Layout.fillHeight: true
            Layout.minimumWidth: 320
            backgroundColor: "#121218"
            headerDoubleClickEnabled: false
            icon.source: "qrc:/icons/visibility.svg"
            title: qsTr("View")

            ScrollView {
                clip: true
                anchors.fill: parent
                anchors.margins: app.spacing
                anchors.topMargin: viewOptions.borderWidth
                anchors.bottomMargin: viewOptions.borderWidth

                ColumnLayout {
                    Item {
                        height: app.spacing
                    }
                    Rectangle {
                        id: sidebar
                        width: 300
                        height: 900
                        property int spacing: 10 //项之间距离
                        property bool autoExpand: false
                        property var graphs: [[], [], []]
                        property var groupNames: []
                        property var subGraphs: []
                        property bool avgTempSw: true
                        property bool heatPowerSw: true
                        property bool tempSw: true

                        //背景
                        color: Qt.rgba(2 / 255, 19 / 255, 23 / 255, 128 / 255)

                        property alias model: list_view.model
                        ListView {
                            id: list_view
                            anchors.fill: parent
                            anchors.margins: 0
                            //通过+1来给每个item一个唯一的index
                            //可以配合root的currentItem来做高亮
                            property int itemCount: 0
                            delegate: list_delegate
                            clip: true
                        }
                        Component {
                            id: list_delegate
                            Row {
                                id: list_itemgroup
                                spacing: 0

                                //canvas 画项之间的连接线
                                Canvas {
                                    id: list_canvas
                                    width: item_titleicon.width + 10
                                    height: list_itemcol.height
                                    //开了反走样，线会模糊看起来加粗了
                                    antialiasing: false
                                    //最后一项的连接线没有尾巴
                                    property bool isLastItem: (index == parent.ListView.view.count - 1)
                                    onPaint: {
                                        var ctx = getContext("2d")
                                        var i = 0
                                        //ctx.setLineDash([4,2]); 遇到个大问题，不能画虚线
                                        // setup the stroke
                                        ctx.strokeStyle = Qt.rgba(201 / 255,
                                                                  202 / 255,
                                                                  202 / 255, 1)
                                        ctx.lineWidth = 1
                                        // create a path
                                        ctx.beginPath()
                                        //用短线段来实现虚线效果，判断里-3是防止width(4)超过判断长度
                                        //此外还有5的偏移是因为我image是透明背景的，为了不污染到图标
                                        //这里我是虚线长4，间隔2，加起来就是6一次循环
                                        //效果勉强
                                        ctx.moveTo(width / 2,
                                                   0) //如果第一个item虚线是从左侧拉过来，要改很多
                                        for (i = 0; i < list_itemrow.height / 2 - 5 - 3; i += 6) {
                                            ctx.lineTo(width / 2, i + 4)
                                            ctx.moveTo(width / 2, i + 6)
                                        }

                                        ctx.moveTo(width / 2 + 5,
                                                   list_itemrow.height / 2)
                                        for (i = width / 2 + 5; i < width - 3; i += 6) {
                                            ctx.lineTo(i + 4,
                                                       list_itemrow.height / 2)
                                            ctx.moveTo(i + 6,
                                                       list_itemrow.height / 2)
                                        }

                                        if (!isLastItem) {
                                            ctx.moveTo(width / 2,
                                                       list_itemrow.height / 2 + 5)
                                            for (i = list_itemrow.height / 2
                                                 + 5; i < height - 3; i += 6) {
                                                ctx.lineTo(width / 2, i + 4)
                                                ctx.moveTo(width / 2, i + 6)
                                            }
                                            //ctx.lineTo(10,height)
                                        }
                                        // stroke path
                                        ctx.stroke()
                                    }

                                    //项图标框--可以是ractangle或者image
                                    Image {
                                        property string onSrc: "qrc:/images/on.png"
                                        property string offSrc: "qrc:/images/off.png"
                                        id: item_titleicon
                                        visible: false
                                        //如果是centerIn的话展开之后就跑到中间去了
                                        anchors.left: parent.left
                                        anchors.top: parent.top
                                        anchors.leftMargin: list_canvas.width / 2 - width / 2
                                        anchors.topMargin: list_itemrow.height / 2 - width / 2
                                        source: item_repeater.count ? item_sub.visible ? offSrc : onSrc : offSrc
                                        MouseArea {
                                            anchors.fill: parent
                                            onClicked: {
                                                if (item_repeater.count)
                                                    item_sub.visible = !item_sub.visible
                                            }
                                        }
                                    }
                                }

                                //项内容：包含一行item和子项的listview
                                Column {
                                    id: list_itemcol
                                    //这一项的内容，这里只加了一个text
                                    Row {
                                        id: list_itemrow
                                        width: sidebar.width
                                        height: item_text.contentHeight + sidebar.spacing
                                        anchors.margins: 0
                                        spacing: 10

                                        property int itemIndex

                                        Rectangle {
                                            property int currentItem: -1 //当前选中item
                                            height: item_text.contentHeight + sidebar.spacing
                                            width: parent.width
                                            anchors.verticalCenter: parent.verticalCenter
                                            color: (currentItem === list_itemrow.itemIndex) ? Qt.rgba(101 / 255, 255 / 255, 255 / 255, 38 / 255) : "transparent"
                                            Text {
                                                id: item_text
                                                anchors.left: parent.left
                                                width: 30
                                                anchors.verticalCenter: parent.verticalCenter
                                                text: modelData.text
                                                font.pixelSize: 14
                                                font.family: "Microsoft YaHei UI"
                                                color: Qt.rgba(101 / 255, 1, 1, 1)
                                            }
                                            Switch {
                                                id: sw
                                                width: 45
                                                height: 20
                                                anchors.fill: parent
                                                anchors.leftMargin: 140
                                                Component.onCompleted: checked = true
                                                onCheckedChanged: {
                                                    console.log("1111111",list_itemrow.itemIndex)
                                                    var itemIndex = list_itemrow.itemIndex
                                                    // 全选 全部取消
                                                    if (itemIndex == avgTemCount){
                                                        setShowCurve(0,itemIndex,avgTemCount,0,checked)
                                                    }
                                                    if (itemIndex == (avgTemCount + heatPowerCount + 1)) {
                                                        setShowCurve(1,itemIndex,heatPowerCount,1,checked)
                                                    }
                                                    if (itemIndex == (avgTemCount + heatPowerCount + tempCount + 2)){
                                                        setShowCurve(2,itemIndex,tempCount,2,checked)
                                                    }
                                                    if (itemIndex == (avgTemCount + heatPowerCount*2 + tempCount + 3)){
                                                        setShowCurve(3,itemIndex,tempCount,3,checked)
                                                    }
//                                                    // 单选
                                                    if (itemIndex >= 0 && itemIndex < avgTemCount) {
                                                        swChecked[0][itemIndex] = sw
                                                        console.log(list_itemrow.itemIndex)
                                                        histGraphDelegate.itemAt(0).seriesArr[list_itemrow.itemIndex].visible = checked
                                                    }
                                                    if (itemIndex >= (avgTemCount + 1) && itemIndex < (avgTemCount + channelCount + 1))
                                                    {
                                                        swChecked[1][itemIndex - (avgTemCount+1)] = sw

                                                        histGraphDelegate.itemAt(1).seriesArr[itemIndex - (avgTemCount+1)].visible = checked
                                                    }
                                                    if (itemIndex >= (avgTemCount+ heatPowerCount + 2) && itemIndex < (avgTemCount + channelCount + tempCount + 2))
                                                    {
                                                        swChecked[2][itemIndex - (avgTemCount + heatPowerCount + 2)] = sw
                                                        histGraphDelegate.itemAt(2).seriesArr[itemIndex - (avgTemCount+ heatPowerCount + 2)].visible = checked
                                                    }
                                                    if (itemIndex >= (avgTemCount + channelCount + tempCount + 3) && itemIndex < (avgTemCount + channelCount*2 + tempCount + 3))
                                                    {
                                                        swChecked[3][itemIndex - (avgTemCount + channelCount + tempCount + 3)] = sw
                                                        histGraphDelegate.itemAt(3).seriesArr[itemIndex - (avgTemCount + channelCount + tempCount + 3)].visible = checked
                                                    }
                                                }
                                            }
                                        }

                                        Component.onCompleted: {
                                            list_itemrow.itemIndex = list_view.itemCount
                                            list_view.itemCount += 1
                                            if (modelData.istitle)
                                                item_titleicon.visible = true
                                        }
                                    }

                                    //放子项
                                    Column {
                                        property int indent: 5 //子项缩进距离,注意实际还有icon的距离
                                        id: item_sub
                                        visible: sidebar.autoExpand
                                        //上级左侧距离=小图标宽+x偏移
                                        x: indent
                                        Item {
                                            width: 20
                                            height: item_repeater.contentHeight
                                            //需要加个item来撑开，如果用Repeator获取不到count
                                            ListView {
                                                id: item_repeater
                                                anchors.fill: parent
                                                anchors.margins: 0
                                                delegate: list_delegate
                                                model: modelData.subnodes
                                            }
                                        }
                                    }
                                }
                            }
                            //end list_itemgroup
                        }

                        //end list_delegate
                        Component.onCompleted: {
                            setTestDataA()
                        }
                        function setTestDataA() {
                            list_view.model = JSON.parse(Cpp_UI_DrawCurve.loadHistSwitchText())
                        }
                    }
                }
            }
        }

        Widgets.Window{
            id: histView
            gradient: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 240
            backgroundColor: "#121218"
            headerDoubleClickEnabled: false
            icon.source: "qrc:/icons/scatter-plot.svg"
            title: qsTr("历史数据")
            property var graphTitle: ["室内温度曲线","热通量曲线","体表温度曲线","分区热损失曲线"]
            ColumnLayout {
                spacing: app.spacing / 2
                anchors.margins: app.spacing * 1.5
                anchors.fill: parent
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.margins: app.spacing
                TabBar {
                    id: tab
                    height: 40
                    Layout.fillWidth: true
                    onCurrentIndexChanged: {
                        histGraph.currentIndex = tab.currentIndex
                    }

                    TabButton {
                        text: qsTr("室内温度曲线")
                        height: tab.height + 3
                        width: implicitWidth + 2 * app.spacing
                        onClicked: {
                            Cpp_UI_DrawCurve.sendHistEnvTempSingle()
                        }
                    }

                    TabButton {
                        text: qsTr("热通量曲线")
                        height: tab.height + 3
                        width: implicitWidth + 2 * app.spacing
                        onClicked: {
                            Cpp_UI_DrawCurve.sendHistHPSingle()
                        }
                    }

                    TabButton {
                        text: qsTr("体表温度曲线")
                        height: tab.height + 3
                        width: implicitWidth + 2 * app.spacing
                        onClicked: {
                            Cpp_UI_DrawCurve.sendHistTempSingle()
                        }
                    }

                    TabButton {
                        text: qsTr("分区热损失曲线")
                        height: tab.height + 3
                        width: implicitWidth + 2 * app.spacing
                        onClicked: {
                            Cpp_UI_DrawCurve.sendHistHeatLoss()
                        }
                    }
                }
                StackLayout {
                    id: histGraph
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.margins: app.spacing
                    Repeater {
                        id: histGraphDelegate
                        model: 4
                        anchors.fill: parent
                        delegate: Widgets.HistoryGraphDelegate{
                            id: graph
                            title: histView.graphTitle[modelData]
                            onFirstValueChanged: syncCurvedFirstValue(graph.firstValue)
                            onSecondValueChanged: syncCurvedSecondValue(graph.secondValue)
                        }
                    }
                    Component.onCompleted: {
                        createHistGraph();
                    }
                }
            }
        }
    }

    function setShowCurve(ss,index,curveNums,groupIndex,swStatus){
        if (swStatus){
            for(let i=0; i<curveNums; ++i){
                swChecked[groupIndex][i].checked = swStatus
                histGraphDelegate.itemAt(ss).seriesArr[i].visible = swStatus
            }
        }else{
            for(let n=0; n<curveNums; ++n){
                console.log("sssssss",swStatus)
                swChecked[groupIndex][n].checked = swStatus
                histGraphDelegate.itemAt(ss).seriesArr[n].visible = swStatus
            }
        }
    }

    function getAvgTempRangeMin(min_value) {
        syncCurvedFirstValue(min_value)
    }

    function getAvgTempRangeMax(max_value) {

        syncCurvedSecondValue(max_value)
    }

    function getHPRangeMin(min_value) {

        syncCurvedFirstValue(min_value)
    }

    function getHPRangeMax(max_value) {

        syncCurvedSecondValue(max_value)
    }

    function getTempRangeMin(min_value) {
        syncCurvedFirstValue(min_value)
    }

    function getTempRangeMax(max_value) {

        syncCurvedSecondValue(max_value)
    }

    function syncCurvedFirstValue(first_value) {
        hp_min = temp_min = avgtemp_min = first_value
        for (var i = 0; i < histGraphDelegate.count; ++i) {
            if (i != tab.currentIndex) {
                histGraphDelegate.itemAt(i).firstValue = first_value
            }
        }
    }

    function syncCurvedSecondValue(second_value) {
        temp_max = hp_max = avgtemp_max = second_value
        for (var i = 0; i < histGraphDelegate.count; ++i) {
            if (i != tab.currentIndex) {
                histGraphDelegate.itemAt(i).secondValue = second_value
            }
        }
    }

    function getGraphRange() {
        var graphrange = new Array
        graphrange.push(avgtemp_min,avgtemp_max,
                        hp_min,hp_max,temp_min,temp_max)
        return graphrange
    }

    function createHistGraph() {
        for (let i=0; i<histGraphDelegate.count; i++) {
            histGraphDelegate.itemAt(i).createSeriesLine(Cpp_UI_DrawCurve.getHistoryCurvedCount()[i])
        }
    }
}
