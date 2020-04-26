#include "Dijkstra.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

/**
 * You should implement the methods:`readFromFile`,`run1`and`run2` here.
 */
void DijkstraProject2::readFromFile(const char *inputfile)
{
	std::cout << "readFromFile: " << inputfile << std::endl;
	//TODO
	//freopen(inputfile, "r", stdin);
	string x;
	cin >> x;
	if(x.length()<3)
	cin>>x;

	getNM(x);
	//cin >> n >> m;
	side = new int *[n];
	for (int i = 0; i < n; i++)
	{
		side[i] = new int[n];
		for (int j = 0; j < n; j++)
			side[i][j] = 0;
	}
	dist = new int[n];
	for (int i = 0; i < n; i++)
		dist[i] = 0;
	flag = new int[n];
	for (int i = 0; i < n; i++)
		flag[i] = 0;
	pre = new vector<int>[n];

	for (int i = 0; i < m; i++)
	{
		string x;
		cin >> x;
		getSide(x);
	}
	if(feof(stdin)) read=false;
}
void DijkstraProject2::getNM(string x)
{
	int t = 0;
	for (t = 0; t < x.size(); t++)
	{
		if (x[t] == ',')
			break;
	}
	n = s_int(x.substr(0, t));
	m = s_int(x.substr(t + 1, x.size() - t - 1));
}
void DijkstraProject2::getSide(string x)
{
	int p = 0, q = 0;
	int u, v, w;
	for (int i = 0; i < x.size(); i++)
	{
		if (x[i] == ',')
		{
			if (p == 0)
				p = i;
			else
			{
				q = i;
				break;
			}
		}
	}
	u = s_int(x.substr(0, p));
	v = s_int(x.substr(p + 1, q - p - 1));
	w = s_int(x.substr(q + 1, x.size() - q - 1));
	if (w > maxside)
		maxside = w;
	side[u][v] = w; //记录边
	side[v][u] = -w;
}
int DijkstraProject2::s_int(string x)
{
	int ans = 0;
	for (int i = 0; i < x.size(); i++)
	{
		ans = ans * 10 + (x[i] - '0');
	}
	return ans;
}
void DijkstraProject2::run1(const char *outputFile)
{
	//freopen(outputFile, "w", stdout);
	updateDist1(0);
	vector<int> a;
	a.push_back(n - 1);
	getResult1(n - 1, a);
	saveResult1(outputFile);
	//TODO
	std::cout << "Save result to file:" << outputFile << std::endl;
}
void DijkstraProject2::updateDist1(int x)
{
	flag[x] = 1;
	//判断flag是否为0，为0则比较dist
	//小于则改变dist及pre（注意清零）pre[y].clear()
	//等于则增加pre[y].push_back(x)
	for (int i = 0; i < n; i++)
	{
		if (flag[i])
			continue; //i已经被接上就返回
		int w = side[x][i];
		if (w <= 0)
			continue; //没有这条边就返回
		if (!dist[i] || dist[x] + w < dist[i])
		{
			pre[i].clear();
			pre[i].push_back(x);
			dist[i] = dist[x] + w;
		}//小于则改变dist及pre（注意清零）pre[y].clear()
		else if (dist[x] + w == dist[i])
			pre[i].push_back(x);//等于则增加pre[y].push_back(x)
		else
			continue;
	}
	int min = -1;
	int t = -1;
	for (int i = 0; i < n; i++)
	{
		if ((min == -1 || dist[i] < min) && !flag[i] && !pre[i].empty())
		{
			min = dist[i];
			t = i;
		}
	}//找出最近的顶点
	if (t >= 0)
		updateDist1(t);
	else
		return;
}
void DijkstraProject2::getResult1(int x, vector<int> a)
{
	//从pre[n-1]开始，获取最短路径并写入文件
	//考虑多条路径问题，递归
	if (x == 0)
	{
		path.push_back(a);
		return;
	}//到达顶点0，结束
	for (int i = 0; i < pre[x].size(); i++)
	{
		vector<int> b = a;
		int y = pre[x][i];
		b.push_back(y);
		getResult1(y, b);
	}
}
void DijkstraProject2::saveResult1(const char *outputFile)
{
	freopen(outputFile, "a", stdout);

	cout << dist[n - 1] << '\n'
		 << path.size() << '\n';
	for (int i = 0; i < path.size(); i++)
	{
		vector<int>::iterator it;
		it = path[i].end();
		it = it - 1;
		for (it; it != path[i].begin(); it--)
		{
			cout << *it << ",";
		}
		cout << *it << '\n';
	}//倒序写入
	cout << '\n';
	fclose(stdout);
	freopen("CON", "w", stdout);
}
void DijkstraProject2::run2(const char *outputFile)
{
	//TODO
	for (int i = 0; i < n; i++)
	{
		dist[i] = 0;
		flag[i] = 0;
		pre[i].clear();
	}
	path.clear();

	updateDist2(0);
	vector<int> a;
	a.push_back(n - 1);
	getResult2(n - 1, a, maxside + 2, 0); //单调递增
	int x = dist[n - 1];

	for (int i = 0; i < n; i++)
	{
		dist[i] = 0;
		flag[i] = 0;
		pre[i].clear();
	}
	path2.clear();
	reverseGraph();
	updateDist2(n - 1);
	int y = dist[0];
	vector<int> b;
	b.push_back(0);
	getResult2(0, b, maxside + 2, n - 1); //单调递减

	saveResult2(outputFile, x, y);
	std::cout << "Save result to file:" << outputFile << std::endl;
}
void DijkstraProject2::updateDist2(int x)
{
	flag[x] = 1;
	//判断flag是否为0，为0则比较dist
	//小于则改变dist及pre（注意清零）pre[y].clear()
	//等于则增加pre[y].push_back(x)
	for (int i = 0; i < n; i++)
	{
		if (flag[i])
			continue; //i已经被接上就返回
		int w = side[x][i];
		if (w <= 0)
			continue; //没有这条边就返回
		int lastmin = getMin(x);//得到最短的前置边长
		if ((!dist[i] || dist[x] + w < dist[i]) && w > lastmin)
		{
			pre[i].clear();
			pre[i].push_back(x);
			dist[i] = dist[x] + w;
		}
		else if (dist[x] + w == dist[i] && w > lastmin)
			pre[i].push_back(x);
		else
			continue;
	}
	int min = -1;
	int t = -1;
	for (int i = 0; i < n; i++)
	{
		if ((min == -1 || dist[i] < min) && !flag[i] && !pre[i].empty())
		{
			min = dist[i];
			t = i;
		}
	}
	if (t > 0)
		updateDist2(t);
	else
		return;
}
void DijkstraProject2::getResult2(int x, vector<int> a, int last, int target)
{
	//从pre[n-1]开始，获取最短路径并写入文件
	//考虑多条路径问题，递归函数调用
	if (x == target)
	{
		if (target == 0)
			path.push_back(a);
		else if (target == n - 1)
			path2.push_back(a);
		return;
	}
	for (int i = 0; i < pre[x].size(); i++)
	{
		int y = pre[x][i];
		if (getMin(y) >= side[y][x] || side[y][x] >= last)
			continue;
		vector<int> b = a;
		b.push_back(y);
		getResult2(y, b, side[y][x], target);
	}
}
int DijkstraProject2::getMin(int x)
{
	//vector<int>* s=new vector<int> [pre[x].size()];
	if (x == 0)
		return -1;
	int sum = pre[x].size();
	int min = side[pre[x][0]][x];
	for (int i = 1; i < sum; i++)
	{
		int y = side[pre[x][i]][x];
		if (y > 0 && y < min)
			min = y;
	}
	return min;
}
void DijkstraProject2::reverseGraph()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			side[i][j] = -side[i][j];
}
void DijkstraProject2::saveResult2(const char *outputFile, int x, int y)
{
	freopen(outputFile, "a", stdout);

    //比较递增和递减得到的最短路径
	if (x >0 && (x < y||y<=0))//递增存在最短路径时，递减不存在最短路径或距离大于递增
		{cout << x << '\n'
			 << path.size() << '\n';}
	else if (y >0 && (y < x||x<=0))//递减存在最短路径时，递增不存在最短路径或距离大于递增
		cout << y << '\n'
			 << path2.size() << '\n';
	else if (x == y && x > 0)//递增递减均存在最短路径且距离相同
	{
		cout << y << '\n'
			 << path2.size() + path.size() << '\n';
	}
	else//不存在单调路径
	{
		cout << x << ' ' << y << ' ' << "no such path\n0\n";
		return;
	}
    if(y<=0) y=x+1;
	else if(x<=0) x=y+1;//处理 递增或递减时，不存在单调路径的情况


	if (x <= y)
		for (int i = 0; i < path.size(); i++)
		{
			vector<int>::iterator it;
			it = path[i].end();
			it = it - 1;
			for (it; it != path[i].begin(); it--)
			{
				cout << *it << ",";
			}
			cout << *it << '\n';
		}//倒序输出
	if (y <= x)
		for (int i = 0; i < path2.size(); i++)
		{
			vector<int>::iterator it;
			for (it = path2[i].begin(); it != path2[i].end()-1; it++)
			{
				cout << *it << ",";
			}
			cout << *it << '\n';
		}//正序输出
	cout << "end\n\n";
	fclose(stdout);
	freopen("CON", "w", stdout);
}
DijkstraProject2::~DijkstraProject2()
{
	if (pre)
		delete[] pre;
	if (flag)
		delete[] flag;
	if (dist)
		delete[] dist;
	for (int i = 0; i < n; i++)
		if (side[i])
			delete[] side[i];
	if (side)
		delete[] side;
	//cout<<'f';
}
void DijkstraProject2::reset()
{
	//cout<<'r';
	if (pre)
		delete[] pre;
	if (flag)
		delete[] flag;
	if (dist)
		delete[] dist;
	for (int i = 0; i < n; i++)
		if (side[i])
			delete[] side[i];
	if (side)
		delete[] side;
	path.clear();
	path2.clear();
	maxside=0;
	n=0;
	m=0;
	//cout<<'f';
}