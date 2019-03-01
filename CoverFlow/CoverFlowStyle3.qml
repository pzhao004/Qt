import QtQuick 2.0

Rectangle{
    id: coverButton
    property int itemCount: 5
    property double panelWidth: parent.width*0.25
    property double panelHeight:parent.height*0.9
    property double delegateItemWidth: panelWidth*0.8
    property double delegateItemHeight: panelHeight*0.15
    property variant modelist: [qsTr("Menu1"),qsTr("Menu2"),qsTr("Menu3"),qsTr("Menu4"),qsTr("Menu5"),qsTr("Menu6")]
    width: panelWidth;height: panelHeight;anchors.verticalCenter: parent.verticalCenter;//color: "#9595ea";
    anchors.right: parent.right
    PathView{
        id:btnPathView
        anchors.fill: parent ; pathItemCount: itemCount
        preferredHighlightBegin: 0.5;preferredHighlightEnd: 0.5; path:btnPath

        model: coverButton.modelist
        delegate: Item{
            id:delegateItem
            width: delegateItemWidth; height: delegateItemHeight;
            scale: PathView.itemScale; opacity: PathView.itemAlpha; z:PathView.zOrder
            Rectangle{
                id:button
                anchors.fill: parent;anchors.margins: 2;radius:15;
                color: (delegateItem.opacity < 0.8 && delegateItem.opacity>0.6)&&itemArea.pressed ? "#42b342":"#156d15"
                Text{
                    anchors.fill: parent; anchors.margins: 1;
                    verticalAlignment: Text.AlignVCenter;horizontalAlignment: Text.AlignRight
                    font.pixelSize: 25;font.family: "Segoe UI";text:modelData
                }
            }
            MouseArea{
                id:itemArea
                anchors.fill: parent;
                onClicked: {
                        console.log("hello: ",modelData, delegateItem.z,index)
                }
            }
        }
    }
    Path{
        id:btnPath
        startX: panelWidth*0.8; startY: 20;                                  //100  0
        PathAttribute{name: "zOrder"; value: 0}
        PathAttribute{name: "itemAlpha"; value: 0.2}
        PathAttribute{name: "itemScale"; value: 0.6}

        PathLine{x:panelWidth*0.6; y: (panelHeight-40)*0.25+20}     //60   0.25
        PathAttribute{name: "zOrder"; value: 5}
        PathAttribute{name: "itemAlpha"; value: 0.5}
        PathAttribute{name: "itemScale"; value: 0.7}

        PathLine{x:panelWidth*0.4; y: (panelHeight-40)*0.5+20}   //40
        PathAttribute{name: "zOrder"; value: 10}
        PathAttribute{name: "itemAlpha"; value: 0.8}
        PathAttribute{name: "itemScale"; value: 1}

        PathLine{x:panelWidth*0.6; y:  (panelHeight-40)*0.75+20}          //60
        PathAttribute{name: "zOrder"; value: 5}
        PathAttribute{name: "itemAlpha"; value: 0.5}
        PathAttribute{name: "itemScale"; value: 0.7}

        PathLine{x:panelWidth*0.8; y: panelHeight-20}                  //100
        PathAttribute{name: "zOrder"; value: 0}
        PathAttribute{name: "itemAlpha"; value: 0.2}
        PathAttribute{name: "itemScale"; value: 0.6}
    }
}
