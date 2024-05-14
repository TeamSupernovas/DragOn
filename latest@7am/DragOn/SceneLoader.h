#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <QTextStream>
#include "DragOnScene.h"

class SceneLoader {

public:
    SceneLoader(QTextStream &stream) : in(stream) {}
    void loadToScene(DragOnScene *scene);

private:
    QTextStream &in;
};

#endif // SCENELOADER_H
