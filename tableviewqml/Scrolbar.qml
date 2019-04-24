import QtQuick 2.7
import QtQuick.Controls 1.4

// 滚动条
Rectangle {
    id: scrollbar;
    opacity: 0
    // 绑定到ListView组件
    property TableView target : TableView{}

    width: 15; height: target.height;
    anchors.right: parent.right
    color: "#ccbfbf";radius: 10;clip: true;
    // 按钮
    Rectangle { id: button; x: 0;
        //y: tableView.visibleArea.yPosition * scrollbar.height;
        y:scrollbar.height
        width: 15;
        //height: tableView.visibleArea.heightRatio * scrollbar.height;
        height: scrollbar.height
        color: "#6D665C"; radius: 10;
        Text{ text:"☰";anchors.centerIn: parent}

        // 鼠标区域
        MouseArea {id: mouseArea;anchors.fill: button
            drag.target: button;drag.axis: Drag.YAxis;drag.minimumY: 0;drag.maximumY: scrollbar.height - button.height
            onPressed: {button.color = "#A4D3EE";fadeIn.start();}
            onReleased: {button.color = "#6D665C";fadeOut.start();}
            // 拖动
            onMouseYChanged: {
                target.contentY = button.y / scrollbar.height * tableView.contentHeight
            }
        }
    }
    // 移动时显隐滚动轴
//    Connections{
//        target: scrollbar.target


//        onMovingVerticallyChanged: {
//            if (target.movingVertically)
//                fadeIn.start();
//            else
//                fadeOut.start();
//        }
//        onMovingHorizontallyChanged: {
//            if (target.movingHorizontally)
//                fadeIn.start();
//            else
//                fadeOut.start();
//        }
//    }
    NumberAnimation { id:fadeIn;  target: scrollbar; properties: "opacity"; duration: 500; from:0; to:1 }
    NumberAnimation { id:fadeOut; target: scrollbar; properties: "opacity"; duration: 500; from:1; to:0 }
}
