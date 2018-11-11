#pragma once

#define SQLITE_ROW         100  /* sqlite3_step() has another row ready */
#define SQLITE_DONE        101  /* sqlite3_step() has finished executing */


typedef const char *(__cdecl *sqlite3_column_textA_f)(void *, int);
extern sqlite3_column_textA_f sqlite3_column_textA;

typedef const wchar_t *(__cdecl *sqlite3_column_textW_f)(void *, int);
extern sqlite3_column_textW_f sqlite3_column_textW;

typedef const char *(__cdecl *sqlite3_column_blob_f)(void *, int);
extern sqlite3_column_blob_f sqlite3_column_blob;

typedef int (__cdecl *sqlite3_column_bytes_f)(void *, int);
extern sqlite3_column_bytes_f sqlite3_column_bytes;

INT64 __stdcall sqlite3_column_int64(void *pStmt, int col);


//��ϵ��
class CContactInfo
{
public:
	int      m_nType = 0;
	int      m_nDelFlag = 0;
	int      m_nVerifyFlag = 0;
	int		 m_nChatRoomType = 0;
	int      m_nChatRoomNotify = 0;
	CStringA m_strWxid;
	CStringA m_strAlias;
	CStringA m_strNickName;
	CStringA m_strRemark;
	CStringA m_strEncryptUserName;
	CStringA m_strDomainList;
	CStringA m_strBigHeadImgUrl;
	CStringA m_strSmallHeadImgUrl;

	CStringA ToString()
	{
		CStringA strContact;

		CStringA strNickName = CUTF82Gbk(m_strNickName);
		CStringA strAlias = CUTF82Gbk(m_strAlias);
		CStringA strRemark = CUTF82Gbk(m_strRemark);
		strContact.Format("Wxid:%s, Alias:%s, NickName:%s, Remark:%s, BigHeadImgUrl:%s, SmallHeadImgUrl:%s, Type:%d", m_strWxid, strAlias, strNickName, strRemark, m_strBigHeadImgUrl, m_strSmallHeadImgUrl, m_nType);
		
		LOG("%s", strContact);

		return strContact;
	}
};


class CDbUtil : public Singleton<CDbUtil>
{
public:
	CDbUtil();

	//ִ��SQL
	BOOL ExcuteSql(void *pInstance, LPCSTR szSql, std::function<BOOL(void *)> *cb);

	//��ȡ�����б�(��db��ȡ)
	list<shared_ptr<CContactInfo>> GetContactList();

	//��ȡ���������¼(��db��ȡ)
	int GetChatRecord();

	//��ȡ��ǰ��¼�˺�wxid
	CStringA	GetLoginWxid();

	//��ϵ�˱��ַ
	void *GetContactInstance();

	//�����¼���ַ
	void *GetChatCRMsgInstance();
private:
	void *m_pDbMicroMsgInstance = NULL;			//MicroMsg���ݿ��ַ
};
#define pDbUtil (CDbUtil::GetInstance())