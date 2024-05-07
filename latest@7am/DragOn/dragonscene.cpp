
#include "dragonscene.h"

#include<QGraphicsItem>
#include<QMimeData>
#include <QTextCursor>
#include<QDrag>
#include <QGraphicsRectItem>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include "AddShapeCommand.h"
#include "AddTextCommand.h"
#include "MoveCommand.h"
#include "ResizeCommand.h"
#include "diagramtextitem.h"
#include "ChangeTextColorCommand.h"
#include "ChangeTextFontCommand.h"

#include <QCursor>

bool canResize(QRectF sceneBoundingRect, QPointF eventScenePos) {
    return (sceneBoundingRect.bottomRight() - eventScenePos).manhattanLength() < 30;
}


DragOnScene::DragOnScene(CommandManager * commandManager, QObject *parent)
    : QGraphicsScene(parent), commandManager(commandManager), textItemColor(Qt::black)
{
}

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
    bool dragCreated = false;
    if (event->button() == Qt::LeftButton) {
        if (selectedItem) {
            if (auto *selectedShapeItem = dynamic_cast<ShapeItem*>(selectedItem)) {
                if (canResize(selectedShapeItem->sceneBoundingRect(), event->scenePos())) {
                    dragCreated = true;
                    // start Resize
                    event->accept();
                    setSelectedItem(selectedItem);
                    sceneMode = SceneMode::ResizeItem;
                    qDebug() << "scene mode is ResizeItem now";

                    QDrag *drag = createDrag("Resize");

                    // Start the drag operation
                    drag->exec(Qt::MoveAction);
                }
            }

        }
        if (!dragCreated){
            // Find the top-most item at the mouse position
            QGraphicsItem *graphicsItem = itemAt(event->scenePos(), QTransform());
            if (graphicsItem == nullptr) {
                unSelectIfSelectedItem();
            }
            else if (auto *sceneItem = dynamic_cast<DragOnSceneItem*>(graphicsItem)) {
                if (sceneMode == SceneMode::None) {
                    if (graphicsItem && graphicsItem->flags() & QGraphicsItem::ItemIsMovable) {

                        event->accept();
                        setSelectedItem(sceneItem);
                        sceneMode = SceneMode::MoveItem;
                        qDebug() << "scene mode is MoveItem now";

                        QDrag *drag = createDrag("Move");
                        if (auto *shapeItem = dynamic_cast<ShapeItem*>(graphicsItem)) {
                            drag->setPixmap(shapeItem->image());
                        }
                        drag->setHotSpot((event->scenePos() - graphicsItem->scenePos()).toPoint());
                        dragCreated = true;
                        // Start the drag operation
                        drag->exec(Qt::MoveAction);
                    }
                }
            }
        }
        if (!dragCreated) {
            QGraphicsScene::mousePressEvent(event);
        }
    }
}

void DragOnScene::dropEvent(QGraphicsSceneDragDropEvent *event) {
    qDebug() << "Dropped Dropped:";

    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasText()) {
        QString text = mimeData->text();
        qDebug() << "Dropped text:" << text;
        if (sceneMode == SceneMode::InsertText) {
            QTransform transform;
            transform.translate(event->scenePos().rx(), event->scenePos().ry());
            DiagramTextItem * textItem = DiagramTextItem::createTextItem(
                QString("lorem ipsum"),
                textItemFont,
                textItemColor,
                transform
            );
            setSelectedItem(textItem);
            qDebug() << "insert text item now";
            commandManager->executeCommand(new AddTextCommand(textItem, this));
            sceneMode = SceneMode::None;
            event->accept();
        } else if (selectedItem) {
            if (sceneMode == SceneMode::AddShapeItem) {
                if (auto *shapeItem = dynamic_cast<ShapeItem*>(selectedItem)) {
                    shapeItem->setPos(event->scenePos());
                    commandManager->executeCommand(new AddShapeCommand(shapeItem, this));
                    sceneMode = SceneMode::None;
                    event->accept();
                }
            } else if (sceneMode == SceneMode::MoveItem) {
                if (auto *graphicsItem = dynamic_cast<QGraphicsItem*>(selectedItem)) {
                    QPointF dropPos = event->scenePos();
                    QPointF moveBy = dropPos - sceneDragStartPos;
                    if (moveBy.x() || moveBy.y()) {
                        commandManager->executeCommand(new MoveCommand(graphicsItem, moveBy));
                    }
                    sceneMode = SceneMode::None;
                    event->accept();
                }
            } else if (sceneMode == SceneMode::ResizeItem) {
                if (auto *shapeItem = dynamic_cast<ShapeItem*>(selectedItem)) {
                    QPointF newBottomRight = event->scenePos() - shapeItem->pos();
                    QPointF changeBoundingRectSizeBy = newBottomRight - shapeItem->polygon().boundingRect().bottomRight();
                    commandManager->executeCommand(new ResizeCommand(shapeItem, changeBoundingRectSizeBy));
                    sceneMode = SceneMode::None;
                    event->accept();
                }
            }
        }
    }
    qDebug() << "Dropped Dropped:";
}

