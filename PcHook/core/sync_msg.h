#pragma once

class CSyncMsg : public Singleton<CSyncMsg>
{
public:
	//����Hook ͬ����Ϣ
	BOOL Start();

	//ͼƬ����(���)���Ϊ
	BOOL MMXor(CString strEncryptFileName, CString strSaveAsFileName);
};
#define pSyncMsg		(CSyncMsg::GetInstance())