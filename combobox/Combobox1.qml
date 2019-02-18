import QtQuick 2.0

Rectangle{
    property variant items: [qsTr("English"), qsTr("Chinese"), qsTr("Japanese")]
    property int boxheight: 50
    property int boxwidth: 200
    signal comboClicked;
    id:combobox
    width: boxwidth
    height: boxheight
    smooth: true;

    Rectangle{
        id:choseitem
        smooth: true
        radius: 3
        width: boxwidth
        height: boxheight
        color:  "#2EB3FF"
        Text {
            id: choseitemText
            anchors.fill: parent
            anchors.margins: 3
            smooth: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: combobox.items[0]
            font.family: "Arial";font.pixelSize: 15
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                var comboboxstate= combobox.state
                if(comboboxstate === "dropdown1"){
                    combobox.state = ""
                }else{
                    combobox.state = "dropdown1"
                }
                console.log(combobox.state)
                //combobox.state=combobox.state==="dropdown" ?  "" : "dropdown"
            }
        }
    }
    Rectangle {
        id:dropdown
        width: boxwidth
        height: 0
        radius: 3
        anchors.top: choseitem.bottom
        anchors.topMargin: 1
        color: "lightgray"
        clip: true
        Rectangle{
            id:dropdownMask
            height: 0
            width: boxwidth
            anchors.top: dropdown.top
        }
        ListView{
            id:listview
            height: boxheight*3+1
            width: boxwidth-4
            anchors.top: dropdownMask.bottom
            anchors.topMargin: -1
            anchors.horizontalCenter: parent.horizontalCenter
            z:1
            model: combobox.items
            delegate: Item {
                width: boxwidth-4;height: boxheight
                Rectangle{
                    id:mousemoveHightLight
                    anchors.fill: parent;color: "green";radius: 3;opacity: 0;z:0
                }
                Text {
                    id:language
                    text: modelData
                    anchors.fill: parent
                    anchors.margins: 4
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 14
                    z:1
                }
                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        combobox.state = ""
                        var preselection = choseitemText.text
                        if(modelData === combobox.items[0]){
                            choseitemText.text = "English"
                        }else if(modelData === combobox.items[1]){
                            choseitemText.text="中文"
                        }else if(modelData === combobox.items[2]){
                            choseitemText.text= "わぶん"
                        }
                        //choseitemText.text = modelData
                        if(choseitemText.text != preselection){
                            combobox.comboClicked()
                        }
                        listview.currentIndex =index
                        console.log(listview.currentIndex)
                        //handle the Language
                        //lanquageswitch.setLanguage(listview.currentIndex)
                    }
                    onEntered: {mousemoveHightLight.opacity=0.5}
                    onExited: {mousemoveHightLight.opacity=0}
                }
            }
            highlight: Rectangle{
                width: boxwidth-4
                height: boxheight
                color: "blue"
                radius: 3
            }
        }
        MouseArea{
            anchors.fill: dropdown
            hoverEnabled: true
            onClicked: {
                console.log("select number is",index)
            }
            onExited: {
                if(!containsMouse){
                    combobox.state=""
                }
            }
        }
    }
    states: State {
        name: "dropdown1"
        PropertyChanges {target: dropdown;height:boxheight*combobox.items.length}
    }
    transitions: Transition {
        NumberAnimation{target: dropdown;properties: "height";easing.type: Easing.OutExpo;duration: 300}
    }
}
