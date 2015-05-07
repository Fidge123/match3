#include "grid.h"

#include <stdlib.h>
#include <time.h>

#include <QVector2D>
#include <QDebug>

#include "tile.h"

Grid::Grid()
{
    srand (time(nullptr));

    for (int x = 0; x < c_height; x++)
    {
        for (int y = 0; y < c_width; y++)
        {
            switch (rand() % 5)
            {
            case 0:
                m_tiles.push_back(new Tile(Color::GREEN, QVector2D(x, y)));
                break;
            case 1:
                m_tiles.push_back(new Tile(Color::BLUE, QVector2D(x, y)));
                break;
            case 2:
                m_tiles.push_back(new Tile(Color::PURPLE, QVector2D(x, y)));
                break;
            case 3:
                m_tiles.push_back(new Tile(Color::RED, QVector2D(x, y)));
                break;
            case 4:
                m_tiles.push_back(new Tile(Color::YELLOW, QVector2D(x, y)));
                break;
            default:
                break;
            }
        }
    }
}

Grid::~Grid()
{

}

std::vector<Tile *> Grid::tiles()
{
    return m_tiles;
}

