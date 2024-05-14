#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QPushButton>
#include <QIcon>

class IconButton : public QPushButton {

public:
    IconButton(const QIcon &icon, QWidget *parent = nullptr);

};

#endif // ICONBUTTON_H
