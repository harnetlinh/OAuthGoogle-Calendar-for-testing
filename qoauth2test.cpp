

#include "qoauth2test.h"
#include <QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QtDebug>
#include <data.h>
#include <QtNetwork>
#include <QByteArray>
#include <data.h>
#include <data_import.h>

QOAuth2Test::QOAuth2Test(QObject *parent) : QObject(parent)
{

    // Truy cập browser để xác thực
    connect(&google, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
        &QDesktopServices::openUrl);
    // Receive answer from authorization request process
    connect(&google, &QOAuth2AuthorizationCodeFlow::granted, this, &QOAuth2Test::onGranted);
    google.setScope("https://www.googleapis.com/auth/calendar");
    QString authUri = "https://accounts.google.com/o/oauth2/auth";
    QString clientId = "243977505354-ed8vaqcecbclr6lj0drm8p6i1djs06iv.apps.googleusercontent.com";
    QString tokenUri = "https://oauth2.googleapis.com/token";
    QString clientSecret = "qNrAzdzOcg74_352n40aBnsd";
    quint16 port = 8080;
    google.setAuthorizationUrl(authUri);
    google.setClientIdentifier(clientId);
    google.setAccessTokenUrl(tokenUri);
    google.setClientIdentifierSharedKey(clientSecret);
    // QOAuth2Test : creating reply handler server
    auto replyHandler = new QOAuthHttpServerReplyHandler(port, this);
    // QOAuth2Test reply handler server created";
    google.setReplyHandler(replyHandler);
    // QOAuth2Test reply handler set";
}

void QOAuth2Test::grant()
{
    google.grant();
    passing();
}

void QOAuth2Test::onGranted()
{
    qInfo() << "received Token: " << google.token();
    QString token = google.token();
    Token = token;
    setToDisplay(google.token());
    Token = token;
    //testCalendarId(token);
    QVariantList list;
    setCalendarId(m_calendarlist);
}

QString QOAuth2Test::getToken()
{
     return Token;
}

QString QOAuth2Test::getToDisplay() const
{
    return toDisplay;
}
QJsonDocument QOAuth2Test::getQJSonData() const
{
    return jsondata;
}
void QOAuth2Test::setQJSonData(const QJsonDocument &datajson)
{
    QOAuth2Test::jsondata = datajson;
    emit send_data(jsondata, Token, m_calendarID);
}
void QOAuth2Test::passing(){

    emit send_data(jsondata, Token, m_calendarID);
}


void QOAuth2Test::setToDisplay(const QString &value)
{
    if (toDisplay != value)
    {
        toDisplay = value;
        emit textToDisplayChanged();
    }
}
void QOAuth2Test::refreshdata()
{
    QJsonDocument doc;
    jsondata = doc;
    emit ResetClicked();
    for(int i = 0; i < m_listCalendarIdAdded.length();i++ ){

     m_calendarID = m_listCalendarIdAdded.at(i);
    testCalendarId(Token);
    }
}


void QOAuth2Test::testCalendarId(const QString &token)
{
    const QString bearerFormat = QStringLiteral("Bearer %1");
    //fpt.edu.vn_al3chhtnae1dmjlttboj8g0jr4%40group.calendar.google.com
    //?timeMax="+timeMax+"&timeMin="+timeMin+"&
//    json.insert("timeMax","2020-12-30T09:45:00+07:00");
//    json.insert("timeMin","2019-12-30T09:45:00+07:00");
    QString min = timeMin.toLocal8Bit();
    QString max = timeMax.toLocal8Bit();
    qDebug() << "timeMax: " << timeMax;
    qDebug() << "timeMin: " << timeMin;
    QNetworkRequest request(QUrl("https://www.googleapis.com/calendar/v3/calendars/"+ m_calendarID +"/events?timeMax=2020-12-30T09%3A45%3A00%2B07%3A00&timeMin=2019-12-30T09%3A45%3A00%2B07%3A00&key=AIzaSyDC969ZTJewE_2MalRP20HPnTVkSoTvx5A HTTP/1.1"));
    qDebug() << "QUrl: " << "https://www.googleapis.com/calendar/v3/calendars/"+ m_calendarID +"/events?timeMax="+max+"&timeMin="+min+"&key=AIzaSyDC969ZTJewE_2MalRP20HPnTVkSoTvx5A HTTP/1.1";
    request.setRawHeader("Authorization", "Bearer "+token.toUtf8());
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("User-Agent", "My Calendar v0.1");
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    foreach( QByteArray rawHeader , request.rawHeaderList() )
    {
        qDebug() << request.rawHeader(rawHeader);
    }
    QJsonObject json;

    QNetworkAccessManager nam;
    QNetworkReply *reply = nam.get(request);
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QByteArray response_data = reply->readAll();
    qDebug() <<"testCalendarId" << response_data;
    QJsonDocument datajson = QJsonDocument::fromJson(response_data);
    setQJSonData(datajson);
}

void QOAuth2Test::setCalendarId(QVariantList &calendarlist)
{
    if(calendarlist.isEmpty())
    {
        //https://www.googleapis.com/calendar/v3/users/me/calendarList?key=[YOUR_API_KEY] HTTP/1.1
        QNetworkRequest request(QUrl("https://www.googleapis.com/calendar/v3/users/me/calendarList?key=AIzaSyDC969ZTJewE_2MalRP20HPnTVkSoTvx5A HTTP/1.1"));
        request.setRawHeader("Authorization", "Bearer "+Token.toUtf8());
        request.setRawHeader("Content-Type", "application/json");
        request.setRawHeader("User-Agent", "My Calendar v0.1");
        request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
        QJsonObject json;
        QNetworkAccessManager nam;
        QNetworkReply *reply = nam.get(request);
        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();
        QByteArray response_data = reply->readAll();
        //qDebug() << "list calendar = " << response_data;
        QJsonDocument datajson = QJsonDocument::fromJson(response_data);
        QJsonObject jsonObject =  datajson.object();
        QJsonArray array = jsonObject.value("items").toArray();
        int i=0;
        foreach (const QJsonValue & v, array)
        {
            i++;
            m_calendarlist.push_back(QString::number(i) + " || " + v.toObject().value("summary").toString());
            m_calendarlistID.push_back(v.toObject().value("id").toString());
        }

    }
    emit calendarlistToDisplayChanged();
    testCalendarId(Token);
}
QVariantList QOAuth2Test::getCalendarId()
{
    return m_calendarlist;
}
void QOAuth2Test::choosenCalendar(QString choosen)
{
    int i = choosen.split("||").first().toInt();
    m_calendarID = m_calendarlistID.at(i-1).toString();
    //qDebug() <<"Choosen calendar id ="<< m_calendarID;
    m_listCalendarIdAdded.push_back(m_calendarID);
    testCalendarId(Token);
}
void QOAuth2Test::configTimeMin(QDate timeMinChoosen)
{
    timeMin = timeMinChoosen.toString("yyyy-MM-dd")+"T10:00:00-07:00";
}
void QOAuth2Test::configTimeMax(QDate timeMaxChoosen)
{
    timeMax = timeMaxChoosen.toString("yyyy-MM-dd")+"T10:00:00-07:00";
}











