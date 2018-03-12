import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import QtCharts 2.2

import Fluid.Controls 1.0

import PitchDetector 1.0

ApplicationWindow {
	visible: true
	width: 640
	height: 480
	initialPage: Page {
		title: qsTr("Quick Pitch")
		actions: [
			Action {
				icon.source: Utils.iconUrl("action/settings")
				text: qsTr("Settings")
				shortcut: "Ctrl+I"
				onTriggered: {
					pitchDetector.active = false;
					pageStack.push(Qt.resolvedUrl("Settings.qml"));
				}
			},
			Action {
				icon.source: Utils.iconUrl("navigation/close")
				text: qsTr("Quit")
				onTriggered: close();
				shortcut: "Ctrl+Q"
			}

		]
		ChartView {
			id: chartView
			anchors.fill: parent
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
		OctaveIndicator {
			id: octaveIndicator
			anchors.top: parent.top
			anchors.horizontalCenter: parent.horizontalCenter
			octave: pitchDetector.confidentPitch.octave
		}
		NoteAccuracyIndicator {
			anchors.centerIn: parent
			noteName: pitchDetector.confidentPitch.noteLong
			accuracy: pitchDetector.confidentPitch.accuracy
		}
		PitchDetector {
			id: pitchDetector
			active: true
		}
	}
}
