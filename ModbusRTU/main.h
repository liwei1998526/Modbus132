#include<iostream>
#include<vector>
#include<string>
#include<windows.h>
#include<ctype.h>
using namespace std;
HANDLE InitCOM(LPCTSTR Port, int baud_rate, BYTE date_bits, BYTE stop_bit, BYTE parity);
bool SendData(HANDLE m_hComm, char* data, int len);
string DEtoHEX(int n);
string DEtoBIN(int n);
unsigned short CRC16(unsigned char* puchMsg, unsigned short usDataLen);
void HexstrtoByte(const char* source, unsigned char* dest, int sourcelen);
char* hex2str(UINT8 *hex, int len);
char* function01(string add, string code);
char* function0F(string add, string code);
char* function10(string add, string code);
void respond_massage(string read_str, string send_buf);
void respond_01(string Read_buf, string send_buf);
void respond_03(string Read_buf, string send_buf);