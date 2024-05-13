#ifndef DRAGONSCENE_H
#define DRAGONSCENE_H

#include <QDrag>
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QPainter>
#include <QFont>
#include <QColor>

#include "ItemVisitors.h"
#include "DragOnSceneItem.h"
#include "TextItem.h"
#include "SceneMode.h"
#include "SceneModeState.h"

class DragOnScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit DragOnScene(QObject *parent = nullptr);
    void setMode(SceneMode mode);
    void setSelectedItem(DragOnSceneItem * shapeItem);
    void unSelectIfSelectedItem();
    void addTextItem(TextItem * textItem);
    void setTextColor(const QColor &color);
    QFont currentFont();
    void setFont(const QFont &font);
    void setFontSize(int fontSize);
    void  accept(SceneItemVisitor *visitor);
    DragOnSceneItem * getSelectedItem();

    QColor getTextItemColor() const;

    QPointF getSceneDragStartPos() const;

    bool getDragCreated() const;
    void setDragCreated(bool newDragCreated);
    QDrag * createDrag(const QString& text);
    bool canResize(QRectF sceneBoundingRect, QPointF eventScenePos);

public slots:
    void editorLostFocus(TextItem *item);

signals:
    void textInserted(QGraphicsTextItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    SceneMode sceneMode{SceneMode::None};
    DragOnSceneItem * selectedItem{nullptr};
    QPointF sceneDragStartPos;
    QFont textItemFont;
    QColor textItemColor;
    int stextFontSize{12};
    QGraphicsRectItem *boundingBox = nullptr;
    std::map<SceneMode, SceneModeState*> sceneModeStateMap;
    bool dragCreated;
};


#endif // DRAGONSCENE_H
