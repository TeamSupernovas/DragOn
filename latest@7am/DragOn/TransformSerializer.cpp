#include "TransformSerializer.h"

TransformSerializer::TransformSerializer() {}

QString TransformSerializer::serialize(const QTransform& transform) {
    QString serialized;
    serialized += QString::number(transform.m11()) + "," +
                  QString::number(transform.m12()) + "," +
                  QString::number(transform.m13()) + "," +
                  QString::number(transform.m21()) + "," +
                  QString::number(transform.m22()) + "," +
                  QString::number(transform.m23()) + "," +
                  QString::number(transform.m31()) + "," +
                  QString::number(transform.m32()) + "," +
                  QString::number(transform.m33());
    return serialized;
}

QTransform TransformSerializer::deserialize(const QString& serialized) {
    QStringList parts = serialized.split(",");
    if (parts.size() != 9) {
        // Error handling: Invalid input format
        return QTransform();
    }

    qreal m11 = parts[0].toDouble();
    qreal m12 = parts[1].toDouble();
    qreal m13 = parts[2].toDouble();
    qreal m21 = parts[3].toDouble();
    qreal m22 = parts[4].toDouble();
    qreal m23 = parts[5].toDouble();
    qreal m31 = parts[6].toDouble();
    qreal m32 = parts[7].toDouble();
    qreal m33 = parts[8].toDouble();

    return QTransform(m11, m12, m13, m21, m22, m23, m31, m32, m33);
}
