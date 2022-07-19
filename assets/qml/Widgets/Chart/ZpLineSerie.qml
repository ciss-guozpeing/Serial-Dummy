import QtQuick 2.0
import QtQuick.Controls 2.15
import QtCharts 2.3

LineSeries{
            id:lineSeries
            name: "LineSeries"
            axisX: myDateTimeAxis
            axisY:myAxisY
            color: "#00ffff"
            width: 3
            onHovered: {
                var chartPosition = chartView.mapToPosition(point,lineSeries)
                myCanvas.xx = chartPosition.x
                myCanvas.yy = chartPosition.y
                toolTip.visible = state
                toolTip.text = "X："+point.x+"  Y："+point.y
                toolTip.x = chartPosition.x+10
                toolTip.y = chartPosition.y-40
                var d = new Date()
                myCanvas.requestPaint()
            }
            ToolTip{
                    id:toolTip
                    delay: 4
                    font.family: "微软雅黑"
                    font.bold: true
                    font.pointSize: 13
                }
            Canvas{
                    id:myCanvas
                    anchors.fill: chartView
                    property double xx: 0
                    property double yy: 0
                    onPaint: {
                        if(xx+yy>0){
                            var ctx = getContext("2d")
                            ctx.clearRect(0,0,parent.width,parent.height)
                            ctx.strokeStyle = '#ccf48993'
                            ctx.lineWidth = 3
                            ctx.beginPath()
                            ctx.moveTo(xx,chartView.plotArea.y)
                            ctx.lineTo(xx,chartView.plotArea.height+chartView.plotArea.y)
                            ctx.stroke()
                            ctx.beginPath()
                            ctx.moveTo(chartView.plotArea.x,yy)
                            ctx.lineTo(chartView.plotArea.x+chartView.plotArea.width,yy)
                            ctx.stroke()
                        }
                    }
                }
            Component.onCompleted: {
                console.log("加载法师大法师地方")
            }
}
