#include "ExportToPNG.h"

#include <QPixmap>

void ExportToPNG::exportScene(const QPixmap &pixmap, const QString &fileName) {
    pixmap.save(fileName, "PNG");
}

