#include "Header.h"



void* init(std::vector<std::string>& mas)
{
	

	std::string adres,line;

	std::cout << "Введите адрес файла (полностью)\n";

	std::getline(std::cin, adres);
	adres = remove(adres);

	std::ifstream file(adres);
	system("cls");

	if (!file.is_open())
	{
		std::cout << "Ошибка!Обратитесь к администратору!\n\n";
		std::exit(0);
	}

	else
	{
		while (std::getline(file, line))
		{
			mas.push_back(line);
		}
	}

	file.close();
}

void print_arr(std::vector<std::string> mas, const std::string sms, const std::string message, bool flag)
{
	system("cls");

	if (flag)
	{
		std::cout << sms << "  ";

		std::cout << mas.size();
	}
	std::cout << std::endl;

	std::cout << message << "\n\n";

	int i = 1;

	for (std::vector<std::string>::iterator it = mas.begin(); it != mas.end(); it++)
	{
		std::cout << i<<") " <<* it << "\n";
		i++;
	}
}

std::string remove(std::string str) 
{
	str.erase(std::remove(str.begin(), str.end(), '\"'), str.end()); 
	str.erase(std::remove(str.begin(), str.end(), '\''), str.end());

	return str;

}

void menu(int &x)
{

	std::cout << "powered by N1ktarchik\ntg: @n1ktarchik\n\n";
	std::cout << std::endl;

	std::cout <<"1) Все зарегистрированные команды\n";
	std::cout <<"2) Создать группы\n";
	std::cout <<"3) Команды в определённой группе\n";
	std::cout <<"4) Жеребьевка всех команд\n";
	std::cout <<"5) Жеребьевка команд в определенной группе\n";
	std::cout <<"6) Жеребьевка команд по группам\n";
	std::cout <<"7) Добавить команду в группу\n";
	std::cout <<"8) Удалить группу\n";
	std::cout <<"9) Все команды по группам\n";
	std::cout <<"10) Выход\n";
	
	std::cout << std::endl;
	
	getchoise<int>("Выберите одну из предложенных команд" , "Ошибка!Попробуйте снова или обратитесь к администратору!", x, [](int vallue) {return (vallue <=10&&vallue>=1); });

}

std::vector<std::string> zher_4(std::vector<std::string> mas)
{
	bool flag{ false };
	srand(time(0));

	

	if (mas.size() % 2 != 0)
	{
		std::cout << "Колличество команд не чётное!\n";
		std::cout << "Команда " << mas[mas.size()-1] << " не будет участвовать в жеребьевке!\n\n";
		mas.pop_back();
		flag = true;
	}
	
	std::unordered_map<std::string, int>commands;

	int i = 0;

	while (commands.size() != mas.size())
	{
		int x =  rand() % (mas.size());

		if (commands.count(mas[x]) == 0)
		{
			commands[mas[x]] = i;
			i++;
		}
	}
	std::vector<std::string>arr;

	for (const auto& pair:commands)
	{
		arr.push_back(pair.first);
	}
	

	return arr;
}

std::vector<std::string> groups(int n, std::vector<std::string>arr)
{
	std::vector<std::string>mas;
	int count = arr.size();

	std::string name;


	for (int i = 0; i < n; i++)
	{
		std::cout << "Введите название группы\n";
		std::cin >> name;

		if (name == "")
		{
			name = "group_" + std::to_string(count) + ".txt";
		}

		else
		{
			name = name + ".txt";
		}

		count++;
		std::ofstream file(name);
		mas.push_back(name);
	}

	return mas;
}

void print_group(const std::string name, std::vector<std::string>group)
{
	std::ifstream file(name);
	std::string line;
	int count = 1;

	if (file.is_open())
	{
		std::cout << "Команды в группе "+name<<":\n";
		while (std::getline(file, line))
		{
			std::cout << count <<") "<< line << "\n";
			count++;
		}

		std::cout << std::endl;
	}

	else
	{
		std::cout << "Ошибка!Обратитесь к администратору\n";
		for (int i = 0; i < group.size(); i++)
		{
			if (std::remove(group[i].c_str()) == 0)
			{
				std::cout << "Файл " << group[i] << " успешно удален\n";
			}

			else
			{
				std::cout << "Не удалось удалить файл " << group[i] << "\n";
			}

		}
		std::exit(0);
	}
}

void write_group(const std::string name, const std::string command)
{
	std::ofstream file(name,std::ios::app);

	file << command << std::endl;

	file.close();


}

void func_6(std::vector<std::string>mas, std::vector<std::vector<std::string>>&matrix)
{
	srand(time(0));

	int size = mas.size();

	for (int i = 0; i < mas.size(); i++)
	{
		for (int j = 0; j < matrix.size(); j++)
		{
			for (int g = 0; g < matrix[j].size(); g++)
			{
				if (mas[i] == matrix[j][g])
				{
					mas.erase(mas.begin() + i);
					break;
				}
			}
		}
	}

	
	if (mas.size() % 2 != 0)
	{
		std::string last_name = mas[mas.size()-1];

		mas = zher_4(mas);

		mas.push_back(last_name);
	}

	else
	{
		mas = zher_4(mas);
	}

	system("cls");

	std::vector<int>count;

	count = func_6_help(matrix.size(), size);

	int temp = mas.size();
	while (temp > 0)
	{
		int in_command = rand() % (temp);
		std::string command = mas[in_command];

		int group = rand() % (matrix.size());

		if (matrix[group].size() < count[group])
		{
			matrix[group].push_back(command);
			mas.erase(mas.begin() + in_command);
			temp --;
		}
	}
}

std::vector<int> func_6_help(int n_group, int size)
{
	int count = int(size / n_group);


	std::vector<int>arr;

	for (int i = 0; i < n_group; i++)
	{
		arr.push_back(count);
	}

	if (size != count * n_group)
	{
		int count_d = count*n_group;
		int k = 0;

		while (count_d != size)
		{
			count_d++;
			arr[k]=arr[k]+1;
			k++;
		}
	}

	return arr;
}