#pragma once

#include <vector>

#include "tile.h"

class Grid
{

public:
    Grid();
    ~Grid();

    std::vector<Tile *> tiles();
    Tile & getTileAt(int x, int y);

    void fillGrid();

protected:
    std::vector<Tile *> m_tiles;
    int c_height = 8;
    int c_width = 8;
};
