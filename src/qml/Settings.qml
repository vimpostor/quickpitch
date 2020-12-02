import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Dialog {
	ColumnLayout {
		anchors.fill: parent
		ComboBox {
			model: [ "default", "schmitt", "fcomb", "mcomb", "yin", "yinfast", "yinfft" ]
			Component.onCompleted: currentIndex = find(c_settings.algorithm);
			onActivated: {
				pitchDetector.algorithm = currentText;
				c_settings.algorithm = pitchDetector.algorithm;
			}
		}
		ComboBox {
			model: [ "8000", "44100", "48000" ]
			Component.onCompleted: currentIndex = find(c_settings.sampleRate);
			onActivated: {
				pitchDetector.sampleRate = currentText;
				c_settings.sampleRate = pitchDetector.sampleRate;
			}
		}
	}
}
