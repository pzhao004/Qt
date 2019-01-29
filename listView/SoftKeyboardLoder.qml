import QtQuick 2.0

Rectangle{
    id:loaderkeyboard
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
