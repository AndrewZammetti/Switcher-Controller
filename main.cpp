#include<iostream>
#include<string>
#include<windows.h>

using namespace std;

int main(){
    HANDLE serialHandle = CreateFile((LPCWSTR)"COM1", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

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