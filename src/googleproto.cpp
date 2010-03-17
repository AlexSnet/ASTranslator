#include "googleproto.h"

GoogleProto::GoogleProto()
{
    http = new QHttp(this);
    version = new QString("0.9.11");

    setTranslationArrays();

    connect( http, SIGNAL(done(bool)), this, SLOT(textTranslated()) );
}
int GoogleProto::setProxy( const QString & host, int port, const QString & username = QString(), const QString & password = QString() )
{
    return http->setProxy( host, port, username, password );
}
int GoogleProto::unsetProxy( )
{
    return http->setProxy(QNetworkProxy());
}
void GoogleProto::startTranslation( int from, int to, QString text )
{
    QString fr;

    if( from >= 0 ) fr = translatesShort.at(from);
    else fr = "auto";

    QString url = QString("/translate_a/t?client=t&sl=" + fr + "&tl=" + translatesShort.at(to) );

    QByteArray ba("text=");
    ba.append( text.toUtf8() );

    headers = QHttpRequestHeader("POST", url, 1, 1);
    headers.setValue("Host", "www.google.com");
    headers.setValue("User-Agent", "Mozilla/5.0 (ASTranslator)" );
    headers.setValue("Accept-Encoding", "deflate");
    headers.setContentLength(text.length());
    headers.setValue("Connection", "Close");

    http->setHost("www.google.com");
    http->request( headers, ba );

}
void GoogleProto::textTranslated()
{
    QString text;
    QByteArray json;
    QVariant val;

    json.append( http->readAll() );

    THJsonStreamReader reader( json );
    while (!reader.atEnd()) {
                switch (reader.readNext()) {
                        case THJsonStreamReader::NoToken:
                                break;
                        case THJsonStreamReader::Invalid:
                                break;
                        case THJsonStreamReader::PropertyNumerical:
                                break;
                        case THJsonStreamReader::PropertyString:
                                if( !QString("trans").compare( reader.name() ) ){
                                    val = reader.value();
                                    text.append( QString::fromUtf8( val.toByteArray() ) + "\n" );
                                    val.clear();
                                    qDebug() << "^^^ Here is it ^^^";
                                }
                                break;
                        case THJsonStreamReader::PropertyFalse:
                                break;
                        case THJsonStreamReader::PropertyTrue:
                                break;
                        case THJsonStreamReader::PropertyNull:
                                break;
                        case THJsonStreamReader::Object:
                                break;
                        case THJsonStreamReader::ObjectEnd:
                                break;
                        case THJsonStreamReader::Array:
                                break;
                        case THJsonStreamReader::ArrayEnd:
                                break;
                }
        }

    emit( translationComplete( text ) );
}

void GoogleProto::setTranslationArrays()
{
    translatesShort
    <<"sq"  <<"ar"  <<"bg"  <<"ca"
    <<"zh-CN"   <<"zh-TW"   <<"hr"
    <<"cs"  <<"da"  <<"nl"  <<"en"
    <<"et"  <<"tl"  <<"fi"  <<"fr"
    <<"gl"  <<"de"  <<"el"  <<"iw"
    <<"hi"  <<"hu"  <<"id"  <<"it"
    <<"ja"  <<"ko"  <<"lv"  <<"lt"
    <<"mt"  <<"no"  <<"pl"  <<"pt"
    <<"ro"  <<"ru"  <<"sr"  <<"sk"
    <<"sl"  <<"es"  <<"sv"  <<"th"
    <<"tr"  <<"uk"  <<"vi";
    translatesFull
    <<"Albanian"  <<"Arabic"  <<"Bulgarian"  <<"Catalan"
    <<"Chinese (Simplified)"   <<"Chinese (Traditional)"   <<"Croatian"
    <<"Czech"  <<"Danish"  <<"Dutch"  <<"English"
    <<"Estonian"  <<"Filipino"  <<"Finnish"  <<"French"
    <<"Galician"  <<"German"  <<"Greek"  <<"Hebrew"
    <<"Hindi"  <<"Hungarian"  <<"Indonesian"  <<"Italian"
    <<"Japanese"  <<"Korean"  <<"Latvian"  <<"Lithuanian"
    <<"Maltese"  <<"Norwegian"  <<"Polish"  <<"Portuguese"
    <<"Romanian"  <<"Russian"  <<"Serbian"  <<"Slovak"
    <<"Slovenian"  <<"Spanish"  <<"Swedish"  <<"Thai"
    <<"Turkish"  <<"Ukrainian"  <<"Vietnamese";
}
