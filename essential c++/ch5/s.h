#pragma once
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <typeinfo>

using namespace std;

class num_sequence {
public:
	typedef vector<unsigned int>::iterator iterator;

	virtual ~num_sequence() {};
	virtual num_sequence* clone() const = 0;

	unsigned int elem(int pos) const;
	bool is_elem(unsigned int) const;
	int  pos_elem(unsigned int) const;

	const char* what_am_i() const;
	static  int max_elems() { return _max_elems; }
	ostream& print(ostream& os = cout) const;

	int length()  const { return _length; }
	int beg_pos() const { return _beg_pos; }

	iterator begin() const
	{
		return _relems.begin() + _beg_pos - 1;
	}

	iterator end() const
	{
		return _relems.begin() + _beg_pos + _length;
	}

	void set_position(int pos);
	void set_length(int pos);

	bool operator ==(const num_sequence&) const;
	bool operator !=(const num_sequence&) const;

	const vector<unsigned int>* sequence() const
	{
		return &_relems;
	}

protected:
	// static const int    _max_elems = 1024;	
	// for compilers not supporting const static
	enum { _max_elems = 1024 };

	virtual void gen_elems(int pos) const = 0;//纯虚函数，在子类定义
	int _calc_pos(unsigned int elem) const;
	bool check_integrity(int pos, int size) const;

	num_sequence(int, int, vector<unsigned int>&);

	int _length;
	int _beg_pos;
	vector< unsigned int>& _relems;
};
inline bool num_sequence::
operator==(const num_sequence& rhs) const
{
	return (_beg_pos == rhs._beg_pos) &&
		(_length == rhs._length);
}

inline bool num_sequence::
operator !=(const num_sequence& rhs) const
{
	return !(*this == rhs);
}

inline void num_sequence::
set_position(int pos)
{
	if (pos <= 0 || pos > _max_elems) {
		cerr << "!! invalid position: " << pos
			<< " setting pos to default value of 1\n"
			<< "If inadequate, invoke set_position(pos)\n";
		pos = 1;
	}
	_beg_pos = pos;
}

inline void num_sequence::
set_length(int len)
{
	if (len <= 0 || len + _beg_pos - 1 > _max_elems) {
		cerr << "!! invalid length for this object: " << len
			<< " setting length to default value of 1\n"
			<< "If inadequate, invoke set_length(len)\n";
		len = 1;
	}
	_length = len;
}
//构造器
inline num_sequence::
num_sequence(int beg_pos, int len,
	vector< unsigned int>& re) : _relems(re)
{
	set_position(beg_pos);
	set_length(len);
}

inline unsigned int num_sequence::
elem(int pos) const
{
	return (!check_integrity(pos, _relems.size()))
		? 0 : _relems[pos - 1];
}
inline const char* num_sequence::
what_am_i() const
{
	return typeid(*this).name();
}

inline bool num_sequence::
check_integrity(int pos, int size) const
{
	bool status = true;

	if (pos <= 0 || pos > _max_elems) {
		cerr << "!! invalid position: " << pos
			<< " Cannot honor request\n";
		status = false;
	}
	else if (pos > size)
		gen_elems(pos);

	return status;
}



inline bool num_sequence::
is_elem(unsigned int elem) const
{
	return (!check_integrity(_beg_pos, _length))
		? false : binary_search(begin(), end(), elem);
}



