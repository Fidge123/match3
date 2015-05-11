#include "grid.h"

#include <stdlib.h>
#include <time.h>

#include <QVector2D>
#include <QDebug>

#include "game.h"
#include "tile.h"

Grid::Grid(Game * game)
    : m_selectedTile(nullptr)
    , m_game(game)
{
    m_tiles.resize(c_height * c_width);
    fillGrid();

    while(removePairs())
    {
        applyGravity();
        fillGrid();
    }
}

Grid::~Grid()
{
}

void Grid::setSelectedTile(Tile * tile)
{
    if (m_selectedTile == nullptr)
    {
        m_selectedTile = tile;
    }
    else
    {
        swap(m_selectedTile, tile);
        m_selectedTile = nullptr;
    }
}

bool Grid::swap(Tile * t1, Tile * t2)
{
    auto pos1 = t1->position();
    auto pos2 = t2->position();

    m_tiles[pos1.x() * c_width + pos1.y()] = t2;
    t2->setPosition(pos1);

    m_tiles[pos2.x() * c_width + pos2.y()] = t1;
    t1->setPosition(pos2);

    bool isValid = false;

    while (removePairs())
    {
        isValid = true;
        applyGravity();
        fillGrid();
    }

    if (isValid)
    {
        return true;
    }
    else
    {
        m_tiles[pos2.x() * c_width + pos2.y()] = t2;
        t2->setPosition(pos2);

        m_tiles[pos1.x() * c_width + pos1.y()] = t1;
        t1->setPosition(pos1);

        qDebug() << "Nope";
        return false;
    }
}

std::vector<Tile *> Grid::tiles() const
{
    return m_tiles;
}

void Grid::fillGrid()
{
    srand (time(nullptr));

    for (int x = 0; x < c_width; x++)
    {
        for (int y = 0; y < c_height; y++)
        {
            if (m_tiles.at(x * c_width + y) == nullptr)
            {
                m_tiles[x * c_width + y] = new Tile(Color(rand() % 5), QVector2D(x, y), this);
                m_game->scene()->addItem(m_tiles[x * c_width + y]);
            }
        }
    }
}

void Grid::applyGravity()
{
    bool hasFloatingTiles = false;

    while (!hasFloatingTiles)
    {
        hasFloatingTiles = true;

        for (int x = 0; x < c_width; x++)
        {
            for (int y = 1; y < c_height; y++)
            {
                if (m_tiles.at(x * c_width + y) == nullptr &&
                    m_tiles.at(x * c_width + y - 1) != nullptr)
                {
                    m_tiles.at(x * c_width + y - 1)->setPosition(QVector2D(x, y));
                    m_tiles[x * c_width + y] = m_tiles[x * c_width + y - 1];
                    m_tiles[x * c_width + y - 1] = nullptr;

                    hasFloatingTiles = false;
                }
            }
        }
    }
}

bool Grid::removePairs()
{
    for (int x = 0; x < c_width; x++)
    {
        for (int y = 0; y < c_height; y++)
        {
            int xCounter = 1;
            int yCounter = 1;

            for (int i = 1; i + x < c_width; i++)
            {
                if (m_tiles.at(x * c_width + y) == nullptr ||
                    m_tiles.at((x + i) * c_width + y) == nullptr)
                {
                    break;
                }

                auto my_color = m_tiles.at(x * c_width + y)->color();
                auto other_color = m_tiles.at((x + i) * c_width + y)->color();

                if (my_color == other_color)
                {
                    xCounter++;
                }
                else
                {
                    break;
                }
            }

            for (int i = 1; i + y < c_height; i++)
            {
                if (m_tiles.at(x * c_width + y) == nullptr ||
                    m_tiles.at(x * c_width + y + i) == nullptr)
                {
                    break;
                }

                auto my_color = m_tiles.at(x * c_width + y)->color();
                auto other_color = m_tiles.at(x * c_width + y + i)->color();

                if (my_color == other_color)
                {
                    yCounter++;
                }
                else
                {
                    break;
                }
            }

            if (xCounter >= 3)
            {
                for (int i = 0; i < xCounter; i++)
                {
                    m_game->scene()->removeItem(m_tiles[(x + i) * c_width + y]);
                    m_tiles[(x + i) * c_width + y] = nullptr;
                    m_game->setScore(m_game->score() + 1);
                }
                return true;
            }

            if (yCounter >= 3)
            {
                for (int i = 0; i < yCounter; i++)
                {
                    m_game->scene()->removeItem(m_tiles[x * c_width + y + i]);
                    m_tiles[x * c_width + y + i] = nullptr;
                    m_game->setScore(m_game->score() + 1);
                }
                return true;
            }
        }
    }
    return false;
}

