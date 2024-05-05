
#include "LoadSaveVisitor.h"
#include "dragonscene.h"
#include<QStringList>
#include <QTransform>


QString serializeTransform(const QTransform& transform) {
    QString serialized;
    serialized += QString::number(transform.m11()) + "," +
                  QString::number(transform.m12()) + "," +
                  QString::number(transform.m13()) + "," +
                  QString::number(transform.m21()) + "," +
                  QString::number(transform.m22()) + "," +
                  QString::number(transform.m23()) + "," +
                  QString::number(transform.m31()) + "," +
                  QString::number(transform.m32()) + "," +
                  QString::number(transform.m33());
    return serialized;
}

QTransform deserializeTransform(const QString& serialized) {
    QStringList parts = serialized.split(",");
    if (parts.size() != 9) {
        // Error handling: Invalid input format
        return QTransform();
    }

    qreal m11 = parts[0].toDouble();
    qreal m12 = parts[1].toDouble();
    qreal m13 = parts[2].toDouble();
    qreal m21 = parts[3].toDouble();
    qreal m22 = parts[4].toDouble();
    qreal m23 = parts[5].toDouble();
    qreal m31 = parts[6].toDouble();
    qreal m32 = parts[7].toDouble();
    qreal m33 = parts[8].toDouble();

    return QTransform(m11, m12, m13,
                      m21, m22, m23,
                      m31, m32, m33);
}

QString serializePolygon(const QPolygonF& polygon) {
    QStringList points;
    for (const QPointF& point : polygon) {
        points << QString::number(point.x()) + "," + QString::number(point.y());
    }
    return points.join(";");
}

QPolygonF deserializePolygon(const QString& serialized) {
    QStringList pointStrings = serialized.split(";");
    QPolygonF polygon;
    for (const QString& pointString : pointStrings) {
        QStringList coords = pointString.split(",");
        if (coords.size() == 2) {
            qreal x = coords[0].toFloat();
            qreal y = coords[1].toFloat();
            polygon << QPointF(x, y);
        }
    }
    return polygon;
}



void SaveVisitor::visitSceneItem(QGraphicsItem *item) {
    if (auto *shapeItem = dynamic_cast<ShapeItem*>(item)) {
        visitShapeItem(shapeItem);
    }

}


void SaveVisitor::visitShapeItem(ShapeItem *item) {

    out << "ShapeItem::" << static_cast<int>(item->getShapeType()) << "::" << serializePolygon(item->polygon()) << "::" << serializeTransform(item->sceneTransform()) << "\n";
}

void loadDeserializeShapeItem(DragOnScene *scene, const QString& serialized) {
    QStringList parts = serialized.split("::");
    if (parts.size() != 4 or parts[0].compare("ShapeItem") != 0) {
        // Error handling: Invalid input format
        qDebug() << "wrong serialization of shapeitem: " << serialized;
        return;
    }

    ShapeType shapeType = static_cast<ShapeType>(parts[1].toInt());
    QPolygonF polygon = deserializePolygon(parts[2]);
    QTransform transform = deserializeTransform(parts[3]);

    ShapeItem * item = new ShapeItem(shapeType, polygon);
    item->setTransform(transform);

    scene->addItem(item);
}

void loadDeserializeShapeItemList(DragOnScene *scene, const QString& serializedList) {
    QStringList itemStrings = serializedList.split("\n", Qt::SkipEmptyParts);

    for (const QString& itemString : itemStrings) {
        loadDeserializeShapeItem(scene, itemString);
    }
}


void SceneLoader::loadToScene(DragOnScene *scene) {
    QString serializedList = in.readAll();
    qDebug() << "Loaded file:" << serializedList;

    scene->clear();

    // Deserialize and load the serialized list
    loadDeserializeShapeItemList(scene, serializedList);
}

