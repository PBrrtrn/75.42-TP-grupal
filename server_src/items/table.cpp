#include "table.h"

Table::Table(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns) {
    this->canBePicked = false;
    this->isDecoration = true;
    this->has_volume = true;
    this->type = TYPE_TABLE;
}

bool Table::pickUpAction(Player& p) {
    return false;
}

Table::~Table(){}
