#include"speechManager.h"


//��ʵ��
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

	cout << "*******��ӭ�μ��ݽ�����**********" << endl;
	cout << "*******1.��ʼ�ݽ�����***********" << endl;

	cout << "*******2.�鿴�����¼***********" << endl;
	cout << "*******3.��ձ�����¼***********" << endl;
	cout << "*******0.�˳���������**********" << endl;
	cout << endl;
}

void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("puase");
	exit(0);

}

void SpeechManager::initSpeech()
{
	this -> v1.clear();
	this -> v2.clear();
	this -> vVictory.clear();
	this -> m_Speaker.clear();
	//��ʼ������������
	this->m_Index = 1;
	//��ʼ����¼����
	this->m_Record.clear();
}
//����12��ѡ��
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJIK";

	//��ÿ��ѡ���������
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
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
	cout << "��<<" << this->m_Index << ">>�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "������������������������������������" << endl;
	cout << "��ǩ���ݽ�˳������" << endl;

	if (this->m_Index == 1)
	{
		//��һ�ֱ���
		random_shuffle(v1.begin(),v1.end());//����˳��
		//���Ҳ��ǩ���
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//�ڶ��ֱ���
		random_shuffle(v2.begin(), v2.end());//����˳��
		//���Ҳ��ǩ���
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
	//��һ�ֱ�����ʼ


	//1.��ǩ
	this->speechDraw();

	//2.����
	this->speechContest();

	//3.��ʾ�������
	this->speechScore();

	//�ڶ��ֱ�����ʼ
	this->m_Index++;

	//1����ǩ

	this->speechDraw();

	//2������
	this->speechContest();

	//3����ʾ���
	this->speechScore();
	//4���������
	this->saveRecord();

	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();

	cout << "����������" << endl;
	system("pause");
	system("cls");
}


void SpeechManager::speechContest()
{
	cout << "��<<" << this->m_Index << ">>��"<<endl;
	//׼����ʱ���������С��ɼ�
	multimap<double, int, greater<double>>groupScore;
	int num = 0;//��¼��Ա����
	vector<int>v_Src;//����ѡ������

	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	//��������ѡ�ֽ��б���
	for (vector<int>::iterator it = v_Src.begin(); it!= v_Src.end(); it++)
	{ 
		num++;
		//�������������ί���
		deque<double>d;//ͷβɾ��Ч�ʸ���
		for(int i = 0;i < 10;i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			cout << score << " ";
			d.push_back(score);
		}
		cout << endl;
		sort(d.begin(), d.end(), greater<double>());//����
		d.pop_front();//ȥ����߷�
		d.pop_back();//ȥ����ͷ�


		double sum = accumulate(d.begin(),d.end(),0.0);

		double avg = sum / (double)d.size();//ƽ����

		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;//��ƽ���ִ洢
		groupScore.insert(make_pair(avg, *it));

		//ÿ����ȡ��ǰ����
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С���������:  " << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "��ţ�" << it->second << "  ������ " << this->m_Speaker[it->second].m_Name 
					<< " ���� " << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}

			//ȡ��ǰ����
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
	cout << "��" << this->m_Index << "�ֱ������!" << endl;
	system("pause");
	cout << endl;
}

void SpeechManager::speechScore()
{
	cout << "��" << this->m_Index << "�ֽ���ѡ����Ϣ����!" << endl;
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
		cout << "ѡ�ֱ�ţ�" << *it << "������" << m_Speaker[*it].m_Name
			<< "�÷֣�" << m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
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
	cout << "��¼�Ѿ�����" << endl;
	this->fileIsEmpty = false;
}

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;//���ļ��ж���һ���ַ�
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ�գ�" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	this->fileIsEmpty = false;

	ifs.putback(ch);//���ַ������ļ�

	string data;

	int index = 0;
	while (ifs>>data)//һ��һ�ж�ȡ
	{
		vector<string>v;

		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;//û���ҵ�����
			}
			string tmp = data.substr(start, pos - start);//��ȡ�ַ���

			v.push_back(tmp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}

	ifs.close();

	/*for(map<int, vector<string>>::iterator it=m_Record.begin(); it != m_Record.end();it++)
	{
		cout << it->first << " ��� " << it->second[0] << " ���� " << it->second[1] << endl;
	}*/
}

void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ��߲����ڣ�" << endl;
	}
	else 
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "��" << i + 1 << "��:" << "\n"
				"�ھ����: " << this->m_Record[i][0] << ",	�÷�	:" << this->m_Record[i][1] << "\n"
				"�Ǿ����: " << this->m_Record[i][2] << ",	�÷�	:" << this->m_Record[i][3] << "\n"
				"�������: " << this->m_Record[i][4] << ",	�÷�	:" << this->m_Record[i][5] << endl;
		}
	}
	
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord()
{
	cout << "�Ƿ�ȷ������ļ�?" << endl;
	cout << "1����" << endl;
	cout << "2����" << endl;

	int select = 0;

	cin >> select;
	if (select == 1)
	{
		//ȷ�����
		ofstream ofs("speech.csv", ios::trunc);//������´���
		ofs.close();

		this->initSpeech();

		this->createSpeaker();

		this->loadRecord();

		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}