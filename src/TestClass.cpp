/*
 * TestClass.cpp - Example LLVM 'script'. Example native class to be accessed.
 *
 * Written in 2011 by David C. Bishop <david@davidbishop.org>
 *
 * To the extent possible under law, the author(s) have dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along
 * with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

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
