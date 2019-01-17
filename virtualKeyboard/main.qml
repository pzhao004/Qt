import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id:root
    visible: true
    width: 800
    height: 480
    title: qsTr("Virtual Key Board")

    Rectangle{
        width: root.width
        height: root.height

        Column{
            //anchors.centerIn: parent
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            //first Line
            Rectangle{
                id:firstRect
                width: root.width*4/5
                height: root.height/7
                border.width: 3
                border.color: t1.focus? "orange" : "blue"
                radius: 10

                TextInput{
                    id:t1
                    width: parent.width*0.618
                    height: parent.height*0.618
                    anchors.centerIn: parent
                    text: "Fist Line"
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            KBCtx.doInput(t1.text)
                            t1.text=""
                        }
                    }
                }
            }
            //second Line
            Rectangle{
                id:secRect
                width: root.width*4/5
                height: root.height/7
                border.width: 3
                border.color: t2.focus? "orange" : "gray"
                radius: 10

                TextInput{
                    id:t2
                    width: parent.width*0.618
                    height: parent.height*0.618
                    anchors.centerIn: parent
                    text: "Second Line"
                    MouseArea{
                        id: mouseArea
                        anchors.fill: parent
                        onClicked: {
                            KBCtx.doInput(t2.text)
                            t2.text=""
                        }
                    }
                }
            }
        }

        SoftKeyboardLoder{
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: parent.height * 0.6
            visible: KBCtx.active
        }
    }
}
