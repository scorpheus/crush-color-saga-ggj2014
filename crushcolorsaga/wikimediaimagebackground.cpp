#include "wikimediaimagebackground.h"

#include <QDebug>
#include <QDateTime>
#include <QDomDocument>
#include <QNetworkReply>
#include <QGraphicsBlurEffect>


WikimediaImageBackground::WikimediaImageBackground() :
    Background(),
    _network(new QNetworkAccessManager(this))
{
    requestList();
}

void WikimediaImageBackground::requestList()
{
    connect(_network, SIGNAL(finished(QNetworkReply*)),
                      SLOT(onListRequestFinished(QNetworkReply*)),
                      Qt::UniqueConnection);

    QDateTime startTime(QDate(2003, 1, 1));
    QDateTime lastTime = QDateTime::currentDateTimeUtc();
    qint64 delta = startTime.msecsTo(lastTime);
    qsrand(delta);
    qreal randFactor = qrand() / qreal(RAND_MAX);
    QDateTime randomTime = startTime.addMSecs(randFactor * delta);

    QString request = "http://en.wikipedia.org/w/api.php?action=query&list=allimages&ailimit=10&aisort=timestamp&format=xml&aistart=";
    request += randomTime.toString(Qt::ISODate);
    _network->get(QNetworkRequest(QUrl(request)));
}

void WikimediaImageBackground::onListRequestFinished(QNetworkReply *reply)
{
    reply->deleteLater();

    QDomDocument doc;
    doc.setContent(reply);

    QDomNodeList imageNodes = doc.elementsByTagName("query").at(0).firstChild().childNodes();
    for(int i=0 ; i<imageNodes.count() ; i++)
    {
        QString url = imageNodes.at(i).attributes().namedItem("url").nodeValue();
        QString lowUrl = url.toLower();
        if(lowUrl.endsWith(".jpg") || lowUrl.endsWith(".jpeg") || lowUrl.endsWith(".png"))
        {
            qDebug() << url;
            disconnect(_network, 0, this, 0);
            connect(_network, SIGNAL(finished(QNetworkReply*)),
                              SLOT(onDownloadRequestFinished(QNetworkReply*)));
            _network->get(QNetworkRequest(QUrl(url)));
            return;
        }
    }

    requestList();
}

void WikimediaImageBackground::onDownloadRequestFinished(QNetworkReply *reply)
{
    reply->deleteLater();

    disconnect(_network, 0, this, 0);

    QImage image = QImage::fromData(reply->readAll());
    if(image.isNull())
    {
        requestList();
    }
    else
    {
        setImage(image.scaled(boundingRect().size().toSize()));
    }
}
