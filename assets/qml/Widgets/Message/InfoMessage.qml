import QtQuick 2.0

Item {
    property point startPoint: Qt.point(0, 0)
    property point endPoint: Qt.point(0, 0)
    property var lineColor: "#E5F012"
    property var lineWidth: 2

    //斜线长度
    property var oblLineLength: 0
    //水平线长度
    property var horLineLength: 0

    function drawCala() {
        oblLine.visible = true;
        horLine.visible = true;
        //相对角度
        var angle= 0

        //实际角度值
        var realAngle = 0;

        var newOblLeng = 0;
        var newHorLeng = 0;

        var tmpx = Math.abs(startPoint.x - endPoint.x);
        var tmpy = Math.abs(startPoint.y - endPoint.y);

        //情况1 30°夹角
        if (tmpx >= Math.floor((Math.sqrt(3) / 3) * tmpy))
        {
            newOblLeng = Math.floor(tmpy / (Math.sqrt(3) / 2));
            newHorLeng = tmpx - Math.floor((Math.floor((Math.sqrt(3) / 3) * tmpy)));
            angle = 60;
        }
        //情况2 垂线和直线配合
        else
        {
            newOblLeng = tmpy;
            newHorLeng = tmpx;
            angle = 90;
        }

        //水平线的Y坐标 和结束点Y坐标相同
        horLine.y = endPoint.y;

        //结束的点在起始点的左上方
        if ((startPoint.x >= endPoint.x) && (startPoint.y >= endPoint.y))
        {
            realAngle = 180 + angle;
            horLine.x = endPoint.x + newHorLeng;
            horLine.rotation = 180;
        }
        //结束的点在起始点的右上方
        else if ((startPoint.x <= endPoint.x) && (startPoint.y >= endPoint.y))
        {
            realAngle = -angle;
            horLine.x = endPoint.x - newHorLeng;
            horLine.rotation = 0;
        }
        //结束的点在起始点的右下方
        else if ((startPoint.x <= endPoint.x) && (startPoint.y <= endPoint.y))
        {
            realAngle = angle;
            horLine.x = endPoint.x - newHorLeng;
            horLine.rotation = 0;
        }
        //结束的点在起始点的左下方
        else if ((startPoint.x >= endPoint.x) && (startPoint.y <= endPoint.y))
        {
            realAngle = 180 - angle;
            horLine.x = endPoint.x + newHorLeng;
            horLine.rotation = 180;
        }

        oblLine.x = startPoint.x;
        oblLine.y = startPoint.y;
        oblLine.rotation = realAngle
        oblLineLength = newOblLeng;
        horLineLength = newHorLeng;

        if (oblLineLength > 0)
        {
            oblAnimation.restart();
        }
        else
        {
            //当使用垂线时斜线长度清零
            oblLine.width = oblLineLength;
            //直接进行水平延伸
            horLine.visible = true;
            horAnimation.restart();
        }
    }

    function init()
    {
        oblLine.visible = true;
        horLine.visible = true;
    }

    function clear()
    {
        oblLine.visible = false;
        horLine.visible = false;
        oblAnimation.stop();
        horAnimation.stop();
    }

    Rectangle{
        id: oblLine

        antialiasing: true
        height: lineWidth
        color: lineColor
        transformOrigin: Item.TopLeft
    }

    Rectangle{
        id: horLine

        antialiasing: true
        height: lineWidth
        color: lineColor
        transformOrigin: Item.TopLeft
    }

    PropertyAnimation {
        id: oblAnimation
        target: oblLine
        property: "width"
        duration: 200
        from: 0
        to: oblLineLength
        onStopped: {
            if (horLineLength > 0)
            {
                horLine.visible = true
                horAnimation.restart()
            }
        }
        onStarted: {
            horLine.visible = false
        }
    }
    PropertyAnimation {
        id: horAnimation
        target: horLine
        property: "width"
        duration: 400
        from: 0
        to: horLineLength
    }
}
