#include "data.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork>
#include <qoauth2test.h>
#include <QJsonDocument>
#include <QVariant>


data::data(QObject *parent) : QObject(parent)
{

}
void data::calendarID_text2index()
{
    for(int i = 0; i < m_qvariantListCalendar.length();i++)
    {
//        qDebug() << "Calendar ID in calendarID_text2index: at "<< i << " " << m_qvariantListCalendar.at(i).toString();
//        qDebug() << "Calendar ID in calendarID_text2index: at "<< i << " " << m_calendarID;
//        qDebug() << "_____________________________________________";
        if (QString::compare(m_calendarID, m_qvariantListCalendar.at(i).toString(), Qt::CaseInsensitive) == 0)
        {
            m_index_calendarID = i;
//            qDebug() << "INDEX CHANGE = " << i;
            break;
        }
    }
}

void data::setCalendarID(QString &id)
{
    if(QString::compare(m_calendarID, id, Qt::CaseInsensitive) == 0)
    {
        m_calendarID =  id;
    }
}

QString data::calendarID()
{
    return m_calendarID;
}

void data::setIndex_calendarID(int &index)
{
    if(m_index_calendarID != index)
    {
        m_index_calendarID =  index;
    }
}

int data::index_calendarID()
{
    return m_index_calendarID;
}

void data::setdisplayName(QString &displayName)
{
    if(QString::compare(m_displayName, displayName, Qt::CaseInsensitive) == 0)
    {
        m_displayName =  displayName;
    }
}

QString data::displayName()
{
    return m_displayName;
}

void data::setid( QString &id)
{
    if(QString::compare(m_id, id, Qt::CaseInsensitive) == 0)
    {
        m_id =  id;
    }
}
QString data::id()
{
    return m_id;
}
void data::setsummary(QString &summary)

{
    if(QString::compare(m_summary, summary, Qt::CaseInsensitive) == 0)
    {
        m_summary = summary;
    }
}
QString data::summary()
{
    return m_summary;
}
void data::sethtmllink(QString &htmllink)
{
    if(QString::compare(m_htmllink, htmllink, Qt::CaseInsensitive) == 0)
    {
        m_htmllink = htmllink;
    }
}
QString data::htmllink()
{
    return m_htmllink;
}
void data::setstart(QDateTime &start)
{
    if(QString::compare(m_start.toString(), start.toString(), Qt::CaseInsensitive) == 0)
    {
        m_start = start;
    }
}
QDateTime data::start()
{
    return m_start;
}
void data::setend(QDateTime &end)
{
    if (QString::compare(m_end.toString(), end.toString(), Qt::CaseInsensitive) == 0)
    {
        m_end = end;
    }
}
QDateTime data::end()
{
    return m_end;
}
QString data::dateend()
{
    QString d;
    if (m_end.isNull()) d = QDate::currentDate().toString("yyyy-MM-dd");
    else d =  m_end.date().toString(("yyyy-MM-dd"));
    return d;
}
QString data::datestart()
{
    QString d;
    if (m_start.isNull()) d = QDate::currentDate().toString("yyyy-MM-dd");
    else d =  m_start.date().toString(("yyyy-MM-dd"));
    return d;
}
QString data::timestart()
{
    QString t = m_start.time().toString();
    return t;
}
QString data::timeend()
{
    QString t = m_end.time().toString();
    return t;
}

void data::setiCalUID(QString &iCalUID)
{
    if(QString::compare(m_iCalUID, iCalUID, Qt::CaseInsensitive) == 0)
    {
        m_iCalUID =  iCalUID;
    }
}
QString data::iCalUID()
{
    return m_iCalUID;
}
void data::setdescription(QString &description)
{
    if(QString::compare(m_description, description, Qt::CaseInsensitive) == 0)
    {
        m_description = description;
    }
}
QString data::description()
{
    return m_description;
}
void data::setlocation(QString &location)
{
    if(QString::compare(m_location, location, Qt::CaseInsensitive) == 0)
    {
        m_location = location;
    }
}
QString data::location()
{
    return m_location;
}

void data::setTimePicker(QDate q){

    m_chosenSummaries.clear();
    int x = 0;


    for (int i = 0; i < calendar.size(); i++)
    {
        if(calendar.at(i).start.date() == q)
        {

//            qDebug() << calendar.at(i).summary;
//            qDebug() << calendar.at(i).start.date();
//            qDebug() << calendar.at(i).id;
            m_chosenSummaries.push_back(QVariant(calendar.at(i).id + "_" + calendar.at(i).summary +"_"+ calendar.at(i).start.time().toString()) );
        }
        else {
            x++;
            if (x == calendar.size())
            {
                qDebug() << "Empty schedule";
                x=0;
            }

        }
    }

    //testList();
    emit idToDisplayChanged();
    
}
void data::testList()
{
for(int i = 0; i < m_chosenSummaries.size(); i++)
{
    qDebug() << "testlis" << m_chosenSummaries[i];
}
}

