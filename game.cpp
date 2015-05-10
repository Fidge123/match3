#include "game.h"

#include <QGraphicsScene>

#include "tile.h"
#include "grid.h"

Game::Game()
    : m_scene(new QGraphicsScene(this))
{
    setScene(m_scene);

    Grid * grid = new Grid;

    QGraphicsPixmapItem * bg = new QGraphicsPixmapItem(QPixmap(":/assets/BackGround.jpg"));
    m_scene->addItem(bg);

    for (auto tile : grid->tiles())
        m_scene->addItem(tile);
}

Game::~Game()
{

}

QGraphicsScene * Game::scene()
{
    return m_scene;
}

