#ifndef APPWRAPPER_HPP
#define APPWRAPPER_HPP

#include <memory>
#include <QObject>
#include <QByteArray>
#include <QStringList>
#include <QNetworkReply>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QNetworkAccessManager>

class AppWrapper : public QObject
{
    Q_OBJECT
    static constexpr const char *API_ENDPOINT = "https://jsonplaceholder.typicode.com/posts";
    static constexpr const char *MODULE_NAME = "QMLNetworkAccessManager";
    using NetworkAccessManagerPtr = std::unique_ptr<QNetworkAccessManager>;
    using NetworkReplyPtr = QNetworkReply *;
public:
    explicit AppWrapper(QObject *po_parent = nullptr);
    ~AppWrapper() = default;
    bool init(QGuiApplication *po_app);
    Q_INVOKABLE void fetchPosts();
    Q_INVOKABLE void removeLast();

private slots:
    void dataReadyRead();
    void dataReadFinished();

private:
    void resetModel();
    void convertToJsonArray();

private:
    NetworkAccessManagerPtr _po_netAccessMgr;
    NetworkReplyPtr         _po_netReply;
    QByteArray              _o_dataBuffer;
    QStringList             _o_posts;
    QQmlApplicationEngine   _o_appEngine;
};

#endif // APPWRAPPER_HPP
