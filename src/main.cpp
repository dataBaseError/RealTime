/**
 * Copyright (C) 2014 Jonathan Gillett, Joseph Heron, Khalil Fazal, Daniel Smullen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <Writer.hpp>
#include <Reader.hpp>
#include <unistd.h>

//Declare the maximum buffer size for interacting with the socket.
#define MAX_BUFFER_SIZE 256

int main(int argc, char *argv[])
{
	//Declare a socket instance here.
	struct sockaddr_in server;
	string address = "192.168.0.1";
	server.sin_port = htons(1234);
	inet_aton(address, &server.sin_addr.s_addr);

	//Open the socket. If it fails to bind, terminate.
	int s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == -1) {
		cout << "Invalid socket descriptor.";
		return -1;
	} else {
		cout << "Socket bound.";
	}

	//Connect to the socket. If it fails to connect, terminate.
	cout << "Connecting to socket on address: " << address << " port: "
			<< server.sin_port << endl;
	if (connect(s, (struct sockaddr *) &server, sizeof(server)) == -1) {
		cout << "Socket connection failed.";
		return -1;
	}

	//Instantiate reader thread here; bind to connected socket.
	Reader r(s, MAX_BUFFER_SIZE);
	//Instantiate writer thread here; bind to connected socket.
	Writer w(s, MAX_BUFFER_SIZE);

	//Signal the writer thread to subscribe to the events.
	//Put the following into the buffer, and notify the writer thread:
	w.sendCommand("request(100,view)\n");

	Begin main control loop:
	for(;;){
		//Check if we've received something from the socket.
		//Output it to the console.
		cout << r->readCommand() << endl;
	}

	//Join and release the reader thread.
	r.release();
	//Join and release the writer thread.
	w.release();


	return 0;
}
