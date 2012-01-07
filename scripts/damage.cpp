/*
 * damage.cpp - Example LLVM 'script'. Calls setHealth function in TestClass.
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


#include <iostream>
using namespace std;

#include "../src/TestClass.hpp"

void initilize() {
	cout << "Initilizing attack script..." << endl;
}

void attack(TestClass* tc) {
	cout << "I stab at thee thustly!" << endl;
	tc->setHealth(tc->getHealth() - 10);
}
