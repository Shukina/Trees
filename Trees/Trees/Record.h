
#ifndef _RECORD_H 
#define _RECORD_H

#include <iostream>


using namespace std;

typedef double Key;

class Record 
{
public:
	Key key;
	int value;
public:
	Record()
	{
		key = NULL;
		value = NULL;//0
	}

	Record(Record& m) 
	{
		key = m.GetKey();
		value = m.GetValue();
	}

	Record(  Key _key ,int _val) 
	{
		key = _key;
		value = _val;
	}

	Key GetKey() const
	{
		return key; 
	}

	int GetValue(void) const
	{
		return value; 
	}

	void SetKey(Key _key)
	{
		key = _key;
	}

	void SetValue(int _value)
	{
		value = _value;
	}

	//string Refresh(string s)//заглавные буквы переводятся в прописные
	//{
	//	char c = s[0];
	//	char* word = new char[30];
	//	int i = 0, j = 0;
	//	while (s[i] != '\0'&& isalpha(s[i]))
	//	{
	//		word[i] = tolower(s[i]);
	//		i++;
	//	}
	//	word[i] = '\0';
	//	return word;
	//}

	Record operator++(int)
	{
		value++;
		return *this;
	}

	Record& operator=(const Record& m)
	{
		if (this == &m) {
			return *this;
		}
		key = m.GetKey();
		value = m.GetValue();
		return *this;
	}

	bool operator==(const Record &rec)
	{
		return key == rec.key; 
	}

	friend ostream& operator << (ostream &os,Record &w)
	{
		os << w.key;
		cout << " : " << w.value;
		return os;
	}
};
#endif