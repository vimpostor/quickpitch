import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import QtCharts 2.2
import QtQuick.Layouts 1.12

import PitchDetector 1.0

ApplicationWindow {
	id: root
	visible: true
	width: 640
	height: 480
	title: "Quick Pitch"
	header: ToolBar {
		RowLayout {
			anchors.fill: parent
			Button {
				text: qsTr("Settings")
				flat: true
				onClicked: {
					settings.open();
				}
			}
			Button {
				text: qsTr("Quit")
				flat: true
				onClicked: close();
			}
		}
	}
	Settings {
		id: settings
	}
	ChartView {
		id: chartView
		anchors.top: piano.bottom
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.bottom: accuracyIndicator.top
		legend.visible: false
		margins.top: 0
		margins.left: 0
		margins.bottom: 0
		margins.right: 0
		ValueAxis {
			id: axisX
			min: 0
			max: 7999
			labelsVisible: false
			gridVisible: false
		}
		ValueAxis {
			id: axisY
			min: -1
			max: 1
			labelsVisible: false
			gridVisible: false
		}
		LineSeries {
			id: lineSeries
			axisX: axisX
			axisY: axisY
			useOpenGL: true
			Component.onCompleted: {
				pitchDetector.setLineSeries(lineSeries);
			}
		}
	}
	Piano {
		id: piano
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.top: parent.top
		height: parent.height / 4
		noteName: pitchDetector.confidentPitch.note
	}
	NoteAccuracyIndicator {
		id: accuracyIndicator
		height: Math.min(implicitHeight, parent.height / 4)
		anchors.bottom: parent.bottom
		anchors.horizontalCenter: parent.horizontalCenter
		noteName: pitchDetector.confidentPitch.noteLong
		accuracy: pitchDetector.confidentPitch.accuracy
	}
	PitchDetector {
		id: pitchDetector
		active: !settings.visible
	}
}
