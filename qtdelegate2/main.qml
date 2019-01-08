import QtQuick 2.10
import QtQuick.Window 2.10

Window {
    id:root
    visible: true
    width: 400
    height: 240
    title: qsTr("Hello World")

    ListModel{
        id:list_model
        ListElement{name:"Jason";age: 21}
        ListElement{name:"Jbson";age: 22}
        ListElement{name:"Jdson";age: 23}
        ListElement{name:"Jcson";age: 24}
        ListElement{name:"Jeson";age: 25}
        ListElement{name:"Jkson";age: 26}
        ListElement{name:"Jlson";age: 27}
        ListElement{name:"Jnson";age: 28}
        ListElement{name:"Jeson";age: 29}
        ListElement{name:"Jsson";age: 30}
    }
    Component{
        id:delegate_rect
        Rectangle{
            width: root.width
            height: root.height/8
            color: Qt.rgba(Math.random(),Math.random(),Math.random(),Math.random())
            Grid{
                spacing: 10
                anchors.centerIn: parent
                Text{text:name}
                Text{text:age}
            }
            MouseArea{
                id:msa
                anchors.fill: parent
                onClicked: {
                    console.log(mouseX,mouseY)
                }
            }
        }
    }
    ListView{
        id:view
        anchors.fill:parent
        anchors.margins:5
        model: list_model
        delegate: delegate_rect
        spacing: 1
        clip:true
    }
    //scroll bar
    Rectangle{
        id:scrollbar
        anchors.right: view.right
        anchors.top:view.top
        width: 5
        radius:1
        height: view.height
        color: "lightgray"
        clip:true
        //scroll button
        Rectangle{
            id:button
            x:0
            y:view.visibleArea.yPosition*scrollbar.height
            width: 5
            height: view.visibleArea.heightRatio*scrollbar.height
            color:"blue"
            radius: 3
            MouseArea{
                id:mousearea
                anchors.fill: button
                //drag the button
                drag.target: button
                drag.axis: Drag.YAxis
                drag.minimumY: 0
                drag.maximumY: scrollbar.height-button.height
                onMouseYChanged: {
                    view.contentY=button.y/scrollbar.height*view.contentHeight
                }
            }
        }
    }
}
