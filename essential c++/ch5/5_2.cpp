#include<iostream>
#include<string>
#include<vector>

//生成两个字符堆栈
using namespace std;
typedef string elemType;

class Stack {
public:
	Stack(int capacity = 0) :_top(0) 
	{
		if (capacity)
		{
			_stack.reserve(capacity);//开辟内存
		}
	}
	virtual ~Stack() {};
	//virtual bool peek(int index, elemType&) = 0;//是否支持顶层元素访问

	virtual bool peek(int index, elemType&) { return false; }//子类中重新这个函数
	 bool pop(elemType&) ;//删除
	 bool push(const elemType&);//加入

	 int  size() const { return _stack.size(); }
	 int  top() const { return _top;}

	 bool empty() const { return !_top; }
	 bool full() const { return size() >= _stack.max_size(); }
	
	 void print(ostream & os) const;//打印

protected:
	vector<elemType> _stack;
	int _top;//存储的元素个数
};
bool Stack::push(const elemType& elem) 
{
	//判断队列是否满了
	if (full())
		return false;
	_stack.push_back(elem);
	++_top;
	return true;
}

bool Stack::pop(elemType& elem)//删除
{
	if (empty())
		return false;
	elem = _stack[--_top];
	_stack.pop_back();
	return true;
}

void Stack::print(ostream& os = cout) const
{
	vector<elemType>::const_reverse_iterator
		rit = _stack.rbegin(),
		rend = _stack.rend();

	os << "\n\t";
	while (rit != rend)
		os << *rit++ << "\n\t";
	os << endl;
}

ostream& operator<<(ostream& os, const Stack& rhs)
{
	rhs.print(); 
	return os;
}

class LIFO_Stack : public Stack {
public:
	LIFO_Stack(int capacity = 0) : Stack(capacity) {};//调用父类构造函数接口为自己赋值

	//virtual bool peek(int index, elemType& elem);

};

class Peekback_Stack : public Stack {
public:
	Peekback_Stack(int capacity = 0) : Stack(capacity){};
	
	virtual bool peek(int index, elemType& elem);
	
};

bool Peekback_Stack::peek(int index, elemType& elem) {
	if (empty())
		return false;

	if (index < 0 || index >= size())
		return false;

	elem = _stack[index];
	return true;
}

void peek(Stack& st, int index)
{
	cout << endl;
	string t;
	if (st.peek( index, t))
		cout << "peek: " << t;
	else cout << "peek failed!";
	cout << endl;
}


int main()
{
	LIFO_Stack st;
	string str;

	cout << "Please enter a series of strings.\n";

	while (cin >> str && !st.full())
		st.push(str);

	cout << endl << "About to call peek() with LIFO_Stack" << endl;
	peek(st, st.top() - 1);
	cout << st;

	Peekback_Stack pst;
	while (!st.empty()) {
		string t;
		if (st.pop(t))//删除，传入是引用，所以t才会被赋值
			pst.push(t);//插入
	}

	cout << "About to call peek() with Peekback_Stack" << endl;
	peek(pst, pst.top() - 1);
	cout << pst;

	system("pause");
	return 0;
}