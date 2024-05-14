#ifndef COLORSERIALIZER_H
#define COLORSERIALIZER_H

#include <QString>
#include <QColor>

class ColorSerializer
{
public:
    ColorSerializer();
    static QString serialize(const QColor& color);
    static QColor deserialize(const QString& str);
};

#endif // COLORSERIALIZER_H
