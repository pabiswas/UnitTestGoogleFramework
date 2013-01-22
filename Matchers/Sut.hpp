#ifndef SUT_HPP
#define SUT_HPP


class Intf
{
	public:
	virtual void dummyFunc(int, int, int) = 0;
};

class Sut
{
	public:
	Sut(Intf* intf): _a(0), _b(0), _c(0)
	{
		_intf = intf;
	}

	void setA(int i)
	{
		_a = i;
	}
	
	void setB(int i)
	{
		_b = i;
	}
	
	void setC(int i)
	{
		_c = i;
	}

	void doATask()
	{
		_intf->dummyFunc(_a,_b,_c);
	}

	private:
	int _a, _b, _c;
	Intf* _intf;
};

#endif