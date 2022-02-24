#include<iostream>
#include"speechManager.h"
#include<ctime>
using namespace std;
//演讲比赛流程管理系统


int main()
{
	srand((unsigned int)time(NULL));
	SpeechManager sm;
	for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	{
		
		cout << "选手编号：" << it->first << "  姓名：" << it->second.m_Name << "  分数：" << it->second.m_Score[0] << endl;
	}
	
	int choice = 0;
	

	while(true)
	{
		sm.show_Menu();
		cin >> choice;
		switch (choice)
		{
		case 1://开始比赛
			sm.startSpeech();
			//sm.speechContest();
			break;
		case 2://查看往届记录
			sm.showRecord();
			break;
		case 3:;//清空比赛记录
			sm.clearRecord();
			break;
		case 0://退出系统
			sm.exitSystem();
			break;
		default:
			system("cls"); 
			break;
		}

	}

	/*ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	ofs << 'A' << endl;

	ofs.close();*/
	return 0;
}
