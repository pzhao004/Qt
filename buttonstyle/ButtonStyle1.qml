import QtQuick 2.0

Rectangle {
    property int boxheight: 40
    property int boxwidth: 120
    id:combobox
    width: boxwidth;height: boxheight;smooth: true
    Rectangle{
        id:choseitem
        width: boxwidth;height: boxheight;color: "lightblue";radius: 4;smooth: true
        Rectangle{
            id:dropdown
            anchors.top: parent.top;
            width: boxwidth;height: 0; clip: true; color: "lightblue";  radius: 4;smooth: true
            Text {
                text: qsTr("Read")
                font.family: "Arial";font.pixelSize: 19;anchors.fill: parent; anchors.margins: 2
                horizontalAlignment: Text.AlignHCenter;verticalAlignment: Text.AlignVCenter
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {console.log("Stop");combobox.state = ""}
            }
        }
        Text {
            id: choseitemText
            text:qsTr("Read")
            font.family: "Arial";font.pixelSize: 19;anchors.fill: parent; anchors.margins: 2
            horizontalAlignment: Text.AlignHCenter;verticalAlignment: Text.AlignVCenter
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                combobox.state=(combobox.state==="dropdownflag" ?  "" : "dropdownflag")
                if(combobox.state === ""){
                    console.log("stop")
                }else{
                    console.log("Start")
                }
            }
        }
    }
    states: State {
        name: "dropdownflag"
        PropertyChanges {
            target: dropdown;height:combobox.boxheight
        }
    }
}
