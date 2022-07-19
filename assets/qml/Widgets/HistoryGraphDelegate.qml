
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
import QtCharts 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import SerialStudio 1.0

import "Message"
import "Chart"
Window {
    id: root
    spacing: -1
    showIcon: false
    visible: opacity > 0
    opacity: enabled ? 1 : 0
    borderColor: root.headerVisible ? "#517497" : "transparent"

    property double scalefactor: 1.01
    property var seriesArr: []

    property int framenumber
    property int max_value: Cpp_UI_DrawCurve.windowsize
    property double minvalue_Y
    property double maxvalue_Y

    property alias firstValue: rangeslider.first.value
    property alias secondValue: rangeslider.second.value

    Connections {
        target: Cpp_UI_DrawCurve

        function onSendFrameCount() {
            framenumber = Cpp_UI_DrawCurve.frameCount
            if (framenumber % Cpp_UI_DrawCurve.windowsize === 0) {
                let num = framenumber / Cpp_UI_DrawCurve.windowsize
                max_value = Cpp_UI_DrawCurve.windowsize * (num + 1) + 1
            }
        }

        function onSendHistoryEnvTemp() {
            if (root.title === "室内温度曲线") {
                for (let i = 0; i < Cpp_UI_DrawCurve.envCurveNum; i++) {
                    Cpp_UI_DrawCurve.updateHistoryEnvTempGraph(chartView.series[i], i)
                }
            }
            setAxisYValue()
        }

        function onSendHistoryHeatPower() {
            if (root.title === "热通量曲线") {
                for (let p = 0; p < Cpp_UI_DrawCurve.heatPowerNum; p++) {
                    Cpp_UI_DrawCurve.updateHistoryHeatPowerGraph(chartView.series[p], p)
                }
            }
            setAxisYValue()
        }

        function onSendHistoryTemp() {
            if (root.title === "体表温度曲线") {
                for (let n = 0; n < Cpp_UI_DrawCurve.tempCurveNum; n++) {
                    Cpp_UI_DrawCurve.updateHistoryTempGraph(chartView.series[n], n)
                }
            }
            setAxisYValue()
        }

        function onSendHistHeatLoss() {
            if (root.title === "分区热损失曲线") {
                for (let m = 0;m < Cpp_UI_DrawCurve.heatPowerNum; m++){
                    Cpp_UI_DrawCurve.updateHistoryHeatLossGraph(chartView.series[m], m)
                }
            }
            setAxisYValue()
        }
    }

    signal sendAvgTempRangeMin(int value)
    signal sendTempRangeMin(int value)
    signal sendHPRangeMin(int value)
    signal sendAvgTempRangeMax(int value)
    signal sendTempRangeMax(int value)
    signal sendHPRangeMax(int value)
    signal sendFirstXAxisChange(int value)
    signal sendSecondXAxisChange(int value)

    ChartView {
        id: chartView
        anchors.fill: parent
        animationOptions: ChartView.AllAnimations
        theme: ChartView.ChartThemeDark
        antialiasing: true
        legend.visible: true
        backgroundRoundness: 0
        enabled: root.enabled
        visible: root.enabled
        backgroundColor: root.backgroundColor

        property var series: []
        margins {
            top: 0
            bottom: 40
            left: 0
            right: 0
        }

        ValueAxis {
            id: axisX
            min: 1
            max: max_value
            tickCount: 10
            labelsColor: "#ffffff"
            labelsFont.pointSize: 13
            labelsFont.bold: true
            labelFormat: '%d'
        }

        ValueAxis {
            id: axisY
            min: minvalue_Y
            max: maxvalue_Y
        }

        ToolTip{
                id:toolTip
                delay: 4
                font.family: "微软雅黑"
                font.bold: true
                font.pointSize: 13
        }

        RangeSlider {
            id: rangeslider
            from: 1
            to: axisX.max
            first.value: 1
            second.value: axisX.max
            x: chartView.plotArea.x
            y: chartView.height - 40
            width: chartView.plotArea.width

            first.onMoved: {
                var p = Qt.point(first.value, 1)
                start_canvas.xx = chartView.mapToPosition(p, chartView.axes[0]).x
                start_canvas.requestPaint()
            }

            second.onMoved: {
                var p = Qt.point(second.value, 1)
                end_canvas.xx = chartView.mapToPosition(p, chartView.axes[0]).x
                end_canvas.requestPaint()
            }
        }

        Canvas {
            id: start_canvas
            anchors.fill: chartView
            property double xx: 0
            onPaint: {
                var ctx = getContext("2d")
                ctx.reset()
                ctx.strokeStyle = '#ccf48993'
                ctx.lineWidth = 2
                ctx.beginPath()
                ctx.setLineDash([2])
                ctx.moveTo(xx, chartView.plotArea.y)
                ctx.lineTo(xx, chartView.plotArea.height + chartView.plotArea.y)
                ctx.fill()
                ctx.stroke()
            }
        }

        Canvas {
            id: end_canvas
            anchors.fill: chartView
            property double xx: 0
            onPaint: {
                var ctx = getContext("2d")
                ctx.reset()
                ctx.strokeStyle = 'white'
                ctx.lineWidth = 2
                ctx.beginPath()
                ctx.setLineDash([2])
                ctx.moveTo(xx, chartView.plotArea.y)
                ctx.lineTo(xx, chartView.plotArea.height + chartView.plotArea.y)
                ctx.fill()
                ctx.stroke()
            }
        }
    }

    onFirstValueChanged: {
        console.log("开始值。。。。")
        var p = Qt.point(firstValue, 1)
        start_canvas.xx = chartView.mapToPosition(p, chartView.axes[0]).x
        start_canvas.requestPaint()
    }

    onSecondValueChanged: {
        console.log("结束值。。。")
        var p = Qt.point(secondValue, 1)
        end_canvas.xx = chartView.mapToPosition(p, chartView.axes[0]).x
        end_canvas.requestPaint()
    }

    function setAxisYValue() {
        if (root.title === "体表温度曲线") {
            minvalue_Y = Cpp_UI_DrawCurve.minHistT
            maxvalue_Y = Cpp_UI_DrawCurve.maxHistT * scalefactor
        }
        if (root.title === "热通量曲线") {
            minvalue_Y = Cpp_UI_DrawCurve.minHistHP
            maxvalue_Y = Cpp_UI_DrawCurve.maxHistHP * scalefactor
        }
        if (root.title === "室内温度曲线") {
            minvalue_Y = Cpp_UI_DrawCurve.minHistE
            maxvalue_Y = Cpp_UI_DrawCurve.maxHistE * scalefactor
        }
        if (root.title === "分区热损失曲线") {
            console.log((Cpp_UI_DrawCurve.maxHistHL * scalefactor).toFixed(2))
            minvalue_Y = Cpp_UI_DrawCurve.minHistHL
            maxvalue_Y = (Cpp_UI_DrawCurve.maxHistHL * scalefactor).toFixed(2)
        }
    }

    function createSeriesLine(seriesCount) {
        for (let i=0; i< seriesCount; i++) {
            var series = chartView.createSeries(chartView.SeriesTypeLine, i+1, axisX, axisY)
            series.useOpenGL = true
            series.color = Cpp_UI_DrawCurve.getCurvedColor()[i]
            root.seriesArr.push(series)
            chartView.series.push(series)
        }
    }
}