QVariantList data::chosenSummaries()
{
    return m_chosenSummaries;
}

void data::setIdPicker(QString idstr)
{
    bool checkinListCalendarID = true;
    for (int i = 0; i < m_qvariantListCalendar.length(); i++)
    {
        if (QString::compare(idstr, m_qvariantListCalendar.at(i).toString(), Qt::CaseInsensitive) == 0)
        {
            checkinListCalendarID =  false; // already has this idstr
            break;
        }
    }

    if (checkinListCalendarID == true)
    {
        qDebug() << "Add IDSTR";
        for (int i = 0; i < calendar.size(); i++)
        {
            if(calendar.at(i).id == idstr )
            {
                m_summary = calendar.at(i).summary;
                m_start = calendar.at(i).start;
                m_end = calendar.at(i).end;
                m_htmllink = calendar.at(i).htmllink;
                m_id = calendar.at(i).id;
                m_iCalUID = calendar.at(i).iCalUID;
                m_description = calendar.at(i).description;
                m_location = calendar.at(i).location;
                qDebug() << "CALENDAR ID : " << calendar.at(i).calendarID;

                if (calendar.at(i).calendarID != m_calendarID )
                {
                m_displayName = calendar.at(i).displayName;
                m_calendarID = calendar.at(i).calendarID;
                qDebug() << "CALENDAR IN IF : " << calendar.at(i).calendarID;

                }
                calendarID_text2index();

                break;
            }
        }
        emit idToDisplayChanged();
    }
    else{qDebug() << "SAME IDSTR";}

}

QVariantList data::CalendarList()
{
    return m_qvariantListCalendar;
}



void data::receive(QJsonDocument data, QString token, QString calendarID)
{
    QStringList propertyIds;
    QStringList propertyHtmls;
    m_token = token;
    m_calendarID_received = calendarID;
    qDebug() << "calendarID" << calendarID;
    if ((calendarID != "") & (!calendarID.isEmpty()) & (!calendarID.isNull()) )
    {
        QVariant x = calendarID;
        bool same = false;
        for(int i = 0; i < m_qvariantListCalendar.length();i++)
        {
            if(m_qvariantListCalendar[i] == x)
            {
                same = true;
            }
        }
        if (same == false)
        {
            m_qvariantListCalendar.push_back(x);
        }
    }
    if (!data.isEmpty()){
    qDebug() << "data is not null";
    read(data);
    }
    emit updateClicked();

}

void data::reset()
{
    calendar.clear();
    m_qvariantListCalendar.clear();
    emit updateClicked();
    emit idToDisplayChanged();

}

void data::read(QJsonDocument data)
{
    QJsonObject sett2 = data.object();
    qDebug() << "Read QJObject is running - parse to vector";
    QJsonValue value = sett2.value("items");
    QJsonArray array = value.toArray();
    //calendar.clear(); ----- CLEAR DATA OF 1 CALENDAR
    foreach (const QJsonValue & v, array)
    {
            struct event e;
            e.id = v.toObject().value("id").toString();
            e.htmllink = v.toObject().value("htmllink").toString();
            e.summary = v.toObject().value("summary").toString();
            e.start = QDateTime::fromString(v.toObject().value("start")["dateTime"].toString().left(19),"yyyy-MM-ddTHH:mm:ss");
            e.end= QDateTime::fromString(v.toObject().value("end")["dateTime"].toString().left(19), "yyyy-MM-ddTHH:mm:ss");
//            qDebug()<< e.start.date();
//            qDebug() << e.end.date();
            e.iCalUID = v.toObject().value("iCalUID").toString();
            e.calendarID = m_calendarID_received;
            e.displayName = v.toObject().value("organizer")["displayName"].toString();
            e.email = v.toObject().value("creator")["email"].toString();
            e.description = v.toObject().value("description").toString();
            e.location = v.toObject().value("location").toString();
            calendar.push_back(e);
    }
}

void data::setToDisplay(QString &value)
{
    if (toDisplay != value)
    {
        data::toDisplay = value;
        emit textToDisplayChanged();
    }
}

QString data::getToDisplay()
{
    return toDisplay;
}

QVariantMap data::passingVariant(){
    return m_passingVariant;
}

