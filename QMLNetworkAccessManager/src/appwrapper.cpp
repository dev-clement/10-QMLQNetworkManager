#include <QUrl>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QQmlContext>
#include <QJsonDocument>
#include "appwrapper.hpp"

AppWrapper::AppWrapper(QObject *po_parent)
    : QObject{po_parent}
    , _po_netAccessMgr{ std::make_unique<QNetworkAccessManager>() }{}

void AppWrapper::fetchPosts() {
    const QUrl o_apiEndpoint = QUrl(API_ENDPOINT);

    QNetworkRequest o_request;
    o_request.setUrl(o_apiEndpoint);

    _po_netReply = _po_netAccessMgr->get(o_request);
    connect(_po_netReply, &QNetworkReply::readyRead, this, &AppWrapper::dataReadyRead);
    connect(_po_netReply, &QNetworkReply::finished, this, &AppWrapper::dataReadFinished);
}

void AppWrapper::removeLast() {
    if (!_o_posts.isEmpty()) {
        _o_posts.removeLast();
        resetModel();
    }
}

void AppWrapper::dataReadyRead() {
    _o_dataBuffer.append(_po_netReply->readAll());
}

void AppWrapper::dataReadFinished() {
    if (_po_netReply->error()) {
        qCritical() << "Error: " << _po_netReply->errorString();
    } else {
        convertToJsonArray();
    }
}

void AppWrapper::resetModel(){
    _o_appEngine.rootContext()->setContextProperty("myModel", QVariant::fromValue(_o_posts));
}

void AppWrapper::convertToJsonArray() {
    QJsonDocument o_doc = QJsonDocument::fromJson(_o_dataBuffer);
    QJsonArray o_arr = o_doc.array();

    for (int i_idx = 0; i_idx < o_arr.size(); ++i_idx) {
        QJsonObject o_obj = o_arr[i_idx].toObject();
        QVariantMap o_map = o_obj.toVariantMap();
        QString o_title = o_map["title"].toString();
        _o_posts.append(o_title);
    }
    if (o_arr.size() != 0) {
        resetModel();
    }
    // Clearing buffer
    _o_dataBuffer.clear();
}

bool AppWrapper::init(QGuiApplication *po_app) {
    _o_appEngine.rootContext()->setContextProperty("Wrapper", this);
    resetModel();

    QObject::connect(
        &_o_appEngine
        , &QQmlApplicationEngine::objectCreationFailed
        , po_app
        , []() { QCoreApplication::exit(-1); }
        , Qt::QueuedConnection
    );
    _o_appEngine.loadFromModule(AppWrapper::MODULE_NAME, "Main");
    return !_o_appEngine.rootObjects().isEmpty();
}
