import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Window 2.12

Window {
    id:root
    visible: true
    width: 400
    height: 240
    title: qsTr("Hello World")

    Rectangle{
            id: dst//(0,0)
        }

        ListView{
            id: view
            anchors.fill: parent
            anchors.margins: 10
            model: 20
            spacing: 1
            clip: true

            delegate: Rectangle{
                width: parent.width
                height: 50
                //产生随机颜色
                color: Qt.rgba(Math.random(),Math.random(),Math.random())
                Text {
                    anchors.centerIn: parent
                    text: index
                }
                MouseArea{
                    id: msa
                    anchors.fill: parent
                    onClicked: {
                        //相对于dst（0，0）点的位置坐标
                        var pos = dst.mapFromItem(msa,mouse.x, mouse.y);
                        console.log(pos.x,pos.y)
                    }
                }
            }
        }

        // 滚动条  风格样式以效果图未注
        Rectangle {
            id: scrollbar
            anchors.right: view.right
            anchors.top: view.top
            width: 7
            radius: 1
            height: view.height
            color: "lightgray"
            clip: true

            // 按钮
            Rectangle {
                id: button
                x: 0
                //view.visibleArea.yPosition表示一个变量,初始值为0,滚动条滚到底部时最大
                y: view.visibleArea.yPosition * scrollbar.height
                width: 8
                //滚动按钮的长度为view.height/view.contentHeight*scrollbar.height;与下方代码等价
                height: view.visibleArea.heightRatio * scrollbar.height;
                color: "green"
                radius: 3

                // 鼠标区域
                MouseArea {
                    id: mouseArea
                    anchors.fill: button
                    //使得按钮可以上下拖动
                    drag.target: button
                    drag.axis: Drag.YAxis
                    drag.minimumY: 0
                    drag.maximumY: scrollbar.height - button.height

                    // 拖动
                    onMouseYChanged: {
                        view.contentY = button.y / scrollbar.height * view.contentHeight
                    }
                }
            }
        }

}
