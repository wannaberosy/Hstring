#pragma once
#include<iostream>
#include<cstdlib>

class Hstring
{
public:
	inline static char nochar{ -1 };
	Hstring();
	~Hstring();
	Hstring(const char* str);//
	Hstring(const int val);
	Hstring(const Hstring& str);//
	const char* getHstring()const { return cstr; }
	Hstring& operator=(const Hstring& str);
	Hstring& operator=(const int& value);
	Hstring& operator+(const Hstring& str)const;
	Hstring& operator+=(const Hstring& str);


	Hstring& operator<<(const Hstring& str);
	const char& operator[](const unsigned short idx)const;
	Hstring operator()(const int start, const int len)const;
	bool ResetBufferSize(unsigned short _size);
	unsigned short GetBufferSize();
	unsigned short GetStringSize();
	unsigned short length;//�ַ����ĳ���
private:
	unsigned short memLen;//�ַ����ڴ泤��
	unsigned short getLength(const char* str)const;//��ȡ�ַ�������
	void copyHstring(const char* dest, const char* scoure);//�����ַ���
	char* cstr;
	int BufferSize{ 100 };//����������
};
std::ostream& operator<<(std::ostream& out, const Hstring& str);
std::istream& operator>>(std::istream& in, Hstring& str);
