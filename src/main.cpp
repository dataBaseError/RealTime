#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>


int main(int argc, char *argv[])
{
	//Declare a socket instance here.
	struct sockaddr_in server;
	string address = "192.168.0.1";
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
