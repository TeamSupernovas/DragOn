#ifndef PIXMAPGENERATOR_H
#define PIXMAPGENERATOR_H

#include <QPixmap>
#include <QGraphicsScene>
#include "dragonscene.h"

class PixmapGenerator
{
public:
    static QPixmap createPixmapFromScene(DragOnScene *scene);
};

#endif // PIXMAPGENERATOR_H
