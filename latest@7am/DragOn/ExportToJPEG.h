#ifndef EXPORTTOJPEG_H
#define EXPORTTOJPEG_H

#include "ExportStrategy.h"

class ExportToJPEG : public ExportStrategy {
public:
    void exportScene(const QPixmap &pixmap, const QString &fileName) override;
    QString getName() const override;
    QString getExtension() const override;
    QIcon getIcon() override;
};

#endif // EXPORTTOJPEG_H

