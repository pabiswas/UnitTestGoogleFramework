#ifndef DBUTILS_HPP
#define DBUTILS_HPP

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <string>

using ::testing::_;
using ::testing::Invoke;

class IDbUtility
{
	public:
	virtual void readSubscriber(std::string str)=0; //TODO: Add exception handling
	virtual int writeSubscriber() = 0;
};

/*
 * Actual implementation
 */
class DbUtilityImpl : public IDbUtility
{
	public:
	virtual void readSubscriber(std::string str)
	{
		if(str.length() > 15)
			std::cout <<"Error!!" << std::endl; //TODO: Add exception handling
	}

	virtual int writeSubscriber()
	{
		return 0;
	}
};

/*
 * Mock implementation
 */
class MockDbUtility : public IDbUtility
{
	public:
	MOCK_METHOD1(readSubscriber, void(std::string));
	MOCK_METHOD0(writeSubscriber, int(void));

	void DelegateToOriginal()
	{
		ON_CALL(*this, readSubscriber(_)).
			WillByDefault(Invoke(&dbUtil, &DbUtilityImpl::readSubscriber));
		ON_CALL(*this, writeSubscriber()).
			WillByDefault(Invoke(&dbUtil, &DbUtilityImpl::writeSubscriber));
	}

	private:
	DbUtilityImpl dbUtil;
};
#endif
