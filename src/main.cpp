// C Libraries
#include <netdb.h>
#include <unistd.h>
#include <sstream>
#include <string.h>
#include <sys/socket.h>

// C++ Libraries

#include <Writer.hpp>
#include <Reader.hpp>

int open(const char* hostname, const uint16_t port) {
    // The socket address
    struct sockaddr_in address;

    // The socket host
    struct hostent* host = gethostbyname(hostname);

    // The socket's file descriptor
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // allocate address with null bytes
    bzero((char *) &address, sizeof(address));

    // set the address format to IPV4
    address.sin_family = AF_INET;

    // set the host in the address
    memmove((char *) &address.sin_addr.s_addr, (char *) host->h_addr, host->h_length);

    // set the port in the address
    address.sin_port = htons(port);

    // connect to the socket
    connect(sockfd, (struct sockaddr *) &address, sizeof(address));

    // return the socket
    return sockfd;
}

int main(int argc, char** argv) {
    // hide warning: unused parameter
    (void) argc;
    (void) argv;

	/*Writer w;
	unsigned int i;
	for(i = 0; i < 10; i++) {
		stringstream sstm;
		sstm << "hello " << i;
		//cout << sstm.str() << endl;
		w.buffer.push(sstm.str());
		pthread_mutex_lock(&w.emptyMutex);
		pthread_cond_signal(&w.empty);
		pthread_mutex_unlock(&w.emptyMutex);

	}


	//usleep(1);
	w.release();*/

	/*Reader r;
	unsigned int i;
	for(i = 0; i < 10; i++) {
		pthread_mutex_lock(&r.newValue);
		pthread_cond_wait(&r.available, &r.newValue);
		pthread_mutex_unlock(&r.newValue);

		cout << "Value " << r.value[0] << endl;
	}

	r.release();*/

	//Declare a socket instance here.
	//struct sockaddr_in server;
    //server.sin_port = htons(1234);

	//const string address = "192.168.0.1";

	//inet_aton(address.c_str(), &server.sin_addr.s_addr);

	//int s = socket(AF_INET, SOCK_STREAM, 0);

    std::string address = "192.168.0.1";
    uint16_t port = 1234;

    int s = open(address.c_str(), port);

	if (s == -1) {
		std::cout << "Invalid socket descriptor." << std::endl;
		return -1;
	} else {
		std::cout << "Socket bound." << std::endl;
	}

	std::cout << "Connecting to socket on address: " << address << " port: " << port << std::endl;

	//Instantiate reader thread here; bind to connected socket.
	//Instantiate writer thread here; bind to connected socket.

	//Signal the writer thread to subscribe to the events.
	//Put the following into the buffer, and notify the writer thread:
	//out = "request(100,view)\n";
	//writerThread.notify();

	//Begin main control loop:
	//{
	//	//Check if we've received something from the socket.
		//The local buffer will contain it since the reader thread outputs directly into the buffer.
		//cout << "RECEIVED COMMAND: " << endl;
		//cout << buffer << endl;
	//}

	return 0;
}
