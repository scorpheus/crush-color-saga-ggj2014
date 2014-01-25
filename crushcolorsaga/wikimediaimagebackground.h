#ifndef WIKIMEDIAIMAGEBACKGROUND_H
#define WIKIMEDIAIMAGEBACKGROUND_H

#include "background.h"

#include <QNetworkAccessManager>

class WikimediaImageBackground : public Background
{
    Q_OBJECT

    public:
        explicit WikimediaImageBackground();

    private slots:
        void onListRequestFinished(QNetworkReply *reply);
        void onDownloadRequestFinished(QNetworkReply *reply);

    private:
        void requestList();

    private:
        QNetworkAccessManager *_network;
};

#endif // WIKIMEDIAIMAGEBACKGROUND_H
