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

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <Writer.hpp>
#include <Reader.hpp>
#include <unistd.h>

//Declare the maximum buffer size for interacting with the socket.
#define MAX_BUFFER_SIZE 256

int open(const char* hostname, const uint16_t port) {
    //The socket address.
    struct sockaddr_in address;

    //The socket host.
    struct hostent* host = gethostbyname(hostname);

    //The socket's file descriptor.
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1){
    	cout << "Failed to bind socket." << endl;
    }

    //Allocate address with null bytes.
    bzero((char *) &address, sizeof(address));

    //Set the address format to IPV4.
    address.sin_family = AF_INET;

    //Set the host address.
    memmove((char *) &address.sin_addr.s_addr, (char *) host->h_addr, host->h_length);

    //Set the port in the address.
    address.sin_port = htons(port);

    //Connect to the socket.
    if (connect(sockfd, (struct sockaddr *) &address, sizeof(address)) == -1){
    	cout << "Socket connection failed." << endl;
    }

    //Return the socket descriptor.
    return sockfd;
}

int main(int argc, char** argv) {
    (void) argc;
    (void) argv;

    int s = open("192.168.0.1", 1234);
    assert(s != -1);

	//Instantiate reader thread here; bind to connected socket.
	Reader r(s, MAX_BUFFER_SIZE);
	//Instantiate writer thread here; bind to connected socket.
	Writer w(s, MAX_BUFFER_SIZE);

	//Signal the writer thread to subscribe to the events.
	w.sendCommand("request(100,view)\n");

	//Begin main control loop:
	while (true) {
		//Check if we've received something from the socket.
		//Output it to the console.
		cout << r.readCommand() << endl;
	}

	//Join and release the reader thread.
	r.release();
	//Join and release the writer thread.
	w.release();

	return 0;
}
