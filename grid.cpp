#include "grid.h"
#include <iostream>
#include <queue>

Grid::Grid()
{
    this->mask_grid = new int*[this->GRID_HEIGHT];
    this->grid = new CellNode*[this->GRID_HEIGHT];
    for (int i = 0; i < this->GRID_HEIGHT; i++) {
        this->mask_grid[i] = new int[this->GRID_WIDTH];
        this->grid[i] = new CellNode[this->GRID_WIDTH];
    }
    for (int i = 0; i < this->GRID_WIDTH; i++) {
        for (int j = 0; j < this->GRID_HEIGHT; j++) {
            this->mask_grid[i][j] = 0;
        }
    }
    for (int i = 0; i < this->GRID_WIDTH; i++) {
        for (int j = 0; j < this->GRID_HEIGHT; j++) {
            CellNode* left      = nullptr;
            CellNode* right     = nullptr;
            CellNode* top       = nullptr;
            CellNode* bottom    = nullptr;
            if (i != 0) {
                left = &this->grid[i - 1][j];
            }
            if (i != this->GRID_WIDTH - 1) {
                right = &this->grid[i + 1][j];
            }
            if (j != 0) {
                top = &this->grid[i][j - 1];
            }
            if (j != this->GRID_HEIGHT - 1) {
                bottom = &this->grid[i][j + 1];
            }
            this->grid[i][j].set_cell_node(left, right, top, bottom);
        }
    }
}

Grid::~Grid() {
    /*
    for (int i = 0; i < this->GRID_HEIGHT; i++) {
        delete [] this->grid[i];
        delete [] this->mask_grid[i];
    }
    delete [] this->grid;
    delete [] this->mask_grid;
    */
}

void Grid::distribute_potential(int x, int y, float potential) {
    std::queue<CellNode*> nodes;
    std::queue<float> potentials;
    this->grid[x][y].set_potential(potential);
    nodes.push(&this->grid[x][y]);
    nodes.front()->setEntered();
    potentials.push(potential);

    while(!nodes.empty()) {
        CellNode* node = nodes.front();
        nodes.pop();
        potential = potentials.front();
        potentials.pop();

        if (node->left != nullptr && node->left->checkEntered() == 0) {
            nodes.push(node->left);
            potentials.push(potential - 1);
            node->left->setEntered();
            node->left->set_potential(potential);
        }
        if (node->right != nullptr && node->right->checkEntered() == 0) {
            nodes.push(node->right);
            potentials.push(potential - 1);
            node->right->setEntered();
            node->right->set_potential(potential);

        }
        if (node->top != nullptr && node->top->checkEntered() == 0) {
            nodes.push(node->top);
            potentials.push(potential - 1);
            node->top->setEntered();
            node->top->set_potential(potential);
        }
        if (node->bottom != nullptr && node->bottom->checkEntered() == 0) {
            nodes.push(node->bottom);
            potentials.push(potential - 1);
            node->bottom->setEntered();
            node->bottom->set_potential(potential);
        }
    }
}

void Grid::dump() {
    for (int i = 0; i < this->GRID_WIDTH; i++) {
        for (int j = 0; j < this->GRID_HEIGHT; j++) {
            std::cout << this->grid[i][j].get_potential() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

int Grid::get_grid_width() {
    return this->GRID_WIDTH;
}

int Grid::get_grid_height() {
    return this->GRID_HEIGHT;
}
