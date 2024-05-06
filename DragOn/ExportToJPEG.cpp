#include "ExportToJPEG.h"
#include <QPixmap>

void ExportToJPEG::exportScene(const QPixmap &pixmap, const QString &fileName) {
    pixmap.toImage().save(fileName, "JPEG");
}

