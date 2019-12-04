/**!
  @author: mettler toledo.
  @date: 2019.11.20
  @description: side navigations menu.
*/

import Style 1.0
import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    Drawer{
        id:drawerId
        edge: Qt.LeftEdge
        height: Layouts.viewHeight//480
        width: Layouts.drawerNavigationLeftWidth //160
        dragMargin: Qt.styleHints.startDragDistance
        //@disable-check M16 which is used to suppress the warning.
        Overlay.modal: Rectangle { color: "#99ffffff" }
        onPositionChanged: {
            if(position > 0){
                handleId.z=drawerId.z+1
            }else{
                handleId.z=drawerId.z
            }
        }
        // Load pages.
    }
    /**!
      handle icon of navigation
    */
    Image {
        id: handleId
        parent: window.overlay
        visible: drawerId.interactive
        width: Layouts.drawerIconLeftWidth
        source: drawerId.opened ? Images.drawerHandleLeftOpen:Images.drawerHandleLeftClosed
        x:(drawerId.width)*drawerId.position -1
        y:Layouts.viewHeight-handleId.height-Layouts.pageFooterHeight-Layouts.pageHeaderHgh

        MouseArea{
            id:handleAreaId
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: Qt.styleHints.startDragDistance-1
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            onClicked: {
                drawerId.open()
            }
        }
    }
}
