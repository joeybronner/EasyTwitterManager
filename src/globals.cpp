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

using namespace std;


/* if logged = 1 ; else = 0 */
int loggedIn = 99;

/* twitter global variables */
string tmpStr, tmpStr2;
string replyMsg;
char tmpBuf[1024];