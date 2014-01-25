#ifndef MOVINGPROJECTORBACKGROUND_H
#define MOVINGPROJECTORBACKGROUND_H

#include "background.h"

#include <QDateTime>

class MovingProjectorBackground : public Background
{
    Q_OBJECT

    public:
        explicit MovingProjectorBackground();

    protected:
        virtual void timerEvent(QTimerEvent *);

    private:
        void updateImage();

        QObject *createAnimation(qreal minAngle, qreal maxAngle, int duration);

    private slots:
        void updateProjectorAngle(const QVariant &angle);

        void onAnimationFinished();

    private:
        typedef struct
        {
            QPoint position;
            qreal frustum;
            qreal angle;
            QColor color;
            QObject *animation;
        } Projector;

    private:
        QDateTime _start;
        QList<Projector> _projectors;
};

#endif // MOVINGPROJECTORBACKGROUND_H
