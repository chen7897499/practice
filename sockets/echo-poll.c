/*
 * select-server.c : 
 * simple echo server - allows client to connect and echos strings
 * received over socket connection to local terminal (stdout)
 * 
 * modification: now allows connections to occur simultaneously
 * (before if we ran connections in a loop, the second connection would
 *  not be displayed until the first terminated with end line)
 * 
 * For more info see: http://www.gnu.org/s/libc/manual/html_node/Server-Example.html#Server-Example
 */

//https://lms.ksu.edu.sa/bbcswebdav/users/mdahshan/Courses/CEN463/Examples/tcpechopoll1_srv.pdf
//http://cse.gecgudlavalleru.ac.in/pdf/manuals/nplab.pdf
//http://beej.us/guide/bgnet/output/html/multipage/pollman.html


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <signal.h>
#include <poll.h>

#define ERROR(x) do { perror(x); exit(1); } while(0)

#define NAME       257
#define BUFSIZE    257
#define MAXPENDING 1

void handle_connection(int NS);

int main(int argc, char *argv[])
{
	struct pollfd readfds[1024], activefds[1024];	/* the set of read descriptors */
	unsigned short port;		/* Port to which server will bind */
	char servhost[NAME];		/* Local host name */
	struct sockaddr_in sock;	/* INTERNET socket space */
	struct hostent *server;		/* Local host information */
	int S;						/* fd for socket */
	int NS;						/* fd for connected socket */
	int pid;					/* used to determine parent or child */
	int i;						/* counter to go through FDs in fdset */

	if (argc != 2)
	{
		fprintf(stderr,"usage: select-server <port>\n");
		exit(1);
	}

	port = atoi(argv[1]);

	/*
	 * Get socket - INTERNET DOMAIN - TCP
	 */
	if ((S = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ERROR("select-server: socket");

	/*
	 * Obtain host name & network address
	 */
	gethostname(servhost, sizeof(servhost));
	if ((server = gethostbyname(servhost)) == NULL)
	{
		fprintf(stderr,"%s: unknown host\n",servhost);
		exit(1);
	}

	/*
	 * Bind to server address - in network byte order
	 */
	sock.sin_family = AF_INET;
	sock.sin_port = htons(port);
	memcpy(&sock.sin_addr, server->h_addr, server->h_length);

	/*
	 * Bind socket to port/addr
	 */
	if (bind(S, (struct sockaddr *)&sock, sizeof(sock)) < 0)
		ERROR("server: bind");

	/*
	 * Listen on this socket
	 */
	if (listen(S,MAXPENDING) < 0)
		ERROR("server: listen");
	
	/* Initialize the set of active sockets. */
    for(i=1; i<1024;i++){
    	activefds[i].fd = -1;
    }
    for(i=1; i<1024; i++){
    	if(activefds[i].fd < 0){
    		activefds[i].fd = S;
    		activefds[i].events = POLLIN;
    		break;
    	}
    }
	
	while(1)
	{
		/* Block until input arrives on one or more active sockets. */
        for(i=1; i<1024; i++){
        	readfds[i] = activefds[i];
        }
        if (poll(readfds, 1024, -1) < 0)
        {
			perror ("poll");
            exit (EXIT_FAILURE);
        }
		
		/* Service all the sockets with input pending. */
		for (i = 0; i < 1024; ++i)
		{
			if (readfds[i].revents & POLLIN)
			{
				if (activefds[i].fd == S)
				{
					/* Connection request on original socket. */

					/*
					 * Accept connections.  Once connected, the client will be
					 * connected on fd NS, a second and third parameter may be passed
					 * to accept which will be filled in with information regarding the
					 * client connection if desired.
					 *
					 * In this example, once connected the server is done with the
					 * master socket (so closes it).
					 */
					if ((NS = accept(S,NULL,NULL)) < 0)
						ERROR("server: accept");
					for(i=1; i<1024; i++){
						if(activefds[i].fd < 0){
							activefds[i].fd = NS;
							activefds[i].events = POLLIN;
							break;
						}
					}
				}
				else
				{
					/* Data arriving on an already-connected socket. */
					handle_connection(activefds[i].fd);
				}
			}
		} /* //end of for */
	} /* //end of while */
  
	return(0);
}

void handle_connection(int NS)
{
	char buf[BUFSIZE];			/* Input buffer */
	FILE *fp;					/* Stream (converted file des.) */
	int n;
		
	memset(buf,0,BUFSIZE);

	if( (n = recv(NS, buf, BUFSIZE,0)) > 0)  {
	 printf("String received from and resent to the client: %s\n", buf);
	 send(NS, buf, n, 0);
	}

}
