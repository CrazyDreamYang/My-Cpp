
//继承，生成斐波那契数列子类
//在基类中将所有子类共同的内容都定义，大大减少子类的代码量
//用积累构造器完成其内部的数据的初始化
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
