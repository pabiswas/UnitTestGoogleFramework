#ifndef SUT_HPP
#define SUT_HPP

#include <vector>

class Intf
{
	public:
	virtual void dummyFunc(int, int, int) = 0;
	virtual void dummyPointer(int*) = 0;
	virtual void dataContainer(const std::vector<int>& data) = 0;
};

class Sut
{
	public:
	Sut()
	{
	}

	Sut(Intf* intf): _a(0), _b(0), _c(0)
	{
		_intf = intf;
	}

	void setA(int i)
	{
		_a = i;
	}

	int getA() const
	{
		return _a;
	}
	
	void setB(int i)
	{
		_b = i;
	}

	int getB() const
	{
		return _b;
	}

	void setC(int i)
	{
		_c = i;
	}

	void doATask()
	{
		_intf->dummyFunc(_a,_b,_c);
	}

	void checkD()
	{
		_intf->dummyPointer(&d);
	}

	void compute()
	{
		_intf->dataContainer(mContainer);
	}

	void insertData(int i)
	{
		mContainer.push_back(i);
	}

	int d;

	private:
	int _a, _b, _c;
	Intf* _intf;
	std::vector<int> mContainer;
};

#endif
