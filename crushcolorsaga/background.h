#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QObject>
#include <QGraphicsItem>

class Background : public QObject, public QGraphicsItem
{
    Q_OBJECT

    public:
        Background(const QImage &image=QImage());

        virtual QRectF boundingRect() const;

        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    public:
        QColor colorAt(const QPoint &point)
         { return _image.pixel(point); }

    signals:
        void imageChanged();

    protected:
        inline void setImage(const QImage &image)
        { _image = image; update(); emit imageChanged(); }

    private:
        QImage _image;
};

#endif // BACKGROUND_H
