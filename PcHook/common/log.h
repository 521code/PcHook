#pragma once

#ifdef DEBUG

//��������̨log
#define USE_CONSOLE_LOG

//ʹ���ļ���¼��־
#define USE_FILE_LOG

#endif

//���������
//#define USE_OUTPUT_DEBUG_LOG

//��־����������
#define MAX_LOG_BUFF		(10*1024)

//��־Ŀ¼
#define LOG_PATH			L".\\log\\"
#define LOG_FILE_NAME		L"%04d-%02d-%02d.log"

class CLog
{
public:
	CLog();
	
	//��¼��־
	void Log(const char * szLog, ...);

	static CLog *GetInstance();
private:
	FILE *m_fp = NULL;
	static CLog *m_instance;
};
#define pLog	(CLog::GetInstance())

#define LOG(fmt, ...)  pLog->Log("[%s] "fmt"\n",   __FUNCTION__,  ##__VA_ARGS__)