#ifndef GOOGLEPROTO_H
#define GOOGLEPROTO_H

#include <QObject>
#include <QtNetwork>

#include "jsonstreamreader.h"

class QHttp;

class GoogleProto : public QObject
{
    Q_OBJECT
public:
    GoogleProto();

    int setProxy( const QString & host, int port, const QString & username, const QString & password );
    int unsetProxy();

    QStringList translatesShort;
    QStringList translatesFull;

public slots:
    void textTranslated();
    void startTranslation( int from, int to, QString text );

signals:
    QString translationComplete( QString text );

private:
    QHttp *http;
    QHttpRequestHeader headers;

    void setTranslationArrays();

    QString *version;
};

#endif // GOOGLEPROTO_H
