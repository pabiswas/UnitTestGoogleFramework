#include "MyClass.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::AtLeast;

class InterfaceMock : public Interface 
{
	public:
		MOCK_METHOD0(readData, void());
};

TEST(MyCalculator, Addition)
{
	MyCalculator m;
	EXPECT_EQ(2, m.add(1,1)) << "Addition of 2 numbers Failed";
}

TEST(MyCalculator, Substraction)
{
	MyCalculator m;
	EXPECT_EQ(0, m.sub(1,1)) << "Substraction of 2 numbers Failed";
}

TEST(MyCalculator, MockTest)
{
	InterfaceMock interfaceMock;
	MyCalculator cal(&interfaceMock);
		
	EXPECT_CALL(interfaceMock, readData()).Times(AtLeast(1));
	cal.doSomething();
}
