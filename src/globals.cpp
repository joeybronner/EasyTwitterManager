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

/*
* 08/07/2014
* Here, all global values used in the program execution
* 
**/

/* closing app if true */
bool endApp = false;

/* if logged = 1 ; else = 0 */
bool loggedIn = false;

/* twitter global variables */
string tmpStr, tmpStr2;
string replyMsg;
char tmpBuf[1024];
string user;
string lang;
int followers;
int following;
char * database;

