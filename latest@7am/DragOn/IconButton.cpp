#include "iconbutton.h"

IconButton::IconButton(const QIcon &icon, QWidget *parent) : QPushButton(parent) {
    setIcon(icon);
    setStyleSheet("border: none;");
}
