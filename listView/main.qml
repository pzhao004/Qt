import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.12

Window {
    id:root
    visible: true
    width: 800
    height: 480
    objectName: "rootObject"
    title: qsTr("Virtual Key Board Demo")

    Datashow{
        smooth: true
        width: parent.width
        height: parent.height*0.4
        anchors.top: parent.top
    }

        SoftKeyboardLoder{
            id:loader
            smooth: true
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: parent.height * 0.6
            visible: KBCtx.active
        }

}
