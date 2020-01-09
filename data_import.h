#ifndef DATA_IMPORT_H
#define DATA_IMPORT_H
#include <QObject>
#include <QOAuth2AuthorizationCodeFlow>
#include <QDesktopServices>
#include <QOAuthHttpServerReplyHandler>
#include <QJsonDocument>
#include <QObject>

class data_import : public QObject
{
    Q_OBJECT
public:
    explicit data_import(QObject *parent=nullptr);
    void set_token();


private:
    QString m_token;
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
};

#endif // DATA_IMPORT_H
