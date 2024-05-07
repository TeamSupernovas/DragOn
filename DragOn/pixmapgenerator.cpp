#include "pixmapgenerator.h"



#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>


QPixmap PixmapGenerator::createPixmapFromScene(DragOnScene *scene) {
    scene->unSelectIfSelectedItem();

    // Create a pixmap with the size of the scene
    QPixmap pixmap(800, 600);
    pixmap.fill(Qt::white);

    // Create a painter to render the scene onto the pixmap
    QPainter painter(&pixmap);
    painter.translate(-scene->sceneRect().topLeft());
    scene->render(&painter);

    return pixmap;
}
