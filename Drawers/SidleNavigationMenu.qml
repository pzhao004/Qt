/**!
  @author: mettler toledo.
  @date: 2019.11.20
  @description: side navigations menu.
   SidleNavigationMenu{
        tempEdge: Qt.RightEdge
        anchors.right: parent.right
    }
*/

import Style 1.0
import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    property int flag: 0
    property alias tempEdge:drawerId.edge
    /**!
      drawer
    */
    Drawer{
        id:drawerId
        //z:100
        x:if(tempEdge === Qt.RightEdge){
              console.log("drawerId x")
                return Layouts.drawerNavigationRightX
            }else{
                return 0
          }
        width:if(tempEdge === Qt.LeftEdge){
                return Layouts.drawerNavigationLeftWidth //160
              }else if(tempEdge === Qt.RightEdge){
                return (Layouts.viewWidth-handleId.width*2-Layouts.drawerNavigationLeftWidth)
              }else{
                return Layouts.viewWidth//800
              }
        height: if(tempEdge === Qt.TopEdge){
                    return Layouts.viewHeight-handleId.height
                }else{
                    return Layouts.viewHeight//480
                }
        /**!
          color of background if side navigation is opened
        */
        //@disable-check M16 which is used to suppress the warning.
        Overlay.modal: Rectangle {
            color: "#99ffffff"
            //color: "lightblue"
        }
        edge: tempEdge

        dragMargin: if(tempEdge === Qt.RightEdge){
                        return Layouts.drawerNavigationLeftWidth+Qt.styleHints.startDragDistance
                    }else{
                        return Qt.styleHints.startDragDistance
                    }
        onPositionChanged: {
            if(drawerId.position === 1){
                handleId.z=drawerId.z+1
                methodMenuId.z=drawerId.z+1
            }else{
                handleId.z=drawerId.z
                methodMenuId.z=drawerId.z
            }
        }
        /**!
          loader contexts for navigations.
        */
        Loader{
            id:loaderId
            anchors.fill: parent
            source: if(tempEdge === Qt.TopEdge){
                        return "qrc:///Context/ContextTop.qml"
                    }else if(tempEdge === Qt.RightEdge){
                        return "qrc:///Context/ContextRight.qml"
                    }else{
                        return "qrc:///Context/ContextLeft.qml"
                    }
        }
    }
    /**!
      methods menu
    */
    Rectangle{
        id:methodMenuId
        parent: window.overlay
        visible: drawerId.interactive
        height: if(tempEdge === Qt.RightEdge){
                    return Layouts.viewHeight
                }else{
                    return 0
                }
        color: Colors.methodMenuBgColor
        width: if(tempEdge === Qt.RightEdge){
                   return Layouts.drawerNavigationLeftWidth
               }else{
                   return 0
               }
        x:if(tempEdge === Qt.RightEdge){
              return Layouts.viewWidth-((drawerId.width)*drawerId.position-1)-Layouts.drawerNavigationLeftWidth
          }else{
              return Layouts.viewWidth-Layouts.drawerNavigationLeftWidth
          }
        MouseArea{
            id:methodMenuAreaId
            parent:methodMenuId
            anchors.fill: parent
            onClicked: {
                console.log("on click",methodMenuId.enabled,drawerId.z,methodMenuId.z,methodMenuAreaId.z,handleId.z,handleAreaId.z,methodMenuAreaId.enabled)
            }
        }
        Loader{
            anchors.fill: parent
            source: if(drawerId.position>0 && tempEdge === Qt.RightEdge){
                        return "qrc:///Context/Results.qml"
                    }else{
                        return ""
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
        width: if(tempEdge === Qt.LeftEdge || tempEdge === Qt.RightEdge){
                    return Layouts.drawerIconLeftWidth
               }else{
                    return 115
               }
        height: if(tempEdge === Qt.TopEdge){
                    return Layouts.drawerIconTopHeight
                }else{
                    return 115
                }
        source:
            if(tempEdge === Qt.LeftEdge){
                drawerId.opened ? Images.drawerHandleLeftOpen:Images.drawerHandleLeftClosed
            }else if(tempEdge === Qt.RightEdge){
                drawerId.opened ? Images.drawerHandleRightOpen:Images.drawerHandleRightClosed
            }else{
                drawerId.opened ? Images.drawerHandleTopOpen:Images.drawerHandleTopClosed
            }
        x:if(tempEdge === Qt.LeftEdge){
                return (drawerId.width)*drawerId.position -1
            }else if(tempEdge === Qt.RightEdge){
                return Layouts.viewWidth-((drawerId.width)*drawerId.position-1)-handleId.width-Layouts.drawerNavigationLeftWidth
            }else{
              return (Layouts.viewWidth-handleId.width)/2
          }
        y:if(tempEdge === Qt.TopEdge){
              return (drawerId.height)*drawerId.position-1
          }else{
              return Layouts.viewHeight-handleId.height-Layouts.pageFooterHeight
          }

        MouseArea{
            id:handleAreaId
            anchors.top: parent.top
            anchors.topMargin: if(tempEdge === Qt.TopEdge){
                                   return Qt.styleHints.startDragDistance-1
                               }else{
                                   return 0
                               }
            anchors.left: parent.left
            anchors.leftMargin: if(tempEdge === Qt.LeftEdge){
                                    return Qt.styleHints.startDragDistance-1
                                }else{
                                    return 0
                                }
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.rightMargin: if(tempEdge === Qt.RightEdge){
                                    return Qt.styleHints.startDragDistance-1
                                }else{
                                    return 0
                                }
            onClicked: {
                console.log(handleId.x,handleId.y)
                drawerId.open()
            }
        }
    }
}
