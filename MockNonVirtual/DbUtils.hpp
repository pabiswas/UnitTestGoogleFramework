#ifndef DBUTILS_HPP
#define DBUTILS_HPP

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <string>

using ::testing::_;
using ::testing::Invoke;

/*
 * Actual implementation
 */
class DbUtility 
{
	public:
	void readSubscriber(std::string str)
	{
	    std::cout <<"Actual code is been called!!" << std::endl; 
		if(str.length() > 15)
			std::cout <<"Error!!" << std::endl; //TODO: Add exception handling
	}

	int writeSubscriber()
	{
		return 0;
	}
};

/*
 * Mock implementation
 */
class MockDbUtility 
{
	public:
	MOCK_METHOD1(readSubscriber, void(std::string));
	MOCK_METHOD0(writeSubscriber, int(void));

};
#endif
