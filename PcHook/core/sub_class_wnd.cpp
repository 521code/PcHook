#include "stdafx.h"
#include "db.h"
#include "debug_helper.h"
#include "sub_class_wnd.h"
#include "send_msg.h"


INIT_SINGLETON(CSubClassMainWnd);


LRESULT CSubClassMainWnd::MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_USER_SEND_TEXT:
	{
		CMsgParam *param = (CMsgParam *)wParam; if(!param) break;
		pSendMsg->SendTextMsg(param->m_wstring[0], param->m_wstring[1]);
		break;
	}
	case WM_USER_SEND_IMAGE:
	{
		CMsgParam *param = (CMsgParam *)wParam; if (!param) break;
		pSendMsg->SendImageMsg(param->m_wstring[0], param->m_wstring[1]);
		break;
	}
	case WM_USER_SEND_FILE:
	{
		CMsgParam *param = (CMsgParam *)wParam; if (!param) break;
		pSendMsg->SendFileMsg(param->m_wstring[0], param->m_wstring[1]);
		break;
	}
	case WM_USER_SQL:
	{
		CMsgParam *param = (CMsgParam *)wParam; if (!param) break;
		param->m_bRet = pDbUtil->ExcuteSql(param->m_lpvoid[0], param->m_cstringA[0], (std::function<BOOL(void *)> *)param->m_lpvoid[1]);
		break;
	}		
	case WM_DESTROY:
		pDebugHelper->CloseAutoUpdate();
		pSubClassMainWnd->SetWeChatHwnd(NULL);
		pDebugHelper->CancelDumpProto();
		LOG("--------------------Logout--------------------");
		break;
	default:
		//LOG("msg:0x%x", message);
		break;
	} 


	return CallWindowProc(pSubClassMainWnd->m_oldWndProc, hWnd, message, wParam, lParam);
}

BOOL CSubClassMainWnd::SendMessage(WM_USER_MSG msg, CMsgParam *param)
{
	if (GetMainWnd())
	{
		return S_OK == ::SendMessage(GetWeChatHwnd(), msg, (WPARAM)param, NULL);
	}

	return FALSE;
}

void CSubClassMainWnd::SubClassMainWnd()
{
	while (1)
	{
		if (GetMainWnd())
		{
			//�ӹ���������Ϣ
			m_oldWndProc = (WNDPROC)::SetWindowLong(m_hWeChatWnd, GWL_WNDPROC, (LONG)MyWndProc);
			LOG("��ǰ��¼wxid: %s", pDbUtil->GetLoginWxid());

			//����CreateToolhelp32Snapshot API
			//pDebugHelper->FuckReport();
			break;
		}

		Sleep(1000);
	}
}

HWND CSubClassMainWnd::GetMainWnd()
{
	//����࿪ʱ��FindWindow�Ҳ��������̴���, ö�����ж��㴰��
	if (!m_hWeChatWnd)
		EnumWindows(&CSubClassMainWnd::GetMainWndCallback, NULL);
	
	return m_hWeChatWnd;
}

BOOL CSubClassMainWnd::GetMainWndCallback(HWND hwnd, LPARAM lParam)
{
	CString strTitle, strClass;
	::GetWindowText(hwnd, strTitle.GetBuffer(MAX_PATH), MAX_PATH);
	::GetClassName(hwnd, strClass.GetBuffer(MAX_PATH), MAX_PATH);
	strTitle.ReleaseBuffer();
	strClass.ReleaseBuffer();

	if ( (strTitle == L"΢��") && (strClass == L"WeChatMainWndForPC") )
	{
		DWORD dwPid;
		GetWindowThreadProcessId(hwnd, &dwPid);

		if (GetCurrentProcessId() == dwPid)
		{
			//ֻ��ע��ǰ����������
			pSubClassMainWnd->SetWeChatHwnd(hwnd);
			return FALSE;
		}
	}

	return TRUE;
}
