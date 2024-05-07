#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include "Command.h"
#include <QGraphicsItem>

class MoveCommand : public Command {
public:
    MoveCommand(QGraphicsItem * item, QPointF moveBy);

    void undo() override;
    void redo() override;

private:
    QGraphicsItem * item;
    QPointF moveBy;

};

#endif // MOVECOMMAND_H
