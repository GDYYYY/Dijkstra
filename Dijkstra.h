#pragma once
#include <vector>
#include <cstdint>
#include <string>
using namespace std;
//const int maxsize = 100;
/**
 * This file declare the main class of Project2:DijstraProject2.
 * You should implement the methods:`readFromFile`,`run1`and`run2` in Dijstra.cpp.
 * You can add anything in DijstraProject2 class to implement Project2.
 */
class DijkstraProject2
{
private:
	//You can declare your graph structure here.
	//建邻接矩阵
	int n = 0, m = 0; //n个顶点，m条边
	int **side;//邻接矩阵
	int *dist; //记录各点到s的距离
	//vector<int> pre[maxsize];
	vector<int> *pre;//前驱节点
	vector<vector<int>> path; //记录最短路径
	vector<vector<int>> path2; //记录最短路径
	int *flag; //判断该点是否已求出最短路径
	//int flag[maxsize]={0};
	//int cnt = 0; //第几条路径
	int maxside = 0;

public:
	bool read = true;
	~DijkstraProject2();
	void reset();
	/**
	 * Read graph from Param:`inputfile`.
	 * 
	 */
	//void addToGraph(int x,int y,int w);//添加点进入邻接表
	void getNM(string x);//读入n和m
	void getSide(string x);//读入边
	int s_int(string x);//将string转化为int
	void readFromFile(const char *inputfile = "input.txt");

	/**
	 * Part 1, implement Dijstra algorithm to finish Part 1
	 * and save the result to Param:`outputFile`.
	 * Save the path as: node_1,node_2...node_n. (seperate nodes with comma)
	 *
	 */
	void run1(const char *outputFile = "output.txt");
	void updateDist1(int x);//更新距离并拓展
	void getResult1(int x, vector<int> a);//得到路径
	void saveResult1(const char *outputFile);//存储路径

	/**
	 * Part 2, find the monotonically increasing path to finish Part 2
	 * and save the result to Param:`outputFile`.
	 * Save the path as: node_1,node_2...node_n. (seperate nodes with comma)
	 *
	 */
	void run2(const char *outputFile = "output.txt");
	void updateDist2(int x);
	void getResult2(int x, vector<int> a, int last, int target);
	void saveResult2(const char *outputFile, int x, int y);
	void reverseGraph();//将图反向
	int getMin(int x);//得到最短的前置边长
};
