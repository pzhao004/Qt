/**!
  @author: mettler toledo.
  @date: 2019.11.20
  @description: side navigations menu.
    if you want use the SideNavigationRight,
    example:
    SideNavigationRight{
        smooth: true
        height: Layouts.viewHeight
        width: Layouts.drawerNavigationRightWidth
    }
*/

import Style 1.0
import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    id:drawer
    x:closeX
    property real flag: 0
    property bool open:false
    property real velocity: 0
    property real oldMouseX: 0
    property Item rootItem: parent
    property int position: Qt.RightEdge
    property int mousePosition: Layouts.viewWidth-Layouts.drawerNavigationRightWidth

    readonly property bool rightEdge: position === Qt.RightEdge
    readonly property int closeX: rightEdge ? rootItem.width : -drawer.width
    readonly property int openX: rightEdge ? (rootItem.width- drawer.width):0
    readonly property int maxnum_X: rightEdge ? rootItem.width: 0
    readonly property int minnum_X: rightEdge ? (rootItem.width-drawer.width): -drawer.width

    onOpenChanged:completeSlideDirection()
    onRightEdgeChanged: setupAnchors()
    function setupAnchors(){
        rootItem = parent;

        optionIcon.anchors.right=undefined
        optionIcon.anchors.left=undefined

        mouse.anchors.left=undefined
        mouse.anchors.right=undefined

        if(rightEdge){
            mouse.anchors.right=mouse.parent.right
            optionIcon.anchors.right=drawer.left
        }else{
            mouse.anchors.left=mouse.parent.left
            optionIcon.anchors.left=drawer.right
        }
        slideAnimation.enabled=false;
        drawer.x= rightEdge? rootItem.width : -drawer.width
        slideAnimation.enabled=true;
    }
    function handleRelease(velocity,oldMouseX){
        /*judge right slide drawer.*/
        if(flag === 0){
            if(velocity>oldMouseX || (velocity===mousePosition && oldMouseX===mousePosition)){
                open=true
                completeSlideDirection()
                velocity=0
                oldMouseX=0
            }else{
                open=false
                completeSlideDirection()
                velocity=0
                oldMouseX=0
            }
        }else{
            if(velocity<oldMouseX || (velocity===mousePosition && oldMouseX===mousePosition)){
                open=true
                completeSlideDirection()
                velocity=0
                oldMouseX=0
            }else{
                open=false
                completeSlideDirection()
                velocity=0
                oldMouseX=0
            }
        }

    }
    function completeSlideDirection(){
        if(open){
            drawer.x=openX
        }else{
            drawer.x=closeX
            Qt.inputMethod.hide()
        }
    }
    function handleClick(mouse){
        if(rightEdge && mouse.x>0 && mouse.x<optionIcon.width){
            open=true
        } else if(rightEdge && (mouse.x<mousePosition-1)){
            open=false
        }
    }

    Behavior on x{
        id:slideAnimation
        enabled: !mouse.drag.active
        NumberAnimation{
            duration: 200
            easing.type: Easing.OutCubic
        }
    }

    NumberAnimation {
        id:holdAnimation
        target: drawer
        property: "x"
        running: false
        /*to:closeX+(openMarginSize*(rightEdge? -1:1))*/
        to:closeX
        duration: 200
        easing.type: Easing.InOutQuad
    }

    /*MouseArea*/
    MouseArea{
        id:mouse
        parent: rootItem
        y:rootItem.y
        width: open ? rootItem.width: optionIcon.width
        height: rootItem.height

        drag.target: drawer
        drag.axis: Qt.Horizontal
        drag.minimumX: minnum_X
        drag.maximumX: maxnum_X
        drag.onActiveChanged: if(active) {holdAnimation.stop()}

        onClicked: { handleClick(mouse)}
        onPressed: {if(!open) holdAnimation.restart()}
        onReleased: {handleRelease(velocity,oldMouseX)}

        onMouseXChanged: {
            /*record the last x postion*/
            if(flag===0){
                velocity = drawer.x;
                flag=1;
            }else{
                oldMouseX=drawer.x;
                flag=0;
            }
        }
        z: open ? 100:0
    }
    Connections{
        target: rootItem
        onWidthChanged:{
            slideAnimation.enabled=false;
            completeSlideDirection();
            slideAnimation.enabled=true;
        }
    }
    Rectangle {
           id: backgroundBlackout
           parent: rootItem
           anchors.fill: parent
           //opacity: 0.5 * Math.min(1, Math.abs(drawer.x - closeX) / rootItem.width/2)
           color: "#99ffffff"
           //color: "black"
       }
    /*icon of side drawer navigation.*/
    Image{
        id: optionIcon
        anchors.right: drawerId.left
        source: Images.drawerHandleRightClosed
        y:Layouts.viewHeight-optionIcon.height-Layouts.pageFooterHeight-Layouts.pageHeaderHgh
    }

    Rectangle{
        id:contextId
        anchors.fill: parent
        color: Colors.colorActionButtonText_re
    }
}
