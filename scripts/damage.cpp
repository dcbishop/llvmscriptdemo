#include <iostream>
using namespace std;

#include "damage.hpp"

#include "../src/TestClass.hpp"

void initilize() {
	cout << "Initilizing attack script..." << endl;
}

void attack(TestClass* tc) {
	cout << "I stab at thee thustly!" << endl;
	tc->setHealth(tc->getHealth() - 10);
}
