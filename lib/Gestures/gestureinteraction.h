#ifndef GESTUREINTERACTION_H
#define GESTUREINTERACTION_H

#include <QObject>
#include <QSharedPointer>
#include "gesturetypes.h"

struct GestureInteractionPrivate;
class GestureBackend;
class GestureInteraction : public QObject {
        Q_OBJECT
    public:
        explicit GestureInteraction(QObject* parent = nullptr);
        ~GestureInteraction();

        GestureTypes::GestureType gestureType();
        GestureTypes::GestureDirection gestureDirection();
        int fingers();

        double percentage();
        double percentage(quint64 time);
        double extrapolatePercentage(quint64 after);

        GestureTypes::DeviceType deviceType();
        double velocity();

        QList<quint64> dataTimes();

        quint64 currentTime();
        quint64 lastDataTime();

        bool isActive();

        bool isValidInteraction(GestureTypes::GestureType type, GestureTypes::GestureDirection direction, int fingers);

    signals:
        void interactionUpdated();
        void interactionEnded();

    protected:
        friend GestureBackend;

        void gestureUpdate(GestureTypes::GestureType type, GestureTypes::GestureDirection direction, double percentage, int fingers, GestureTypes::DeviceType deviceType, quint64 time);
        void gestureEnd();

    private:
        GestureInteractionPrivate* d;
};

typedef QSharedPointer<GestureInteraction> GestureInteractionPtr;

#endif // GESTUREINTERACTION_H
