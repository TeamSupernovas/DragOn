#ifndef TRANSFORMSERIALIZER_H
#define TRANSFORMSERIALIZER_H

#include <QTransform>
#include <QStringList>

class TransformSerializer
{
public:
    TransformSerializer();
    static QString serialize(const QTransform& transform);
    static QTransform deserialize(const QString& serialized);
};

#endif // TRANSFORMSERIALIZER_H
