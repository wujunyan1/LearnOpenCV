#pragma once
#include "../Core/Core.h"
#include <string>


namespace Core {
	
	class StringUtil
	{

	public:
		static String Format(String fomat, ...)
		{

			std::vector<char> finished_message_backing(MaxMessageSize);
			char* finished_message = finished_message_backing.data();
			auto finished_message_len = MaxMessageSize;

			const char* formatMessage = fomat.c_str();

			va_list arglist;
			va_start(arglist, fomat);
			const int nbrcharacters = vsnprintf(finished_message, finished_message_len, formatMessage, arglist);
			va_end(arglist);

			return finished_message;
		}


		static const int MaxMessageSize = 2048;
	};

}

