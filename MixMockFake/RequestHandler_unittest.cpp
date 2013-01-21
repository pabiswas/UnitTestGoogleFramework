#include "DbUtils.hpp"
#include "RequestHandler.hpp"

using ::testing::Return;

TEST(RequestHandler, OriginalImplementation)
{
	MockDbUtility mock;
	RequestHandler requestHandler(&mock);
	mock.DelegateToOriginal();
		
	EXPECT_CALL(mock, readSubscriber("262024210001000")).Times(1);

	requestHandler.processIncomingRequest("262024210001000");
}

TEST(RequestHandler, MockImplementation)
{
	MockDbUtility mock;
	RequestHandler requestHandler(&mock);
		
	EXPECT_CALL(mock, readSubscriber("262024210001000")).Times(1);

	requestHandler.processIncomingRequest("262024210001000");
}

TEST(RequestHandler, overrideMockCallingOriginal)
{
	MockDbUtility mock;
	RequestHandler requestHandler(&mock);
	mock.DelegateToOriginal();

	EXPECT_CALL(mock, writeSubscriber()).Times(1).WillOnce(Return(1));

	EXPECT_EQ(1, requestHandler.updateData());
}

TEST(RequestHandler, MockCallingOriginal)
{
	MockDbUtility mock;
	RequestHandler requestHandler(&mock);
	mock.DelegateToOriginal();

	EXPECT_CALL(mock, writeSubscriber()).Times(1);

	EXPECT_EQ(0, requestHandler.updateData());
}
