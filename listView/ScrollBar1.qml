import QtQuick 2.0

Rectangle{
    property ListView target : ListView{}
    id:scrollbar
    anchors.right: view.right
    anchors.top:view.top
    width: 5
    radius:1
    height: view.height
    color: "white"
    clip:true
    //scroll button
    Rectangle{
        id:button
        x:0
        y:view.visibleArea.yPosition*scrollbar.height
        width: 5
        height: view.visibleArea.heightRatio*scrollbar.height
        color:"#0c0c4d"
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
