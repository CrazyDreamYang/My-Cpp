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
	//构造函数
	SpeechManager();
	void show_Menu();
	void exitSystem();
	//析构函数
	~SpeechManager();

	//初始化
	void initSpeech();

	//创建演讲者

	void createSpeaker();

	//开始演讲
	void startSpeech();

	//抽签
	void speechDraw();

	//比赛
	void speechContest();
	//显示比赛成绩
	void speechScore();

	//保存记录
	void saveRecord();

	//查看往届记录
	void loadRecord();
	//记录文件是否是非空

	bool fileIsEmpty;

	//往届记录
	map<int,vector<string>>m_Record;

	//查看往届记录
	void showRecord();

	//清空记录
	void clearRecord();
	

	//保存第一轮比赛的选手的容器
	vector<int>v1;

	//保存第一轮晋级的选手的容器
	vector<int>v2;
	//前三名选手编号容器
	vector<int>vVictory;
	//存放编号与对应选手的容器
	map<int, Speaker>m_Speaker;

	//存放比赛轮数
	int m_Index=1;
};
