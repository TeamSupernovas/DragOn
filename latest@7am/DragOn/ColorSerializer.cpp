#include "ColorSerializer.h"

ColorSerializer::ColorSerializer() {}

QString ColorSerializer::serialize(const QColor& color) {
    return QString("%1|%2|%3|%4")
        .arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha());
}

QColor ColorSerializer::deserialize(const QString& str) {
    QStringList parts = str.split("|");
    if (parts.size() >= 4) {
        int red = parts[0].toInt();
        int green = parts[1].toInt();
        int blue = parts[2].toInt();
        int alpha = parts[3].toInt();
        return QColor(red, green, blue, alpha);
    }
    return QColor();
}
