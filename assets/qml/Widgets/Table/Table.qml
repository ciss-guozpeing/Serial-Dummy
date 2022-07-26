import QtQuick 2.0
import QtQml 2.15
import QtQuick.Controls 2.5

import "../"

Window{
    id: root
    spacing: -1
    borderColor: root.headerVisible ? "#517497" : "transparent"

    width: 570
    height: 155
    property var tables: []
    property int rowCount:3
    property int columnCount: 10

    Column{
        x: app.spacing / 2
        id: tableContent
    }

    function createTable(rowCount, columnCount, defaultValue="") {
        for (let i=0; i<rowCount; i++){
            var component = Qt.createComponent("Base.qml")
            var sprite = component.createObject(tableContent)
            tables.push(sprite)
            sprite.modelCount = columnCount
        }
    }

    function createDefaultTable(defaultValue="") {
        let startSerial = 0
        for (let i=0; i< rowCount; i++){
            var component = Qt.createComponent("Base.qml")
            var sprite = component.createObject(tableContent)
            tables.push(sprite)
            if (i===1) {
                sprite.startSerial = 10
                sprite.defaultValue = defaultValue
            }

            if (i===2) {
                sprite.startSerial = 20
                sprite.modelCount = 9
                sprite.defaultValue = defaultValue
            }
            if (i!==2){
                sprite.modelCount =10
                sprite.defaultValue = defaultValue
            }
        }
    }

    function getTableData(){
        let data = []
        for (let i=0; i<tables.length; i++) {
            let rowData = tables[i].getRowData()
            data.push(rowData)
        }
        return data
    }

    function setTableData(data) {
        let startIndex=0;
        for (let i=0; i<tables.length; i++) {
            let rowData = data.slice(startIndex, startIndex+10)
            tables[i].setDefaultRowData(rowData)
            startIndex = startIndex + 10
        }
    }

    function setTableTitle(titleList) {
        for (let i=0; i<tables.length; i++) {
            tables[i].setTitleText(titleList[i])
        }
    }

    function setValidator(regExpValue) {
        for (let i=0; i<tables.length; i++) {
            tables[i].setValidator(regExpValue)
        }
    }
}


