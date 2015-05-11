#pragma once

#include <vector>
#include <QVector2D>

#include "tile.h"

class Game;

class Grid
{

public:
    Grid(Game * game);
    ~Grid();

    void setSelectedTile(Tile * tile);

    bool swap(Tile * t1, Tile * t2);

protected:
    void initializeTiles();
    void fillGrid();
    void applyGravity();
    bool removePairs(bool enableScoring);

protected:
    std::vector<std::vector<Tile *>> m_tiles;
    Tile * m_selectedTile;
    Game * m_game;
    unsigned int c_height = 8;
    unsigned int c_width = 8;
};
