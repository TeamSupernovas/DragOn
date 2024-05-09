#include <QGraphicsItem>
#include <QMimeData>
#include <QDrag>
#include <QGraphicsRectItem>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

#include "DragOnView.h"

DragOnView::DragOnView(DragOnScene * scene): QGraphicsView(scene) {
    setAcceptDrops(true);
}
