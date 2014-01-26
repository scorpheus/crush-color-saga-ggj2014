#ifndef CHARACTER_H
#define CHARACTER_H

#include <QDateTime>
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsRectItem>

class Level;

class Character : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_ENUMS(State)

    public:
        Character(int id, Level *level, const QColor &color);

        virtual QRectF boundingRect() const;

        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

        inline virtual int type() const
        { return UserType + 101; }

    public:
        typedef enum
        {
            Idle          =0x00,
            MovingLeft    =0x01,
            MovingRight   =0x02,
            HittingLeft   =0x04,
            HittingRight  =0x08,
            ThrowingLeft  =0x10,
            ThrowingRight =0x20,
            Attack        =HittingLeft | HittingRight | ThrowingLeft | ThrowingRight,
            Jumping       =0x40
        } State;

        Q_DECLARE_FLAGS(States, State);

        typedef enum
        {
           Normal = 0,
           Stronger,
           VeryStronger,
           Surhuman
        } ShieldState;

        int _Health;

        Character::States getStates();
        int getCharacterHealth();
        void setCharacterHealth(int health);

        inline ShieldState getShield() const
        { return _shield; }

    signals:
        void registerFireBall(QGraphicsItem *fireBall, bool superPower, Qt::LayoutDirection direction);
        void statesChanged(Character::States changedStates);

    public slots:
        void setStates(Character::States states);

    protected:
        virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    private slots:
        void updateAnimation();

        void CheckVulnerabilityColor();

        void updateParticles();

        void updateSuperShield();

    private:
        int _id;
        States _states;
        QTimer *_timerAnimation;
        QTimer *_timerParticles;
        QTimer *_timerSuperShield;
        int _animationIndex;
        int _particleIndex;
        Level *_level;
        QColor _color;
        QColor _surhumanShieldCurrentColor;
        QDateTime _lastShieldUpdate;
        ShieldState _shield;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Character::States);

#endif // CHARACTER_H
