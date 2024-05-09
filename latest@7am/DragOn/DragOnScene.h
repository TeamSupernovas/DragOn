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

public slots:
    void editorLostFocus(TextItem *item);

signals:
    void textInserted(QGraphicsTextItem *item);

protected:
    QDrag * createDrag(const QString& text);

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
    int textFontSize{12};
    QGraphicsRectItem *boundingBox = nullptr;
};


#endif // DRAGONSCENE_H