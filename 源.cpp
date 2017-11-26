#include<iostream>
#include<string>
#include<unordered_map>
#include <sstream>
#include<fstream>
#include<list>
using namespace std;
const int n=1000000;
int i = 0, k;
string st, tem, tem2, tem3;

//list<int>* blablabla = new list<int>[1024];

//list<int>::iterator v;
//list<int> a[100];
string source[1000001];
int map[1000001][101];
ifstream infile("1.fa");
ifstream finfile("2.fa");
//ifstream infile("test.fa");
//void int2str(const int &int_temp, string &string_temp)
//{
//	stringstream stream;
//	stream << int_temp;
//	string_temp = stream.str();   //此处也可以用 stream>>string_temp  
//}
//int tran(string st)
//{
//	int ten = 1, ans = 0, o = 0;
//	for (int i = st.length() - 1; i >= 0; i--)
//	{
//		if (st[i] == 'A') o = 0; else
//			if (st[i] == 'T') o = 1; else
//				if (st[i] == 'C') o = 2; else
//					if (st[i] == 'G') o = 3;
//		ans = ans + ten*o;
//		ten = ten * 10;
//	}
//	return ans;
//}

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


int main()
{

	cin >> k;
	//n=1000000;
	i=0;
	while (infile >> st)
	{
		if (st[0] != 'A' && st[0] != 'T' && st[0] != 'C' && st[0] != 'G') continue;
		i++;
		source[i] = st;
		if (i % 10000 == 0) cout << i;
	}
	while (finfile >> st)
	{
	if (st[0] != 'A' && st[0] != 'T' && st[0] != 'C' && st[0] != 'G') continue;
	i++;
	source[i] = st;
	if (i % 10000 == 0) cout << i;
	}
	if (k<=10)
	{
		for (i=1;i<=n;i++)
		{
			st = source[i];
			if (i % 10000 == 0) cout << i;
			string stt = st.substr(0, k);
			int num = fun(stt);

			for (int j = 0; j <= st.length() - k ; j++)
			{
				/*int2str(i,tem);
				int2str(j+1,tem2);
				int2str(j+k+1,tem3);*/
				//int h=tran(st.substr(j,k));
				/*int num = 0;
				for (int i = 0; i < stt.length() - 1; i++)
				{
				switch (stt[i])
				{
				case 'A':
				case 'T':
				case 'C':
				case 'G':
				default:
				break;
				}
				}*/

				//int h = tran(stt);
				/*list<int> &l = blablabla[num];
				if (l.empty()) l.push_back(i); else
				if (i!=*(--l.end())) l.push_back(i);*/

				map[i][j]=num;
				/*l.push_back(i);

				*/
				//umap[st.substr(j,k)]=umap[st.substr(j,k)]+tem+" {"+tem2+","+tem3+"}";
				//stt.erase(stt.begin());
				num = ((num - (value(st[j]) << 8))<<2) + value(st[j + k]);
				/*stt = stt + st[j + k];*/

			}

		}
		infile.close();

		cout << i;
		cout << endl;



		while (true)
		{
			cin >> st;
			int h = fun(st);

			//int oo = 0;
			//for (v = blablabla[h].begin(); v != blablabla[h].end(); ++v)
			//{

			//	int found = 0;
			//	/*cout << *v << endl;
			//	oo++;
			//	if (oo % 3 == 0)
			//	{
			//	oo = 0;
			//	cout << '\n';
			//	}*/
			//	cout << *v << " { ";
			//	while (true)
			//	{
			//		int t = source[*v].find(st, found);
			//		if (t == source[*v].npos) break;
			//		cout << t + 1 << ' ';
			//		found = t + 1;
			//	}
			//	cout << "}\n";
			//}
			for (i=1;i<=n;i++)
			{
				bool flag=true;
				for (int j=0;j<=100-k;j++)
				{
					if (map[i][j]==h)
					{
						if (flag==true) {cout<<i<<" { "; flag=false;}
						cout<<j+1<<' ';
					}
				}
				if (flag==false) cout<<"}\n";
			}
			//cout<<umap[st];
		}
	}
	else
	{
		while (true)
		{
			cin>>st;
			for (i=1;i<=n;i++)
			{
				bool flag=true;
				int found=0;
				while (true)
				{
					int t = source[i].find(st, found);
					if (t == source[i].npos) break;
					if (flag==true) {cout<<i<<" { "; flag=false;}
					cout << t + 1 << ' ';
					found = t + 1;

				}
				if (flag==false) cout<<"}\n";
			}
		}
	}
}