void DragOnScene::editorLostFocus(DiagramTextItem *item)
{
    QTextCursor cursor = item->textCursor();
    cursor.clearSelection();
    item->setTextCursor(cursor);

    if (item->toPlainText().isEmpty()) {
        removeItem(item);
        item->deleteLater();
    }
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

void DragOnScene::setSelectedItem(DragOnSceneItem *item) {
    unSelectIfSelectedItem();
    selectedItem = item;
    if (auto *graphicsItem = dynamic_cast<QGraphicsItem*>(item)) {
        graphicsItem->setSelected(true);
        if (1) {
            // Create and show the bounding box only if not in resize mode
            boundingBox = addRect(graphicsItem->sceneBoundingRect(), QPen(Qt::DashLine));
        }
    }
}

void DragOnScene::unSelectIfSelectedItem() {
    foreach (QGraphicsItem *item, selectedItems()) {
        item->setSelected(false);
    }
    // Remove and hide the bounding box
    if (boundingBox) {
        removeItem(boundingBox);
        boundingBox = nullptr;
    }
    selectedItem = nullptr;
}

void DragOnScene::drawBackground(QPainter *painter, const QRectF &rect) {
    const qreal gridSize = 10.0;  // Grid spacing
    qreal left = int(rect.left()) - (int(rect.left()) % int(gridSize));
    qreal top = int(rect.top()) - (int(rect.top()) % int(gridSize));

    QVarLengthArray<QLineF, 100> lines;

    for (qreal x = left; x < rect.right(); x += gridSize) {
        lines.append(QLineF(x, rect.top(), x, rect.bottom()));
    }

    for (qreal y = top; y < rect.bottom(); y += gridSize) {
        lines.append(QLineF(rect.left(), y, rect.right(), y));
    }

    painter->setPen(QPen(Qt::blue, 0, Qt::DotLine));
    painter->drawLines(lines.data(), lines.size());
}


void DragOnScene::addTextItem(DiagramTextItem * textItem) {
    textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
    connect(textItem, &DiagramTextItem::lostFocus,
            this, &DragOnScene::editorLostFocus);
    addItem(textItem);
}

void DragOnScene::setTextColor(const QColor &color)
{
    textItemColor = color;
    if (selectedItem) {
        if (auto *textItem = dynamic_cast<DiagramTextItem*>(selectedItem)) {
            commandManager->executeCommand(new ChangeTextColorCommand(textItem, color));
        }
    }
}

QFont DragOnScene::currentFont() {
    return textItemFont;
}

void DragOnScene::setFont(const QFont &font)
{
    textItemFont = font;
    if (selectedItem) {
        if (auto *textItem = dynamic_cast<DiagramTextItem*>(selectedItem)) {
            commandManager->executeCommand(new ChangeTextFontCommand(textItem, font));
        }
    }

}

void DragOnScene::accept(SceneItemVisitor *visitor) {
    foreach (QGraphicsItem *item, items()) {
        if (auto *sceneItem = dynamic_cast<DragOnSceneItem*>(item)) {
            sceneItem->accept(visitor);
        }
    }
}

