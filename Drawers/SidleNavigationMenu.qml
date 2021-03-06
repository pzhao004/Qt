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
        width:(Layouts.viewWidth-handleId.width*2)
        height: Layouts.viewHeight//480
        //@disable-check M16 which is used to suppress the warning.
        Overlay.modal: Rectangle { color: "#99ffffff" }
        edge: Qt.RightEdge
        dragMargin: Layouts.drawerNavigationLeftWidth+Qt.styleHints.startDragDistance
        onPositionChanged: {
            if(drawerId.position === 1){
                handleId.z=drawerId.z+1
            }else{
                handleId.z=drawerId.z
            }
        }
        // Loader Pages.
    }
    /**!
      handle icon of navigation
    */
    Image {
        id: handleId
        parent: window.overlay
        visible: drawerId.interactive
        width: Layouts.drawerIconLeftWidth
        source:drawerId.opened ? Images.drawerHandleRightOpen:Images.drawerHandleRightClosed
        x:Layouts.viewWidth-((drawerId.width)*(drawerId.position)-1)-handleId.width
        y:Layouts.viewHeight-handleId.height-Layouts.pageFooterHeight

        MouseArea{
            id:handleAreaId
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.rightMargin:Qt.styleHints.startDragDistance-1
            onClicked: {
                console.log(handleId.x,handleId.y)
                drawerId.open()
            }
        }
    }
}
