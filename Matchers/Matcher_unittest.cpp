#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <string>
#include <ostream>

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
using ::testing::Pointee;
using ::testing::MatcherInterface;
using ::testing::MatchResultListener;
using ::testing::MakeMatcher;
using ::testing::internal::StringMatchResultListener;

class MockIntf : public Intf
{
	public:
	MOCK_METHOD3(dummyFunc, void(int, int, int));
	MOCK_METHOD1(dummyPointer, void(int*));
};

class SumIsGreaterThan : public MatcherInterface<const Sut&>
{
	public:
		explicit SumIsGreaterThan(int min):_min(min) {}

		virtual void DescribeTo(std::ostream* os) const 
		{
		}

		virtual bool MatchAndExplain(const Sut& testObj, MatchResultListener* listener) const
		{
			return (testObj.getA() + testObj.getB() ) > _min;
		}

	private:
		int _min;

};

Matcher<const Sut&> checkSumGreaterThan(int minimum)
{
	return MakeMatcher(new SumIsGreaterThan(minimum));
}

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

TEST(MatcherTest, PointeeTest)
{
	MockIntf mock;
	Sut testObj(&mock);

	testObj.d=3;
	EXPECT_CALL(mock, dummyPointer(Pointee(3)));

	testObj.checkD();
}

TEST(MatcherTest, MatchAndExplain)
{
	Matcher<const Sut&> m = checkSumGreaterThan(10);
	StringMatchResultListener listener;
	MockIntf mock;
	Sut testObj(&mock);
	
	testObj.setA(5);
	testObj.setB(6);
	EXPECT_TRUE(m.MatchAndExplain(testObj, &listener));

	testObj.setB(1);
	EXPECT_FALSE(m.MatchAndExplain(testObj, &listener));
}
