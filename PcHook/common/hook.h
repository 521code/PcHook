#pragma  once
#include <vector>

#define VERSION_2_6_4_38									L"2.6.4.38"
#define VERSION_2_6_4_56									L"2.6.4.56"
#define VERSION_2_6_5_38									L"2.6.5.38"

//��ַ����
enum BASEADDR_TYPE
{
	BASEADDR_TYPE_INVALID = -1,

	BASEADDR_TYPE_OPEN_XLOG,								//����xlog
	BASEADDR_TYPE_XLOGGER_LEVEL,							//xlogger_Level
	BASEADDR_TYPE_HOOK_ENCODE_REQBUF,						//Hook EncodeReqbuf
	BASEADDR_TYPE_HOOK_DECODE_RESPBUF,						//Hook DecodeRespbuf

	BASEADDR_TYPE_IS_MMTLS_ENABLE,							//mmtls����(���°汾��ʧЧ)
	BASEADDR_TYPE_LONGLINK_RUN_CONNECT,						//������connect

	BASEADDR_TYPE_SEND_TEXT_MSG_CALL ,						//��������Ϣcall
	BASEADDR_TYPE_SEND_IMAGE_MSG_GET_MGR_CALL,				//����ͼƬ��Ϣmgr��ַ
	BASEADDR_TYPE_SEND_IMAGE_MSG_CALL,						//��ͼƬ��Ϣcall
	BASEADDR_TYPE_SEND_FILE_MSG_GET_MGR_CALL,				//�����ļ���Ϣmgr��ַ
	BASEADDR_TYPE_SEND_FILE_MSG_CALL,						//�����ļ���Ϣcall

	BASEADDR_TYPE_HOOK_SYNC_MSG,							//Hook newsyncͬ����Ϣ
	BASEADDR_TYPE_HOOK_CREATE_CDN_DOWNLOAD_TASK,			//Hook cdn��ʼ��������
	BASEADDR_TYPE_HOOK_CDN_TASK_ONSUCCEED,					//Hook cdn�����������
	BASEADDR_TYPE_MMXOR_CALL,								//����ͼƬ���� mmxor call

	BASEADDR_TYPE_LOGIN_WXID,								//��ǰ��¼wxid��ַ
	BASEADDR_TYPE_DB_INSTANCE,								//MicroMsg���ݿ��ַ
	BASEADDR_TYPE_SQLITE3_PREPARE_V2_CALL,					//sqlite3_prepare_v2 call
	BASEADDR_TYPE_SQLITE3_STEP_CALL,						//sqlite3_step call
	BASEADDR_TYPE_SQLITE3_FINALIZE_CALL,					//sqlite3_finalize call
	BASEADDR_TYPE_SQLITE3_COLUMN_INT64_CALL,				//sqlite3_column_int64 call
	BASEADDR_TYPE_SQLITE3_COLUMN_TEXTA_CALL,				//sqlite3_column_textA call
	BASEADDR_TYPE_SQLITE3_COLUMN_TEXTW_CALL,				//sqlite3_column_textW call
	BASEADDR_TYPE_SQLITE3_COLUMN_BLOB_CALL,					//sqlite3_column_blob call
	BASEADDR_TYPE_SQLITE3_COLUMN_BYTES_CALL,				//sqlite3_column_bytes call
	
	BASEADDR_TYPE_CNT
};

//��ַ
class CBaseAddr
{
public:
	CBaseAddr(BASEADDR_TYPE type, char *szBaseName, string strMainCode, string strSubCode, int nOffset = 0, BOOL bRelativeCall = FALSE, DWORD dwStartAddr = 0x00401000, DWORD dwEndAddr = 0x01000000, DWORD dwSubSearchLen = 0x100);

	//����������
	BOOL SearchCode();
 
	DWORD GetAddr() { return m_dwBaseAddr; }
	BASEADDR_TYPE GetType() { return m_type; }
	string		  GetName() { return m_strBaseName; }
private:

	BASEADDR_TYPE	m_type = BASEADDR_TYPE_INVALID;		//baseaddr type
	string			m_strBaseName;						//��ַ��������
	DWORD			m_dwBaseAddr = NULL;				//��ַ
	string			m_strMainCode;						//������1
	string			m_strSubCode;						//������2
	int				m_nOffset;							//Hook����������������������ƫ��
	BOOL			m_bRelativeCall;					//���call��ַ
	DWORD			m_dwStartAddr;						//������ʼ��ַ
	DWORD			m_dwEndAddr;						//����������ַ
	DWORD			m_dwSubSearchLen;					//������2��������
};

//Hook
class CHOOK
{
public:
	CHOOK(DWORD dwHookAddr, DWORD dwLenCode, DWORD dwMyFunAddr, DWORD &dwHookRetAddr);
	CHOOK(BASEADDR_TYPE type, DWORD dwLenCode, DWORD dwMyFunAddr, DWORD &dwHookRetAddr);
	
	//����Hook
	BOOL HookOn();

	//�ر�Hook
	BOOL HookOff();

private:
	DWORD					m_dwHookAddr = NULL;					//Hook��ַ
	BOOL					m_bHookOn = FALSE;						//��ǰHook״̬
	string					m_strOriginalCode;						//Hook��ԭʼ����
	DWORD					m_dwMyFunAddr = NULL;					//Hook��ת������ַ
};

class CBaseAddrMgr : public Singleton<CBaseAddrMgr>
{
public:
	CBaseAddrMgr();

	//��ʼ�����л�ַ
	void Init();

	//��ȡ��ַ
	shared_ptr<CBaseAddr> GetBaseAddr(BASEADDR_TYPE type);

	//��ȡdll�汾��
	CString GetVersion();

	//�Ƚϰ汾��
	int VersionCompare(CString strVer1, CString strVer2);

	//dll��ַ
	DWORD GetModuleBaseAddr() { return m_dwModuleBaseAddr; }
	DWORD GetModuleSize()	  { return m_dwModuleSize; }
private:
	//���ݰ汾�ų�ʼ��������
	void InitFeatureCode();

	//����������
	static void SearchFeatureCode(atomic<DWORD> *nSearchIndex);

	//������������ʼ��ַ
	DWORD  m_dwModuleBaseAddr = 0x00401000;
	DWORD  m_dwModuleSize     = 0x01000000;
	
	//dll�汾��
	CString m_strVersion;

	//��ַ
	vector<shared_ptr<CBaseAddr>> m_baseAddr;
};
#define pBaseAddrMgr				(CBaseAddrMgr::GetInstance())

#define MODULE_BASE_ADDR		    (pBaseAddrMgr->GetModuleBaseAddr())
#define MODULE_SIZE					(pBaseAddrMgr->GetModuleSize())
#define SEARCH_START_ADDR			 MODULE_BASE_ADDR
#define SEARCH_END_ADDR				(MODULE_BASE_ADDR + MODULE_SIZE)

#define GET_DWORD(x)				(*(DWORD *)(x))
#define GET_CALL_ADDR(x)			(GET_DWORD(x+1) + x + 5)