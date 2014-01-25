#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>

class Character;
class EndLevel;

class Level : public QGraphicsScene
{
    Q_OBJECT

    public:
        explicit Level(QString level_name, QObject *parent = 0);

        QColor GetBackgroundColor(QPoint pos);


        virtual void CreateLevelPlatform()=0;
        virtual void FinishCreateLevel();

    private:
        Character *character1;
        Character *character2;

        EndLevel* _end_level;

    public slots:
        void level_changed( const QList<QRectF> & region);


protected:
    void drawBackground ( QPainter * painter, const QRectF & rect );

private:
    QString _level_name;
};

#endif // LEVEL_H
