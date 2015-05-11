#pragma once

#include <QGraphicsView>

class QGraphicsScene;

class Game : public QGraphicsView
{
public:
    Game();
    ~Game();

    QGraphicsScene * scene();
    int score();
    void setScore(int score);

protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

protected:
    QGraphicsScene * m_scene;
    unsigned int m_score;
};
