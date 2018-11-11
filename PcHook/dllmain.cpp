// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"

#include "core/debug_helper.h"
#include "core/send_msg.h"
#include "core/sync_msg.h"
#include "core/sub_class_wnd.h"
#include "core/db.h"


void TestSendMsg()
{
#ifndef DEBUG
	return;
#endif

#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

	//���Է�ͼ
	WCHAR szTempShortPath[MAX_PATH] = { 0 };
	WCHAR szTempPath[MAX_PATH] = { 0 };
	GetTempPath(MAX_PATH, szTempShortPath);
	GetLongPathName(szTempShortPath, szTempPath, MAX_PATH);
	PathRemoveBackslash(szTempPath);
	wsprintf(szTempPath, L"%s\\test_%d_%d.jpg", szTempPath, (DWORD)time(NULL), GetCurrentThreadId());

	srand(GetCurrentThreadId());
	CString strUrl;
	strUrl.Format(L"https://pics.javcdn.pw/cover/%d_b.jpg", rand()%5000 + 1);
	if (!URLDownloadToFile(NULL, strUrl, szTempPath, NULL, NULL))
	{
		CStringA strUrlA = CW2A(strUrl);
		CStringA strTempPathA = CW2A(szTempPath);
		LOG("�����ļ�%s���سɹ�, �ļ�·��:%s", strUrlA, strTempPathA);

		{
			//���Է�������Ϣ
			CMsgParam param;
			param.m_wstring[0] = L"filehelper";
			param.m_wstring[1] = L"Hello!";
			pSubClassMainWnd->SendMessage(WM_USER_SEND_TEXT, &param);
		}
		
		{
			//���Է�ͼƬ
			CMsgParam param;
			param.m_wstring[0] = L"filehelper";
			param.m_wstring[1] = szTempPath;
			pSubClassMainWnd->SendMessage(WM_USER_SEND_IMAGE, &param);
		}

		{
			//���Է��ļ�
			CMsgParam param;
			param.m_wstring[0] = L"filehelper";
			param.m_wstring[1] = szTempPath;
			pSubClassMainWnd->SendMessage(WM_USER_SEND_FILE, &param);
		}

		{
			//���Ի�ȡ��ϵ��
			list<shared_ptr<CContactInfo>> l = pDbUtil->GetContactList();
			LOG("������ϵ��%dλ", l.size());

			//���Ի�ȡ������ʷ�����¼
			int CntChatRecord = pDbUtil->GetChatRecord();
			LOG("������ʷ��Ϣ��¼����%d��", CntChatRecord);
		}
	}
	else
	{
		LOG("�����ļ�%s����ʧ�ܣ�", CW2A(strUrl));
	}
}

void Start()
{
	try
	{
		LOG("���سɹ�, ��ǰ�ͻ��˰汾��:%S", pBaseAddrMgr->GetVersion());

		//����࿪
		pDebugHelper->EnableMultiProcess();

		//��ʼ����ַ
		pBaseAddrMgr->Init();

		//����Xlog
		pDebugHelper->OpenXlog();

		//���ó�����
		//pDebugHelper->DisableLonglink();
		//��ӡ���
		//pDebugHelper->DumpProto();
		
		//ͬ����Ϣ����
		pSyncMsg->Start();

		//���������໯(�ȴ���¼�ɹ�)
		pSubClassMainWnd->SubClassMainWnd();

		//������Ϣ��������
		thread t(TestSendMsg);
		t.join();
	}
	catch (...)
	{
		LOG("Crash!\n");
	}
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Start, NULL, NULL, NULL));
		break;
	case DLL_THREAD_ATTACH:
		//LOG("�߳�����:tid=%d", GetCurrentThreadId());
		break;
	case DLL_THREAD_DETACH:
		//LOG("�߳��˳�:tid=%d", GetCurrentThreadId());
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}