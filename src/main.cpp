#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <Writer.hpp>
#include <Reader.hpp>
#include <unistd.h>
#include <sstream>

int main(int argc, char *argv[])
{
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
	struct sockaddr_in server;
	string address = "192.168.0.1";
	server.sin_port = htons(1234);
	inet_aton(address, &server.sin_addr.s_addr);

	int s = socket(AF_INET, SOCK_STREAM, 0);

	if (s == -1) {
		cout << "Invalid socket descriptor.";
		return -1;
	} else {
		cout << "Socket bound.";
	}

	cout << "Connecting to socket on address: " << address << " port: "
			<< server.sin_port << endl;

	if (connect(s, (struct sockaddr *) &server, sizeof(server)) == -1) {
		cout << "Socket connection failed.";
		return -1;
	}

	//Instantiate reader thread here; bind to connected socket.
	Reader r;
	//Instantiate writer thread here; bind to connected socket.
	Writer w;

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
