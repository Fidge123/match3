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
    void mousePressEvent(QMouseEvent *event);

protected:
    QGraphicsScene * m_scene;
};
