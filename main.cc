/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cc
 * Copyright (C) 2014 aman <>
 * 
 */

#include <iostream>
#include "socks.h"

int main()
{
	 string msg;
	// client c ( "74.125.236.78" , "80" );
	// c.set_buff ("GET /index.php HTTP/1.1\r\nHost: www.google.com:80\r\nConnection: keep-alive\r\n"
	//             "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
	//             "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.22 (KHTML,"
	//             "like Gecko) Ubuntu Chromium/25.0.1364.160 Chrome/25.0.1364.160 Safari/537.22\r\n"
	//             "Accept-Language: en-US,en;q=0.8\r\n"
	//             "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.3\r\n\r\n");
	// c.sen ();
	// c.rec ( msg );
	// cout << msg << endl;
	// client cc ( "127.0.0.1" , "13" );
	// cc.rec ( msg );
	// cout << msg << endl;
	server s;
	cout << "Server is running at port : " << s.port << endl;
	s.acc ();
	cout << "Connection accepted" << endl;
	s.rec ( msg );
	cout << msg << endl;
	s.set_buff ( "Hello, World!!!" );
	s.sen ();
	return 0;
}
