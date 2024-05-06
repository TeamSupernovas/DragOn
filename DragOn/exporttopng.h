#ifndef EXPORTTOPNG_H
#define EXPORTTOPNG_H

#include "ExportStrategy.h"

class ExportToPNG : public ExportStrategy {
public:
    void exportScene(const QPixmap &pixmap, const QString &fileName) override;
    QString getName() const override;
    QString getExtension() const override;
    QIcon getIcon() override;
};

#endif // EXPORTTOPNG_H

