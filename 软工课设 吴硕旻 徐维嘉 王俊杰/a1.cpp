#include<iostream>
#include<string>
#include <sstream>
#include<fstream>
#include<ctime>
using namespace std;
const int n=1000000;
int i = 0, k,k1;
string st, tem, tem2, tem3;
time_t start_time,end_time;
string source[1000001];
const int maxn=1050000;
const int maxt=100000000;
int hashmap[maxn],p[maxt][2],top;//hashmap biaotou p memory
ifstream infile("1.fa");
ifstream finfile("2.fa");
//ifstream infile("test.fa");


int value(char ch) 
{
	switch (ch)
	{
	case 'A':return 0;
	case 'T':return 1;
	case 'C':return 2;
	case 'G':return 3;
	default:
		return 4;
	}

}

int fun(string stt)
{
	int num = 0;
	for (int j = 0; j < stt.length(); j++)
	{
		num = num << 2;
		switch (stt[j])
		{
		case 'A':num += 0; break;
		case 'T':num += 1; break;
		case 'C':num += 2; break;
		case 'G':num += 3; break;
		default:
			break;
		}
	}
	return num;
}

void insert(int hash,int row)
{
	


	if (row!=p[hashmap[hash]][0]) 
	{
		top++;
		p[top][0]=row;
		p[top][1]=hashmap[hash];
		hashmap[hash]=top;
	}
}
void read()
{
	
	i=0;

	cout<<"开始读取"<<endl;

	start_time = time(NULL);

	while (infile >> st)
	{
		if (st[0] != 'A' && st[0] != 'T' && st[0] != 'C' && st[0] != 'G') continue;
		i++;
		source[i] = st;
		if (i % 10000 == 0) cout << i/10000<<"%......";
	}

	infile.close();
	while (finfile >> st)
	{
		if (st[0] != 'A' && st[0] != 'T' && st[0] != 'C' && st[0] != 'G') continue;
		i++;
		source[i] = st;
		if (i % 10000 == 0) cout << i/10000<<"%......";
	}
	finfile.close();
	cout<<endl<<"读取完毕"<<endl;
	end_time = time(NULL);
	cout<<"耗时"<<end_time-start_time<<"s"<<endl;
}
void makehash()
{

	for (int j=0;j<=maxn-1;j++) hashmap[j]=-1;
	for (int j=0;j<=maxt-1;j++) {p[j][0]=-1; p[j][1]=-1;}
	top=0;//initialize
	cout<<"输入k值:";
	cin >> k;
	start_time = time(NULL);
	cout<<"开始建立kmer索引表"<<endl;
	k1=k;
	if (k>10) k=10;
	for (i=1;i<=n;i++)
	{
		st = source[i];
		if (i % 10000 == 0) cout << i/10000<<"%......";
		string stt = st.substr(0, k);
		int num = fun(stt);

		for (int j = 0; j <= st.length() - k ; j++)
		{
			insert(num,i);
			int jw=2*(k-1);
			num = ((num - (value(st[j]) << jw))<<2) + value(st[j + k]);

		}
	}
	cout<<i-1<<"条数据"<<endl;
	cout<<endl<<"索引表建立完毕"<<endl;

	end_time = time(NULL);
	cout<<"耗时"<<end_time-start_time<<"s"<<endl;
}
void check()
{
	while (true)
	{
		cout<<"请输入要查询的k-mer:";
		cin >> st;
		if (st=="EXIT") break;
		if (st.length()!=k1) continue;
		bool ff=false;
		for (int i=0;i<=st.length()-1;i++)
			if (st[i] != 'A' && st[i] != 'T' && st[i] != 'C' && st[i] != 'G') {ff=true; break;}
		if (ff) continue;
		start_time = time(NULL);
		cout<<"查询的k-mer行号与位置如下:"<<endl;
		int h = fun(st.substr(0,k));
		int jump=hashmap[h];
		while (jump!=-1)
		{
			int row=p[jump][0];
			bool flag=true;
			int found=0;
			while (true)
			{
				int t = source[row].find(st, found);
				if (t == source[row].npos) break;
				if (flag==true) {cout<<row<<" { "; flag=false;}
				cout << t + 1 << ' ';
				found = t + 1;

			}
			if (flag==false) cout<<"}\n";

			jump=p[jump][1];
		}

		end_time = time(NULL);
		cout<<"查找与输出耗时"<<end_time-start_time<<"s"<<endl;
	}
}
int main()
{
	read();
	while (true)
	{
		makehash();
		check();
	}
	
}