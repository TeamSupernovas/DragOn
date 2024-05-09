#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QButtonGroup>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QToolBox>

#include "ShapeItem.h"
#include "DragOnScene.h"


class DragOnSidebar: public QToolBox
{
public:
    DragOnSidebar(QMainWindow *mainWindow, DragOnScene * scene, QGraphicsView * view);

private slots:
    void buttonGroupPressed(QAbstractButton *button);


private:
    QWidget *createCellWidget(const QString &text, ShapeType type);

    QMainWindow * mainWindow;
    DragOnScene * scene;
    QGraphicsView *view;

    QButtonGroup * buttonGroup;

};

#endif // SIDEBAR_H
