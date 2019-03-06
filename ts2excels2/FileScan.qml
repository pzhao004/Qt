import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.2

Item{
    Rectangle{
        anchors.fill: parent; radius:5;color: "#e0e0dd"
        Text{
            id:tip1
            text: qsTr("Please Select Ts Files Director:")
            width: parent.width; height: 40;y:10;
            font.bold: true;font.family: ""; font.pixelSize: 25;color: "green";
        }
        Rectangle{
            id:select1
            radius: 3;width: parent.width; height: 40;anchors.top: tip1.bottom
            BorderImage {
                source: selectArea.pressed ? bgSelectSource:bgNormalSource
                width:parent.width;height: 40
                border.left: 5; border.top: 5; border.right: 5; border.bottom: 5
            }
            TextInput{
                id:showPathText
                width: parent.width-83;height: parent.height-6;
                anchors.verticalCenter: parent.verticalCenter
                verticalAlignment: Text.AlignVCenter;
            }
            MouseArea{
                id: selectArea
                width: parent.width-showPathText.width;height: parent.height;
                anchors.right: parent.right
                onClicked: {fileDialog.open()}
            }
        }
        Text{
            id:tip2
            text: qsTr("Please Select Destination Director:")
            anchors.top: select1.bottom; anchors.topMargin: 8
            width: parent.width; height: 40; y:10;
            font.bold: true;font.family: ""; font.pixelSize: 25;color: "green";
        }
        Rectangle{
            id:select2
            radius: 3;width: parent.width; height: 40;anchors.top: tip2.bottom
            BorderImage {
                source: selectArea2.pressed ? bgSelectSource:bgNormalSource
                width:parent.width;height: 40
                border.left: 5; border.top: 5; border.right: 5; border.bottom: 5
            }
            TextInput{
                id:showPathText2
                width: parent.width-83;height: parent.height-6;
                anchors.verticalCenter: parent.verticalCenter
                verticalAlignment: Text.AlignVCenter;
            }
            MouseArea{
                id: selectArea2
                width: parent.width-showPathText.width;height: parent.height;
                anchors.right: parent.right
                onClicked: {fileDialog2.open()}
            }
        }
        Text{
            id:tip
            anchors.top: select2.bottom;anchors.topMargin: 20;
            text:TS2EXCEL.message
        }
        Connections{
            target:TS2EXCEL
            onMessageChanged:{
                tip.color="red";tip.font.pixelSize=30;
            }}
        Rectangle{id:button;color: "#195e19";
            anchors.bottom: parent.bottom;anchors.bottomMargin: 5;
            width: 150;height: 40 ;radius: 5;
            Text{text: "Translate";anchors.fill: parent;verticalAlignment: Text.AlignVCenter;horizontalAlignment:Text.AlignHCenter}
            MouseArea{anchors.fill: parent;onClicked: {
                    TS2EXCEL.xml2excel();
                }
            }

        }
    }
    FileDialog {
       id: fileDialog
       title: qsTr("Please choose an image file")
       selectFolder: true
       nameFilters: ["*.ts","Photo Files", "Image Files (*.jpg *.png *.gif *.bmp *.ico)", "*.*"]
       onAccepted: {
                showPathText.text = String(fileUrl);
                TS2EXCEL.getResourceDirector(fileUrl);
           }
       }
    FileDialog {
            id: fileDialog2
            selectFolder: true
            nameFilters: ["Image Files (*.png *.jpg *.gif *.bmp)", "全部文件 (*.*)"]
            onAccepted: {
                showPathText2.text = String(fileUrl);
                TS2EXCEL.getDestationDirector(fileUrl)

            }
        }
}
