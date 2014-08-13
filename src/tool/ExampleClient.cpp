#include <iostream>
#include <string>
#include <signal.h>

#ifdef _WIN32
#include "json/value.h"
#else
#include <jsoncpp/json/value.h>
#endif
#include "StreamClient.h"
#include "Types.h"

/// this object represents
static hbm::streaming::StreamClient stream;

static void sigHandler(int)
{
	stream.stop();
}

int main(int argc, char* argv[])
{
	// some signals should lead to a normal shutdown
	signal( SIGTERM, &sigHandler);
	signal( SIGINT, &sigHandler);

	if((argc<2) || (std::string(argv[1])=="-h") ) {
		std::cout << "syntax: " << argv[0] << " <stream server address>" << std::endl;
		return EXIT_SUCCESS;
	}

	// the control port might differ when communication runs via a router (CX27)
	std::string controlPort = "http";
	if(argc>2) {
		controlPort = argv[2];
	}

	// give control to the receiving function.
	// returns on signal (terminate, interrupt) buffer overrun on the server side or loss of connection.
	stream.start(argv[1], hbm::streaming::DAQSTREAM_PORT, controlPort);
}
