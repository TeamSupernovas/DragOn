#ifndef DRAGONMAINWINDOW_H
#define DRAGONMAINWINDOW_H

#include <QMainWindow>
#include "dragonscene.h"
#include "sidebar.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    DragOnScene *scene;
    QGraphicsView * view;
    SideBar *sidebar;

};
#endif // DRAGONMAINWINDOW_H
