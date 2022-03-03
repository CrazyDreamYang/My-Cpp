#include<iostream>
#include<ctime>
#include<map>
#include<string>
#include<set>
#include<fstream>

using namespace std;
//��ʼ���ַ����б�
void initialize_exclusion_set(set<string>&exs)
{
	static string _excluded_words[25] = {
	"the","and","but","that","them","are","been","can","a","could",
	"did","for","of","had","had","for","have"
	};
	exs.insert(_excluded_words, _excluded_words + 25);
}
//�Ӽ�����ж�ȡ�ļ�
void process_file(map<string,int> &word_count,const set<string> &exclude_set, ifstream &ifile)
{
	string word;
	if (! ifile)
	{
		cerr << "��ʧ��" << endl;
	}
	else
	{
		while (ifile >> word)//���ַ����ļ�����
		{
			if(exclude_set.count(word))//�ж��ַ��Ƿ����ų�������
			{
				continue;//���ų������У���ͳ�Ƴ��ִ���
			}
			word_count[word]++;
		}
	}

}

void user_query(const map<string, int>& word_map)
{
	string search_word;
	cout << "please enter a word to search: q to quit"<<'\n';
	cin >> search_word;
	while (search_word.size() && search_word != "q")
	{
		map<string, int>::const_iterator it;
		if ((it = word_map.find(search_word)) != word_map.end())
		{
			cout << "Found " << it->first
				<< "  occurs: " << it->second
				<< "  times. \n";
		}
		else cout << search_word << "\n" << " Another search ? (q to quit)" << endl;
		cin >> search_word;
	}
	

}
void display_word_count(const map<string, int>& word_map, ofstream &os)
{
	map<string, int>::const_iterator iter = word_map.begin(), end_it = word_map.end();
	while (iter != end_it)
	{
		os << iter->first << "(" << iter->second << ")" << endl;
		iter++;
	}
	os << endl;
}


int main()
{
	ofstream ofile("column_o.txt", ios_base::app);
	ifstream ifile("column.txt");
	
	if (!ifile || ! ofile) {
		cerr << "Unable to open file --bailing out!\n";
		return -1;
	}

	set<string> exculde_set;
	
	initialize_exclusion_set(exculde_set);

	map<string, int> word_count;
	process_file(word_count, exculde_set, ifile);
	user_query(word_count);
	display_word_count(word_count, ofile);

	////��׷�ӷ�ʽ����һ���ļ�,��д������
	//ofstream outfile("seq_data.txt", ios_base::app);
	//if (!outfile)
	//{
	//	cerr << "�򿪴���" << endl;
	//}
	//else
	//{
	//	outfile << "a" << "an" << "the" << "and" << "but" << endl;
	//		
	//}
	//int i = 0;
	//cout << i << endl;
	system("pause");
	return 0;
}
