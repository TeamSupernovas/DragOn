
#include "dragonscene.h"

#include<QGraphicsItem>
#include<QMimeData>
#include<QDrag>
#include <QGraphicsRectItem>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include "AddCommand.h"
#include "MoveCommand.h"
#include "ResizeCommand.h"

#include <QCursor>

bool canResize(QRectF sceneBoundingRect, QPointF eventScenePos) {
    return (sceneBoundingRect.bottomRight() - eventScenePos).manhattanLength() < 30;
}


DragOnScene::DragOnScene(CommandManager * commandManager, QObject *parent): QGraphicsScene(parent), commandManager(commandManager)
{}

void DragOnScene::setMode(SceneMode mode) {
    sceneMode = mode;
}

QDrag * DragOnScene::createDrag(const QString& text) {

    // Create a MIME data object to hold the item's data
    QMimeData *mimeData = new QMimeData;
    mimeData->setText(text);

    // Create a drag object and set the MIME data
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);

    return drag;
}

void DragOnScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "scene mouse pressed";
    if (event->button() == Qt::LeftButton) {
        if (selectedItem && canResize(selectedItem->sceneBoundingRect(), event->scenePos())) {
            // start Resize
            event->accept();
            setSelectedItem(selectedItem);
            sceneMode = SceneMode::ResizeItem;
            qDebug() << "scene mode is ResizeItem now";

            QDrag *drag = createDrag("Resize");

            // Start the drag operation
            drag->exec(Qt::MoveAction);

        } else {
            unSelectIfSelectedItem();

            // Find the top-most item at the mouse position
            QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
            if (auto *shapeItem = dynamic_cast<ShapeItem*>(item)) {
                if (sceneMode == SceneMode::None) {
                    if (item && item->flags() & QGraphicsItem::ItemIsMovable) {

                        event->accept();
                        setSelectedItem(shapeItem);
                        sceneMode = SceneMode::MoveItem;
                        qDebug() << "scene mode is MoveItem now";


                        QDrag *drag = createDrag("Move");
                        drag->setPixmap(shapeItem->image());
                        drag->setHotSpot((event->scenePos() - shapeItem->scenePos()).toPoint());

                        // Start the drag operation
                        drag->exec(Qt::MoveAction);
                    }
                }
            }
        }
    }
}

void DragOnScene::dropEvent(QGraphicsSceneDragDropEvent *event) {
    qDebug() << "Dropped Dropped:";
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasText()) {
        QString text = mimeData->text();
        qDebug() << "Dropped text:" << text;
        if (selectedItem) {
            if (sceneMode == SceneMode::AddItem) {
                selectedItem->setPos(event->scenePos());
                commandManager->executeCommand(new AddCommand(selectedItem, this));
                sceneMode = SceneMode::None;
                event->accept();
            } else if (sceneMode == SceneMode::MoveItem) {
                QPointF dropPos = event->scenePos();
                QPointF moveBy = dropPos - sceneDragStartPos;
                if (moveBy.x() || moveBy.y()) {
                    commandManager->executeCommand(new MoveCommand(selectedItem, moveBy));
                }
                sceneMode = SceneMode::None;
                event->accept();
            } else if (sceneMode == SceneMode::ResizeItem) {
                QPointF newBottomRight = event->scenePos() - selectedItem->pos();
                QPointF changeBoundingRectSizeBy = newBottomRight - selectedItem->polygon().boundingRect().bottomRight();
                commandManager->executeCommand(new ResizeCommand(selectedItem, changeBoundingRectSizeBy));
                sceneMode = SceneMode::None;
                event->accept();
            }
        }
    }
    qDebug() << "Dropped Dropped:";
}

void DragOnScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
    //qDebug() << "Drag Move Event";
}


void DragOnScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {

    if (event->mimeData()->hasText()) {
        qDebug() << "dragEnterEvent has text: " << event->mimeData()->text();
    }
    sceneDragStartPos = event->scenePos();
    qDebug() << "Drag entered entered";
    QGraphicsScene::dragEnterEvent(event);
}

void DragOnScene::setSelectedItem(ShapeItem *item) {
    unSelectIfSelectedItem();
    selectedItem = item;
    selectedItem->setSelected(true);
}

void DragOnScene::unSelectIfSelectedItem() {
    foreach (QGraphicsItem *item, items()) {
        if (item->isSelected()) {
            item->setSelected(false);
        }
    }
    selectedItem = nullptr;
}

void DragOnScene::drawBackground(QPainter *painter, const QRectF &rect) {
    const qreal gridSize = 20.0;  // Grid spacing
    qreal left = int(rect.left()) - (int(rect.left()) % int(gridSize));
    qreal top = int(rect.top()) - (int(rect.top()) % int(gridSize));

    QVarLengthArray<QLineF, 100> lines;

    for (qreal x = left; x < rect.right(); x += gridSize) {
        lines.append(QLineF(x, rect.top(), x, rect.bottom()));
    }

    for (qreal y = top; y < rect.bottom(); y += gridSize) {
        lines.append(QLineF(rect.left(), y, rect.right(), y));
    }

    painter->setPen(QPen(Qt::gray, 0, Qt::DotLine));
    painter->drawLines(lines.data(), lines.size());
}

