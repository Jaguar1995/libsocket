#pragma once

#include <iostream>
#include <map>
#include <windows.h>
using namespace std;
#pragma comment(lib,"WS2_32.lib")//��ʾ�����׽��ֿ�

typedef void(*Servfun)(SOCKET s);
#define uint unsigned int

class DataReceivingSending {
public:
	static string R(SOCKET sockClient, int rl);
	static bool Send(SOCKET sockClient, string &buff);
	static bool Recv(SOCKET sockClient, int len, string &r);
};

class CPP_Server {

private:
	SOCKET SockS;
	WSADATA WsaData;
	Servfun sf;
public:
	bool Open(int port);
	void Acpt();
	void Destroy();
	void SetServfun(Servfun sft);
};

struct HeadDemo {
	char RequestType[50]; //�������� SAVEFILE|RETMSG|
	char MsgType[50];  // �������� XML/JSON/PIC
	char DateTime[20]; //20180528-165401
	char Name[150]; // ����
	char Password[32]; //�ļ�����
};

static map<int, string> Ret_Msgs = {
	{ 0,"�����ɹ�" },
	{ -1,"����ʧ��" },

};

#define HEADFIRSTLEN sizeof(HeadDemo)
class  protocolDemo:public DataReceivingSending {
public:
	bool RecvFIRSTBYTES(SOCKET st, uint &len);
	bool RecvSECONDBYTES(SOCKET st, uint &len);
    bool RecvFIRST(SOCKET st, uint &len, string &first);
	bool RecvSECOND(SOCKET st, uint &len, string &second);
	string GenerateFIRSTBYTES(uint ln);
	string GenerateSECONDBYTES(uint ln);
	string GenerateErrRet(string &OriginHead, int errorCode);
};

class CPP_Server_Handle_Demo :public CPP_Server, public protocolDemo {



};


class SynchroShortConnection {
public:
	SOCKET sc;
public:
	void Destroy();
	bool Connect(string Ip, string port);
	bool Start(string Ip, string port);
	void SetTimeOut(int nNetTimeout);
};

class SynchroShortConnection_Demo : public SynchroShortConnection ,public protocolDemo {
public:

};