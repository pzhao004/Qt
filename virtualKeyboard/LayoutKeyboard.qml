import QtQuick 2.0
import QtQuick.Controls 2.4

Item {
    id:kbloader
    width: 500
    height: 360

    property string currString: KbdMode.currString
    property string initString: ""                  // Used in function group rename screen
    property string mode: KbdMode.inputMode //need to bind to mode

    property string strVal;
    property bool hasBeep:true

    Rectangle {
        id: pinYin
        anchors.top: parent.top
        width: parent.width
        height: 50
        border.width:1
    }

    Flow{
        id: keyFlow
        anchors.bottom: parent.bottom
        width: parent.width
        height: parent.height-pinYin.height
        spacing: KbdMode.keySpacing

        property int  numOfRow: (KbdMode.keyRows!==0) ? KbdMode.keyRows : 4
        property int  numOfCol:   (KbdMode.rowCells!==0) ? KbdMode.rowCells : 20
        property int  cellHieght:   (keyFlow.height-keyFlow.spacing*(numOfRow-1))/numOfRow
        property int  cellWidth:    (keyFlow.width-keyFlow.spacing*(numOfCol-1))/numOfCol

        Repeater{
            model: KbdMode
            delegate: keyItem
        }
    }

    Component{
        id:keyItem
        Rectangle{
            id:drawer
            width:keyFlow.cellWidth * span + keyFlow.spacing * (span - 1) - 1
            height: keyFlow.cellHieght
            BorderImage {
                source:  {
                    if(keyColor === "green"){
                        console.log("green");
                            if(keyMA.pressed){
                                return "./pix/bg_green_press.png"
                            }else{
                                return "./pix/bg_green_normal.png"
                            }
                    }else if(keyColor === "blue"){
                        console.log("blue");
                            if (keyMA.pressed) {
                                return "./pix/bg_blue_press.png"
                            } else {
                                return "./pix/bg_blue_normal.png"
                            }
                    }else{
                            if (keyMA.pressed) {
                                console.log("button")
                                return "./pix/bg_button_press.png"
                            } else {
                                return "./pix/bg_button_normal.png"
                            }
                    }
                }
                visible: !isEmpty
                anchors.fill: parent
                border.left: 10
                border.right:10
                border.top:10
                border.bottom: 10

                Image {
                    anchors.centerIn: parent
                    visible: isIcon
                    source: pic != "" ? ("./pix/" + pic) : ""
                }
                Text{
                    id:keyLabel
                    anchors.centerIn: parent
                    font.pixelSize: 20
                    visible: !isIcon
                    color: keyColor === "" ? "black":"white"
                    text: {
                        if(txt=== "Space"){
                            return ""; //"[" + KBCtx.currIM + "]";
                        }else if(txt === "Mode"){
                            return "ssss";
                        }else{
                            return txt;
                        }
                    }
                }
                Image {
                    anchors.centerIn: parent
                    visible: isIcon
                    source: pic !== "" ? "./pix/" + pic  : ""
                }

                MouseArea{
                    id:keyMA
                }
            }
        }
    }
}
