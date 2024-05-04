#include "DragOnMainWindow.h"
#include "dragonview.h"
#include <QHBoxLayout>

DragOnMainWindow::DragOnMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scene = new DragOnScene;
    scene->setSceneRect(QRectF(0, 0, 5000, 5000));

    view = new DragOnView(scene);
    sidebar = new SideBar(this, scene, view);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(sidebar);

    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("Drag On"));
    setUnifiedTitleAndToolBarOnMac(true);

}

DragOnMainWindow::~DragOnMainWindow() {}
