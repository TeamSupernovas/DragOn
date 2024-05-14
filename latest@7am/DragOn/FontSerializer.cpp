#include "FontSerializer.h"
#include <QStringList>

FontSerializer::FontSerializer() {}

QString FontSerializer::serialize(const QFont& font) {
    return QString("%1|%2|%3|%4")
        .arg(font.family())
        .arg(font.pointSize())
        .arg(static_cast<int>(font.style()))
        .arg(font.weight());
}

QFont FontSerializer::deserialize(const QString& str) {
    QStringList parts = str.split("|");
    if (parts.size() >= 4) {
        QString family = parts[0];
        int size = parts[1].toInt();
        QFont::Style style = static_cast<QFont::Style>(parts[2].toInt());
        int weight = parts[3].toInt();
        return QFont(family, size, weight, false);
    }
    return QFont();
}
