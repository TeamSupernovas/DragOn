#include <QAbstractButton>
#include <QGridLayout>
#include <QToolButton>
#include <QHBoxLayout>
#include <QMimeData>
#include <QDrag>
#include <QLabel>
#include "ShapeFactory.h"
#include "IconButton.h"
#include "DragOnSidebar.h"

const int InsertTextButton = 10;

DragOnSidebar::DragOnSidebar(QMainWindow *mainWindow, DragOnScene *scene, QGraphicsView *view):
    mainWindow(mainWindow), scene(scene), view(view) {

    buttonGroup = new QButtonGroup(mainWindow);
    buttonGroup->setExclusive(false);

    scene->connect(buttonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonPressed),
                   this, &DragOnSidebar::buttonGroupPressed);

    QVBoxLayout *layout = new QVBoxLayout;

    // Text button
    QToolButton *textButton = new QToolButton;
    textButton->setCheckable(true);
    buttonGroup->addButton(textButton, InsertTextButton);
    textButton->setIcon(QIcon(QPixmap(":/images/textpointer.png")));
    textButton->setIconSize(QSize(50, 50));

    QWidget *textWidget = new QWidget;
    QHBoxLayout *textLayout = new QHBoxLayout(textWidget);
    textLayout->addWidget(textButton);
    textLayout->addStretch(); // Add stretch to push the button to the right
    layout->addWidget(textWidget);

    // Horizontal line
    QFrame *line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    layout->addWidget(line);

    // Shape buttons
    QGridLayout *shapeLayout = new QGridLayout;
    layout->addLayout(shapeLayout);
    const QStringList shapeLabels = {tr("Rectangle"), tr("Circle"), tr("Line"), tr("Square"), tr("Triangle"), tr("Rhombus"), tr("Pentagon")};
    const QList<ShapeType> shapeTypes = {ShapeType::Rectangle, ShapeType::Circle, ShapeType::Line, ShapeType::Square, ShapeType::Triangle, ShapeType::Rhombus, ShapeType::Pentagon};
    for (int i = 0; i < shapeLabels.size(); ++i) {
        QWidget *shapeWidget = createCellWidget(shapeLabels[i], shapeTypes[i]);
        shapeLayout->addWidget(shapeWidget, i / 2, i % 2);
    }

    layout->addStretch(); // Add stretch to push shapes to the top


    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(layout);

    setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    setMinimumWidth(itemWidget->sizeHint().width());
    addItem(itemWidget, tr(""));
}

QWidget *DragOnSidebar::createCellWidget(const QString &text, ShapeType type) {
    ShapeItem* item = ShapeFactory::createDefaultShape(type);
    QIcon icon(item->image());
    IconButton *button = new IconButton(icon);
    button->setIcon(icon);
    button->setIconSize(QSize(100, 100));
    button->setToolTip(text);
    button->setCheckable(true);
    buttonGroup->addButton(button, int(type));

    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(button, 0, Qt::AlignHCenter);
    return widget;
}


void DragOnSidebar::buttonGroupPressed(QAbstractButton *button) {
    const QList<QAbstractButton *> buttons = buttonGroup->buttons();
    for (QAbstractButton *myButton : buttons) {
        if (myButton != button) {
            button->setChecked(false);
        }
    }
    const int id = buttonGroup->id(button);
    QPixmap pixmap;
    // Create a MIME data object to hold the data being dragged
    QMimeData *mimeData = new QMimeData;
    if (id == InsertTextButton) {
        scene->setMode(SceneMode::AddTextItem);
        mimeData->setText("add text");
    } else {
        ShapeItem* item = ShapeFactory::createDefaultShape(ShapeType(id));
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
