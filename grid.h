#pragma once

#include <vector>
#include <QVector2D>

#include "tile.h"

class Grid
{

public:
    Grid();
    ~Grid();

    std::vector<Tile *> tiles() const;

    void fillGrid();
    void applyGravity();
    bool removePairs();

protected:
    std::vector<Tile *> m_tiles;
    int c_height = 8;
    int c_width = 8;
};
