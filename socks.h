#ifndef __SOCKS_H__
#define __SOCKS_H__

#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

class client{
	public:
		int sockdes;
		int port;
		char addr[16];
		char buff [8192];
		struct sockaddr_in server;
		client ();
		client ( const char * , const char * );
		int sen ();
		int rec ( string & msg );
		char * set_buff ( const char * );
		~client ();
};

class server{
	public:
		int sockdes;
		int clides;
		int port;
		int cl;
		char addr[16];
		char buff [8192];
		struct sockaddr_in serv , client;
		server ();
		server ( int );
		server & operator= ( const server & );
		int sen ();
		int acc ();
		int thread_acc ( void *(*)(void * , int) );
		int rec ( string & msg );
		char * set_buff ( const char * );
		~server ();
};

#endif
