#include <iostream>
#include "../socks.h"

int main(int argc, const char *argv[])
{
	string msg;
	if ( argc != 2 )
	{
		cerr << "Usage : " << argv[1] << " IP_ADDRESS" << endl;
	}
	client c ( argv[1] , "13" );
	c.rec ( msg );
	cout << msg << endl;
	return 0;
}
