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

const int InsertTextButton = 10;

SideBar::SideBar(QMainWindow *mainWindow, DragOnScene * scene, QGraphicsView * view):
    mainWindow(mainWindow), scene(scene), view(view) {

    buttonGroup = new QButtonGroup(mainWindow);
    buttonGroup->setExclusive(false);

    scene->connect(buttonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonPressed),
                   this, &SideBar::buttonGroupPressed);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createCellWidget(tr("Rectangle"), ShapeType::Rectangle), 1, 0);
    layout->addWidget(createCellWidget(tr("Circle"), ShapeType::Circle), 1, 1);
    layout->addWidget(createCellWidget(tr("Line"), ShapeType::Line), 2, 0);
    layout->addWidget(createCellWidget(tr("Square"), ShapeType::Square), 2, 1);
    layout->addWidget(createCellWidget(tr("Triangle"), ShapeType::Triangle), 3, 0);
    layout->addWidget(createCellWidget(tr("Rhombus"), ShapeType::Rhombus), 3, 1);
    layout->addWidget(createCellWidget(tr("Pentagon"), ShapeType::Pentagon), 4, 0);


    QToolButton *textButton = new QToolButton;
    textButton->setCheckable(true);
    buttonGroup->addButton(textButton, InsertTextButton);
    textButton->setIcon(QIcon(QPixmap(":/images/textpointer.png")));
    textButton->setIconSize(QSize(50, 50));
    QGridLayout *textLayout = new QGridLayout;
    textLayout->addWidget(textButton, 0, 0, Qt::AlignHCenter);
    textLayout->addWidget(new QLabel(tr("Text")), 1, 0, Qt::AlignCenter);
    QWidget *textWidget = new QWidget;
    textWidget->setLayout(textLayout);
    layout->addWidget(textWidget, 0, 1);

    layout->setRowStretch(3, 10);
    layout->setColumnStretch(2, 10);

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
    QPixmap pixmap;
    // Create a MIME data object to hold the data being dragged
    QMimeData *mimeData = new QMimeData;
    if (id == InsertTextButton) {
        scene->setMode(SceneMode::InsertText);
        mimeData->setText("add text");
    } else {
        ShapeItem*  item = ShapeFactory::createDefaultShape(ShapeType(id));
        scene->setSelectedItem(item);
        scene->setMode(SceneMode::AddShapeItem);
        mimeData->setText("add shape");
        pixmap = item->image();
    }

    // Create a drag object and set the MIME data
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);

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
