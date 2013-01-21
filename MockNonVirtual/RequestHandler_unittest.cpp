#include "DbUtils.hpp"
#include "RequestHandler.hpp"

using ::testing::Return;
using ::testing::HasSubstr;

TEST(RequestHandler, MockImplementation)
{
	MockDbUtility mock;
	RequestHandler<MockDbUtility> requestHandler;
		
	//EXPECT_CALL(mock, readSubscriber("262024210001000")).Times(1);
	EXPECT_CALL(mock, readSubscriber(HasSubstr("26202"))).Times(1);

	requestHandler.processIncomingRequest(&mock, "262024210001000");
}

TEST(RequestHandler, OriginalImplementation)
{
	DbUtility dbUtil;
	RequestHandler<> requestHandler;
		
	requestHandler.processIncomingRequest(&dbUtil, "262024210001000");
}

