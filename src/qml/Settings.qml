import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Fluid.Controls 1.0

TabbedPage {
	title: qsTr("Settings")
	onGoBack: pitchDetector.active = true;
	Tab {
		title: qsTr("General")
		ColumnLayout {
			anchors.fill: parent
			ListItem {
				text: qsTr("Pitch detection algorithm")
				rightItem: ComboBox {
					model: ListModel {
						ListElement {name: "default"}
						ListElement {name: "schmitt"}
						ListElement {name: "fcomb"}
						ListElement {name: "mcomb"}
						ListElement {name: "yin"}
						ListElement {name: "yinfft"}
					}
					onCurrentTextChanged: pitchDetector.algorithm = currentText;
				}
			}
			ListItem {
				text: qsTr("Sample rate")
				rightItem: ComboBox {
					model: ListModel {
						ListElement {name: "8000"}
						ListElement {name: "48000"}
					}
					onCurrentTextChanged: pitchDetector.sampleRate = currentText;
				}
			}
		}
	}
}
