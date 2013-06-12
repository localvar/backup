////////////////////////////////////////////////////////////////////////////////
// ��дini�ļ�, ����Section����, ��������Key����. ���ͨ��CIniFile������������
// Section���ܻ��д���, ��Ϊ���ܱ�֤���ײ���������һ��. ��ʱӦ���ö��Section,
// �ҵ���Ҫ��Section��, �ٲ�����. ÿ��Key��Value���ڲ������ַ�����ʾ, ���Value
// ����ԼΪ2000, һ�����㹻ʹ����. ���ڳ�����Value, �ڲ�ʵ����ֱ�ӽضϵ�.
// Ҫע��binary���͵�Value, �ڲ�ת��ʱ���͵ĺ�����, һ���ֽڻ��������ַ�.

#pragma once

////////////////////////////////////////////////////////////////////////////////

class CIniKey
{
protected:
	TCHAR m_szName[16];
	TCHAR m_szValue[16];
	LPTSTR m_pValue;

public:
	explicit CIniKey( LPCTSTR szName );
	~CIniKey();

	LPCTSTR GetName();

	LPCTSTR GetValueString();
	int GetValueInt();
	bool GetValueBool();
	void GetValueBinary( BYTE* bin, size_t* pLen );

	void SetValueString( LPCTSTR str );
	void SetValueInt( int n );
	void SetValueBool( bool b );
	void SetValueBinary( const BYTE* bin, size_t len );
};

////////////////////////////////////////////////////////////////////////////////

class CIniSection
{
protected:
	TCHAR m_szName[16];
	CIniKey** m_arrKey;
	size_t m_capacity;

protected:
	void EnsureCapacity( size_t capacity );
	CIniKey* AddKey( LPCTSTR szKey );

public:
	explicit CIniSection( LPCTSTR szName );
	~CIniSection();

	LPCTSTR GetName();

	CIniKey* FindKey( LPCTSTR szKey );
	CIniKey* GetKey( LPCTSTR szKey );
	void RemoveKey( LPCTSTR szKey );

	size_t GetFirstKeyPosition();
	CIniKey* GetNextKey( size_t& pos );

	LPCTSTR GetValueString( LPCTSTR szKey, LPCTSTR szDflt );
	int GetValueInt( LPCTSTR szKey, int nDflt );
	bool GetValueBool( LPCTSTR szKey, bool bDflt );
	void GetValueBinary( LPCTSTR szKey, BYTE* bin, size_t* pLen );

	void SetValueString( LPCTSTR szKey, LPCTSTR str );
	void SetValueInt( LPCTSTR szKey, int n );
	void SetValueBool( LPCTSTR szKey, bool b );
	void SetValueBinary( LPCTSTR szKey, const BYTE* bin, size_t len );
};

////////////////////////////////////////////////////////////////////////////////

class CIniFile
{
protected:
	CIniSection** m_arrSection;
	size_t m_capacity;

protected:
	LPTSTR GetNextLine( FILE* fp, LPTSTR buf, int size );
	void EnsureCapacity( size_t capacity );

public:
	CIniFile();
	~CIniFile();
	bool Open( LPCTSTR szPath );
	bool OpenDefault();
	bool Save( LPCTSTR szPath );
	bool SaveToDefault();
	void Clear();

	CIniSection* FindSection( LPCTSTR szSctn );
	CIniSection* AddSection( LPCTSTR szSctn );
	CIniSection* GetSection( LPCTSTR szSctn );
	void RemoveSection( LPCTSTR szSctn );
	void RemoveSection( CIniSection* pSctn );

	size_t GetFirstSectionPosition();
	CIniSection* GetNextSection( size_t& pos );

	CIniKey* FindKey( LPCTSTR szSctn, LPCTSTR szKey );
	CIniKey* GetKey( LPCTSTR szSctn, LPCTSTR szKey );
	void RemoveKey( LPCTSTR szSctn, LPCTSTR szKey );

	LPCTSTR GetValueString( LPCTSTR szSctn, LPCTSTR szKey, LPCTSTR szDflt );
	int GetValueInt( LPCTSTR szSctn, LPCTSTR szKey, int nDflt );
	bool GetValueBool( LPCTSTR szSctn, LPCTSTR szKey, bool bDflt );
	void GetValueBinary( LPCTSTR szSctn, LPCTSTR szKey, BYTE* bin, size_t* pLen );

	void SetValueString( LPCTSTR szSctn, LPCTSTR szKey, LPCTSTR str );
	void SetValueInt( LPCTSTR szSctn, LPCTSTR szKey, int n );
	void SetValueBool( LPCTSTR szSctn, LPCTSTR szKey, bool b );
	void SetValueBinary( LPCTSTR szSctn, LPCTSTR szKey, const BYTE* bin, size_t len );
};

////////////////////////////////////////////////////////////////////////////////