#ifndef CALENDAR_H
#define CALENDAR_H
#include <qobject.h>

class calendar : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString textToDisplay READ getToDisplay WRITE setToDisplay NOTIFY textToDisplayChanged)
public:
    explicit calendar(QObject *parent = nullptr);
    QString getToDisplay() const;
    void setToDisplay(const QString &value);

};

#endif // CALENDAR_H
