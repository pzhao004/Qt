/**!
  @author: mettler toledo.
  @date: 2019.11.20
  @description: side navigations menu.
*/

import Style 1.0
import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    id:drawer
    x:closeX
    property real flagT: 0
    property bool open:false
    property real velocity: 0
    property real oldMouseX: 0
    property Item rootItem: parent
    property int position: Qt.RightEdge
    property int edgeValue: Layouts.viewWidth-Layouts.drawerNavigationRightWidth

    readonly property bool rightEdge: position === Qt.RightEdge
    readonly property int closeX: rightEdge ? rootItem.width-Layouts.drawerNavigationRightWidth : -drawer.width+Layouts.drawerNavigationRightWidth
    readonly property int openX: rightEdge ? rootItem.width-drawer.width  : 0
    readonly property int mininum_X: rightEdge ? rootItem.width-drawer.width: -drawer.width
    readonly property int maxnum_X: rightEdge ? rootItem.width-Layouts.drawerNavigationRightWidth: 0
    readonly property int sideDuration: 200
    readonly property int pullThreshold: drawer.width*0.5

    onOpenChanged:completeSlideDirection()
    onRightEdgeChanged: setupAnchors()
    function setupAnchors(){
        console.log("enter set up...")
        rootItem = parent;

        optionIcon.anchors.right=undefined
        optionIcon.anchors.left=undefined

        mouse.anchors.left=undefined
        mouse.anchors.right=undefined

        if(rightEdge){
            //console.log("set up right .....")
            mouse.anchors.right=drawer.left
            optionIcon.anchors.right=drawer.left
        }else{
            //console.log("set up left ......")
            mouse.anchors.left=mouse.parent.left
            optionIcon.anchors.left=drawer.right
        }
        slideAnimation.enabled=false;
        drawer.x= rightEdge? (rootItem.width-Layouts.drawerNavigationRightWidth) : -drawer.width
        slideAnimation.enabled=true;
        //console.log("set up end function...")
    }
    function handleRelease(velocity,oldMouseX){
        //console.log("flagT=",flagT,"velocity=",velocity,"oldMouseX=",oldMouseX)
        /*judge right slide drawer.*/
        if(flagT === 0){
            if(velocity>oldMouseX || (velocity===edgeValue && oldMouseX===edgeValue)){
                //console.log("tag 0 open")
                open=true
                completeSlideDirection()
                velocity=0
                oldMouseX=0
            }else{
                //console.log("tag 0 close")
                open=false
                completeSlideDirection()
                velocity=0
                oldMouseX=0
            }
            flagT=1
        }else{
            if(velocity<oldMouseX || (velocity===edgeValue && oldMouseX===edgeValue)){
                //console.log("tag 1 open")
                open=true
                completeSlideDirection()
                velocity=0
                oldMouseX=0
            }else{
                //console.log("tag 1 close")
                open=false
                completeSlideDirection()
                velocity=0
                oldMouseX=0
            }
            flagT=0
        }

    }
    function completeSlideDirection(){
        //console.log("enter complete...")
        if(open){
            //console.log("complete open")
            drawer.x=openX
        }else{
            //console.log("complete close")
            drawer.x=closeX
            Qt.inputMethod.hide()
        }
    }
    function handleClick(mouse){
        //console.log("mouse.x=", mouse.x, "flagT:", flagT)
        if(rightEdge && flagT===1){
            open=true
        } else if(rightEdge && flagT===0){
            open=false
        }
    }

    Behavior on x{
        id:slideAnimation
        enabled: !mouse.drag.active
        NumberAnimation{
            duration: sideDuration
            easing.type: Easing.OutCubic
        }
    }

    NumberAnimation {
        id:holdAnimation
        target: drawer
        property: "x"
        running: false
        to:closeX
        duration: sideDuration
        easing.type: Easing.InOutQuad
    }

    /*MouseArea*/
    MouseArea{
        id:mouse
        parent: rootItem
        y:open? 0 : Layouts.viewHeight-height-Layouts.pageFooterHeight-Layouts.pageHeaderHgh
        width: open ? Layouts.viewWidth:Layouts.drawerIconRightWidth
        height: open ? Layouts.viewHeight: optionIcon.height

        drag.target: drawer
        drag.axis: Qt.Horizontal
        drag.minimumX: mininum_X
        drag.maximumX: maxnum_X
        drag.onActiveChanged: if(active) {holdAnimation.stop()}

        onClicked: { handleClick(mouse)}
        onPressed: {if(!open) holdAnimation.restart()}
        onReleased: {handleRelease(velocity,oldMouseX)}

        onMouseXChanged: {
            //console.log("mouse x changed...","mouse.x=",mouse.x, "oldMouseX=", oldMouseX)
            /*record the last x postion*/
            if(flagT===0){
                velocity = drawer.x;
                console.log("velocity: ",velocity)
            }else{
                oldMouseX=drawer.x;
                console.log("oldMouseX: ",oldMouseX)
            }
        }
        z: open ? 3:0
    }
    Connections{
        target: rootItem
        onWidthChanged:{
            //console.log("width changed...")
            slideAnimation.enabled=false;
            completeSlideDirection();
            slideAnimation.enabled=true;
        }
    }
    Rectangle {
        id: backgroundBlackout
        parent: drawer
        anchors.fill: parent
        anchors.right: drawer.left
        opacity: 0.9 * Math.min(1, Math.abs(drawer.x - closeX) / rootItem.width/2)
        color: "whitesmoke"
    }
    /*icon of side drawer navigation.*/
    Image{
        id: optionIcon
        anchors.right: drawer.left
        anchors.rightMargin: 0
        width: Layouts.drawerIconRightWidth
        source:open? Images.drawerHandleRightOpen:Images.drawerHandleRightClosed
        y:Layouts.viewHeight-height-Layouts.pageFooterHeight-Layouts.pageHeaderHgh
    }
    Rectangle{
        anchors.fill: parent
        color: Colors.colorActionButtonText_re
    }

}
