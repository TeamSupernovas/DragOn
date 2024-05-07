#ifndef DRAGONSCENE_H
#define DRAGONSCENE_H

#include <QDrag>
#include <QGraphicsScene>
#include <QObject>
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsSceneDragDropEvent>
#include<QPainter>


#include "shapeitem.h"
#include "CommandManager.h"


enum class SceneMode {
None, AddItem, MoveItem, RotateItem, ResizeItem
};


class DragOnScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit DragOnScene(CommandManager * commandManager, QObject *parent = nullptr);
    void setMode(SceneMode mode);
    void setSelectedItem(ShapeItem * shapeItem);
    void unSelectIfSelectedItem();

protected:
    QDrag * createDrag(const QString& text);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    SceneMode sceneMode{SceneMode::None};
    ShapeItem * selectedItem{nullptr};
    CommandManager * commandManager;
    QPointF sceneDragStartPos;
};

#endif // DRAGONSCENE_H
