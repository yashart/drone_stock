import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0


Item {
    width: 300
    height: 300
    //! [filedialog]
    FileDialog {
        id: fileDialog
        //visible: true
        //folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrls)
            Qt.quit()
        }
        onRejected: {
            console.log("Canceled")
            Qt.quit()
        }
    }
    //! [filedialog]
        Button {
            text: qsTr("Выберете файл с заданием")
            onClicked: fileDialog.open()
        }

}
