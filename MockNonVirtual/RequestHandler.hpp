#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

#include "DbUtils.hpp"

template <typename DbUtil = DbUtility>
class RequestHandler
{
	public:

	void processIncomingRequest(DbUtil* dbUtil, std::string subscriber)
	{
		dbUtil->readSubscriber(subscriber);
	}

	int updateData(DbUtil* dbUtil)
	{
		return 	dbUtil->writeSubscriber();
	}
};

#endif
