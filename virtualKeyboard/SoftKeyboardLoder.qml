import QtQuick 2.0

Rectangle{
    width: 500
    height: 360
    border.width: 1
    Rectangle{
        id:currTxt
        width: parent.width
        height: parent.height/8
        anchors.left: parent.left
        anchors.top: parent.top
        border.width: 1

        Text {
            id:curText
            font.pixelSize: 18
            anchors.centerIn: parent
            color: "#c05018"
            text: ""//KBCtx.currIM
        }
    }

    Loader{
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: currTxt.bottom
        anchors.bottom: parent.bottom
        anchors.margins: 5

        source: {
            if(KBCtx.currStr === "AI"){
                return "LayoutKeyboard.qml"
            }else{
                return "LayoutKeyboard.qml"
            }
        }
    }
}
