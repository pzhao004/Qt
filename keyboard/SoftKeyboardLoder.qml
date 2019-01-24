import QtQuick 2.0

Rectangle{
    width: 500
    height: 360
//    Rectangle{
//        id:currTxt
//        width: parent.width
//        height: parent.height/8
//        anchors.left: parent.left
//        anchors.top: parent.top
//        border.width: 1

//        Text {
//            id:curIM
//            font.pixelSize: 18
//            anchors.centerIn: parent
//            color: "#c05018"
//            text: {
//                if(KBCtx.obName == "t1"){
//                        return KBCtx.curr1Str
//                } else if(KBCtx.obName== "t2"){
//                        return KBCtx.curr2Str
//                }else{
//                        return ""
//                }
//            }
//        }
//    }

    Loader{
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        //anchors.top: currTxt.bottom
        anchors.leftMargin: 15
        anchors.rightMargin: 5
        anchors.topMargin: 5
        anchors.bottomMargin: 5
        source:  "LayoutKeyboard.qml"
    }
}
