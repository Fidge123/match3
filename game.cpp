#include "game.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>

#include <QDebug>

#include "tile.h"
#include "grid.h"

Game::Game()
    : m_scene(new QGraphicsScene(this))
    , m_score(0)
{
    setScene(m_scene);

    QGraphicsPixmapItem * bg = new QGraphicsPixmapItem(QPixmap(":/assets/BackGround.jpg"));
    m_scene->addItem(bg);

    Grid * grid = new Grid(this);

    QGraphicsTextItem * score = new QGraphicsTextItem("Score: 0");
    score->setScale(4);
    score->setDefaultTextColor(QColor(255, 255, 255));
    score->setPos(50, 50);
    m_scene->addItem(score);

    /*for (auto tile : grid->tiles())
    {
        if (tile != nullptr)
        {
            m_scene->addItem(tile);
        }
    }*/
}

Game::~Game()
{

}

QGraphicsScene * Game::scene()
{
    return m_scene;
}

int Game::score()
{
    return m_score;
}

void Game::setScore(int score)
{
    m_score = score;
    qDebug() << "Score:" << score;
}

void Game::mousePressEvent(QMouseEvent * event)
{
    QGraphicsView::mousePressEvent(event);
}

