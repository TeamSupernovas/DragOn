#ifndef DRAGONSCENE_H
#define DRAGONSCENE_H

#include <QGraphicsScene>
#include <QObject>
#include "shapeitem.h"


enum class SceneMode {
None, AddItem, MoveItem
};


class DragOnScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit DragOnScene(QObject *parent = nullptr);
    void setMode(SceneMode mode);
    void setSelectedItem(ShapeItem * shapeItem);

signals:

private:
    SceneMode sceneMode{SceneMode::None};
    ShapeItem * selectedItem{nullptr};
};

#endif // DRAGONSCENE_H
