#pragma once

//�������ͺ�����ö��ָ�����̾��, ����dwOptionsĬ������Զ�̹رոþ��.
HANDLE FindHandle(ULONG pid, LPCTSTR szObjectType, LPCTSTR szObjectName, DWORD dwOptions = DUPLICATE_CLOSE_SOURCE);