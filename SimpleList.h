#pragma once

#ifndef SIMPLELIST_H
#define SIMPLELIST_H

#include "Item.h"
#include <iostream>
#include <string>
#include <fstream>

class SimpleList
{
private:
	Item* head;
	int size;

	Item* getLastAddr() const {

		Item* temp(nullptr);
		Item* iter = this->head;

		while (iter->getAddr()) {
			temp = iter;
			iter = iter->getNextItemAddr();
		}
		iter = nullptr;
		return temp;
	}

	bool isEmpty() const {
		return head == nullptr;
	}

public:
	SimpleList() : head(nullptr), size{} {}

	~SimpleList() 
	{
		if (isEmpty())
			return;

		Item* next = this->head->getNextItemAddr();
		
		while (next != nullptr)
		{
			delete this->head;
			this->head = next;
			next = this->head->getNextItemAddr();
		}

		delete this->head;
		this->head = nullptr;
	}

#pragma region getter
	Item* getHead() {
		return &(*this->head);
	}

	int getSize() const {
		return this->size;
	}

	Item* getItem(const int& index) const
	{
		if (isEmpty())
			return nullptr;

		Item* iter = this->head;
		for (size_t i = 0; i < index; i++)
		{
			iter = iter->getNextItemAddr();
		}

		return iter;
	}

	int getLength() const
	{
		int count{};

		Item* iter = this->head;
		while (iter->getAddr()) {
			count++;
			iter = iter->getNextItemAddr();
		}
		iter = nullptr;
		return count;
	}
#pragma endregion

	void pushBack(const int& value)
	{
		if (isEmpty()) {
			this->head = new Item(value);
			this->size++;
		}
		else {
			Item* iter = getLastAddr();
			iter->setNextItem(new Item(value));
			this->size++;
		}
	}

	Item* findItemByValue(const int& value) const 
	{
		if (isEmpty())
			return nullptr;

		Item* iter = this->head;
		while (iter) 
		{
			if (iter->getValue() == value)
				return iter;
			iter = iter->getNextItemAddr();
		}

		return nullptr;
	}

	void DeleteFirst()
	{
		if (isEmpty())
			return;
		Item* iter = this->head;
		this->head = this->head->getNextItemAddr();
		
		delete iter;
		iter = nullptr;

		this->size--;
	}

	void DeleteLast() 
	{
		if (isEmpty())
			return;

		if (head == getLastAddr()) {
			DeleteFirst();
			return;
		}

		Item* iter = this->head;
		Item* last = getLastAddr();

		while (iter->getNextItemAddr() != last)
		{
			iter = iter->getNextItemAddr();
		}

		delete last;
		last = nullptr;

		iter->clearNextAddr();
		iter = nullptr;

		this->size--;
	}

	void DeleteByIndex(const int& index)
	{
		if (abs(index) > this->size || isEmpty())
			return;

		Item* iter = this->head;
		Item* temp = operator[](index);

		if (!index)
			this->head = this->head->getNextItemAddr();
		else
		{
			for (size_t i = 0; i < index - 1; i++)
				iter = iter->getNextItemAddr();

			iter->setNextItem(temp->getNextItemAddr());
		}

		delete temp;
		temp = nullptr;
		iter = nullptr;
		this->size--;
	}

	int writeFile(const std::string& path = "data.txt")
	{
		std::ofstream fout;
		fout.open(path);

		if (!fout.is_open())
			return -1;
		else
		{
			size_t size = this->size;
			for (size_t i = 0; i < size; i++)
			{
				fout << this->operator[](i)->getValue() << (i == size - 1 ? "" : "\n");
			}
		}

		fout.close();
	}

	int readFile(std::string path = "data.txt") 
	{
		std::ifstream fin;
		fin.open(path);

		if (!fin.is_open())
			return -1;
		else 
		{
			std::string value{};
			while (true)
			{
				fin >> value;
				if (fin.eof())
					break;
				this->pushBack(std::stoi(value));
			}
		}

		fin.close();
	};

#pragma region operators
	Item* operator[] (const int& index) const
	{
		if (isEmpty())
			return nullptr;

		Item* iter = this->head;
		for (size_t i = 0; i < index; i++)
		{
			iter = iter->getNextItemAddr();
		}
		return iter;
	}

	SimpleList& operator= (SimpleList& list) 
	{
		if (this == &list)
			return *this;

		this->~SimpleList();
		this->head = list.head;
		this->size = list.size;
		list.head = nullptr;

		return *this;
	}

	const SimpleList operator+ (SimpleList& const list) 
	{
		SimpleList temp{};
		this->getLastAddr()->setNextItem(list.head);
		temp.head = this->head;
		temp.size = this->size + list.size;

		list.head = nullptr;
		this->head = nullptr;

		return temp;
	}

	void operator+= (SimpleList& const list) 
	{
		this->getLastAddr()->setNextItem(list.head);
		this->size += list.size;
		list.head = nullptr;
	}

	friend std::ostream& operator<< (std::ostream& out, const SimpleList& list)
	{
		size_t size = list.size;
		for (size_t i = 0; i < size; i++)
		{
			out << list[i]->getValue() << (i == size - 1 ? "" : "\n");
		}
		return out;
	}
#pragma endregion
};
#endif