void data::print(QVector<struct event> calendar)
{
    for (int i = 0; i < calendar.size(); i++) {
        qDebug() << "id: "<< calendar.at(i).id;
        qDebug() << "htmllink: "<< calendar.at(i).htmllink;
        qDebug() << "summary: "<< calendar.at(i).summary;
        qDebug() <<"start: "<< calendar.at(i).start;
        qDebug() <<"end: "<< calendar.at(i).end;
        qDebug() << "iCalID: "<< calendar.at(i).iCalUID;
        qDebug() << "displayName:" << calendar.at(i).displayName;
        qDebug() <<"description: "<< calendar.at(i).description;
        qDebug() <<"location: " << calendar.at(i).location;
        qDebug() << "Calendar ID (calendarID): " << calendar.at(i).calendarID;
    }
}



void data::insert(QString summary, QDate datestart, QString timestart, QDate dateend, QString timeend, QString location, QString description, QString choosenCalendarID)
{
    qDebug() << "Insert to " << choosenCalendarID ;
    const QString bearerFormat = QStringLiteral("Bearer %1");
    QNetworkRequest request(QUrl("https://www.googleapis.com/calendar/v3/calendars/"+choosenCalendarID+"/events?key=AIzaSyDC969ZTJewE_2MalRP20HPnTVkSoTvx5A HTTP/1.1"));
    request.setRawHeader("Authorization", "Bearer "+m_token.toUtf8());
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("User-Agent", "My Calendar v0.1");
    QJsonObject json;
    QJsonObject endObject;
    QJsonObject startObject;
    startObject.insert("dateTime",datestart.toString("yyyy-MM-dd")+"T"+timestart+"+07:00");
    endObject.insert("dateTime",dateend.toString("yyyy-MM-dd")+"T"+timeend+"+07:00");
    json.insert("summary",summary);
    json.insert("start",startObject);
    json.insert("end",endObject);
    json.insert("location", location);
    json.insert("description", description);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    QNetworkAccessManager nam;
    QNetworkReply *reply = nam.post(request, QJsonDocument(json).toJson());
    while (!reply->isFinished())
    {
        qApp->processEvents();
    }
    QString respondata = QVariant(reply->error()).toString();
    qDebug() << "RESPONSE INSERT ->" << respondata;
    data::setStatus(respondata);

}
void data::setStatus(QString &value)
{
    if(value.isNull() | value.isEmpty())
    {
        m_status = "No transmission";
    }else{
        m_status = value;
    }
    emit statusChanged();
}

QString data::getStatus(){
    return m_status;
}

void data::drop(QString id)
{
    QString linkhtml = "https://www.googleapis.com/calendar/v3/calendars/"+m_calendarID+"/events/"+ id + "?key=AIzaSyDC969ZTJewE_2MalRP20HPnTVkSoTvx5A HTTP/1.1";
    qDebug() << linkhtml.toUtf8();
    const QString bearerFormat = QStringLiteral("Bearer %1");
    QNetworkRequest request(QUrl(linkhtml.toUtf8()));
    request.setRawHeader("Authorization", "Bearer "+m_token.toUtf8());
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("User-Agent", "My Calendar v0.1");
    QJsonObject json;
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    QNetworkAccessManager nam;
    QNetworkReply *reply = nam.deleteResource(request);
    while (!reply->isFinished())
    {
        qApp->processEvents();
    }
    QString respondata = QVariant(reply->error()).toString();
    auto response = reply->readAll();
    qDebug() << "RESPONSE DELETE ->" << response;
    data::setStatus(respondata);
}

void data::update(QString id, QString summary, QDate datestart, QString timestart, QDate dateend, QString timeend, QString location, QString description)
{

    const QString bearerFormat = QStringLiteral("Bearer %1");
    QNetworkRequest request(QUrl("https://www.googleapis.com/calendar/v3/calendars/"+m_calendarID+"/events/"+id+"?key=AIzaSyDC969ZTJewE_2MalRP20HPnTVkSoTvx5A HTTP/1.1"));
    request.setRawHeader("Authorization", "Bearer "+m_token.toUtf8());
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("User-Agent", "My Calendar v0.1");
    QJsonObject json;
    QJsonObject endObject;
    QJsonObject startObject;
    startObject.insert("dateTime",datestart.toString("yyyy-MM-dd")+"T"+timestart+"+07:00");
    endObject.insert("dateTime",dateend.toString("yyyy-MM-dd")+"T"+timeend+"+07:00");
    json.insert("summary",summary);
    json.insert("start",startObject);
    json.insert("end",endObject);
    json.insert("location", location);
    json.insert("description", description);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    QNetworkAccessManager nam;
    QNetworkReply *reply = nam.put(request, QJsonDocument(json).toJson());
    while (!reply->isFinished())
    {
        qApp->processEvents();
    }
    QString respondata = QVariant(reply->error()).toString();
    qDebug() << "RESPONSE UPDATE ->" << respondata;
    data::setStatus(respondata);
}
void data::ResetClicked()
{
    calendar.clear();
}


