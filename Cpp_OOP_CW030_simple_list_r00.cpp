#include "SimpleList.h"

void printItem(Item* const);

int main() 
{
	SimpleList list1;
	SimpleList list2;

	//1) function fill list by values
	for (size_t i = 0; i < 5; i++)
		list1.pushBack(i + 1);

	std::cout << "\n2) operator << out in console\n" << list1 << std::endl;

	//3) function write to File
	list1.writeFile("dataTest1.txt");

	list2.readFile("dataTest2.txt");
	std::cout << "\n4) function read from File\n" << list2 << std::endl;

	list2.DeleteLast();
	std::cout << "\n5) function delete item by Last\n" << list2 << std::endl;

	list2.DeleteByIndex(2);
	std::cout << "\n6) function delete item by Index\n" << list2 << std::endl;

	std::cout << "\n7) function seacrhed Item* by operator[index]\n" << std::endl;
	printItem(list2[2]);

	std::cout << "\n8) function seacrhed Item* by value (one of properties)\n" << std::endl;
	printItem(list2.findItemByValue(15));

	list1 += list2;
	std::cout << "\n9) operator += (list1 += list2)\n" << list1 << std::endl;

	SimpleList list4;
	list4.pushBack(25);
	SimpleList list3 = list1 + list4;
	std::cout << "\n10) operator + (list3 = list1 + list4)\n" << list3 << std::endl;

	list1 = list3;
	std::cout << "\n11) operator = (list1 = list4)\n" << list1 << std::endl;
	
	return 0;
}

void printItem(Item* const item) 
{
	if (item == nullptr)
		std::cout << "\nERROR!";
	else
		std::cout << "\nval: " << item->getValue() << " | curAddr: " << item->getAddr() << " | nextAddr: " << item->getNextItemAddr() << "\n";

}
