/**!
  @author: mettler toledo.
  @date: 2019.11.20
  @description: side navigations top.
*/

import Style 1.0
import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    Drawer{
        id:drawerId
        z:Layouts.depZ
        width: Layouts.viewWidth //800
        height: Layouts.viewHeight-handleId.height
        //@disable-check M16 which is used to suppress the warning.
        Overlay.modal: Rectangle {
            color: "#99ffffff"
        }
        edge: Qt.TopEdge
        dragMargin: Qt.styleHints.startDragDistance
        onPositionChanged: {
            if(position>0){
                handleId.z=drawerId.z+1
            }else{
                handleId.z=drawerId.z
            }
        }
    }
    /**!
      handle icon of navigation
    */
    Image {
        id: handleId
        parent: window.overlay
        visible: drawerId.interactive
        height: Layouts.drawerIconTopHeight
        source:drawerId.opened ? Images.drawerHandleTopOpen:Images.drawerHandleTopClosed
        x:(Layouts.viewWidth-handleId.width)/2
        y:(drawerId.height)*drawerId.position-1

        MouseArea{
            id:handleAreaId
            anchors.top: parent.top
            anchors.topMargin: Qt.styleHints.startDragDistance-1
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            onClicked: {
                console.log(handleId.x,handleId.y)
                drawerId.open()
            }
        }
    }
}
