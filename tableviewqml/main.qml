/*!
*@file main.qml
*@brief main file, it is the bottom panel
*@version 1.0
*@author zhao albert.
*/
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import SFPM 1.0
Window {
    property int rowNum: 0
    id:frmWindow
    visible: true
    maximumWidth: CONFIG.mainScreenWidth
    minimumWidth: CONFIG.mainScreenWidth
    maximumHeight: CONFIG.mainScreenHeight
    minimumHeight: CONFIG.mainScreenHeight
    title: qsTr("Hello World")
    TableView {
        height: parent.height-40;width: parent.width
        id: tableView
        TableViewColumn { title: "Book Name"; role: "name";  width: 338; movable: false;resizable: false;delegate: selectBox}
        TableViewColumn { title: "Price"; role: "price";  width: 200; movable: false;resizable: false;delegate: selectBox}
        TableViewColumn { title: "Brief"; role: "description";  width: 210;movable: false;resizable:false;delegate:selectBox}
        TableViewColumn { title: "Del" ; role: "func"; width: 50;movable: false;resizable:false;delegate:imageicon}
        sortIndicatorVisible: true

        model: SortFilterProxyModel{
            source: tableView.columnCount >0 ? TABLEMODEL : null
            sortRole: tableView.rowCount >0 ?  tableView.getColumn(tableView.sortIndicatorColumn).role  : ""
            sortOrder: tableView.sortIndicatorOrder
            sortCaseSensitivity: Qt.CaseInsensitive

            filterString: "*"+serachBox.text+"*"
            filterSyntax: SortFilterProxyModel.Wildcard
            filterCaseSensitivity: Qt.CaseInsensitive
            filterRole: "name"
        }
        alternatingRowColors: false
        backgroundVisible: true
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        headerDelegate: Rectangle{
            width:610; height: 30; color: "#337733"; border.width: 1; border.color: "blue";
            Text{
                text: styleData.value
                color: "white";font.bold: true;anchors.centerIn: parent;
                horizontalAlignment: Text.AlignHCenter;verticalAlignment: Text.AlignVCenter
            }
        }
        rowDelegate: Rectangle {height: 50}
    }

    Component{
        id: imageicon
        Rectangle {
            height: 50;
            Image{
                anchors.centerIn: parent
                width: 20;height: 20;
                source: delArea.pressed ? "":"./images/delete.png"
            }
            MouseArea{
                id:delArea
                anchors.fill: parent
                onClicked: {
                    console.log("set del status...",  styleData.row, styleData.column,styleData.value)
                    TABLEMODEL.del(styleData.value);
                }
            }
        }
    }
    Component{
        id:selectBox
        Rectangle {
            height: 50; border.color: "green"; border.width: 1;  color: "transparent"
            Image{
                anchors.fill: parent
                source: "./images/bg_intput_normal.png"
                Image{
                    id:bgsrc
                    height: parent.height
                    width: parent.width
                    source: txt.focus ? "./images/generic_inputbar_52_re.png": "./images/bg_intput_normal.png"
                    TextInput{
                        id:txt;
                        anchors.fill: parent; objectName: "txf"
                        verticalAlignment: TextInput.AlignVCenter
                        horizontalAlignment: TextInput.AlignHCenter
                        text: styleData.value
                        z: txt.focus? 2:1
                        onFocusChanged: {
                            if(txt.focus){
                               console.log(styleData.row, styleData.column, styleData.value)
                                TABLEMODEL.modify(styleData.row, styleData.column, styleData.value)
                            }
                        }
                        onEditingFinished: {
                            txt.focus=false
                        }
                    }
                    MouseArea{
                        id:areaTxt
                        anchors.fill: parent
                        enabled: true
                        onClicked: {
                            areaTxt.z =1
                        }
                    }
                }
            }
        }
    }

    Row{
            anchors.bottom: parent.bottom;anchors.right: parent.right; spacing: 2
            height: 40
            Rectangle {
                height: 30;width: 110;border.width: 1;border.color: "black"
                TextField{
                    id:serachBox
                    anchors.fill: parent
                    placeholderText: "Search...."
                    inputMethodHints: Qt.ImhNoPredictiveText
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
            Rectangle{
                height: 30;width: 90;border.width: 1;border.color: "black"
                TextField{anchors.fill: parent;placeholderText: "col1" ; id:input1}
            }
            Rectangle{
                height: 30;width: 90;border.width: 1;border.color: "black"
                TextField{anchors.fill: parent;placeholderText: "col2" ;id:input2}
            }
            Rectangle{
                height: 30;width: 90;border.width: 1;border.color: "black"
                TextField{anchors.fill: parent;placeholderText: "col3" ;id:input3}
            }
            Button{
                text: qsTr("Add")
                onClicked: {
                    TABLEMODEL.add(input1.text,input2.text,input3.text)
                }
            }
            Button{
                text: qsTr("DelAll")
                onClicked: {
                    TABLEMODEL.delall()
                }
            }
//            Button{
//                text: qsTr("Refresh")
//                onClicked: {
//                    TABLEMODEL.refresh();
//                }
//            }
        }
}
