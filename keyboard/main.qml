import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.12

Window {
    id:root
    visible: true
    width: 800
    height: 480
    title: qsTr("Virtual Key Board Demo")

    Rectangle{
        width: root.width
        height: root.height

        Column{
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
                    objectName: "t1"
                    width: parent.width*0.618
                    height: parent.height*0.618
                    anchors.centerIn: parent
                    text: KBCtx.curr1Str
                    horizontalAlignment:Text.AlignHCenter;verticalAlignment:Text.AlignVCenter
                    activeFocusOnPress: true
                }
                MouseArea{
                    id: mouseArea1
                    anchors.fill: parent
                    onClicked: {
                        KBCtx.doInput(t1.objectName)
                        t1.focus=true
                        console.log("t2.focus:",t2.focus)
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
                    objectName: "t2"
                    width: parent.width*0.618
                    height: parent.height*0.618
                    anchors.centerIn: parent
                    text: KBCtx.curr2Str
                    horizontalAlignment:Text.AlignHCenter;verticalAlignment:Text.AlignVCenter
                    MouseArea{
                        id: mouseArea
                        anchors.fill: parent
                        onClicked: {
                            KBCtx.doInput(t2.objectName)
                            t2.focus=true
                            console.log("t1.focus:",t1.focus)
                        }
                    }
                }
            }
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
}
