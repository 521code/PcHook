#pragma once

#define OPEN_CONSOLE_XLOG			0
#define XLOG_FILE_FLUSH_TIME		1*1000
#define XLOG_FILE_DIR				L"\\xLog\\"
#define XLOG_FILE_NAME				L"MM_%04d-%02d-%02d_%02d%02d%02d.xlog"


class CDebugHelper : public Singleton<CDebugHelper>
{
public:
	//����xlog
	void OpenXlog();

	//�ر��Զ�����
	void CloseAutoUpdate();

	//����࿪
	void EnableMultiProcess();

	//��ӡ���
	void DumpProto();
	void CancelDumpProto();

	//�ر�mmtls(��֧�־ɰ汾, ��ǰ�汾�ر�tls�󲿷ַ������SessionTimeout)
	void DisableMmtls();

	//�رճ�����
	void DisableLonglink();

	//����CreateToolhelp32Snapshot
	void FuckReport();
private:
	//����xlog��־�ļ�
	static void WriteXLogThread();

	//ȡ��xlog
	CStringA FetchXlog();

	FILE *m_fpXlog = NULL;
	std::mutex m_mutex_xlog;
	list<CStringA> m_list_xlog;

	shared_ptr<CHOOK>  m_spHookEncode = NULL;
	shared_ptr<CHOOK>  m_spHookDecode = NULL;
public:
	//��ӡxlog
	void PrintXlog(const char *szLog, DWORD dwLen);
};
#define pDebugHelper	(CDebugHelper::GetInstance())


