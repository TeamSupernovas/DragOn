#include "sidebar.h"
#include <QAbstractButton>
#include <QGridLayout>
#include <QToolButton>
#include <QHBoxLayout>
#include<QMimeData>
#include<QDrag>
#include <QLabel>
#include "shapefactory.h"
#include "iconbutton.h"


SideBar::SideBar(QMainWindow *mainWindow, DragOnScene * scene, QGraphicsView * view):
    mainWindow(mainWindow), scene(scene), view(view) {

    buttonGroup = new QButtonGroup(mainWindow);
    buttonGroup->setExclusive(false);

    scene->connect(buttonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonPressed),
                   this, &SideBar::buttonGroupPressed);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createCellWidget(tr("Rectangle"), ShapeType::Rectangle), 0, 0);
    layout->addWidget(createCellWidget(tr("Circle"), ShapeType::Circle), 1, 0);
    layout->addWidget(createCellWidget(tr("Line"), ShapeType::Line), 2, 0);
    layout->addWidget(createCellWidget(tr("Square"), ShapeType::Square), 3, 0);
    layout->addWidget(createCellWidget(tr("Triangle"), ShapeType::Triangle), 4, 0);
    layout->addWidget(createCellWidget(tr("Rhombus"), ShapeType::Rhombus), 5, 0);
    layout->addWidget(createCellWidget(tr("Pentagon"), ShapeType::Pentagon), 6, 0);

    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(layout);

    setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    setMinimumWidth(itemWidget->sizeHint().width());
    addItem(itemWidget, tr("Shapes"));
}


void SideBar::buttonGroupPressed(QAbstractButton *button)
{
    const QList<QAbstractButton *> buttons = buttonGroup->buttons();
    for (QAbstractButton *myButton : buttons) {
        if (myButton != button)
        {
            button->setChecked(false);
        }

    }
    const int id = buttonGroup->id(button);
    ShapeItem*  item = ShapeFactory::createDefaultShape(ShapeType(id));
    scene->setSelectedItem(item);
    scene->setMode(SceneMode::AddItem);

    // Create a MIME data object to hold the data being dragged
    QMimeData *mimeData = new QMimeData;
    mimeData->setText("add shape"); // Example: Passing current text

    // Create a drag object and set the MIME data
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(item->image());

    // Start the drag operation
    drag->exec(Qt::CopyAction);

}

QWidget *SideBar::createCellWidget(const QString &text, ShapeType type)
{

    ShapeItem*  item = ShapeFactory::createDefaultShape(type);

    QIcon icon(item->image());


    IconButton *button = new IconButton(icon);
    button->setIcon(icon);
    button->setIconSize(QSize(100, 100));
    button->setToolTip(text);
    button->setCheckable(true);
    buttonGroup->addButton(button, int(type));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button);
    //layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    //layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}
