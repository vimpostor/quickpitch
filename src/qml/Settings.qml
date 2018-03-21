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
					model: [ "default", "schmitt", "fcomb", "mcomb", "yin", "yinfft" ]
					Component.onCompleted: currentIndex = find(c_settings.algorithm);
					onActivated: {
						pitchDetector.algorithm = currentText;
						c_settings.algorithm = pitchDetector.algorithm;
					}
				}
			}
			ListItem {
				text: qsTr("Sample rate")
				rightItem: ComboBox {
					model: [ "8000", "48000" ]
					Component.onCompleted: currentIndex = find(c_settings.sampleRate);
					onActivated: {
						pitchDetector.sampleRate = currentText;
						c_settings.sampleRate = pitchDetector.sampleRate;
					}
				}
			}
		}
	}
}
