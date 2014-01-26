#ifndef MovingProjectorBackground_Level3_H
#define MovingProjectorBackground_Level3_H

#include "background.h"

#include <QDateTime>

class MovingProjectorBackground_Level3 : public Background
{
    Q_OBJECT

    public:
        explicit MovingProjectorBackground_Level3(QString level_name);

    private:
        QObject *createAnimation(qreal minAngle, qreal maxAngle, int duration);
        QString _level_name;

    private slots:
        void updateImage();

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
        bool _imageUpdated;
};

#endif // MovingProjectorBackground_Level3_H
