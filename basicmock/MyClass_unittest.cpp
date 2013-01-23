#include "MyClass.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::NiceMock;
using ::testing::StrictMock;

class InterfaceMock : public Interface 
{
	public:
		MOCK_METHOD0(readData, void());
		MOCK_METHOD1(printData, void(int));
		MOCK_METHOD1(check, int(int));
};

TEST(MyCalculator, Initialization)
{
	InterfaceMock mock;
	MyCalculator calc(&mock);
	
	EXPECT_CALL(mock, printData(1)).Times(1);
	EXPECT_CALL(mock, check(1)).Times(1).WillRepeatedly(Return(1));

	EXPECT_EQ(1,calc.initialize(1));
}

TEST(MyCalculator, SuppressWarningForUninterestedCalls)
{
	NiceMock<InterfaceMock> mock;
	MyCalculator calc(&mock);
	
	EXPECT_CALL(mock, check(1)).Times(1).WillOnce(Return(1));

	EXPECT_EQ(1,calc.initialize(1));
}

TEST(MyCalculator, Addition)
{
	MyCalculator m;
	EXPECT_EQ(2, m.add(1,1)) << "Addition of 2 numbers Failed";
}

TEST(MyCalculator, Substraction)
{
	InterfaceMock interfaceMock;
	MyCalculator cal(&interfaceMock);

	EXPECT_CALL(interfaceMock, printData(0)).Times(1);
	
	EXPECT_EQ(0, cal.sub(1,1)) << "Substraction of 2 numbers Failed";
}

TEST(MyCalculator, MockTest)
{
	InterfaceMock interfaceMock;
	MyCalculator cal(&interfaceMock);
		
	EXPECT_CALL(interfaceMock, readData()).Times(AtLeast(1));
	cal.doSomething();
}
