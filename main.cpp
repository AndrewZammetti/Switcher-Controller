#include<iostream>
#include<string>
#include<windows.h>
// #include<graphics.h>

using namespace std;

void initPort(HANDLE);
void inToOut(HANDLE, char);

int main(){
    HANDLE serialHandle = CreateFile("COM1", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    initPort(serialHandle);

    inToOut(serialHandle, '2');

    CloseHandle(serialHandle);

    return 0;
}

void inToOut(HANDLE serialHandle, char input){
    char audioInput = input;

    char writeBuff[10] = {'*', 'B', 'T', 'S', 'S', '*', '1', '0', audioInput, '2'};
    DWORD dwWrite = 0;
    if(!WriteFile(serialHandle, writeBuff, 10, &dwWrite, NULL)){
        cout<<"Error writing serial port!\n";
    }
}

void initPort(HANDLE serialHandle){
    if(serialHandle==INVALID_HANDLE_VALUE){
        if(GetLastError() == ERROR_FILE_NOT_FOUND){
            cout<<"No Serial device found!\n";
        }
        cout<<"Undefined error!\n";
    }

    DCB dcbSerialParam = {0};
    dcbSerialParam.DCBlength = sizeof(dcbSerialParam);

    if (!GetCommState(serialHandle, &dcbSerialParam)) {
        cout<<"Couldn't get comm state!\n";
    }

    dcbSerialParam.BaudRate=CBR_9600;
    dcbSerialParam.ByteSize=8;
    dcbSerialParam.StopBits=ONESTOPBIT;
    dcbSerialParam.Parity=NOPARITY;

    if(!SetCommState(serialHandle, &dcbSerialParam)){
        cout<<"Couldn't set comm state!\n";
    }

    COMMTIMEOUTS timeout={0};
    timeout.ReadIntervalTimeout=60;
    timeout.ReadTotalTimeoutConstant=60;
    timeout.ReadTotalTimeoutMultiplier=15;
    timeout.WriteTotalTimeoutConstant=60;
    timeout.WriteTotalTimeoutMultiplier=8;
    if(!SetCommTimeouts(serialHandle, &timeout)){
        cout<<"Couldn't set comm timeouts!\n";
    }
}