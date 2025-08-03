import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QMLNetworkAccessManager

Window {
    id: rootId
    width: 640
    height: 480
    visible: true
    title: qsTr("REST Client !")

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        ListView {
            id: listViewId
            model: myModel
            delegate: Rectangle {
                width: rootId.width
                height: textId.implicitHeight + 30
                color: "beige"
                border.color: "yellowgreen"
                radius: 5

                Text {
                    id: textId
                    width: parent.width
                    height: parent.height
                    anchors.centerIn: parent
                    text: modelData
                    font.pointSize: 13
                    wrapMode: Text.WordWrap
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Button {
            id: btnFetchPostId
            text: qsTr("Fetch posts")
            Layout.fillWidth: true
            onClicked: {
                Wrapper.fetchPosts()
            }
        }

        Button {
            id: btnRemoveLastId
            text: qsTr("Remove last")
            Layout.fillWidth: true
            onClicked: {
                Wrapper.removeLast()
            }
        }
    }
}
