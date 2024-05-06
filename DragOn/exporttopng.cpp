#include "ExportToPNG.h"

#include <QPixmap>

void ExportToPNG::exportScene(const QPixmap &pixmap, const QString &fileName) {
    pixmap.save(fileName, "PNG");
}

QString ExportToPNG::getName() const {
    return QString("Export to PNG");
}

QString ExportToPNG::getExtension() const {
    return "png";
}

QIcon ExportToPNG::getIcon() {
    return QIcon(":/images/background2.png");
}

