/*
 * TestClass.hpp - Example LLVM 'script'. Example native class to be accessed.
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

#ifndef TESTCLASS_HPP_
#define TESTCLASS_HPP_

class TestClass {
	public:
	   TestClass();
		void setHealth(const int health);
      int getHealth() const;
      void printHealth() const;
   
	private:
		int health;
};

#endif /* TESTCLASS_HPP_ */
