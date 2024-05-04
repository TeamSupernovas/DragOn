#include "sidebar.h"
#include <QAbstractButton>
#include <QGridLayout>
#include <QToolButton>
#include <QHBoxLayout>
#include<QMimeData>
#include<QDrag>
#include "shapefactory.h"


SideBar::SideBar(QMainWindow *mainWindow, DragOnScene * scene, QGraphicsView * view):
    mainWindow(mainWindow), scene(scene), view(view) {

    buttonGroup = new QButtonGroup(mainWindow);
    buttonGroup->setExclusive(false);
    scene->connect(buttonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonPressed),
            this, &SideBar::buttonGroupPressed);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createCellWidget(tr("Rectangle"), ShapeType::Rectangle), 0, 0);

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
            button->setChecked(false);
    }
    const int id = buttonGroup->id(button);
    ShapeParameters shapeParams;
    shapeParams.params.insert("rect", QRectF(0, 0, 128, 64));
    ShapeItem*  item = ShapeFactory::createShape(ShapeType(id), shapeParams);
    scene->setSelectedItem(item);
    scene->setMode(SceneMode::AddItem);

    // Create a MIME data object to hold the data being dragged
    QMimeData *mimeData = new QMimeData;
    mimeData->setText("rect"); // Example: Passing current text

    // Create a drag object and set the MIME data
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(item->image());

    // Start the drag operation
    drag->exec(Qt::CopyAction);

}

QWidget *SideBar::createCellWidget(const QString &text, ShapeType type)
{

    ShapeParameters shapeParams;
    shapeParams.params.insert(text, QRectF(0, 0, 200, 100));
    ShapeItem*  item = ShapeFactory::createShape(type, shapeParams);

    QIcon icon(item->image());

    delete item;

    QToolButton *button = new QToolButton;
    button->setIcon(icon);
    button->setIconSize(QSize(20, 20));
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
