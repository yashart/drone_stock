#include "cellnode.h"

CellNode::CellNode() {
    this->left = nullptr;
    this->right = nullptr;
    this->top = nullptr;
    this->bottom = nullptr;
    this->potential = 0;
    this->isEntered = 0;
}

void CellNode::set_cell_node(CellNode* left, CellNode* right,
         CellNode* top, CellNode* bottom) {
    this->left = left;
    this->right = right;
    this->top = top;
    this->bottom = bottom;
    this->potential = 0;
    this->isEntered = 0;
}

CellNode::~CellNode() {
    this->left = nullptr;
    this->right = nullptr;
    this->top = nullptr;
    this->bottom = nullptr;
    this->potential = 0;
}

void CellNode::set_potential(float potential) {
    this->potential = potential;
}

float CellNode::get_potential() {
    return this->potential;
}

int CellNode::checkEntered() {
    return this->isEntered;
}

void CellNode::setEntered() {
    this->isEntered = 1;
}
