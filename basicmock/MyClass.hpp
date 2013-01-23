#ifndef MYCLASS_HPP
#define MYCLASS_HPP

class Interface
{
	public:
		virtual void readData()=0;
		virtual void printData(int) = 0;
		virtual int check(int)=0;
};

class MyCalculator
{
	public:
	MyCalculator()
	{
	}

	MyCalculator(Interface* t)
	{
		_t = t;
	}
	
	int initialize(int i)
	{
		_t->printData(i);
		return	_t->check(i);
	}

	int add(int i, int j)
	{
		return i+j;
	}

	int sub(int i, int j)
	{
		_t->printData(i-j);
		return i - j;
	}

	void doSomething()
	{
		_t->readData();
	}

	private:
	Interface* _t;

};

#endif
