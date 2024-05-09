#ifndef DRAGONMAINWINDOW_H
#define DRAGONMAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

#include "DragOnScene.h"
#include "DragOnSidebar.h"
#include "DragOnToolbar.h"

QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QFontComboBox;
class QButtonGroup;
class QLineEdit;
class QGraphicsTextItem;
class QFont;
class QToolButton;
class QAbstractButton;
class QGraphicsView;
QT_END_NAMESPACE

class DragOnMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    DragOnMainWindow(QWidget *parent = nullptr);
    ~DragOnMainWindow();

private:
    DragOnScene *scene;
    QGraphicsView * view;
    DragOnSidebar *sidebar;
    DragOnToolBar * toolbar;

};
#endif // DRAGONMAINWINDOW_H
