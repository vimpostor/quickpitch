import QtQuick 2.10
import QtQuick.Extras 1.4
import QtQuick.Controls 2.12

CircularGauge {
	property string noteName: "0"
	property real accuracy: 0
	value: accuracy
	minimumValue: -1
	maximumValue: 1
	tickmarksVisible: false
	Label {
		anchors.centerIn: parent
		text: noteName
	}
}
