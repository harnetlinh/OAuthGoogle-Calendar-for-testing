#ifndef DATA_H
#define DATA_H
#include <QString>
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <qoauth2test.h>
#include <QJsonDocument>
#include <QDateTime>
#include <QQmlPropertyMap>

struct event {
    Q_GADGET
    Q_PROPERTY(QString id MEMBER id)
    Q_PROPERTY(QString htmllink MEMBER htmllink)
    Q_PROPERTY(QString summary MEMBER summary)
    Q_PROPERTY(QDateTime start MEMBER start)
    Q_PROPERTY(QDateTime end MEMBER end)
    Q_PROPERTY(QString iCalUID MEMBER iCalUID)
    Q_PROPERTY(QString displayName MEMBER displayName)
    Q_PROPERTY(QString description MEMBER description)
    Q_PROPERTY(QString location MEMBER location)
public:
    QString id;
    QString htmllink;
    QString summary;
    QDateTime start;
    QDateTime end;
    QString iCalUID;
    QString displayName;
    QString description;
    QString location;
    QString email;
    QString calendarID;

};
class data : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString textToDisplay READ getToDisplay WRITE setToDisplay NOTIFY textToDisplayChanged)
    Q_PROPERTY(QString idToDisplay READ id WRITE setid NOTIFY idToDisplayChanged)
    Q_PROPERTY(QString htmllinkToDisplay READ htmllink WRITE sethtmllink NOTIFY idToDisplayChanged)
    Q_PROPERTY(QString summaryToDisplay READ summary WRITE setsummary NOTIFY idToDisplayChanged)
    Q_PROPERTY(QString iCalUIDToDisplay READ iCalUID WRITE setiCalUID NOTIFY idToDisplayChanged)
    Q_PROPERTY(QString displayNameToDisplay READ displayName WRITE setdisplayName NOTIFY idToDisplayChanged)
    Q_PROPERTY(QString descriptionToDisplay READ description WRITE setdescription NOTIFY idToDisplayChanged)
    Q_PROPERTY(QString locationToDisplay READ location WRITE setlocation NOTIFY idToDisplayChanged)
    Q_PROPERTY(QVariantMap passingVariantToDisplay READ passingVariant WRITE setPassingVariant NOTIFY idToDisplayChanged)
    Q_PROPERTY(QVariantList chosenSummariesToDisplay READ chosenSummaries WRITE setChosenSummariesToDisplay NOTIFY idToDisplayChanged)
    Q_PROPERTY(QString dateendToDisplay READ dateend WRITE setdateend NOTIFY idToDisplayChanged)
    Q_PROPERTY(QString datestartToDisplay READ datestart WRITE setdatestart NOTIFY idToDisplayChanged)
    Q_PROPERTY(QString timestartToDisplay READ timestart WRITE settimestart NOTIFY idToDisplayChanged)
    Q_PROPERTY(QString timeendToDisplay READ timeend WRITE settimeend NOTIFY idToDisplayChanged)
    Q_PROPERTY(QString calendarIDToDisplay READ calendarID WRITE setCalendarID NOTIFY idToDisplayChanged)
    Q_PROPERTY(int indexcalendarIDToDisplay READ index_calendarID WRITE setIndex_calendarID NOTIFY idToDisplayChanged)
    Q_PROPERTY(QString statusToDisplay READ getStatus WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QVariantList listCalendarToDisplay READ CalendarList WRITE setCalendarList  NOTIFY updateClicked)
public:
    explicit data(QObject *parent=nullptr);

    int index_calendarID();
    void setIndex_calendarID(int &index);

    QString calendarID();
    void setCalendarID(QString &email);

    QString getStatus();
    void setStatus(QString &value);

    QVariant getQvariantCalendar();
    void setCalendarMap(QVector<struct event> &calendar, int i);

    QVariantMap passingVariant();
    void setPassingVariant(QVariantMap &value){}

    QString getToDisplay();
    void setToDisplay(QString &value);

    QString id();
    void setid( QString &id);

    QString summary();
    void setsummary(QString &summary);

    QString htmllink();
    void sethtmllink(QString &htmllink);

    QString iCalUID();
    void setiCalUID( QString &iCalUID);

    QString displayName();
    void setdisplayName(QString &id);

    QDateTime start() ;
    void setstart(QDateTime &start);

    QString datestart();


    void setdatestart(QString &datestart){}
    QString timestart();
    void settimestart(QString &datestart){}

    QDateTime end();
    void setend(QDateTime &end);

    QString dateend();
    void setdateend(QString &dateend){}
    QString timeend();
    void settimeend(QString &dateend){}

    QString location();
    void setlocation(QString &location);

    QString description();
    void setdescription(QString &description);

    QVariantList chosenSummaries();
    void setChosenSummariesToDisplay(QVariantList &value){}

    QVariantList CalendarList();
    void setCalendarList(QVariantList &value){};

    Q_INVOKABLE void setIdPicker(QString idstr);
    Q_INVOKABLE void setTimePicker(QDate q);
    void print(QVector<struct event> calendar);
    void read(QJsonDocument json);
    void write();
    void calendarQML(QVector<struct event> calendar, int i);
    void testList();
    static void testAdd(QString token);
    void calendarID_text2index();
    Q_INVOKABLE void insert(QString summary, QDate datestart, QString timestart,QDate dateend, QString timeend, QString location, QString description, QString choosenCalendarID);
    Q_INVOKABLE void drop(QString id);
    Q_INVOKABLE void reset();
    Q_INVOKABLE void update(QString id,QString summary, QDate datestart, QString timestart,QDate dateend, QString timeend, QString location, QString description);

signals:
    void listCalendarToDisplay();
    void chosenSummariesToDisplay();
    void textToDisplayChanged();
    void qmlToCalendarMapChanged();
    void idToDisplayChanged();
    void htmllinkToDisplay();
    void summaryToDisplay();
    void iCalUIDToDisplay();
    void displayNameToDisplay();
    void locationToDisplay();
    void passingVariantToDisplay();
    void dateendToDisplay();
    void datestartToDisplay();
    void timestartToDisplay();
    void timeendToDisplay();
    void calendarIDToDisplay();
    void stausToDisplay();
    void statusChanged();
    void updateClicked();
    void indexcalendarIDToDisplay();
public slots:
    void receive(QJsonDocument jsondata, QString token, QString calendarID);
    void ResetClicked();
private:
    QVariantList m_qvariantListCalendar;
    //QVector<QString> m_listCalendar;
    QString m_token;
    QVariantList m_chosenSummaries;
    QVector<struct event> calendar;
    QVariantMap toCalendarMap;
    QString toDisplay;
    QVariantMap m_passingVariant;
    QVariant toDisplayQvariant;
    QJsonDocument* jsondata;
    QString m_id;
    QString m_htmllink;
    QString m_summary;
    QDateTime m_start;
    QDateTime m_end;
    QString m_datestart;
    QString m_dateend;
    QString m_iCalUID;
    QString m_displayName;
    QString m_description;
    QString m_location;
    QString m_status;
    QString m_calendarID;
    QString m_email;
    QString m_calendarID_received;
    int m_index_calendarID;
    //QString m_displayName;
};

#endif // DATA_
