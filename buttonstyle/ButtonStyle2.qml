import QtQuick 2.0

Rectangle {
    id:root
    width: 136
    height: 50
    property bool selected: false
    property bool selectAuto: true
    property string bgNormalSource: "./pic/popup-small_workaction_2_2_di.png"
    property string bgSelectedSource: "./pic/popup-small_workaction_prim_re.png"
    property string bgNormalIcon: "./pic/placeholder_valuepanel_re.png"
    property string bgSelectedIcon: "./pic/placeholder_white.png"
    signal clicked();
    states: [
        State {
                    PropertyChanges { target: btn; source: bgNormalSource}
                    PropertyChanges { target: smallicon; source: bgNormalIcon}
                    when: !selected
        },
        State{
                    PropertyChanges {target:btn; source: bgSelectedSource}
                    PropertyChanges { target: smallicon; source: bgSelectedIcon}
                    when: selected
                }
    ]
    Image{
        id:btn
        anchors.fill: parent
        anchors.verticalCenter: parent.verticalCenter
        Image{
            id:smallicon
            anchors.top: parent.top;anchors.horizontalCenter: parent.horizontalCenter
        }
        Text{
            anchors.bottom: parent.bottom;anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter;horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 25;font.family: "Segoe UI";
            text: qsTr("Read")
        }
    }
    MouseArea{
        id:mainMouse
        anchors.fill: parent
        onClicked: {root.clicked()}
        onReleased: {
            if(selectAuto){
                selected = !selected
                if(selected){
                    console.log(selected,"start")
                }else{
                    console.log(selected,"stop")
                    confirm.open()
                }
            }
        }
    }
}
