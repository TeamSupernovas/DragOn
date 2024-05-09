#include "TextItem.h"
#include <QPainter>

TextItem::TextItem(QGraphicsItem *parent)
    : QGraphicsTextItem(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

TextItem * TextItem::createTextItem(QString text, QFont font, QColor color) {
    TextItem * textItem = new TextItem();
    textItem->setFont(font);
    textItem->setPlainText(text);
    textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
    textItem->setDefaultTextColor(color);
    return textItem;
}

TextItem * TextItem::createTextItem(QString text, QFont font, QColor color, QTransform transform) {
    TextItem * textItem = new TextItem();
    textItem->setFont(font);
    textItem->setPlainText(text);
    textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
    textItem->setDefaultTextColor(color);
    textItem->setTransform(transform);
    return textItem;
}

QVariant TextItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
        emit selectedChange(this);
    return value;
}


void TextItem::focusOutEvent(QFocusEvent *event)
{
    setTextInteractionFlags(Qt::NoTextInteraction);
    emit lostFocus(this);
    QGraphicsTextItem::focusOutEvent(event);
}

void TextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (textInteractionFlags() == Qt::NoTextInteraction)
        setTextInteractionFlags(Qt::TextEditorInteraction);
    QGraphicsTextItem::mouseDoubleClickEvent(event);
}

void  TextItem::accept(SceneItemVisitor *visitor) {
    visitor->visitTextItem(this);
}


