import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
//import "canvasinit.js" as Initcanvas
Window {
    id:root
    visible: true
    width: 800
    height: 480
    objectName: "rootObject"
    title: qsTr("Line Chart")

    Rectangle{
        id:canvasBackground
        color: "black"
        width: parent.width*0.4    //320
        height: parent.height*0.4  //192
        border.color: "#90ee90"
        anchors.centerIn: parent
        Canvas{
            id:canvas
            anchors.fill: parent
            property int wid: parent.width
            property int valueoftime: phdata.timeValue
            property int xl: 0
            property int yl: canvasBackground.height/2
            property var index: 0
            property var m_timevalue: 0
            property bool endtag: true
            property variant ph_array: []
            property int next_start: 1
            onPaint: {
                var m_phvalue;
                var ctx = getContext("2d");
                if(phdata.timeValue != 0){
                    if(phdata.phValue > 7){
                        m_phvalue=yl-phdata.phValue;
                    }else if(phdata.phValue==7){
                        m_phvalue=yl;
                    }else{
                        m_phvalue=yl+phdata.phValue;
                    }
                    ph_array.push(m_phvalue)
                }
                if(endtag===true){
                    ctx.strokeStyle = "#08b95a"; //set color of pen
                    ctx.lineJoin = "round";      //set point of the pen
                    ctx.lineWidth = 1;           //set the line width
                    ctx.fillStyle = "black"
                    ctx.beginPath();
                    ctx.moveTo(xl,yl)
                    endtag=false
                }else if(phdata.timeValue - wid >= 0){
                    ctx.reset();
                    ctx.strokeStyle = "#08b95a";
                    ctx.lineJoin = "round";
                    ctx.lineWidth = 1;
                    ctx.beginPath();
                    ctx.moveTo(xl,yl);
                    console.log(ph_array[next_start]);
                    var i;
                    console.log(next_start,0)
                    for(i=0;i<31;i++){
                        ctx.lineTo(i*10,ph_array[i+next_start]);
                        ctx.stroke();
                    }
                    next_start++;
                    console.log(next_start,1)
                    m_timevalue= phdata.timeValue-index*wid;
                    //ctx.globalCompositeOperation="xor";
                    if(phdata.phValue > 7){
                        m_phvalue=yl-phdata.phValue;
                    }else if(phdata.phValue==7){
                        m_phvalue=yl;
                    }else{
                        m_phvalue=yl+phdata.phValue;
                    }
                    ctx.lineTo(320,m_phvalue);
                    ctx.stroke();
                }else{
                    if(phdata.phValue > 7){
                        m_phvalue=yl-phdata.phValue;
                    }else if(phdata.phValue==7){
                        m_phvalue=yl;
                    }else{
                        m_phvalue=yl+phdata.phValue;
                    }
                    ctx.lineTo(phdata.timeValue,m_phvalue);
                    ctx.stroke();
                }
            }
            onValueoftimeChanged: {
                canvas.requestPaint()
            }
        }
    }

    signal sendStartEvent()
    Text{
        id:text_c
        height: 20
        width: 40
        text:phdata.timeValue
        anchors.bottom: parent.bottom
    }
    Text{
        id:text_s
        height: 20
        width: 40
        text:phdata.phValue
        anchors.bottom: parent.bottom
        anchors.left: text_c.right
    }

    Button{
        id:btn_start
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        text: "Start"
        onClicked: {
            root.sendStartEvent()
        }
    }
}
