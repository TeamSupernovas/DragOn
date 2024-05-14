#ifndef FONTSERIALIZER_H
#define FONTSERIALIZER_H

#include <QString>
#include <QFont>

class FontSerializer
{
public:
    FontSerializer();

    static QString serialize(const QFont& font);
    static QFont deserialize(const QString& str);
};

#endif // FONTSERIALIZER_H
