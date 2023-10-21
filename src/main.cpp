#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "calscontext.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/cals-qt-cpp/Main.qml"_qs);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl)
        {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("calsContext", new CalsContext);
    engine.load(url);

    return app.exec();
}
