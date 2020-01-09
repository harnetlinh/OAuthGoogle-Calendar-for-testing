#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "qoauth2test.h"
#include <data_import.h>
#include <QQmlContext>
#include <data.h>
#include <QJsonDocument>
#include <QQmlPropertyMap>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QOAuth2Test authTest;
    QQmlApplicationEngine engine;
    data d;
    QQmlPropertyMap ownerData;
    QObject::connect(&authTest, SIGNAL(send_data(QJsonDocument, QString, QString)), &d, SLOT(receive(QJsonDocument, QString, QString)));
    QObject::connect(&authTest, SIGNAL(ResetClicked()), &d, SLOT(ResetClicked()));
    engine.rootContext()->setContextProperty("calendar", &d);
    engine.rootContext()->setContextProperty("auth", &authTest);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

