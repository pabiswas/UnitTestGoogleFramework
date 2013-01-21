#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

#include "DbUtils.hpp"

class RequestHandler
{
	public:
	RequestHandler()
	{
	}

	RequestHandler(IDbUtility* dbUtil)
	{
		_dbUtil = dbUtil;
	}

	void processIncomingRequest(std::string subscriber)
	{
		_dbUtil->readSubscriber(subscriber);
	}

	int updateData()
	{
		return 	_dbUtil->writeSubscriber();
	}

	private:
	IDbUtility* _dbUtil;
};

#endif
