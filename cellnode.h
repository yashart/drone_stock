#ifndef CELLNODE_H
#define CELLNODE_H


class CellNode
{
private:
    float potential;
    int isEntered;

public:
    CellNode* left;
    CellNode* right;
    CellNode* top;
    CellNode* bottom;

    CellNode();
    void set_cell_node(CellNode* left, CellNode* right,
             CellNode* top, CellNode* bottom);
    ~CellNode();
    void set_potential(float potential);
    float get_potential();
    int checkEntered();
    void setEntered();
};

#endif // CELLNODE_H
