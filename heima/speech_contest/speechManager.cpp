#include"speechManager.h"


//空实现
SpeechManager::SpeechManager()
{
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
}

SpeechManager::~SpeechManager()
{

}

void SpeechManager::show_Menu()
{
	cout << "***********************" << endl;

	cout << "*******欢迎参加演讲比赛**********" << endl;
	cout << "*******1.开始演讲比赛***********" << endl;

	cout << "*******2.查看往届记录***********" << endl;
	cout << "*******3.清空比赛记录***********" << endl;
	cout << "*******0.退出比赛程序**********" << endl;
	cout << endl;
}

void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("puase");
	exit(0);

}

void SpeechManager::initSpeech()
{
	this -> v1.clear();
	this -> v2.clear();
	this -> vVictory.clear();
	this -> m_Speaker.clear();
	//初始化比赛轮数；
	this->m_Index = 1;
	//初始化记录容器
	this->m_Record.clear();
}
//创建12名选手
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJIK";

	//给每个选手添加名字
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		this->v1.push_back(i + 10001);
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

void SpeechManager::speechDraw()
{
	cout << "第<<" << this->m_Index << ">>轮比赛选手正在抽签" << endl;
	cout << "——————————————————" << endl;
	cout << "抽签后演讲顺序如下" << endl;

	if (this->m_Index == 1)
	{
		//第一轮比赛
		random_shuffle(v1.begin(),v1.end());//打乱顺序
		//输出也抽签结果
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//第二轮比赛
		random_shuffle(v2.begin(), v2.end());//打乱顺序
		//输出也抽签结果
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "-----------------" << endl;
	system("pause");
	cout << endl;
}

void SpeechManager::startSpeech()
{
	//第一轮比赛开始


	//1.抽签
	this->speechDraw();

	//2.比赛
	this->speechContest();

	//3.显示晋级结果
	this->speechScore();

	//第二轮比赛开始
	this->m_Index++;

	//1、抽签

	this->speechDraw();

	//2、比赛
	this->speechContest();

	//3、显示结果
	this->speechScore();
	//4、保存分数
	this->saveRecord();

	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();

	cout << "本届比赛完毕" << endl;
	system("pause");
	system("cls");
}


void SpeechManager::speechContest()
{
	cout << "第<<" << this->m_Index << ">>轮"<<endl;
	//准备临时容器，存放小组成绩
	multimap<double, int, greater<double>>groupScore;
	int num = 0;//记录人员个数
	vector<int>v_Src;//比赛选手容器

	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	//遍历所有选手进行比赛
	for (vector<int>::iterator it = v_Src.begin(); it!= v_Src.end(); it++)
	{ 
		num++;
		//用随机数进行评委打分
		deque<double>d;//头尾删除效率更高
		for(int i = 0;i < 10;i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			cout << score << " ";
			d.push_back(score);
		}
		cout << endl;
		sort(d.begin(), d.end(), greater<double>());//排序
		d.pop_front();//去掉最高分
		d.pop_back();//去掉最低分


		double sum = accumulate(d.begin(),d.end(),0.0);

		double avg = sum / (double)d.size();//平均分

		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;//将平均分存储
		groupScore.insert(make_pair(avg, *it));

		//每六人取出前三名
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次:  " << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号：" << it->second << "  姓名： " << this->m_Speaker[it->second].m_Name 
					<< " 分数 " << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}

			//取走前三名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end()&&count<3; it++,count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back(it->second);
				}
				else
				{
					vVictory.push_back(it->second);
				}
		
			}
			groupScore.clear();
		}
	}
	cout << "第" << this->m_Index << "轮比赛完毕!" << endl;
	system("pause");
	cout << endl;
}

void SpeechManager::speechScore()
{
	cout << "第" << this->m_Index << "轮晋级选手信息如下!" << endl;
	vector<int>v;
	if (this -> m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号：" << *it << "姓名：" << m_Speaker[*it].m_Name
			<< "得分：" << m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << ","
			<< m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "记录已经保存" << endl;
	this->fileIsEmpty = false;
}

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;//从文件中读走一个字符
	if (ifs.eof())
	{
		cout << "文件为空！" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	this->fileIsEmpty = false;

	ifs.putback(ch);//将字符读回文件

	string data;

	int index = 0;
	while (ifs>>data)//一行一行读取
	{
		vector<string>v;

		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;//没有找到逗号
			}
			string tmp = data.substr(start, pos - start);//截取字符串

			v.push_back(tmp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}

	ifs.close();

	/*for(map<int, vector<string>>::iterator it=m_Record.begin(); it != m_Record.end();it++)
	{
		cout << it->first << " 编号 " << it->second[0] << " 分数 " << it->second[1] << endl;
	}*/
}

void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件为空或者不存在！" << endl;
	}
	else 
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "第" << i + 1 << "届:" << "\n"
				"冠军编号: " << this->m_Record[i][0] << ",	得分	:" << this->m_Record[i][1] << "\n"
				"亚军编号: " << this->m_Record[i][2] << ",	得分	:" << this->m_Record[i][3] << "\n"
				"季军编号: " << this->m_Record[i][4] << ",	得分	:" << this->m_Record[i][5] << endl;
		}
	}
	
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord()
{
	cout << "是否确定清空文件?" << endl;
	cout << "1、是" << endl;
	cout << "2、否" << endl;

	int select = 0;

	cin >> select;
	if (select == 1)
	{
		//确认清空
		ofstream ofs("speech.csv", ios::trunc);//清空重新创建
		ofs.close();

		this->initSpeech();

		this->createSpeaker();

		this->loadRecord();

		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}