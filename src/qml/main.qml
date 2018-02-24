import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

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
