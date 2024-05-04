#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QButtonGroup>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "shapeitem.h"
#include "dragonscene.h"


class SideBar: public QObject
{
public:
    SideBar(QMainWindow *mainWindow, DragOnScene * scene, QGraphicsView * view, QObject* parent = nullptr);

private slots:
    void buttonGroupClicked(QAbstractButton *button);


private:
    QWidget *createCellWidget(const QString &text, ShapeType type);

    QMainWindow * mainWindow;
    DragOnScene * scene;
    QGraphicsView *view;

    QButtonGroup * buttonGroup;

};

#endif // SIDEBAR_H
