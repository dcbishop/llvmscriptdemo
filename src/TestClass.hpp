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
