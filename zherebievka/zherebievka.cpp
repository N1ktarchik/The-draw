#include "Header.h"

void main()
{
	setlocale(LC_ALL, "RU");

	int choise{},  count_group{};

	std::string z = "1234567890";
	
	std::vector<std::string>nach_mas;
	std::vector<std::string>group;
	std::vector<std::vector<std::string>>members;
	std::vector<std::vector<std::string>>members_d=members;


	init(nach_mas);

	while (true)
	{
		if (z != "1234567890")
		{
			std::cout << "\nДля продолжения нажмите любую клавишу\n";
			std::cin >> z;
		}
		system("cls");
		menu(choise);

		switch (choise)
		{
			case 1:
			{
				print_arr(nach_mas,"Колличество команд:","Команды:",true);
				break;
			}

			case 2:
			{
				print_arr(group, " ", "Созданные группы:", 0);

				int n;
				char shure;

				std::cout << std::endl;

				std::cout << "Сколько групп вы хотите создать?\n";
				std::cin >> n;

				std::cout << "Вы уверены, что хотите создать " << n << " групп?\nДля этого будет выделена память!\nНажмите y/Y что бы продолжить.\n";
				std::cin >> shure;

				if (shure == 'Y' || shure == 'y')
				{
					system("cls");
					group = groups(n, group);

				}
				print_arr(group, " ", "Созданные группы:", 0);

				members.resize(group.size());

				break;

			}

			case 3:
			{
				int number{}, n = group.size();
				print_arr(group, " ", "Группы:", 0);

				getchoise<int>("Выберите номер группы участников которой хотите узнать", "Ошибка!Обратитесь к администратору!", number, [&n](int vallue) {return vallue >= 0 && vallue <= n; });

				print_group(group[number-1], group);

				break;
			}

			case 4:
			{
				if (nach_mas.size() < 2)
				{
					std::cout << "Ошибка! Команд слишком мало для проведения жеребьёвки!\nОбратитесь к администратору.\n";
					std::exit(0);
				}
				std::vector<std::string>zher_all = zher_4(nach_mas);
				int count = 1;
				for (int i=0;i<=zher_all.size()-2;i+=2)
				{
					std::cout << count<<" пара:\t" << zher_all[i] << " VS " << zher_all[i + 1] << "\n";
					count++;
				}


				break;
			}

			case 5:
			{
				int number{}, n = group.size(), count;
				bool flag(false);
				print_arr(group, " ", "Группы:", 0);

				getchoise<int>("Выберите номер группы в которой	 нужно провести жеребьёвку", "Ошибка!Обратитесь к администратору!", number, [&n](int vallue) {return vallue >= 0 && vallue <= n; });

				getchoise<int>("Сколько раз провести жеребьевку?", "Ошибка!Обратитесь к администратору!", count, [](int vallue) {return vallue >0; });

				std::vector<std::string>zher_group;

				for (int i = 0; i < count; i++)
				{
					system("cls");

					if (members[number - 1].size() >= 2)
					{
						zher_group = zher_4(members[number - 1]);
					}

					else
					{
						std::cout << "Ошибка! Слишком мало команд для проведения жеребьевки!\nОбратитесь к администратору.\n";
						flag = true;

					}
					
				}
				if (!flag)
				{
					int k = 1;
					for (int i = 0; i <= zher_group.size() - 2; i += 2)
					{
						std::cout << k << " пара: " << zher_group[i] << " VS " << zher_group[i + 1] << "\n";
						k++;
					}
				}


				break;
			}

			case 6:
			{
				int count;

				getchoise<int>("Сколько раз провести жеребьевку?", "Ошибка!Обратитесь к администратору!", count, [](int vallue) {return vallue > 0; });
				for (int i = 0; i < count; i++)
				{
					members_d = members;
					func_6(nach_mas, members_d);
				}
				
				members = members_d;
				for (int i = 0; i < members.size(); i++)
				{
					std::string name = group[i];
					for (int j = 0; j < members[i].size();j++)
					{
						write_group(name, members[i][j]);
					}
				}
				break;
			}

			case 7:
			{
				int name_index, group_index,n=nach_mas.size();
				bool flag{ true }, wflag{ true };
				std::string command_choise, group_choise;
				print_arr(nach_mas, " ", "Команды:", false);

				getchoise<int>("Выберите команду которую хотите добавить в любую из групп", "Ошибка!Обратитесь к администратору!", name_index, [&n](int vallue) {return vallue >= 0 && vallue <= n; });
				command_choise = nach_mas[name_index - 1];

				n = group.size();

				print_arr(group, " ", "Группы:", 0);

				getchoise<int>("Выберите группу в которую нужно добавить команду "+command_choise, "Ошибка!Обратитесь к администратору!", group_index, [&n](int vallue) {return vallue >= 0 && vallue <= n; });
				group_choise = group[group_index - 1];


				std::string temp;
				std::fstream file(group_choise);

				while (std::getline(file,temp)&&wflag)
				{

					if (temp==command_choise)
					{
						wflag = false;
						flag = false;
						break;
					}
				}

				file.close();

				if (flag)
				{
					members[group_index - 1].push_back(command_choise);

					write_group(group_choise, command_choise);

					print_group(group_choise, group);
					break;
				}

				else
				{
					std::cout << "Ошибка!Команда уже находится в группе!\n";
					std::ofstream(group_choise, std::ios::trunc);
					file.close();
				}

				break;
			}

			case 8:
			{
				int x{},n=group.size();

				print_arr(group, "", "", 0);
				getchoise<int>("Выберите номер группы которую хотите удалить", "Ошибка!Обратитесь к администратору!", x, [&n](int vallue) {return vallue >= 0 && vallue <= n; });

				if (std::remove(group[x-1].c_str()) == 0)
				{
					std::cout << "Файл " << group[x-1] << " успешно удален\n";

					members.erase(members.begin() + x - 1);
				}

				else
				{
					std::cout << "Не удалось удалить файл " << group[x-1] << "\n";
				}

				if (group.size() != 0)
				{
					group.erase(group.begin()+x - 1);
				}

				break;
			}

			case 9:
			{
				for (int i = 0; i < members.size(); i++)
				{
					std::cout << "Команды в группе " << group[i] << " :\n";
					std::cout << "---------------------------------------------------------------\n";

					for (int j = 0; j < members[i].size(); j++)
					{
						std::cout << members[i][j] << "\n";
					}
					
					std::cout << "---------------------------------------------------------------\n";
					std::cout << std::endl;
				}
				break;
			}

			case 10:
			{
				char shure;

				system("cls");

				std::cout << "Если хотите выйти нажмите y/Y.\nИначе любую другую клавишу\n";
				std::cin >> shure;

				if (shure == 'Y' || shure == 'y')
				{
					system("cls");
					//удаление всех доп.файлов
					for (int i = 0; i < group.size(); i++)
					{
						if (std::remove(group[i].c_str())==0)
						{
							std::cout<<"Файл "<<group[i]<<" успешно удален\n";
						}

						else
						{
							std::cout << "Не удалось удалить файл " << group[i] << "\n";
						}
						
					}

					return;
				}

				break;

				std::cout << "\nХорошего дня!\n";
			}

		}

		z = "z";
	}

}