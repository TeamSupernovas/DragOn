#include "DragOnMainWindow.h"
#include "dragonview.h"
#include <QHBoxLayout>

DragOnMainWindow::DragOnMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scene = new DragOnScene();
    scene->setSceneRect(QRectF(0, 0, 1500, 1000));

    view = new DragOnView(scene);
    sidebar = new SideBar(this, scene, view);
    toolbar = new DragOnToolBar(this, scene);

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
