#ifndef SIMPLEVARIANTANIMATION_H
#define SIMPLEVARIANTANIMATION_H

#include <QVariantAnimation>

class SimpleVariantAnimation : public QVariantAnimation
{
    Q_OBJECT

    public:
        explicit SimpleVariantAnimation(QObject *parent = 0);

    inline virtual void updateCurrentValue(const QVariant &value) {}
};

#endif // SIMPLEVARIANTANIMATION_H
