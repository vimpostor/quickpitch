import QtQuick 2.10
import QtQuick.Extras 1.4

import Fluid.Controls 1.0

CircularGauge {
	property string noteName: "0"
	property real accuracy: 0
	value: accuracy
	minimumValue: -1
	maximumValue: 1
	tickmarksVisible: false
	HeadlineLabel {
		anchors.centerIn: parent
		text: noteName
	}
}
