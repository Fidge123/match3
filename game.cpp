#include "game.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>

#include "tile.h"
#include "grid.h"

Game::Game()
    : m_scene(new QGraphicsScene(this))
{
    setScene(m_scene);

    Grid * grid = new Grid;

    QGraphicsPixmapItem * bg = new QGraphicsPixmapItem(QPixmap(":/assets/BackGround.jpg"));
    m_scene->addItem(bg);

    QGraphicsTextItem * score = new QGraphicsTextItem("Score: 0");
    score->setScale(4);
    score->setDefaultTextColor(QColor(255, 255, 255));
    score->setPos(50, 50);
    m_scene->addItem(score);

    for (auto tile : grid->tiles())
    {
        if (tile != nullptr)
        {
            m_scene->addItem(tile);
        }
    }
}

Game::~Game()
{

}

QGraphicsScene * Game::scene()
{
    return m_scene;
}

