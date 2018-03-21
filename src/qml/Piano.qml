import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2

Item {
	property string noteName: ""
	property color whiteColor: Material.color(Material.Grey, Material.Shade200)
	property color blackColor: Material.color(Material.Grey, Material.Shade900)
	property color activeColor: Material.color(Material.Blue, Material.Shade500)
	Rectangle {
		id: c
		anchors.left: parent.left
		anchors.bottom: parent.bottom
		width: parent.width / 7
		height: parent.height / 2
		color: noteName === "C" ? activeColor : whiteColor
	}
	Rectangle {
		id: d
		anchors.left: c.right
		anchors.bottom: parent.bottom
		width: parent.width / 7
		height: parent.height / 2
		color: noteName === "D" ? activeColor : whiteColor
	}
	Rectangle {
		id: e
		anchors.left: d.right
		anchors.bottom: parent.bottom
		width: parent.width / 7
		height: parent.height / 2
		color: noteName === "E" ? activeColor : whiteColor
	}
	Rectangle {
		id: f
		anchors.left: e.right
		anchors.bottom: parent.bottom
		width: parent.width / 7
		height: parent.height / 2
		color: noteName === "F" ? activeColor : whiteColor
	}
	Rectangle {
		id: g
		anchors.left: f.right
		anchors.bottom: parent.bottom
		width: parent.width / 7
		height: parent.height / 2
		color: noteName === "G" ? activeColor : whiteColor
	}
	Rectangle {
		id: a
		anchors.left: g.right
		anchors.bottom: parent.bottom
		width: parent.width / 7
		height: parent.height / 2
		color: noteName === "A" ? activeColor : whiteColor
	}
	Rectangle {
		id: h
		anchors.left: a.right
		anchors.bottom: parent.bottom
		width: parent.width / 7
		height: parent.height / 2
		color: noteName === "H" ? activeColor : whiteColor
	}
	Rectangle {
		id: c1
		anchors.left: c.left
		anchors.bottom: c.top
		anchors.top: parent.top
		anchors.right: cis.left
		color: c.color
	}
	Rectangle {
		id: cis
		anchors.horizontalCenter: c.right
		anchors.bottom: c.top
		anchors.top: parent.top
		width: c.width / 2
		color: noteName === "Cis" ? activeColor : blackColor
	}
	Rectangle {
		id: d1
		anchors.left: cis.right
		anchors.right: dis.left
		anchors.bottom: c.top
		anchors.top: parent.top
		color: d.color
	}
	Rectangle {
		id: dis
		anchors.horizontalCenter: d.right
		anchors.bottom: c.top
		anchors.top: parent.top
		width: d.width / 2
		color: noteName === "Dis" ? activeColor : blackColor
	}
	Rectangle {
		id: e1
		anchors.left: dis.right
		anchors.right: e.right
		anchors.bottom: c.top
		anchors.top: parent.top
		color: e.color
	}
	Rectangle {
		id: f1
		anchors.left: f.left
		anchors.right: fis.left
		anchors.bottom: c.top
		anchors.top: parent.top
		color: f.color
	}
	Rectangle {
		id: fis
		anchors.horizontalCenter: f.right
		anchors.bottom: c.top
		anchors.top: parent.top
		width: f.width / 2
		color: noteName === "Fis" ? activeColor : blackColor
	}
	Rectangle {
		id: g1
		anchors.left: fis.right
		anchors.right: gis.left
		anchors.bottom: c.top
		anchors.top: parent.top
		color: g.color
	}
	Rectangle {
		id: gis
		anchors.horizontalCenter: g.right
		anchors.bottom: c.top
		anchors.top: parent.top
		width: g.width / 2
		color: noteName === "Gis" ? activeColor : blackColor
	}
	Rectangle {
		id: a1
		anchors.left: gis.right
		anchors.right: ais.left
		anchors.bottom: c.top
		anchors.top: parent.top
		color: a.color
	}
	Rectangle {
		id: ais
		anchors.horizontalCenter: a.right
		anchors.bottom: c.top
		anchors.top: parent.top
		width: a.width / 2
		color: noteName === "Ais" ? activeColor : blackColor
	}
	Rectangle {
		id: h1
		anchors.left: ais.right
		anchors.right: parent.right
		anchors.bottom: c.top
		anchors.top: parent.top
		color: h.color
	}
}
