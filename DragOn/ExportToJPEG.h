#ifndef EXPORTTOJPEG_H
#define EXPORTTOJPEG_H

#include "ExportStrategy.h"

class ExportToJPEG : public ExportStrategy {
public:
    void exportScene(const QPixmap &pixmap, const QString &fileName) override;
};

#endif // EXPORTTOJPEG_H

