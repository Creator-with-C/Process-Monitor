#include<windows.h>
#include<psapi.h>     // must link Psapi lib
#include<tlhelp32.h>
#include<tchar.h>
#include<stdio.h>


char error1[]="ERROR:Failed to retrieve CPU information.\n\n",
    error2[]="ERROR:Failed to retrieve initial CPU usage measurement.\n\n",
    error3[]="ERROR:Failed to retrieve subsequent CPU usage measurement.\n\n",
    error4[]="ERROR:Failed to retrieve RAM information.\n\n",
    error5[]="ERROR:Failed to retrieve Disk I/O information.\n\n",
    error6[]="ERROR:Failed to create a snapshot for thread enumaration.\n\n",
    error7[]="ERROR:Failed to enumerate process threads.\n\n";
