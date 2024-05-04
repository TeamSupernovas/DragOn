#include "DragOnMainWindow.h"
#include "dragonview.h"
#include <QHBoxLayout>

DragOnMainWindow::DragOnMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    CommandManager * commandManager = new CommandManager();
    scene = new DragOnScene(commandManager);
    scene->setSceneRect(QRectF(0, 0, 5000, 5000));

    view = new DragOnView(scene);
    sidebar = new SideBar(this, scene, view);
    toolbar = new DragOnToolBar(this, scene, commandManager);

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
