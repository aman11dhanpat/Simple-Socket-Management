#include <iostream>
#include "../socks.h"

int main(int argc, const char *argv[])
{
	string msg , m;
	if ( argc != 3 )
	{
		cerr << "Usage : " << argv[1] << " IP_ADDRESS PORT" << endl;
	}
	client c ( argv[1] , argv[2] );
	while ( cin >> msg )
	{
		c.set_buff ( msg.c_str() );
		c.sen ();
		c.rec ( m );
		cout << m << endl;
	}
	return 0;
}
