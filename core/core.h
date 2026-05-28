#pragma once
#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Core
{
private:
public:
	template<typename T>
	static void printVectorResult(vector<T> result)
	{
		for (int i=0;i<result.size(); i++)
		{
			if (i == result.size() - 1)
			{
				cout << result[i];
			}
			else
			{
				cout << result[i] << " ";
			}
		}
	}
};