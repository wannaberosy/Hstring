#include "Hstring.h"

Hstring::Hstring()
{
	memLen = BufferSize;
	length = 1;
	cstr = new char[memLen] {};
}

Hstring::~Hstring()
{
	if (!cstr)delete[] cstr;
}

Hstring::Hstring(const char* str):Hstring()
{
	copyHstring(cstr, str);
}

Hstring::Hstring(const int val)
{
	int temp = val;
	int cnt{};
	while (temp)temp /= 10, cnt++;
	length = cnt + 1;
	_itoa_s(val, this->cstr, memLen,10);
}
Hstring::Hstring(const Hstring& str) :Hstring()
{
	copyHstring(cstr, str.cstr);
}

Hstring& Hstring::operator=(const Hstring& str)
{
	copyHstring(cstr, str.cstr);
	return *this;
}

Hstring& Hstring::operator=(const int& value)
{
	_itoa_s(value, this->cstr, memLen, 10);
	return *this;
}

Hstring& Hstring::operator+(const Hstring& str)const
{
	Hstring temp{};
	int len = getLength(str.cstr);
	len = length + len - 1;
	memcpy(temp.cstr, cstr, length);
	memcpy(temp.cstr + length - 1, str.cstr, len - length + 1);
	temp.length = len;
	temp.ResetBufferSize(len);
	return temp;

}
Hstring& Hstring::operator+=(const Hstring& str)
{
	return *this;
}

Hstring& Hstring::operator<<(const Hstring& str)
{
	
	int len = getLength(str.cstr);
	len = len +length  - 1;
	if (len > memLen)
	{
		char* oldstr = cstr;
		cstr = new char[len];//重新分配内存
		memLen = len;//修正内存的长度
		memcpy(cstr, oldstr, length);
		delete[] oldstr;//删除内存
	}
	memcpy(cstr + length - 1, str.cstr, len - length + 1);
	length = len;//字符串长度修正
	return *this;

}

void Hstring::copyHstring(const char* dest, const char* scoure)
{
	unsigned short len = getLength(scoure);
	if (len > memLen)
	{
		delete[] cstr;
		cstr = new char[len];//重新分配内存
		memLen = len;//修改当前内存大小
	}
	memcpy(cstr, scoure, len);
	length = len;//字符串长度修正
}
const char& Hstring::operator[](const unsigned short idx)const
{
	if (idx < length)
		return cstr[idx];
	return Hstring::nochar;
}

Hstring Hstring::operator()(const int start, const int len) const
{
	if (start >= 0)
	{
		if (start > length - 2)
		{
			return Hstring("");
		}
		else
		{
			unsigned _len = start + len > length - 1 ? length - start - 1 : len;
			char* newstr = new char[_len + 1];
			memcpy(newstr, cstr, _len + 1);
			newstr[_len] = 0;
			return Hstring(newstr);
		}
	}
	else if (start < 0)
	{
		std::cout << "WRONG INPUT!";
	}
	return Hstring("");

}
bool Hstring::ResetBufferSize(unsigned short _size)
{
	if (_size > 0)
	{
		BufferSize = _size;
		return true;
	}
	return false;
}


unsigned short Hstring::getLength(const char* str)const
{
	int len{};
	while (str[len++]);
	return len;
}

unsigned short Hstring::GetBufferSize()
{
	return BufferSize;
}
unsigned short Hstring::GetStringSize()
{
	return length;
}
std::ostream& operator<<(std::ostream& out, const Hstring& str)
{
	out << str.getHstring();
	return out;
}

std::istream& operator>>(std::istream& in, Hstring& str)
{
	int tempBufferSize = str.GetBufferSize();
	char* _sRead = new char[tempBufferSize] {};
	in >> _sRead;
	str = _sRead;
	delete[] _sRead;
	return in;
}