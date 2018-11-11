#pragma once


enum WM_USER_MSG
{
	WM_USER_SEND_INVALID = WM_USER + 2018,
	
	//��������
	WM_USER_SEND_TEXT,
	
	//����ͼƬ
	WM_USER_SEND_IMAGE,

	//�����ļ�
	WM_USER_SEND_FILE,

	//�������ݿ��ѯ
	WM_USER_SQL,
};

struct CMsgParam
{
	BOOL		m_bRet = FALSE;
	WM_USER_MSG m_msg = WM_USER_SEND_INVALID;
	DWORD		m_dword[5] = { 0 };
	LPVOID		m_lpvoid[5] = { NULL };
	CString		m_cstring[5];
	CStringA	m_cstringA[5];
	string      m_string[5];
	wstring     m_wstring[5];
};

class CSubClassMainWnd : public Singleton<CSubClassMainWnd>
{
public:
	//���ش�����������Ϣ
	void SubClassMainWnd();

	//���������ھ��
	void SetWeChatHwnd(HWND hwnd) { m_hWeChatWnd = hwnd; }
	HWND GetWeChatHwnd() { return m_hWeChatWnd; }

	//�Զ��崰�ڹ���
	static LRESULT __stdcall MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//�������ڷ���Ϣ
	BOOL SendMessage(WM_USER_MSG msg, CMsgParam *param);

	//ԭʼ���ڹ���
	WNDPROC m_oldWndProc = NULL;
private:
	//ö�ٱ�����������
	HWND GetMainWnd();
	static BOOL __stdcall GetMainWndCallback(HWND hwnd, LPARAM lParam);

	HWND    m_hWeChatWnd = NULL;		//�����ھ��
};
#define pSubClassMainWnd		(CSubClassMainWnd::GetInstance())



