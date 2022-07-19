import QtQuick 2.0
import QtQml 2.15
import QtQuick.Controls 2.5

Row{
    id: rowData
    width: 500
    height: 40
    property alias modelCount: baseComponent.model
    property int startSerial
    property string defaultValue: ''
    RegExpValidator{
        id: regExpValue2
        regExp: /[0-5]/
    }
    Repeater{
        id: baseComponent
        model: modelCount
        delegate: Column{
            Rectangle{
                id: titleInput
                objectName: "rect1"
                width: 56.3; height: 20
                border.width: 1; border.color: "black"
                Text{
                    objectName: "text1"
                    anchors.centerIn: parent
                    text: "区域" + Number(startSerial + modelData + 1)
                }
            }
            Rectangle{
                id: valueRect
                width: 56.3; height: 20
                border.width: 1; border.color: "black"
                TextInput{
                   id: textInput
                   text: defaultValue
                   anchors.centerIn: parent
                   color: "black"
                   anchors.fill: parent
                   font.pointSize: 13
                   selectByMouse: true
                   verticalAlignment: Text.AlignVCenter
                   horizontalAlignment: Text.AlignHCenter
                   validator: regExpValue2
                }
            }
        }
    }

    function getRowData() {
        let data = new Array
        for (let i=0; i<modelCount; i++) {
            data.push(rowData.children[i].children[1].children[0].text)
        }
        return data
    }

    function setDefaultRowData(data) {
        for (let i=0; i<modelCount; i++) {
            rowData.children[i].children[1].children[0].text = data[i]
        }
    }

    function setIndexRowData(index, value) {
        rowData.children[index].children[1].children[0].text = value
    }

    function setTitleText(titleList) {
        for (let i=0; i<modelCount; i++) {
            rowData.children[i].children[0].children[0].text = titleList[i]
        }
    }

    function setValidator(regExpValue) {
        for (let i=0; i<modelCount; i++) {
            rowData.children[i].children[1].children[0].validator=regExpValue
        }
    }
}



