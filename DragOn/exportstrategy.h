#ifndef EXPORTSTRATEGY_H
#define EXPORTSTRATEGY_H

#include <QPixmap>

class ExportStrategy {
public:
    virtual ~ExportStrategy() {}
    virtual void exportScene(const QPixmap &pixmap, const QString &fileName) = 0;
};

#endif // EXPORTSTRATEGY_H
