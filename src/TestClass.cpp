#include "TestClass.hpp"

#include <iostream>
using namespace std;

TestClass::TestClass() {
   setHealth(100);
}

void TestClass::setHealth(const int health) {
   this->health = health;
}

extern int TestClass::getHealth() const {
   return this->health;
}

void TestClass::printHealth() const {
   cout << "I am on " << getHealth() << " hitpoints." << endl;
}
