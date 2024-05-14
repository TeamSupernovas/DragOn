#include "PolygonSerializer.h"

PolygonSerializer::PolygonSerializer() {}

QString PolygonSerializer::serialize(const QPolygonF& polygon) {
    QStringList points;
    for (const QPointF& point : polygon) {
        points << QString::number(point.x()) + "," + QString::number(point.y());
    }
    return points.join(";");
}

QPolygonF PolygonSerializer::deserialize(const QString& serialized) {
    QStringList pointStrings = serialized.split(";");
    QPolygonF polygon;
    for (const QString& pointString : pointStrings) {
        QStringList coords = pointString.split(",");
        if (coords.size() == 2) {
            qreal x = coords[0].toFloat();
            qreal y = coords[1].toFloat();
            polygon << QPointF(x, y);
        }
    }
    return polygon;
}
