#include<iostream>
#include"speechManager.h"
#include<ctime>
using namespace std;
//�ݽ��������̹���ϵͳ


int main()
{
	srand((unsigned int)time(NULL));
	SpeechManager sm;
	for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	{
		
		cout << "ѡ�ֱ�ţ�" << it->first << "  ������" << it->second.m_Name << "  ������" << it->second.m_Score[0] << endl;
	}
	
	int choice = 0;
	

	while(true)
	{
		sm.show_Menu();
		cin >> choice;
		switch (choice)
		{
		case 1://��ʼ����
			sm.startSpeech();
			//sm.speechContest();
			break;
		case 2://�鿴�����¼
			sm.showRecord();
			break;
		case 3:;//��ձ�����¼
			sm.clearRecord();
			break;
		case 0://�˳�ϵͳ
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
