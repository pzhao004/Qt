import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Window 2.2

Window {
    id:root
    visible: true
    width: 800
    height: 375
    title: qsTr("Hello World")
    modality: Qt.ApplicationModal
    property string bgConfirmSource: "./pic/generic_listbg.png"

    Rectangle{
        id:cont;anchors.fill: parent;
        MouseArea{anchors.fill: parent;}
        ButtonStyle1{id:butstyle1;anchors.top:parent.top;anchors.topMargin: 20}
        ButtonStyle2{id:butstyle2;anchors.left: butstyle1.right; anchors.leftMargin: 50;anchors.top:parent.top;anchors.topMargin: 20}
    }
    Popup{
        id:confirm
        modal: true;focus: true;
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        width: parent.width/2;height: parent.height/2;anchors.centerIn: parent
        topInset: -2;leftInset: -2;rightInset: -6;bottomInset: -6
        background : BorderImage {
                border.left: 30; border.top: 30
                border.right: 30; border.bottom: 30
                source: bgConfirmSource
                Rectangle{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: splitline.left;anchors.rightMargin: 15
                    width: confirm.width/3;height: 50;radius: 5;color: "#156d15"
                    Text{
                        text: qsTr("Cancel");anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter;horizontalAlignment: Text.AlignHCenter
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {console.log("Cancel");confirm.close()}
                    }
                }
                Rectangle{id:splitline;width: 1;height: 80;color: "black";anchors.centerIn: parent}
                Rectangle{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: splitline.right;anchors.leftMargin: 15
                    width: confirm.width/3;height: 50;radius: 5;color: "#156d15"
                    Text{
                        text: qsTr("Save");anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter;horizontalAlignment: Text.AlignHCenter
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {console.log("Save");confirm.close()}
                    }
                }
            }
        }
}
