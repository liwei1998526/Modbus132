#include<iostream>
#include<winsock.h>
#include<string>
#include"Modbus.h"
#pragma comment(lib,"ws2_32.lib")
using namespace std;
void initialization();
int main()
{
	string co;
	int code, m = 0, n = 0;
	vector<int>val;
	cout << "�����빦���룺";
	cin >> co;
	code = stoi(co, 0, 16);
	if (code == 1 || code == 15)
	{
		WriteCoilCommand(m, n, val);
	}
	if (code == 3 || code == 16)
	{
		WriteRigisterCommand(m, n, val);
	}
	//���峤�ȱ���
	int send_len = 0;
	int recv_len = 0;
	int len = 0;
	/*char send_buf_code[100];
	memset(send_buf_code, 0, sizeof(send_buf_code));*/
	//���巢�ͻ������ͽ��ܻ�����
	char send_buf[100];
	//��ʼ���ڴ棬����������
	memset(send_buf, 0, sizeof(send_buf));
	char recv_buf[100];
	memset(recv_buf, 0, sizeof(recv_buf));
	//���������׽��֣����������׽���
	SOCKET s_server;
	SOCKET s_accept;
	//����˵�ַ�ͻ��˵�ַ
	SOCKADDR_IN server_addr;
	SOCKADDR_IN accept_addr;
	initialization();
	//���������Ϣ
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(526);
	//�����׽���
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (bind(s_server, (SOCKADDR *)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		cout << "�׽��ְ�ʧ�ܣ�" << endl;
		WSACleanup();
	}
	else
	{
		cout << "�׽��ְ󶨳ɹ���" << endl;
	}
	//�����׽���Ϊ����״̬
	if (listen(s_server, SOMAXCONN) < 0)
	{
		cout << "���ü���״̬ʧ�ܣ�" << endl;
		WSACleanup();
	}
	else
	{
		cout << "���ü���״̬�ɹ���" << endl;
	}
	cout << "��������ڼ������ӣ����Ժ�...." << endl;
	//������������
	len = sizeof(SOCKADDR);
	s_accept = accept(s_server, (SOCKADDR *)&accept_addr, &len);
	if (s_accept == SOCKET_ERROR)
	{
		cout << "����ʧ�ܣ�" << endl;
		WSACleanup();
		return 0;
	}
	cout << "���ӽ�����׼����������" << endl;
	//��������
	while (1)
	{
		recv_len = recv(s_accept, recv_buf, 100, 0);
		if (recv_len < 0)
		{
			cout << "����ʧ�ܣ�" << endl;
			break;
		}
		else
		{
			cout << "�ͻ�����Ϣ:" << recv_buf << endl;
		}
		string recv_str = recv_buf;
		for (int index = 0; index < recv_str.size(); index++)
		{
			if (recv_str[index] == ' ')
			{
				recv_str.erase(index, 1);
				index--;
			}
		}
		string recv_device = recv_str.substr(12, 2);
		int device = stoi(recv_device, 0, 16);
		if (device != 9)
		{
			getchar();
			return -1;
		}
		if (recv_str.size() <= 14)
		{
			return 0;
		}
		string recv_code = recv_str.substr(14, 2);
		int function = stoi(recv_code, 0, 16);
		if (function == 1)
		{
			char *send_buf_code = new char(100);
			memset(send_buf_code, 0, sizeof(send_buf_code));
			//send_buf_code1= FUNCTION01(recv_buf, send_buf_code, m, val);
			//FUNCTION01(recv_buf, send_buf_code, m, val);
			strcpy(send_buf, FUNCTION01(recv_buf, send_buf_code, m, val));
		}
		if (function == 3)
		{
			char *send_buf_code = new char(100);
			memset(send_buf_code, 0, sizeof(send_buf_code));
			strcpy(send_buf, FUNCTION03(recv_buf, send_buf_code, m, val));
		}
		else if (function != 1&&function != 3)
		{
			for (int i = 0; i < 17; i++)
			{
				send_buf[i] = recv_buf[i];
			}
			send_buf[11] = '3';
			send_buf[14] += 8;
			send_buf[16] = '0';
			send_buf[17] = '1';
			cout << "�������쳣" << endl;
			cout << "��Ӧ����Ϊ��" << send_buf << endl;
		}
		//cout << "������ظ���Ϣ:";
		//cin >> send_buf;
		send_len = send(s_accept, send_buf, 100, 0);
		if (send_len < 0)
		{
			cout << "����ʧ�ܣ�" << endl;
			break;
		}
	}
	//�ر��׽���
	closesocket(s_server);
	closesocket(s_accept);
	//�ͷ�DLL��Դ
	WSACleanup();
	return 0;
}
void initialization()
{
	//��ʼ���׽��ֿ�
	WORD w_req = MAKEWORD(2, 2);//�汾��
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0)
	{
		cout << "��ʼ���׽��ֿ�ʧ�ܣ�" << endl;
	}
	else
	{
		cout << "��ʼ���׽��ֿ�ɹ���" << endl;
	}
	//���汾��
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2)
	{
		cout << "�׽��ֿ�汾�Ų�����" << endl;
		WSACleanup();
	}
	else
	{
		cout << "�׽��ֿ�汾��ȷ��" << endl;
	}
	//������˵�ַ��Ϣ
}