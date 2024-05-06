#ifndef EXPORTTOPNG_H
#define EXPORTTOPNG_H

#include "ExportStrategy.h"

class ExportToPNG : public ExportStrategy {
public:
    void exportScene(const QPixmap &pixmap, const QString &fileName) override;
};

#endif // EXPORTTOPNG_H

