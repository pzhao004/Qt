import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    //maximumHeight: 480;minimumHeight: 480
    //maximumWidth: 800;minimumWidth: 800
    width: 800;height: 480
    title: qsTr("Hello World")

    CoverFlowStyle2{z:1}
    CoverFlowStyle1{z:0}
    CoverFlowStyle3{z:1}
}
