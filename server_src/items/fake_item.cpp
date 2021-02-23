#include "fake_item.h"

FakeItem::FakeItem(Vector pos_inicial, bool respawns) : Item(pos_inicial,respawns) {
    this->type = TYPE_FAKE_ITEM;
    this->pos = pos_inicial;
	this->canBePicked = false;
	this->respawns = false;
	this->isDecoration = false;
	this->has_volume = false;
}

bool FakeItem::pickUpAction(Player& p) {
    return false;
}

FakeItem::~FakeItem(){}
