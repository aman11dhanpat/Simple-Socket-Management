#include "socks.h"

client :: client ( const char * srv , const char * po )
{
	sockdes = socket(AF_INET , SOCK_STREAM , 0);
	if (sockdes == -1)
	{
		cerr << "Could not create socket : " << strerror (errno) << endl;
	}
	strcpy ( addr , srv );
	server.sin_addr.s_addr = inet_addr(srv);
	server.sin_family = AF_INET;
	server.sin_port = htons( atoi (po) );
	if ( connect(sockdes , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		cerr << "connect error : " << strerror (errno) << endl;
	}
}

client :: client ()
{
	sockdes = socket(AF_INET , SOCK_STREAM , 0);
	if (sockdes == -1)
	{
		cerr << "Could not create socket : " << strerror (errno) << endl;
	}
}

client :: ~client ()
{
	close (sockdes);
}

int client :: sen ()
{
	if( send(sockdes , buff , strlen(buff) , 0) < 0)
	{
		cerr << "Send failed : " << strerror (errno) << endl;
		return -1;
	}
	return 1;
}

int client :: rec ( string & msg )
{
	int size;
	msg = string ("");
	do
	{
		size = read(sockdes, buff , 8192);
		if ( size < 0 )
		{
			cerr << "Recv failed : " << strerror (errno) << endl;
			return -1;
		}
		buff [size] = 0;
		msg.append (buff);
	}while( size == 8192 );
	return size;
}

char * client :: set_buff ( const char * c )
{
	return strncpy ( buff , c , 8192 );
}

server :: ~server ()
{
	close (sockdes);
}

server :: server ()
{
	server (0);
}

server :: server ( int p )
{
	if ( p < 0 )
		return;
	int c;
	int on = 1;
	sockdes = 0;
	clides = 0;
	sockdes = socket(AF_INET , SOCK_STREAM , 0);
	if (sockdes == -1)
	{
		cerr << "Could not create socket : " << strerror (errno) << endl;
	}
	//strcpy ( addr , srv );
	serv.sin_addr.s_addr = INADDR_ANY;
	serv.sin_family = AF_INET;
	serv.sin_port = htons( p );
	if (setsockopt(sockdes,SOL_SOCKET,SO_REUSEADDR,(char *)&on,sizeof(on)) < 0)
	{
		cerr << "Could not create iterative server : " << strerror (errno) << endl;
	}
	if( bind(sockdes,(struct sockaddr *)&serv , sizeof(serv)) < 0)
	{
		cerr << "bind failed : " << strerror (errno) << endl;
    }
	listen(sockdes , 3);
	getsockname( sockdes, (struct sockaddr *)&client,(socklen_t*)&c);
	port = ntohs (client.sin_port);
}

server & server :: operator= ( const server & rhs )
{
	if ( &rhs != this )
	{
		clides = rhs.clides;
		port = rhs.port;
		strcpy ( addr , rhs.addr );
		strcpy ( buff , rhs.buff );
		serv = rhs.serv;
		client = rhs.serv;
	}
	return *this;
}

int server :: acc ()
{
	int c = sizeof(struct sockaddr_in);
	clides = accept(sockdes, (struct sockaddr *)&client, (socklen_t*)&c);
    if (clides<0)
    {
        cerr << "Accept failed : " << strerror (errno) << endl;
    }
	return clides;
}


int server :: thread_acc ( void * (*f)(void* , int) ){
	int c = sizeof(struct sockaddr_in);
	clides = accept(sockdes, (struct sockaddr *)&client, (socklen_t*)&c);
	cl++;
	int x = fork ();
	if (x == 0)
	{
	    if (clides<0)
	    {
	        cerr << "Accept failed : " << strerror (errno) << endl;
	    }
	    f((void *)this , cl);
	}
	return clides;
}

int server :: sen ()
{
	if( send(clides , buff , strlen(buff) , 0) < 0)
	{
		cerr << "Send failed : " << strerror (errno) << endl;
		return -1;
	}
	return 1;
}

int server :: rec ( string & msg )
{
	int size;
	msg = string ("");
	do
	{
		size = read(clides, buff , 8192);
		if ( size < 0 )
		{
			cerr << "Recv failed : " << strerror (errno) << endl;
			return -1;
		}
		buff [size] = 0;
		msg.append (buff);
	}while( size == 8192 );
	return size;
}

char * server :: set_buff ( const char * c )
{
	return strncpy ( buff , c , 8192 );
}
