#include <iostream>
#include <signal.h>
#include "../socks.h"

void * fun ( void * se , int cl )
{
	string msg;
	server * s = (server *) se;
	do{
			s->rec ( msg );
			cerr << "Message recieved by " << cl << " : " << msg << endl;
			s->set_buff ( msg.c_str() );
			s->sen ();
	} while ( msg.size () != 0 );
}


void die(int x)
{
	exit (0);
}

int main()
{
	string msg;
	server s (1995);
	signal(SIGABRT,die);
    signal(SIGTERM,die);
	cout << "Server is running at port : " << s.port << endl;
	while ( true )
	{
		s.thread_acc ( fun );
		cout << "Connection accepted" << endl;
	}
	return 0;
}
