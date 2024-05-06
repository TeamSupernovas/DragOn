#include "ExportToSVG.h"
#include <QSvgGenerator>
#include <QPainter>

void ExportToSVG::exportScene(const QPixmap &pixmap, const QString &fileName) {
    QSvgGenerator generator;
    generator.setFileName(fileName);
    generator.setSize(pixmap.size());
    generator.setViewBox(QRect(0, 0, pixmap.width(), pixmap.height()));

    QPainter painter(&generator);
    painter.drawPixmap(0, 0, pixmap);
}

