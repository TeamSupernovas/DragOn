#include "LoadSaveVisitor.h"
#include "dragonscene.h"
#include "diagramtextitem.h"
#include <QStringList>
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

QString serializeFont(const QFont& font) {
    return QString("%1|%2|%3|%4")
        .arg(font.family())
        .arg(font.pointSize())
        .arg(static_cast<int>(font.style()))
        .arg(font.weight());
}

QFont deserializeFont(const QString& str) {
    QStringList parts = str.split("|");
    if (parts.size() >= 4) {
        QString family = parts[0];
        int size = parts[1].toInt();
        QFont::Style style = static_cast<QFont::Style>(parts[2].toInt());
        int weight = parts[3].toInt();
        return QFont(family, size, weight, false);
    }
    return QFont();
}

QString serializeColor(const QColor& color) {
    return QString("%1|%2|%3|%4")
        .arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha());
}

QColor deserializeColor(const QString& str) {
    QStringList parts = str.split("|");
    if (parts.size() >= 4) {
        int red = parts[0].toInt();
        int green = parts[1].toInt();
        int blue = parts[2].toInt();
        int alpha = parts[3].toInt();
        return QColor(red, green, blue, alpha);
    }
    return QColor();
}

void SaveVisitor::visitSceneItem(DragOnSceneItem *item) {
    if (auto *shapeItem = dynamic_cast<ShapeItem*>(item)) {
        visitShapeItem(shapeItem);
    }
    if (auto *textItem = dynamic_cast<DiagramTextItem*>(item)) {
        visitTextItem(textItem);
    }
}

void SaveVisitor::visitShapeItem(ShapeItem *item) {
    out << "ShapeItem::" << static_cast<int>(item->getShapeType()) << "::" << serializePolygon(item->polygon()) << "::" << serializeTransform(item->sceneTransform()) << "::" << serializeColor(item->getColor()) << "\n";
}

void SaveVisitor::visitTextItem(DiagramTextItem *item) {
    out << "TextItem::" << QString::fromUtf8(item->toPlainText().toUtf8().toBase64()) << "::" << serializeFont(item->font()) << "::"  << serializeColor(item->defaultTextColor()) << "::" << serializeTransform(item->sceneTransform()) << "\n";
}

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
        QPolygonF polygon = deserializePolygon(parts[2]);
        QTransform transform = deserializeTransform(parts[3]);
        QColor color = deserializeColor(parts[4]);

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
        QFont font = deserializeFont(parts[2]);
        QColor color = deserializeColor(parts[3]);
        QTransform transform = deserializeTransform(parts[4]);
        DiagramTextItem *textItem = DiagramTextItem::createTextItem(text, font, color, transform);
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
