#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <string>

#include "Sut.hpp"

using ::testing::Matcher;
using ::testing::_;
using ::testing::AllOf;
using ::testing::Args;
using ::testing::Lt;
using ::testing::Ge;
using ::testing::Eq;
using ::testing::Property;
using ::testing::Field;

class MockIntf : public Intf
{
	public:
	MOCK_METHOD3(dummyFunc, void(int, int, int));
};

TEST(StringMatcherTest, ImplicitlyConstruction) 
{
	Matcher<std::string> m1 = "hi";
	EXPECT_TRUE(m1.Matches("hi"));
	EXPECT_FALSE(m1.Matches("hello"));

	Matcher<const std::string&> m2 = "hi";
	EXPECT_TRUE(m2.Matches("hi"));
	EXPECT_FALSE(m2.Matches("hello"));
}

TEST(MatcherAllOfTest, ArgsTesting)
{
	MockIntf mock;
	Sut testObj(&mock);

	testObj.setA(4);
	testObj.setB(5);
	testObj.setC(6);

	EXPECT_CALL(mock, dummyFunc(_,_,_)).
		With(AllOf(Args<0,1>(Lt()), Args<1,2>(Lt())));	
	testObj.doATask();
}

TEST (MatcherTest, FieldTesting)
{
	Matcher<Sut&> m1 = Property(&Sut::getA, Ge(0));
	Matcher<Sut&> m2 = Property(&Sut::getA, Eq(5));

	MockIntf mock;
	Sut testObj(&mock);

	EXPECT_TRUE(m1.Matches(testObj));

	EXPECT_FALSE(m2.Matches(testObj));

	testObj.setA(10);
	Matcher<Sut&> m3 = Property(&Sut::getA, Eq(10));
	EXPECT_TRUE(m1.Matches(testObj));
}

TEST(MatcherTest, PropertyTesting)
{
	Matcher<Sut&> m = Field(&Sut::d, Eq(0));
	MockIntf mock;
	Sut testObj(&mock);

	EXPECT_FALSE(m.Matches(testObj));
	testObj.d=0;
	EXPECT_TRUE(m.Matches(testObj));
}
