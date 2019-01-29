import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle{
    id:listview

    ListView{
            id:view
            visible: true
            width: listview.width
            height: listview.height
            boundsBehavior: Flickable.StopAtBounds
            model:DesignBLL.getData()
            delegate:Rectangle {
                height: view.height/4
                width: parent.width
                TextField{
                        id:txi
                        objectName: "txi"
                        height: parent.height - 1
                        width: parent.width/2
                        anchors.left: parent.left
                        text: modelData.str
                        focus: modelData.textFocus
                        style: TextFieldStyle{
                            background: Image{
                                height: view.height/4
                                width: view.width/2
                                source: txi.focus ?  "./pix/bg_intput_press.png":"./pix/bg_intput_normal.png"
                            }
                        }
                        onFocusChanged: {
                            if(focus){
                                KBCtx.doInput(index,txi.objectName)
                            }
                        }
                    }
                TextField{
                        id:txf
                        objectName: "txf"
                        height: parent.height - 1
                        width: parent.width/2
                        anchors.right: parent.right
                        text: modelData.str2
                        focus: modelData.textFocus
                        style: TextFieldStyle{
                            background: Image{
                                height: view.height/4
                                width: view.width/2
                                source: txf.focus ?  "./pix/bg_intput_press.png":"./pix/bg_intput_normal.png"
                            }
                        }
                        onFocusChanged: {
                            if(focus){
                                KBCtx.doInput(index,txf.objectName)
                            }
                        }
                    }
                Rectangle{
                    color: "#0c0c4d"
                    width: listview.width
                    height: 1
                }
            }
     }

    //scrollbar1
    ScrollBar1{
        target: view
    }
}


