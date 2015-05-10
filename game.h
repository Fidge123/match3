#pragma once

#include <QGraphicsView>

class QGraphicsScene;

class Game : public QGraphicsView
{
public:
    Game();
    ~Game();

    QGraphicsScene * scene();

protected:
    QGraphicsScene * m_scene;
};
