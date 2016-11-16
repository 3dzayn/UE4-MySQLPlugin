#pragma once

#include "../Public/DBBase.h"


#ifdef DBSUPPORT_PGSQL

using namespace std;

#include <libpq-fe.h>
#include <shapefil.h>



namespace DBBase
{
	struct  PGConnectionPtr :public IConnectionPtr
	{
		PGconn *pPtr;
	};

	class PGRecordSet :public IRecordSet
	{
	public:
		PGRecordSet();
		PGRecordSet(PGresult * result);
		virtual ~PGRecordSet(){}

		//��ü�¼��
		virtual unsigned int RecordCount();

		//�Ƿ���Ч
		virtual bool IsEOF();

		//�ƶ�����һ��¼
		virtual void MoveFirst();

		//�ƶ�����һ��¼
		virtual void MoveNext();

		//��ȡ��������
		virtual int	 GetIntegerValue(string fieldName);

		//��ȡ����������
		virtual __int64 GetLongLongValue(string fieldName);

		//��ȡ�ַ�����
		virtual string GetStringValue(string fieldName);

		//��ȡ��¼���ֶ���
		virtual int	GetFieldCount();

		//��ȡ�ֶ�����
		virtual string	GetFieldName(int idx);

		//�ر�һ����¼��
		virtual void Close();
	private:
		void init();
	private:
		//���ݿ��ѯ���
		PGresult * m_Data;

		//��ǰλ��;
		unsigned m_CurrentRecord;
	};

	class PGConnection : public IConnection
	{
	public:
		PGConnection();
		PGConnection(PGconn * pConn);
		~PGConnection();

		//�������ݿ�
		virtual bool Connect(string host,string dbname, string user, string password, string Encoding ="GBK", int port = 3306);

		//�Ͽ�����
		virtual bool DisConnect();

		//�Ƿ�����
		virtual bool IsOpen();

		//ִ��SQL���,�޷��ؽ��
		virtual bool Execute(string SQL);

		//ִ�в�ѯ��䣬���ؼ�¼��;
		virtual IRecordSet * Query(string SQL);

		//��ʼ����
		virtual void BeginTrans();

		//ִ������
		virtual void CommitTrans(); 

		//�ع�����
		virtual void RollBackTrans();

		//�������ݿ�����ʽ
		virtual int	SetClientEncoding(const char * encode);

		//������ݿ�����ָ�룻
		virtual IConnectionPtr *ConnectionPtr();

		//�ж����ݿ���ĳ�����Ƿ����
		virtual bool IsTableExist(string TableName);
	private:
		void init();
	private:
		PGconn *m_pConn;
		PGConnectionPtr* m_pPtr;
	};
};
#endif