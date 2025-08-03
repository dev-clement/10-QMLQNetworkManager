#include <QQuickStyle>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "appwrapper.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Material");
    QQmlApplicationEngine engine;
    AppWrapper o_wrapper;

    if (!o_wrapper.init(&app)) {
        return -1;
    }

    return app.exec();
}
