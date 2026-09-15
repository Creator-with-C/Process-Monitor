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


HANDLE file;



void PrintProcessNameAndID(DWORD processID){

    TCHAR szProcessName[MAX_PATH]=TEXT("<unknown>");

    HANDLE hProcess=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,processID);

    if(NULL!=hProcess){
        HMODULE hMod;
        DWORD cbNeeded;

        if(EnumProcessModules(hProcess,&hMod,sizeof(hMod),&cbNeeded)){
            GetModuleBaseName(hProcess,hMod,szProcessName,sizeof(szProcessName)/sizeof(TCHAR));}}

    _tprintf(TEXT(" %s  (PID: %u)\n"),szProcessName,processID);
    CloseHandle(hProcess);}




void print_cpu_usage(DWORD processID){

    HANDLE hProcess=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,processID);

    if(hProcess==NULL){
        WriteFile(file,error1,strlen(error1),NULL,NULL);
        return;}

    FILETIME creationTime,exitTime,kernelTime1,userTime1;
    FILETIME kernelTime2,userTime2;

    if(!GetProcessTimes(hProcess,&creationTime,&exitTime,&kernelTime1,&userTime1)){
        WriteFile(file,error2,strlen(error2),NULL,NULL);
        CloseHandle(hProcess);
        return;}

    Sleep(1000);

    if(!GetProcessTimes(hProcess,&creationTime,&exitTime,&kernelTime2,&userTime2)){
        WriteFile(file,error3,strlen(error3),NULL,NULL);
        CloseHandle(hProcess);
        return;}

    ULARGE_INTEGER k1,u1,k2,u2;

    k1.LowPart=kernelTime1.dwLowDateTime;
    k1.HighPart=kernelTime1.dwHighDateTime;

    u1.LowPart=userTime1.dwLowDateTime;
    u1.HighPart=userTime1.dwHighDateTime;

    k2.LowPart=kernelTime2.dwLowDateTime;
    k2.HighPart=kernelTime2.dwHighDateTime;

    u2.LowPart=userTime2.dwLowDateTime;
    u2.HighPart=userTime2.dwHighDateTime;

    ULONGLONG cpuTime=(k2.QuadPart-k1.QuadPart)+(u2.QuadPart-u1.QuadPart);

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    double cpuUsage=(double)cpuTime/10000000.0*100.0;
    cpuUsage/=sysInfo.dwNumberOfProcessors;

    char *buffer[200];
    size_t len=snprintf(buffer,sizeof(buffer),"CPU usage:" "%.2f%%\n\n",cpuUsage);
    WriteFile(file,buffer,strlen(buffer),NULL,NULL);

    CloseHandle(hProcess);}




void PrintMemoryInfo(DWORD processID){

    PROCESS_MEMORY_COUNTERS pmc;

    HANDLE hProcess=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,processID);
    if(NULL==hProcess){
        WriteFile(file,error4,strlen(error4),NULL,NULL);
        return;}

    if(GetProcessMemoryInfo(hProcess,&pmc,sizeof(pmc))){
        MEMORYSTATUSEX memInfo;
        memInfo.dwLength=sizeof(memInfo);
        if(GlobalMemoryStatusEx(&memInfo)){
            double ramMB=(double)pmc.WorkingSetSize/(1024.0*1024.0);
            double ramPercent=((double)pmc.WorkingSetSize/(double)memInfo.ullTotalPhys)*100.0;
            char *buffer[200];
            size_t len=snprintf(buffer,sizeof(buffer),"RAM usage:" "%.2f MB" "(%.4f%%)\n\n",ramMB,ramPercent);
            WriteFile(file,buffer,strlen(buffer),NULL,NULL);}}

    CloseHandle(hProcess);}




void print_disk_io_information(DWORD processID){

    struct PIO_COUNTERS{
    ULONGLONG ReadOperationCount;
    ULONGLONG WriteOperationCount;
    ULONGLONG OtherOperationCount;
    ULONGLONG ReadTransferCount;
    ULONGLONG WriteTransferCount;
    ULONGLONG OtherTransferCount;}iocounters;

    HANDLE hProcess=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,processID);
    if(OpenProcess==NULL){
        WriteFile(file,error5,strlen(error5),NULL,NULL);
        return 1;}
    if(GetProcessIoCounters(hProcess,&iocounters)){
        char *buffer[200];
        size_t len=snprintf(buffer,sizeof(buffer),
        "DISK I/O information:\n"
        "Read Operation:%llu\nRead Operation Byte:%llu\n"
        "Write Operation:%llu\nWrite Operation Bytes:%llu\n"
        "Other Operation:%llu\nOther Operation Bytes:%llu\n\n",
        iocounters.ReadOperationCount,iocounters.ReadTransferCount,
        iocounters.WriteOperationCount,iocounters.WriteTransferCount,
        iocounters.OtherOperationCount,iocounters.OtherTransferCount);
        WriteFile(file,buffer,strlen(buffer),NULL,NULL);
        CloseHandle(hProcess);}}




void Count_Threads(DWORD processID){

    THREADENTRY32 te32;

    HANDLE hThreadSnap=CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,0);
    if(hThreadSnap==INVALID_HANDLE_VALUE){
        WriteFile(file,error6,strlen(error6),NULL,NULL);
        return(FALSE);}


    te32.dwSize=sizeof(THREADENTRY32);


    if(!Thread32First(hThreadSnap,&te32)){
        CloseHandle(hThreadSnap);
        WriteFile(file,error7,strlen(error7),NULL,NULL);
        return(FALSE);}

    size_t len;
    char *buffer[2000];
    do{
    if(te32.th32OwnerProcessID==processID){
        len=snprintf(buffer,sizeof(buffer),
        "Tread ID=0x%08X\n"
        "Base Priority=%d\n"
        "Delta Priority=%d\n\n",
        te32.th32ThreadID,
        te32.tpBasePri,te32.
        tpDeltaPri);
        WriteFile(file,buffer,strlen(buffer),NULL,NULL);}}
    while(Thread32Next(hThreadSnap,&te32));

    CloseHandle(hThreadSnap);}







int main(){

    int i2=1,i3;

    DWORD aProcesses[1024],cbNeeded,cProcesses;

    if(!EnumProcesses(aProcesses,sizeof(aProcesses),&cbNeeded)){
        printf("ERROR:Failed to enumerate processes.\n");
        Sleep(5000);
        exit(1);}


    cProcesses=cbNeeded/sizeof(DWORD);

    for(int i1=0;i1<cProcesses;i1++){
        if(aProcesses[i1]!=0){
            printf("Number: %d",i2);
            PrintProcessNameAndID(aProcesses[i1]);
            i2+=1;}}

    printf("\n\nSelect a process to monitor by entering its number:\n");

    scanf("%d",&i2);

    printf("\n\nSelected process to monitor: ");
    PrintProcessNameAndID(aProcesses[i2]);
    printf("\n\n");

    printf("Number of measurements:\n");
    scanf("%d",&i3);


    file=CreateFileW(L"monitor.log",FILE_WRITE_DATA,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
    if(file==INVALID_HANDLE_VALUE){
        printf("ERROR:Failed to create the log file.\n");
        Sleep(5000);
        exit(1);}

    for(int i4=0;i4<i3;i4++){

        print_cpu_usage(aProcesses[i2]);

        PrintMemoryInfo(aProcesses[i2]);

        print_disk_io_information(aProcesses[i2]);

        Count_Threads(aProcesses[i2]);}

    CloseHandle(file);

    printf("\n\nProcess complited");
    Sleep(4000);

    return 0;}
