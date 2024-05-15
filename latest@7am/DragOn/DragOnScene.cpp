
#include "DragOnScene.h"

#include <QGraphicsItem>
#include <QMimeData>
#include <QTextCursor>
#include <QDrag>
#include <QGraphicsRectItem>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include "CommandManager.h"
#include "TextItem.h"
#include "ChangeTextColorCommand.h"
#include "ChangeTextFontCommand.h"
#include "SceneModeNone.h"
#include "SceneModeAddShapeItem.h"
#include "SceneModeMoveItem.h"
#include "SceneModeRotateItem.h"
#include "SceneModeResizeItem.h"
#include "SceneModeAddTextItem.h"

#include <QCursor>

DragOnScene::DragOnScene(QObject *parent) : QGraphicsScene(parent), textItemColor(Qt::black) {

    sceneModeStateMap[SceneMode::None] = new SceneModeNone(this);
    sceneModeStateMap[SceneMode::AddShapeItem] = new SceneModeAddShapeItem(this);
    sceneModeStateMap[SceneMode::MoveItem] = new SceneModeMoveItem(this);
    sceneModeStateMap[SceneMode::RotateItem] = new SceneModeRotateItem(this);
    sceneModeStateMap[SceneMode::ResizeItem] = new SceneModeResizeItem(this);
    sceneModeStateMap[SceneMode::AddTextItem] = new SceneModeAddTextItem(this);

}

bool DragOnScene::canResize(QRectF sceneBoundingRect, QPointF eventScenePos) {
    return (sceneBoundingRect.bottomRight() - eventScenePos).manhattanLength() < 30;
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
    sceneModeStateMap.at(sceneMode)->onMousePress(event);
    if (!getDragCreated()) {
        QGraphicsScene::mousePressEvent(event);
    }
}

void DragOnScene::dropEvent(QGraphicsSceneDragDropEvent *event) {
    sceneModeStateMap.at(sceneMode)->onDrop(event);
    if (!event->isAccepted()) {
        QGraphicsScene::dropEvent(event);
    }
}


void DragOnScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
    sceneModeStateMap.at(sceneMode)->onDragMove(event);
}


void DragOnScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
    sceneModeStateMap.at(sceneMode)->onDragEnter(event);
    QGraphicsScene::dragEnterEvent(event);
}


void DragOnScene::editorLostFocus(TextItem *item) {
    QTextCursor cursor = item->textCursor();
    cursor.clearSelection();
    item->setTextCursor(cursor);
    item->update();

    if (item->toPlainText().isEmpty()) {
        removeItem(item);
        item->deleteLater();
    }
}

void DragOnScene::setSelectedItem(DragOnSceneItem *item) {
    unSelectIfSelectedItem();
    selectedItem = item;
    if (auto *graphicsItem = dynamic_cast<QGraphicsItem*>(item)) {
        graphicsItem->setSelected(true);
        if (false) {
            // Create and show the bounding box only if not in resize mode
            boundingBox = addRect(graphicsItem->sceneBoundingRect(), QPen(Qt::DashLine));
        }
    }
}

void DragOnScene::unSelectIfSelectedItem() {
    foreach (QGraphicsItem *item, selectedItems()) {
        item->setSelected(false);
    }
    selectedItem = nullptr;
}

bool DragOnScene::getDragCreated() const {
    return dragCreated;
}

void DragOnScene::setDragCreated(bool newDragCreated) {
    dragCreated = newDragCreated;
}

QPointF DragOnScene::getSceneDragStartPos() const {
    return sceneDragStartPos;
}

QColor DragOnScene::getTextItemColor() const {
    return textItemColor;
}


void DragOnScene::addTextItem(TextItem * textItem) {
    textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
    connect(textItem, &TextItem::lostFocus, this, &DragOnScene::editorLostFocus);
    addItem(textItem);
}

void DragOnScene::setTextColor(const QColor &color) {
    textItemColor = color;
    if (selectedItem) {
        if (auto *textItem = dynamic_cast<TextItem*>(selectedItem)) {
            CommandManager::instance()->executeCommand(new ChangeTextColorCommand(textItem, color));
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
        if (auto *textItem = dynamic_cast<TextItem*>(selectedItem)) {
            CommandManager::instance()->executeCommand(new ChangeTextFontCommand(textItem, font));
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

DragOnSceneItem *DragOnScene::getSelectedItem() {
    return selectedItem;
}

void DragOnScene::drawBackground(QPainter *painter, const QRectF &rect) {
    const qreal gridSize = 10.0;  // Grid spacing
    int left = static_cast<int>(rect.left()) - (static_cast<int>(rect.left()) % static_cast<int>(gridSize));
    int top = static_cast<int>(rect.top()) - (static_cast<int>(rect.top()) % static_cast<int>(gridSize));

    QVarLengthArray<QLineF, 100> lines;

    for (int x = left; x < static_cast<int>(rect.right()); x += static_cast<int>(gridSize)) {
        lines.append(QLineF(x, rect.top(), x, rect.bottom()));
    }

    for (int y = top; y < static_cast<int>(rect.bottom()); y += static_cast<int>(gridSize)) {
        lines.append(QLineF(rect.left(), y, rect.right(), y));
    }

    painter->setPen(QPen(Qt::blue, 0, Qt::DotLine));
    painter->drawLines(lines.data(), lines.size());
}

void DragOnScene::setSceneDragStartPos(QPointF newSceneDragStartPos) {
    sceneDragStartPos = newSceneDragStartPos;
}


