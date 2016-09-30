#include <iostream>
#include "../socks.h"

int main()
{
	string msg;
	server s (1995);
	cout << "Server is running at port : " << s.port << endl;
	s.acc ();
	cout << "Connection accepted" << endl;
	do{
		s.rec ( msg );
		cerr << "Message recieved : " << msg << endl;
		s.set_buff ( msg.c_str() );
		s.sen ();
	} while ( msg.size () != 0 );
	return 0;
}
