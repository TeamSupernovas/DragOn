#ifndef TEXTITEM_H
#define TEXTITEM_H

#include <QGraphicsTextItem>

#include "DragOnSceneItem.h"

class TextItem : public QGraphicsTextItem, public DragOnSceneItem {
    Q_OBJECT

public:
    enum { Type = UserType + 3 };
    TextItem(QGraphicsItem *parent = nullptr);
    int type() const override { return Type; }
    static TextItem * createTextItem(QString text, QFont font, QColor color);
    static TextItem * createTextItem(QString text, QFont font, QColor color, QTransform transform);
    void  accept(SceneItemVisitor *visitor) override;

signals:
    void lostFocus(TextItem *item);
    void selectedChange(QGraphicsItem *item);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void focusOutEvent(QFocusEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};


#endif // TEXTITEM_H
