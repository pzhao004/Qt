import QtQuick 2.0

Rectangle {
    property int boxheight: 40
    property int boxwidth: 120
    property variant items: [qsTr("English"), qsTr("Chinese"), qsTr("Japanese")]

    id:combobox
    width: boxwidth;height: boxheight
    smooth: true

    Rectangle{
        id:choseitem
        smooth: true
        height: boxheight;width: boxwidth;color: "lightblue";radius: 4
        Text {
            id: choseitemText
            anchors.fill: parent; anchors.margins: 2
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text:items[0]
            font.family: "Arial";font.pixelSize: 19
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                combobox.state=(combobox.state==="dropdownflag" ?  "" : "dropdownflag")
                console.log(combobox.state)
            }
        }
    }
    states: State {
        name: "dropdownflag"
        PropertyChanges {
            target: dropdown;height:combobox.boxheight*combobox.items.length
        }
    }
    transitions: Transition {
        NumberAnimation{target: dropdown;properties: "height";easing.type: Easing.OutExpo;duration: 600}
    }
    Rectangle{
        id:dropdown
        width: boxwidth;height: 0;clip: true;color: "gray"
        anchors.top: choseitem.bottom;anchors.topMargin: 0.5;radius: 5
        ListView{
            id:listview
            width: boxwidth-2;height: boxheight*3 +3
            anchors.fill:parent;anchors.margins: 0.5;
            model: combobox.items
            delegate: Item{
                width: boxwidth-2;height: boxheight
                Text {
                    text: modelData
                    width: boxwidth;height: boxheight-2
                    font.pixelSize: 15;font.family: "Arial";
                    verticalAlignment: Text.AlignVCenter;horizontalAlignment: Text.AlignHCenter
                }
                Rectangle{
                    width: boxwidth-10;height: 0.5;color: "blue";anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter;radius: 10
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        combobox.state = ""
                        var preselection = choseitemText.text
                        if(modelData === combobox.items[0]){
                            choseitemText.text = "English"
                        }else if(modelData === combobox.items[1]){
                            choseitemText.text = "中文"
                        }else if(modelData === combobox.items[2]){
                            choseitemText.text = "わぶん"
                        }
                        if(choseitemText.text !== preselection){
                            console.log(choseitemText.text,preselection)
                            //combobox.comboClicked()
                        }
                        listview.currentIndex =index
                        console.log(listview.currentIndex)
                    }
                    onEntered: {}
                    onExited: {}
                }
            }
        }
    }
}
