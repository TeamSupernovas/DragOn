#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QButtonGroup>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QToolBox>

#include "shapeitem.h"
#include "dragonscene.h"


class SideBar: public QToolBox
{
public:
    SideBar(QMainWindow *mainWindow, DragOnScene * scene, QGraphicsView * view);

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
