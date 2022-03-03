#include<iostream>
#include<string>
#include<string>
#include<map>
#include<cstdlib>

using namespace std;

//4.4
class UserProfile 
{
public:

	enum uLevel {Beginner,Inteediate,Advanced,Guru};
	UserProfile(string login, uLevel = Beginner);
	UserProfile();

	bool operator == (const UserProfile&);

	bool operator!=(const UserProfile& rhs);
	
	//读数据,返回的值为不可变
	string login() const { return _login; }
	string user_name() const { return _user_name; }
	int login_count() const { return _times_logged; }

	int guess_count() const { return _guesses; }

	int guess_correct() const { return _correct_guesses; }
	double guess_average() const { return _guesses != 0.0 ? double(_correct_guesses) / double(_guesses) * 100 : 0.0; }
	string level() const;

	//写数据
	void reset_login(const string& val)
	{
		_login=val;
	}

	void user_name(const string& val) { _user_name = val; }

	void reset_level(const string&);
	void reset_level(uLevel newlevel) { _user_level = newlevel; }

	void reset_login_count(int val) { _times_logged = val; }
	void reset_guess_count(int val) { _guesses = val; }
	void reset_guess_correct(int val) { _correct_guesses = val; }

	//追加数据
	void bump_login_count(int cnt = 1) { _times_logged += cnt; }
	void bump_guess_count(int cnt = 1) { _guesses += cnt; }
	void bump_guess_correct(int cnt=1) { _correct_guesses += cnt; }

private:

	string _user_name;//用户名称
	string _login;//登录id
	int _times_logged;//登录次数
	int _guesses;//猜的次数
	int _correct_guesses;//准确次数
	uLevel _user_level;//用户等级
	
	static map<string, uLevel>_level_map;
	static void init_level_map();
	static string guest_login();
};

////返回平均猜对次数
//inline double UserProfile::guess_average() const
//{
//	return _guesses ? double{ _correct_guesses } / double(_guesses) * 100.0 : 0.0;
//}

//构造函数
inline UserProfile::UserProfile(string login, uLevel level)
	:_login(login), _user_level(level),
	_times_logged(1), _guesses(0), _correct_guesses(0) {}

inline UserProfile::UserProfile()
	: _login("guest"), _user_level(Beginner),
	_times_logged(1), _guesses(0), _correct_guesses(0) 
{
	static int id = 0;
	++id;
	/*char buffer[16];
	_itoa(id++, buffer, 10);*/

	_login += to_string(id);//加入独一无二的id
}

//等号运算符重载
inline bool UserProfile::operator==(const UserProfile& rhs)
{
	if (_login == rhs._login && _user_name == rhs._user_name)
		return true;
	return false;
}
//不等号运算符重载

inline bool UserProfile::operator!=(const UserProfile& rhs) { return !(*this == rhs); }

//返回用户等级的字符
inline string UserProfile::level() const {
	static string _level_table[] = { "Beginner","Inteediate","Advanced","Guru" };
	return _level_table[_user_level];
}

//重载<<运算符
ostream& operator<<(ostream& os, const UserProfile& rhs)
{
	os << rhs.login() << ' '
		<< rhs.level() << ' '
		<< rhs.login_count() << ' '
		<< rhs.guess_count() << ' '
		<< rhs.guess_correct() << ' '
		<< rhs.guess_average() << endl;
	return os;
}

//
map<string, UserProfile::uLevel>UserProfile::_level_map;

//一个索引的map
void UserProfile::init_level_map() {
	_level_map["Beginner"] = Beginner;
	_level_map["Inteediate"] = Inteediate;

	_level_map["Advanced"] = Advanced;
	_level_map["Guru"] = Guru;

}

inline void UserProfile::reset_level(const string& level)
{
	map<string, UserProfile::uLevel>::iterator it;
	if (_level_map.empty())
		init_level_map();

	_user_level = ((it = _level_map.find(level)) != _level_map.end()) ? it->second : Beginner;
}

istream& operator>>(istream& is, UserProfile& rhs)
{ // yes, this assumes the input is valid ...
	string login, level;
	is >> login >> level;

	int lcount, gcount, gcorrect;
	is >> lcount >> gcount >> gcorrect;

	rhs.reset_login(login);
	rhs.reset_level(level);

	rhs.reset_login_count(lcount);
	rhs.reset_guess_count(gcount);
	rhs.reset_guess_correct(gcorrect);

	return is;
}

int main()
{
	UserProfile anon;
	cout << anon;

	UserProfile anon_too;
	cout << anon_too;

	UserProfile anna("AnnaL", UserProfile::Guru);
	cout << anna;

	//追加数据
	anna.bump_guess_count(27);//猜的次数
	anna.bump_guess_correct(25);//猜的准确次数
	anna.bump_login_count();//猜的次数计数

	cout << anna;

	cout << "OK: enter user profile data by hand to see if we can read it\n";
	cin >> anon;//重置数据
	cout << anon;
	system("pause");
	return 0;
}
