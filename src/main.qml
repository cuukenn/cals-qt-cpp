import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

Window {
    width: 320
    height: 500
    visible: true
    title: qsTr("Calculator")

    Column {
        spacing: 0  //相邻间距F
        anchors.fill: parent
        Rectangle {
            id: rsRect
            width: parent.width; height: parent.height*0.36
            GridLayout {
                rows:3
                columns: 1
                rowSpacing: 10
                anchors.fill: parent
                Text {
                    Layout.row: 0
                    Layout.column: 0
                    Layout.alignment: Text.AlignRight
                    Layout.rightMargin: 10
                    text: calsContext.lastNumber
                }
                Text {
                    Layout.row: 1
                    Layout.column: 0
                    Layout.alignment: Text.AlignRight
                    Layout.rightMargin: 10
                    text: calsContext.curOps
                }
                Text {
                    Layout.row: 2
                    Layout.column: 0
                    Layout.alignment: Text.AlignRight
                    Layout.rightMargin: 10
                    text: calsContext.curNumber
                }
            }
        }
        Rectangle {
            width: parent.width; height: parent.height-rsRect.height
            GridLayout {
                id: opsLayOut
                property variant operations: ["%", "CE", "C", "<=", "1/x", "x^2", "√x", "%", "7", "8", "9", "x", "4", "5", "6", "-", "1", "2", "3", "+", "+/-", "0", ".", "="]
                columns: 4
                rows: opsLayOut.operations.length/opsLayOut.columns
                anchors.margins: 10
                anchors.fill: parent
                Repeater {
                    model: opsLayOut.operations.length
                    Rectangle {
                        Layout.row: index/opsLayOut.columns
                        Layout.column: index%opsLayOut.columns
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Button {
                            anchors.fill: parent
                            Layout.alignment: Qt.AlignHCenter
                            text: opsLayOut.operations[index]
                            onClicked: {
                                calsContext.sendOps(opsLayOut.operations[index]);
                            }
                        }
                    }
                }

            }
        }
    }
}
