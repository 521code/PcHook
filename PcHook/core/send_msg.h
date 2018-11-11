#pragma once

struct CMMString
{
	const wchar_t	*m_szBuf = NULL;
	DWORD			m_dwLen = 0;
	DWORD			m_dwMaxLen = 0;
	DWORD			m_padding[2] = { 0 };
};

class CSendMsg : public Singleton<CSendMsg>
{
public:
	CSendMsg();

	//����������Ϣ
	void SendTextMsg(wstring strToWxid, wstring strText);

	//����ͼƬ��Ϣ
	void SendImageMsg(wstring strToWxid, wstring strImagePath);

	//�����ļ�
	void SendFileMsg(wstring strToWxid, wstring strFilePath);
private:

};
#define pSendMsg	(CSendMsg::GetInstance())