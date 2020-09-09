#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\ModbusTCP\Modbus.h"
#include<stdio.h>
#include<windows.h>
#include<iostream>
#include <string>
#include<tchar.h>
#define FUN03_PATH "../Function03Test.ini"
using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ModbusTCPTest
{
	TEST_CLASS(Function03Test)
	{
	public:

		TEST_METHOD(Function03Test1)
		{
			int j = GetPrivateProfileInt(_T("test"), _T("j"), 1, _T(FUN03_PATH));
			for (int i = 1; i <= j; i++)
			{
				CString a, b, c;
				char*send_buf = new char(600);
				char*actual;
				memset(send_buf, 0, strlen(send_buf));
				CString str = _T("");
				str.Format(_T("%d"), i);
				USES_CONVERSION;
				const char*st = T2A(str);
				char path[10] = "test";
				strcat_s(path, 8, st);
				CString add(path);
				GetPrivateProfileString(add, _T("input1"), _T("error"), a.GetBuffer(MAX_PATH), MAX_PATH, _T(FUN03_PATH));
				a.ReleaseBuffer();
				string recv_buf(W2A(a));
				int k = GetPrivateProfileInt(add, _T("input2"), -1, _T(FUN03_PATH));
				GetPrivateProfileString(add, _T("input3"), _T("error"), b.GetBuffer(MAX_PATH), MAX_PATH, _T(FUN03_PATH));
				b.ReleaseBuffer();
				char*ch = NULL;
				ch = T2A(b);
				char* sh2 = strtok(ch, ",");
				vector<int>val;
				while (sh2 != NULL)
				{
					val.push_back(atoi(sh2));
					sh2 = strtok(NULL, ",");
				}
				actual = FUNCTION03(recv_buf, send_buf, k, val);
				GetPrivateProfileString(add, _T("output"), _T("error"), c.GetBuffer(MAX_PATH), MAX_PATH, _T(FUN03_PATH));
				c.ReleaseBuffer();
				char*expect = T2A(c);
				Assert::AreEqual(expect, actual);
			}
		}

	};
}