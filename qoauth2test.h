#ifndef QAUTHTEST_H
#define QAUTHTEST_H

#include <QObject>
#include <QOAuth2AuthorizationCodeFlow>
#include <QDesktopServices>
#include <QOAuthHttpServerReplyHandler>
#include <QJsonDocument>
#include <QList>
class QOAuth2Test : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString textToDisplay READ getToDisplay WRITE setToDisplay NOTIFY textToDisplayChanged)
    Q_PROPERTY(QString textToDisplay READ getToDisplay WRITE setToDisplay NOTIFY textToDisplayChanged)
    Q_PROPERTY(QVariantList calendarlistToDisplay READ getCalendarId WRITE setCalendarId NOTIFY calendarlistToDisplayChanged)
public:
    explicit QOAuth2Test(QObject *parent = nullptr);
    Q_INVOKABLE void grant();
    Q_INVOKABLE void refreshdata();
    QString getToDisplay() const;
    void setToDisplay(const QString &value);
    void testInfo(const QString &token);
    void testCalendarId(const QString &token);
    QJsonDocument getQJSonData() const;
    void setQJSonData(const QJsonDocument &datajson);
    void passing();
    void test();
    QString getToken();
    void setToken(QString &token){}

    void setCalendarId(QVariantList &calendarlist);
    QVariantList getCalendarId();
    Q_INVOKABLE void choosenCalendar(QString choosen);
    Q_INVOKABLE void configTimeMin(QDate timeMin);
    Q_INVOKABLE void configTimeMax(QDate timeMin);

signals:
    void textToDisplayChanged();
    void calendarlistToDisplayChanged();
signals:
    void send_data(QJsonDocument jsondata, QString token, QString calendarID);
    void ResetClicked();
public slots:
    void onGranted();
private:
    QOAuth2AuthorizationCodeFlow google;
    QString toDisplay;
    QString Token;
    QVariantList m_calendarlist;
    QVariantList m_calendarlistID;
    QString m_calendarID;
    QJsonDocument jsondata;
    QList<QString> m_listCalendarIdAdded;
    QString timeMax = "2019-01-03T10:00:00-07:00" ;
    QString timeMin = "2020-12-03T10:00:00-07:00" ;
};

#endif // QAUTHTEST_H
