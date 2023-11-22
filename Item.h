#pragma once

#ifndef ITEM_H
#define ITEM_H

#include <cstddef>

class Item
{
private:
	int _value;
	Item* _nextItem;

public:
	Item() : _value{}, _nextItem(nullptr) {}

	Item(const int& val) : _value{ val }, _nextItem(nullptr) {}

	~Item() {
		this->_value = NULL;
		this->_nextItem = nullptr;
	}

#pragma region getter
	int getValue() const {
		return this->_value;
	}
	const Item* getAddr() const {
		return &(*this);
	}
	Item* getNextItemAddr() {
		return &(*this->_nextItem);
	}
#pragma endregion

#pragma region setter
	void setNextItem(Item* const item) {
		this->_nextItem = item;
	}

	void clearNextAddr() {
		this->_nextItem = nullptr;
	}
#pragma endregion
};
#endif