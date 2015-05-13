#include "grid.h"

#include <stdlib.h>
#include <time.h>

#include <QPointF>

#include "game.h"
#include "tile.h"

static constexpr unsigned int s_width = 8;
static constexpr unsigned int s_height = 8;

Grid::Grid(Game * game)
    : m_selectedTile(nullptr)
    , m_game(game)
{
    initializeTiles();
}

Grid::~Grid()
{
    for (auto row : m_tiles)
    {
        for (auto tile : row)
        {
            m_game->scene()->removeItem(tile);
        }
    }
}

void Grid::setSelectedTile(Tile * tile)
{
    if (m_selectedTile == nullptr)
    {
        m_selectedTile = tile;
        tile->setIsSelected(true);
    }
    else
    {
        m_selectedTile->setIsSelected(false);
        swap(m_selectedTile, tile);
        m_selectedTile = nullptr;
    }
}

bool Grid::swap(Tile * t1, Tile * t2)
{
    auto pos1 = t1->position();
    auto pos2 = t2->position();

    m_tiles[pos1.x()][pos1.y()] = t2;
    t2->setPosition(pos1);

    m_tiles[pos2.x()][pos2.y()] = t1;
    t1->setPosition(pos2);

    bool isValid = false;

    while (removePairs(true))
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
        m_tiles[pos2.x()][pos2.y()] = t2;
        t2->setPosition(pos2);

        m_tiles[pos1.x()][pos1.y()] = t1;
        t1->setPosition(pos1);

        return false;
    }
}

bool Grid::swapUp(Tile * t)
{
    return swap(t, m_tiles[t->position().x()][t->position().y() - 1]);
}

bool Grid::swapDown(Tile * t)
{
    return swap(t, m_tiles[t->position().x()][t->position().y() + 1]);
}

bool Grid::swapLeft(Tile * t)
{
    return swap(t, m_tiles[t->position().x() - 1][t->position().y()]);
}

bool Grid::swapRight(Tile * t)
{
    return swap(t, m_tiles[t->position().x() + 1][t->position().y()]);
}

void Grid::initializeTiles()
{
    for (unsigned int x = 0; x < s_width; x++)
    {
        std::vector<Tile *> empty;
        for (unsigned int y = 0; y < s_height; y++)
        {
            empty.push_back(nullptr);
        }

        m_tiles.push_back(empty);
    }

    fillGrid();

    while (removePairs(false))
    {
        applyGravity();
        fillGrid();
    }
}

void Grid::fillGrid()
{
    srand(time(nullptr) * m_game->score());

    bool isFull = false;

    while (!isFull)
    {
        isFull = true;
        for (unsigned int x = 0; x < m_tiles.size(); x++)
        {
            if (m_tiles[x][0] == nullptr)
            {
                m_tiles[x][0] = new Tile(Color(rand() % 5), QPointF(x, 0), this);
                m_game->scene()->addItem(m_tiles[x][0]);
                isFull = false;
            }
        }
        applyGravity();
    }
}

void Grid::applyGravity()
{
    bool hasFloatingTiles = true;

    while (hasFloatingTiles)
    {
        hasFloatingTiles = false;

        for (unsigned int x = 0; x < m_tiles.size(); x++)
        {
            for (unsigned int y = 1; y < m_tiles[x].size(); y++)
            {
                if (m_tiles[x][y] == nullptr &&
                    m_tiles[x][y - 1] != nullptr)
                {
                    m_tiles[x][y - 1]->setPosition(QPointF(x, y));

                    // swap m_tiles[x][y] (which equals nullptr) and m_tiles[x][y-1]
                    m_tiles[x][y] = m_tiles[x][y - 1];
                    m_tiles[x][y - 1] = nullptr;

                    hasFloatingTiles = true;
                }
            }
        }
    }
}

bool Grid::removePairs(bool enableScoring)
{
    for (unsigned int x = 0; x < m_tiles.size(); x++)
    {
        for (unsigned int y = 0; y < m_tiles[x].size(); y++)
        {
            int xCounter = 1;
            int yCounter = 1;

            for (unsigned int i = 1; x + i < m_tiles.size(); i++)
            {
                if (m_tiles[x][y] == nullptr ||
                    m_tiles[x + i][y] == nullptr)
                {
                    break;
                }

                auto my_color = m_tiles[x][y]->color();
                auto other_color = m_tiles[x + i][y]->color();

                if (my_color == other_color)
                {
                    xCounter++;
                }
                else
                {
                    break;
                }
            }

            for (unsigned int i = 1; y + i < m_tiles[x].size(); i++)
            {
                if (m_tiles[x][y] == nullptr ||
                    m_tiles[x][y + i] == nullptr)
                {
                    break;
                }

                auto my_color = m_tiles[x][y]->color();
                auto other_color = m_tiles[x][y + i]->color();

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
                    m_game->scene()->removeItem(m_tiles[x + i][y]);
                    m_tiles[x + i][y] = nullptr;

                    if (enableScoring)
                    {
                        m_game->setScore(m_game->score() + 1);
                    }
                }
                return true;
            }

            if (yCounter >= 3)
            {
                for (int i = 0; i < yCounter; i++)
                {
                    m_game->scene()->removeItem(m_tiles[x][y + i]);
                    m_tiles[x][y + i] = nullptr;

                    if (enableScoring)
                    {
                        m_game->setScore(m_game->score() + 1);
                    }
                }
                return true;
            }
        }
    }
    return false;
}

