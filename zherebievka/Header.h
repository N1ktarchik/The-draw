#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <time.h>
#include <string>
#include <map>
#include <cmath>
#include <math.h>
#include <vector>
#include <functional>
#include <cstdlib>
#include <unordered_map>
#include <cstdio>

template <typename T>
void getchoise(const std::string sms, const std::string message, T& x, std::function<bool(T)>f)
{
	while (true)
	{
		std::cout << sms << "\n";

		std::cin >> x;


		if (std::cin.fail() || !f(x))
		{
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout <<"\n"<< message << "\n\n\n";
		}

		else
		{
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			system("cls");
			return;
		}
	}
}
void* init(std::vector<std::string>& mas);
void print_arr(std::vector<std::string> mas, const std::string sms, const std::string message, bool flag);
std::string remove(std::string str);
void menu(int&x);
std::vector<std::string> zher_4(std::vector<std::string> mas);
std::vector<std::string> groups(int n, std::vector<std::string>arr);
void print_group(const std::string name,std::vector<std::string>group);
void write_group(const std::string name, const std::string command);
void func_6(std::vector<std::string>mas,std::vector<std::vector<std::string>>&matrix);
std::vector<int> func_6_help(int n_group, int size);