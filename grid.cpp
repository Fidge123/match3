#include "grid.h"

#include <stdlib.h>
#include <time.h>

#include <QVector2D>
#include <QDebug>

#include "tile.h"

Grid::Grid()
{
    m_tiles.resize(c_height * c_width);
    fillGrid();

    while(removePairs())
    {
        fillGrid();
    }
}

Grid::~Grid()
{

}

std::vector<Tile *> Grid::tiles() const
{
    return m_tiles;
}

void Grid::fillGrid()
{
    srand (time(nullptr));

    for (int x = 0; x < c_height; x++)
    {
        for (int y = 0; y < c_width; y++)
        {
            if (m_tiles.at(x * c_height + y) == nullptr)
            {
                m_tiles[x * c_height + y] = new Tile(Color(rand() % 5), QVector2D(x, y));
            }
        }
    }
}

bool Grid::removePairs()
{
    for (int x = 0; x < c_height; x++)
    {
        for (int y = 0; y < c_width; y++)
        {
            int xCounter = 1;
            int yCounter = 1;

            for (int i = 1; i + x < c_height; i++)
            {
                auto my_color = m_tiles.at(x * c_height + y)->color();
                auto other_color = m_tiles.at((x + i) * c_height + y)->color();

                if (my_color == other_color)
                {
                    xCounter++;
                }
                else
                {
                    break;
                }
            }

            for (int i = 1; i + y < c_width; i++)
            {
                auto my_color = m_tiles.at(x * c_height + y)->color();
                auto other_color = m_tiles.at(x * c_height + y + i)->color();

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
                    m_tiles[(x + i) * c_height + y] = nullptr;
                }
                return true;
            }

            if (yCounter >= 3)
            {
                for (int i = 0; i < yCounter; i++)
                {
                    m_tiles[x * c_height + y + i] = nullptr;
                }
                return true;
            }
        }
    }
    return false;
}

