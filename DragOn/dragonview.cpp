#include "dragonview.h"
#include<QGraphicsItem>
#include<QMimeData>
#include<QDrag>
#include <QGraphicsRectItem>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

DragOnView::DragOnView(DragOnScene * scene): QGraphicsView(scene) {
    setAcceptDrops(true);
}
