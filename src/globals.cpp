#include "stdafx.h"
#include "windows.h"
#include "tchar.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>     
#include <string>
#include <ctime>
#include <time.h>
//#include "twitcurl.h"

using namespace std;


/* if logged = 1 ; else = 0 */
int loggedIn = 0;

/* twitter global variables */
string tmpStr, tmpStr2;
string replyMsg;
char tmpBuf[1024];