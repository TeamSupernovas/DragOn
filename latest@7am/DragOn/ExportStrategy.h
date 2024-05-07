#ifndef EXPORTSTRATEGY_H
#define EXPORTSTRATEGY_H

#include <QPixmap>
#include <QString>
#include <QIcon>

class ExportStrategy {
public:
    virtual ~ExportStrategy() {}
    virtual void exportScene(const QPixmap &pixmap, const QString &fileName) = 0;
    virtual QString getName() const = 0;
    virtual QString getExtension() const = 0;
    virtual QIcon getIcon() = 0;

};

#endif // EXPORTSTRATEGY_H
