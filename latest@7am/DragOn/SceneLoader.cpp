#include "SceneLoader.h"

#include <QStringList>
#include <QTransform>
#include "DragOnScene.h"
#include "TextItem.h"
#include "PolygonSerializer.h"
#include "TransformSerializer.h"
#include "ColorSerializer.h"
#include "FontSerializer.h"
#include "ShapeItem.h"

void loadDeserializeItem(DragOnScene *scene, const QString& serialized) {
    QStringList parts = serialized.split("::");

    QString type = parts[0];

    if (type.compare("ShapeItem") == 0) {
        if (parts.size() < 5) {
            // Error handling: Invalid input format
            qDebug() << "wrong serialization of shapeitem: " << serialized;
            return;
        }
        ShapeType shapeType = static_cast<ShapeType>(parts[1].toInt());
        QPolygonF polygon = PolygonSerializer::deserialize(parts[2]);
        QTransform transform = TransformSerializer::deserialize(parts[3]);
        QColor color = ColorSerializer::deserialize(parts[4]);

        ShapeItem * item = new ShapeItem(shapeType, polygon);
        item->setTransform(transform);
        item->setColor(color);

        scene->addItem(item);
    } else if (type.compare("TextItem") == 0) {
        if (parts.size() < 5) {
            // Error handling: Invalid input format
            qDebug() << "wrong serialization of shapeitem: " << serialized;
            return;
        }
        QString text = QString::fromUtf8(QByteArray::fromBase64(parts[1].toUtf8()));
        QFont font = FontSerializer::deserialize(parts[2]);
        QColor color = ColorSerializer::deserialize(parts[3]);
        QTransform transform = TransformSerializer::deserialize(parts[4]);
        QPointF pos(transform.dx(), transform.dy());
        TextItem *textItem = TextItem::createTextItem(text, font, color);
        textItem->setPos(pos);
        scene->addTextItem(textItem);
    }
}

void loadDeserializeItemList(DragOnScene *scene, const QString& serializedList) {
    QStringList itemStrings = serializedList.split("\n", Qt::SkipEmptyParts);

    for (const QString& itemString : itemStrings) {
        loadDeserializeItem(scene, itemString);
    }
}

void SceneLoader::loadToScene(DragOnScene *scene) {
    QString serializedList = in.readAll();
    qDebug() << "Loaded file:" << serializedList;

    scene->clear();

    loadDeserializeItemList(scene, serializedList);
}


