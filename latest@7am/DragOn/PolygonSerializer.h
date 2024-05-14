#ifndef POLYGONSERIALIZER_H
#define POLYGONSERIALIZER_H

#include <QString>
#include <QPolygonF>

class PolygonSerializer {

public:
    PolygonSerializer();
    static QString serialize(const QPolygonF& polygon);
    static QPolygonF deserialize(const QString& serialized);
};

#endif // POLYGONSERIALIZER_H
