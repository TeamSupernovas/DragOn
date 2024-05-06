#include "ExportToJPEG.h"
#include <QPixmap>

void ExportToJPEG::exportScene(const QPixmap &pixmap, const QString &fileName) {
    pixmap.toImage().save(fileName, "JPEG");
}


QString ExportToJPEG::getName() const {
    return QString("Export to JPEG");
}

QString ExportToJPEG::getExtension() const {
    return "jpeg";
}

QIcon ExportToJPEG::getIcon() {
    return QIcon(":/images/background1.png");
}
