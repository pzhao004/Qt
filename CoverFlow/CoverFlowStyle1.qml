import QtQuick 2.0

Rectangle{
    id:coverFlow
    color: "#d7a7a7";width: parent.width;height: parent.height
    ListModel{
        id:model
        ListElement{url:"./1.png"}
        ListElement{url:"./2.png"}
        ListElement{url:"./3.png"}
        ListElement{url:"./4.png"}
        ListElement{url:"./5.png"}
        ListElement{url:"./6.png"}
    }
    property int itemCount: 5
    PathView{
        id:pathView
        path:coverFlowPath
        pathItemCount: coverFlow.itemCount
        anchors.fill: parent
        preferredHighlightBegin: 0.5; preferredHighlightEnd: 0.5;
        model: model
        delegate: Item{
            id:delegateItem
            width: 250;height: 250; scale: PathView.iconScale; z: PathView.iconZ
            Image{
                id:image
                source: url
                width: delegateItem.width;height: delegateItem.height
            }
                ShaderEffect{
                    anchors.top: image.bottom;anchors.left: image.left;
                    width: image.width;height: image.height;
                    property variant source: image
                    property size sourceSize: Qt.size(0.5 /image.width, 0.5/image.height);
                    fragmentShader:
                        "varying highp vec2 qt_TexCoord0;
                                                uniform lowp sampler2D source;
                                                uniform lowp vec2 sourceSize;
                                                uniform lowp float qt_Opacity;
                                                void main() {

                                                    lowp vec2 tc = qt_TexCoord0 * vec2(1, -1) + vec2(0, 1);
                                                    lowp vec4 col = 0.25 * (texture2D(source, tc + sourceSize) + texture2D(source, tc- sourceSize)
                                                    + texture2D(source, tc + sourceSize * vec2(1, -1))
                                                    + texture2D(source, tc + sourceSize * vec2(-1, 1)));
                                                    gl_FragColor = col * qt_Opacity * (1.0 - qt_TexCoord0.y) * 0.2;
                                                }"
                }
            transform: Rotation{
                origin.x:image.width/2.0
                origin.y:image.height/2.0
                axis{x:0; y:1; z:0}
                angle:delegateItem.PathView.iconAngle
            }
        }     
    }

    Path{
            id:coverFlowPath
            startX: 0
            startY: coverFlow.height/3

            PathAttribute{name:"iconZ";         value: 0}
            PathAttribute{name:"iconAngle";value: 70}
            PathAttribute{name:"iconScale"; value: 0.6}

            PathLine{x:coverFlow.width/2;y:coverFlow.height/3}

            PathAttribute{name:"iconZ";         value: 100}
            PathAttribute{name:"iconAngle";value: 0}
            PathAttribute{name:"iconScale"; value: 1.0}

            PathLine{x:coverFlow.width;y:coverFlow.height/3}

            PathAttribute{name:"iconZ";         value: 0}
            PathAttribute{name:"iconAngle";value: -70}
            PathAttribute{name:"iconScale"; value: 0.6}
            PathPercent{value:1.0}
    }
}
