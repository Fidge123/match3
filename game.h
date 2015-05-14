#pragma once

#include <QGraphicsView>
#include <QObject>

class QGraphicsScene;
class QGraphicsTextItem;
class QTimer;

class Grid;

class Game : public QGraphicsView
{
    Q_OBJECT

public:
    Game();
    ~Game();

    QGraphicsScene * scene();
    int score();
    void setScore(int score);
    QTimer * timer();

public slots:
    void start();
    void reset();
    void updateTimerDisplay();

protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

protected:
    QGraphicsScene * m_scene;
    QGraphicsTextItem * m_scoreDisplay;
    QGraphicsTextItem * m_timerDisplay;
    unsigned int m_score;
    unsigned int m_seconds;
    QTimer * m_timer;
    bool m_isActive;
    Grid * m_grid;
};
