#include "movingprojectorbackground.h"

#include <QElapsedTimer>
#include <QDebug>
#include <QPainter>
#include <QTimer>

#include "simplevariantanimation.h"


MovingProjectorBackground::MovingProjectorBackground() :
    Background(),
    _start(QDateTime::currentDateTimeUtc()),
    _imageUpdated(false)
{
    Projector projector;
    projector.position = QPoint(0, 0);
    projector.frustum = 60;
    projector.color = Qt::red;
    projector.angle = -45;
    projector.animation = createAnimation(-70, -20, 4000);
    _projectors << projector;

    projector.position = QPoint(boundingRect().width() / 2, 0);
    projector.frustum = 60;
    projector.color = Qt::green;
    projector.animation = createAnimation(-125, -55, 8000);
    projector.angle = -90;
    _projectors << projector;

    projector.position = QPoint(boundingRect().width(), 0);
    projector.frustum = 60;
    projector.color = Qt::blue;
    projector.animation = createAnimation(-160, -110, 6400);
    projector.angle = -135;
    _projectors << projector;

    updateImage();
}

QObject *MovingProjectorBackground::createAnimation(qreal minAngle, qreal maxAngle, int duration)
{
    SimpleVariantAnimation *animation = new SimpleVariantAnimation(this);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->setStartValue(minAngle);
    animation->setEndValue(maxAngle);
    animation->setDuration(duration);
    animation->start();
    connect(animation, SIGNAL(valueChanged(QVariant)), SLOT(updateProjectorAngle(QVariant)));
    connect(animation, SIGNAL(finished()), SLOT(onAnimationFinished()));

    return animation;
}

void MovingProjectorBackground::updateImage()
{
    if(! _imageUpdated)
    {
        QSize size = boundingRect().size().toSize();
        QImage image(size.width(), size.height(), QImage::Format_RGB32);
        image.fill(Qt::black);

        QPainter painter(&image);
        painter.setPen(Qt::NoPen);
        painter.setCompositionMode(QPainter::CompositionMode_Plus);

        foreach(const Projector &projector, _projectors)
        {
            painter.save();
            painter.setBrush(projector.color);
            painter.translate(projector.position);
            painter.drawPie(-600, -600, 1200, 1200,
                            (projector.angle - projector.frustum / 2) * 16,
                            projector.frustum * 16);
            painter.restore();
        }

        painter.end();

        setImage(image);

        _imageUpdated = true;
    }
}

void MovingProjectorBackground::updateProjectorAngle(const QVariant &angle)
{
    for(int i=0 ; i<_projectors.count() ; i++)
    {
        if(_projectors[i].animation == sender())
        {
            Projector newProjector = _projectors[i];
            newProjector.angle = angle.toReal();
            _projectors[i] = newProjector;
            _imageUpdated = false;
            QTimer::singleShot(0, this, SLOT(updateImage()));
            break;
        }
    }
}

void MovingProjectorBackground::onAnimationFinished()
{
    QAbstractAnimation *animation = qobject_cast<QAbstractAnimation *>(sender());
    animation->setDirection(animation->direction() == QAbstractAnimation::Forward ? QAbstractAnimation::Backward : QAbstractAnimation::Forward);
    animation->start();
}
