import QtQuick 2.10
import QtQuick.Layouts 1.3

Item {
	property int octave: 4
	implicitWidth: octaveRow.implicitWidth
	Row {
		id: octaveRow
		spacing: 32
		Repeater {
			model: 7
			delegate: Rectangle {
				width: 40
				height: width
				color: octave === index ? "Red" : "White"
				Text {
					anchors.centerIn: parent
					text: index
				}
			}
		}
	}
}
