
//�̳У�����쳲�������������
//�ڻ����н��������๲ͬ�����ݶ����壬����������Ĵ�����
//�û��۹�����������ڲ������ݵĳ�ʼ��
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include"s.h"
#include"f.h"

using namespace std;
ostream&
operator<<(ostream& os, const num_sequence& ns)
{
	return ns.print(os);
}


inline void
display(ostream& os, const num_sequence& ns,
	int pos, int elem_val)
{
	os << "The element at position " << pos
		<< " for the "
		<< ns.what_am_i()
		<< " sequence is " << elem_val << endl;
}

inline void
display(ostream& os, const num_sequence& ns, int pos)
{
	os << "The element at position "
		<< pos << " for the "
		<< ns.what_am_i() << " sequence is "
		<< ns.elem(pos) << endl;
}

int main()
{

	const int pos = 8;

	Fibonacci fib;
	display(cout, fib, pos);

	return 0;
}
