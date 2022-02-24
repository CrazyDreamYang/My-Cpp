#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<fstream>
#include<string>
#include"speaker.h"
using namespace std;

class SpeechManager
{
public:
	//���캯��
	SpeechManager();
	void show_Menu();
	void exitSystem();
	//��������
	~SpeechManager();

	//��ʼ��
	void initSpeech();

	//�����ݽ���

	void createSpeaker();

	//��ʼ�ݽ�
	void startSpeech();

	//��ǩ
	void speechDraw();

	//����
	void speechContest();
	//��ʾ�����ɼ�
	void speechScore();

	//�����¼
	void saveRecord();

	//�鿴�����¼
	void loadRecord();
	//��¼�ļ��Ƿ��Ƿǿ�

	bool fileIsEmpty;

	//�����¼
	map<int,vector<string>>m_Record;

	//�鿴�����¼
	void showRecord();

	//��ռ�¼
	void clearRecord();
	

	//�����һ�ֱ�����ѡ�ֵ�����
	vector<int>v1;

	//�����һ�ֽ�����ѡ�ֵ�����
	vector<int>v2;
	//ǰ����ѡ�ֱ������
	vector<int>vVictory;
	//��ű�����Ӧѡ�ֵ�����
	map<int, Speaker>m_Speaker;

	//��ű�������
	int m_Index=1;
};
