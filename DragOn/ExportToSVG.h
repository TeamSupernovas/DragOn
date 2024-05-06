#ifndef EXPORTTOSVG_H
#define EXPORTTOSVG_H

#include "ExportStrategy.h"

class ExportToSVG : public ExportStrategy {
public:
    void exportScene(const QPixmap &pixmap, const QString &fileName) override;
};

#endif // EXPORTTOSVG_H

