import QtQuick 2.7
import QtQuick.Window 2.10
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Qt.labs.qmlmodels 1.0
import QtQml 2.0

Window
{


    id:windowmain
    visible: true
    width: 650
    height: 650
    title: qsTr("QOAuth2 Test")
    Dialog {
        anchors.centerIn: parent
        width: 150
        height: 150
        id: dialogstatus
        title: "Status"
        closePolicy: Dialog.CloseOnEscape | Dialog.CloseOnPressOutsideParent
        standardButtons: Dialog.Ok | Dialog.Cancel
        Label {
            anchors.centerIn: parent
            text: "Error: " + calendar.statusToDisplay
        }
    }
    Dialog {
        anchors.centerIn: parent
        width: 150
        height: 150
        id: dialogOK
        closePolicy: Dialog.CloseOnEscape | Dialog.CloseOnPressOutsideParent
        standardButtons: Dialog.Ok | Dialog.Cancel
        Label {
            anchors.centerIn: parent
            text: "OK"
            font.pointSize: 25
        }

    }
    Dialog{
        anchors.centerIn: parent
        id: dialog_choosenID
        width: 320
        height: 250
        closePolicy: Dialog.CloseOnEscape
        standardButtons: Dialog.Ok | Dialog.Reset
        onReset: {
            calendar.reset()
            btnGrant.enabled = true;
            resetDelegate();
//            m_description.text = "";
//            m_iCalUID.text = "";
//            m_id.text = "";
//            m_location.text = "";
//            m_summary.text = "";
//            m_timeend.text = "";
//            m_timestart.text = "";
//            btnStart.text = "START: ";
//            btnEnd.text = "END: ";

        }
        function resetDelegate() {
            for (var i = 0; i < repeaterCalendar.count; i++) {
                repeaterCalendar.itemAt(i).enabled = true;
                repeaterCalendar.itemAt(i).checked = false;
                console.log(repeaterCalendar.itemAt(i));
            }
        }

        Frame{
            anchors.centerIn: parent
            width: parent.width
            height: parent.height
            clip: true
            ScrollView{
                id:scrollcalendarlist
                width: parent.width
                height: parent.height
                clip: true
                Column {
                    spacing: 5
                    width: parent.width
                    Repeater {
                        id: repeaterCalendar
                        width: parent.width
                        anchors.fill: parent
                        model:{
                            console.log("update list: " + auth.calendarlistToDisplay)
                            return auth.calendarlistToDisplay
                        }
                        delegate: CheckDelegate {
                            width: parent.width
                            text: modelData
                            font.pixelSize: 12
                            onClicked: {
                                this.enabled = false;
                                auth.choosenCalendar(modelData)
                                console.log(this)

                                btnGrant.enabled = false;

                            }
                        }
                    }
                }
            }
        }
    }


    Calendar{
        x: 20
        y: 20
        id: calendarshow
        onClicked: {calendar.setTimePicker(calendarshow.selectedDate);}
        enabled: false
    }

    Frame{
        x: 300
        y: 20
        //width: 320
        //anchors.right : parent.right -20
        width: parent.width - calendarshow.width - 70
        height: 250
        ScrollView{
            id:scrolleventlist
            width: parent.width
            height: parent.height
            Column {
                spacing: 5
                Repeater {
                    id: repeaterEvent
                    model:{
                        //console.log("update list: " + calendar.chosenSummariesToDisplay.length)
                        return calendar.chosenSummariesToDisplay
                    }
                    Button {
                        id:tst
                        width: scrolleventlist.width
                        text: { return modelData.substring(27,modelData.lenghth)}
                        font.pixelSize: 12
                        onClicked: {

                            calendar.setIdPicker(modelData.substring(0,26))
                            //cbListCalendar.get(currentIndex).text = calendar.calendarIDToDisplay;
                        }
                    }
                }
            }
        }
    }

    GroupBox{
        x:20
        y:280
        height: 340
        anchors.right : parent.right -20
        title: "INFO"
        width: parent.width - 40
        //anchors.RightAnchor: 20
        Column{
            width: parent.width - 20
            spacing: 7
            //--------------------------------------
            Row{
                width: parent.width
                ComboBox{
                    id: cbListCalendar
                    height: 30
                    width: parent.width
                    model: {
                            return calendar.listCalendarToDisplay;
                    }
                    currentIndex: calendar.indexcalendarIDToDisplay

                }
            }
            //--------------------------------------
            Row {
                width: parent.width-20
                height: 30
                spacing: 20
                    TextField {
                        id: m_id
                        width: parent.width/2
                        height: 30
                        text: calendar.idToDisplay
                        placeholderText: "id"
                    }
                    TextField{
                        id: m_iCalUID
                        height: 30
                        width: parent.width/2
                        text: calendar.iCalUIDToDisplay
                        placeholderText: "iCalUID"
                    }
            }
            //-------------------------------------------


            Row {
                width:parent.width
                height: 30
                TextField {
                    id: m_summary
                    height: 30
                    width: parent.width
                    text: calendar.summaryToDisplay
                    placeholderText: "summary"
                }
            }
            //------------------------------------------
             Row {
                 height: 30
                 width:parent.width
                    TextField {
                        id: m_description
                        height: 30
                        width: parent.width
                        text: calendar.descriptionToDisplay
                        placeholderText: "description"

                    }
                }
             Row{
                 width: parent.width
                 spacing: 7
                 Button {
                     width: parent.width/4
                     id: btnStart
                     text: "START: " +calendar.datestartToDisplay
                     onClicked: popupstart.open()
                     height: 30
                     enabled: false
                 }
                 Button {
                     width: parent.width/4
                     id:btnEnd
                     text: "END: " +calendar.dateendToDisplay
                     onClicked: popupend.open()
                     height: 30
                     enabled: false

                 }
                 TextField {
                     id: m_location
                     width: parent.width/2
                     height: 30
                     text: calendar.locationToDisplay
                     placeholderText: "location"
                 }

                 Popup {
                     id: popupend
                     x: -300
                     y: -500
                     width: 300
                     height: 330
                     modal: true
                     focus: true
                     closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                     Calendar{
                         id: calendarEnd
                         width: parent.width
                         minimumDate: calendarStart.selectedDate
                         maximumDate: new Date(2022, 0, 1)
                         focus: true
                         selectedDate: new Date(calendar.dateendToDisplay)
                     }
                     TextField{
                         id: m_timeend
                         anchors.bottom: parent.bottom
                         text: typeof(calendar.timeendToDisplay) == "undefined"?"00:00:00":calendar.timeendToDisplay
                         font.pixelSize: 16
                         placeholderText: "00:00:00"
                     }
                 }
                 Popup {
                     id: popupstart
                     x: -300
                     y: -500
                     width: 300
                     height: 330
                     modal: true
                     focus: true
                     closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                     function back() {
                         Calendar.selectedDate = new Date();
                     }

                     Calendar{
                         //Date() datenow = new Date();
                         minimumDate: calendarshow.selectedDate
                         maximumDate: new Date(2022, 0, 1)
                         id: calendarStart
                         width: parent.width
                         focus: true
                         onDoubleClicked: back();
                         selectedDate: new Date(calendar.datestartToDisplay)
                     }
                     TextField{
                         id: m_timestart
                         anchors.bottom: parent.bottom
                         text: calendar.timestartToDisplay
                         font.pixelSize: 16
                         placeholderText: "00:00:00"
                     }

                 }
             }

             //---------------------
             Row{
                 height: 7
                 width: parent.width
                 id: comment
                 Text {
                     anchors.centerIn: comment
                     id: name
                     text: qsTr("___Double click___")
                     font.italic : true
                     color: "#a9a9a9"
                 }
             }
             Row{
                 width: parent.width
                 spacing: 5

                 Button{
                     width: parent.width/4
                     id:btnInsert
                     text: qsTr("Insert to G-Calendar")
                     enabled: false
                     onDoubleClicked: {
                        calendar.insert(m_summary.text, calendarStart.selectedDate, m_timestart.text, calendarEnd.selectedDate, m_timeend.text, m_location.text, m_description.text, cbListCalendar.currentText);
                        dialogstatus.open()
                         console.log( cbListCalendar.currentText);
                     }
                 }
                 Button{
                     width: parent.width/4
                     id: btnUpdate
                     enabled: false
                     text: qsTr("Update Event")
                     onDoubleClicked: {
                        calendar.update(m_id.text, m_summary.text, calendarStart.selectedDate, m_timestart.text, calendarEnd.selectedDate, m_timeend.text, m_location.text, m_description.text);
                        dialogstatus.open()
                     }
                 }
                 Button{
                     width: parent.width/4
                     id:btnDelete
                     enabled: false
                     text: qsTr("Delete Event")
                     onDoubleClicked: {
                        calendar.drop(m_id.text)
                        dialogstatus.open()
                     }
                 }
                 Button{
                     width: parent.width/4
                     id:btnRefresh
                     enabled: false
                     text: qsTr("Refresh data")
                     onDoubleClicked: {
                        auth.refreshdata();
                        dialogOK.open()
                     }
                 }

             }


             Row{
                 width: parent.width
                 spacing: 5
                 Button{
                     width: 2*parent.width/10
                     id:btnConfig
                     text: qsTr("Config")
                     //icon.name: "toolbar-setting"
                     onClicked:{
                        popupConfig.open();
                     }
                 }

                 Button
                 {
                     width: 4*parent.width/10
                     id:btnGrant
                     text: qsTr("Grant me access")
                     onClicked: {
                         auth.grant()
                         dialog_choosenID.open()
                         btnInsert.enabled = true
                         btnDelete.enabled = true
                         btnUpdate.enabled = true
                         btnRefresh.enabled = true
                         btnStart.enabled = true
                         btnEnd.enabled = true
                         calendarshow.enabled = true

                     }
                 }


                 Button{
                     width: 4*parent.width/10
                     id:btnShowListCalendar
                     text: qsTr("Open List Calendar")
                     onClicked: {
                         dialog_choosenID.open();
                     }
                 }
             }
             Popup {
                 id: popupConfig
                 x: -300
                 y: -500

                 width: 550
                 height: 330
                 modal: true
                 focus: true
                 closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
            Column{
                spacing: 20
                 Row{
                     width: parent.width
                     spacing: 20
                     Calendar{
                         //Date() datenow = new Date();
                         minimumDate: new Date(2010, 1, 1)
                         maximumDate: new Date(2090, 0, 1)
                         id: configMax
                         //width: parent.width
                         focus: true
                     }
                     Calendar{
                         //Date() datenow = new Date();
                         minimumDate: new Date(2010, 1, 1)
                         maximumDate: new Date(2090, 1, 1)
                         id: configMin
                         //width: parent.width
                         focus: true
                     }

                 }
                 Row{
                     //id: row2
                     //width: parent.width
                     Button{
                         //anchors.centerIn: row2
                         text: qsTr("Open List Calendar")
                         onClicked: {
                             auth.configTimeMax(configMax.selectedDate)
                             auth.configTimeMin(configMin.selectedDate)
                         }
                     }
                 }
            }
             }
        }
    }

}
