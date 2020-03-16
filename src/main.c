/*
 *****************************************************************************

 File        : main.cpp

 The MIT License (MIT)
 Copyright (c) 2019 STMicroelectronics

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

 *****************************************************************************
 */

#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include"debug.h"
#include<errno.h>
#include"client.h"

int main(int argc, char *argv[]) {
	int socket_desc;
	char *message;
	while (1) {
		socket_desc = establish_client_connection();
		message = "Sweet !\n";
		int message_sending_tries = 3;
		while (socket_desc != -1) {
			int message_sending_status = send_client_message(socket_desc,
					message);
			if (message_sending_status == -1) {
				message_sending_tries -= 1;
				sleep(2);
				if (message_sending_tries <= 0){
					close(socket_desc);
					printf("Reset socket.\n");
					socket_desc = -1;
				}
				continue;
			}
			sleep(2);
		}
	}
	return 0;
}
