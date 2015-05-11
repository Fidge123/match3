#pragma once

#include <vector>
#include <QVector2D>

#include "tile.h"

class Grid
{

public:
    Grid();
    ~Grid();

    void setSelectedTile(Tile * tile);

    bool swap(Tile * t1, Tile * t2);

    std::vector<Tile *> tiles() const;

    void fillGrid();
    void applyGravity();
    bool removePairs();

protected:
    std::vector<Tile *> m_tiles;
    Tile * m_selectedTile;
    int c_height = 8;
    int c_width = 8;
};
