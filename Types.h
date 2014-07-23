#ifndef _HBM__STREAMING__TYPES
#define _HBM__STREAMING__TYPES

#ifdef _WIN32
#include "jsoncpp/include/json/reader.h"
#else
#include <jsoncpp/json/reader.h>
#endif

namespace hbm {
	namespace streaming {
		static const std::string STREAM_DATA_PORT = "7411";
		static const char* PARAMS = "params";



		struct ntpTimeStamp_t {
			unsigned int seconds;
			unsigned int fraction;
		};

		struct timeInfo_t {
			void set(const Json::Value& params)
			{
				const Json::Value& stampNode = params["stamp"];
				if(stampNode["type"]=="ntp") {
					stamp.fraction = stampNode["fraction"].asUInt();
					stamp.seconds = stampNode["seconds"].asUInt();
				}
				epoch = params["epoch"].asString();
				scale = params["scale"].asString();
			}

			ntpTimeStamp_t stamp;
			std::string scale;
			std::string epoch;
		};
	}
}

#endif