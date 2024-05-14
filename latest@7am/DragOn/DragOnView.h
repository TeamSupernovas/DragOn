#ifndef DRAGONVIEW_H
#define DRAGONVIEW_H

#include <QGraphicsView>
#include <QDropEvent>
#include <QDragEnterEvent>

#include "DragOnScene.h"

class DragOnView : public QGraphicsView {
    Q_OBJECT

public:
    DragOnView(DragOnScene *scene);

};

#endif // DRAGONVIEW_H
