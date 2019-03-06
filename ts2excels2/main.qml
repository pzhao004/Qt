import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2

Window {
    id:root
    visible: true
    maximumWidth: 800;maximumHeight: 480;
    minimumWidth: 800;minimumHeight: 480;
    title: qsTr("Ts File Translate To Xlxs File")
    property string bgNormalSource: "./images/Controls_bg_normal.png"
    property string bgSelectSource: "./images/Controls_bg_disabled.png"

    FileScan{
        anchors.fill: parent;anchors.margins: 50
    }


}
