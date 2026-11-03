#include <iostream>
#include <string>
#include <windows.h>
#include <ctype.h>
#include <fstream> 
#include <type_traits>
using namespace std;

struct pipeproperties {
	string name;
	double length;
	double diametr;
	bool status;
	bool empty() const {
		return name.empty() || length == 0.0 || diametr == 0.0;
	}
};

struct stationproperties {
	string name;
	int allcex;
	int workcex;
	int specification;
	bool empty() const {
		return name.empty() || allcex == 0;
	}
};

template <typename T>
void readValue(T& val) {
	while (true) {
		string s;
		getline(cin, s);		

		bool isEmpty = true;
		for (int i = 0; i < s.size(); i++) {
			if (!isspace(static_cast<unsigned char>(s[i]))) {
				isEmpty = false;
				break;
			}
		}
		if (isEmpty) {
			cout << "Ошибка: пустая строка. Введите снова: ";
			continue;
		}

		if constexpr (is_same<T, string>::value) {
			val = s;
			return;
		}
		else {
			bool isValid = true;
			int dotCount = 0;
			for (int i = 0; i < s.size(); i++) {
				char c = s[i];
				if (isspace(static_cast<unsigned char>(c))) continue;
				if (isdigit(static_cast<unsigned char>(c))) continue;

				if (c == '.' && is_same<T, double>::value) {
					dotCount++;
					if (dotCount > 1) {
						isValid = false;
						break;
					}
					continue;
				}

				isValid = false;
				break;
			}

			if (!isValid) {
				cout << "Ошибка: введите число без букв. Снова: ";
				continue;
			}

			try {
				if constexpr (is_same<T, int>::value) val = stoi(s);
				else if constexpr (is_same<T, double>::value) val = stod(s);
				return;
			}
			catch (...) {
				cout << "Ошибка: слишком большое число. Снова: ";
			}
		}
	}
}

void inputPipe(pipeproperties& p) {
	cout << "Введите название трубы: ";
	readValue(p.name);

	cout << "Введите длину трубы: ";
	readValue(p.length);
	while (p.length <= 0) {
		cout << "Длина должна быть больше нуля. Введите снова: ";
		readValue(p.length);
	}

	cout << "Введите диаметр трубы: ";
	readValue(p.diametr);
	while (p.diametr <= 0) {
		cout << "Диаметр должен быть больше нуля. Введите снова: ";
		readValue(p.diametr);
	}

	p.status = false;
	cout << "Данные успешно записаны" << '\n';
}

void inputStation(stationproperties& st) {
	cout << "Введите название КС: ";
	readValue(st.name);

	cout << "Введите количество цехов: ";
	readValue(st.allcex);
	while (st.allcex <= 0) {
		cout << "Цехов должно быть больше нуля. Введите снова: ";
		readValue(st.allcex);
	}

	cout << "Введите количество работающих цехов (от 0 до " << st.allcex << "): ";
	readValue(st.workcex);
	while (st.workcex < 0 || st.workcex > st.allcex) {
		cout << "Ошибка! Введите число от 0 до " << st.allcex << ": ";
		readValue(st.workcex);
	}

	cout << "Введите класс станции: ";
	readValue(st.specification);
	while (st.specification <= 0) {
		cout << "Класс должен быть больше нуля. Введите снова: ";
		readValue(st.specification);
	}

	cout << "Данные успешно записаны" << '\n';
}

void printPipe(const pipeproperties& p) {
	if (!p.empty()) {
		cout << '\n' << "У вас есть труба." << endl;
		cout << "1) Название: " << p.name << endl;
		cout << "2) Длина: " << p.length << endl;
		cout << "3) Диаметр: " << p.diametr << endl;
		cout << "4) Статус: " << (p.status ? "В ремонте" : "В работе") << endl << '\n';
	}
	else {
		cout << '\n' << "Вы не создали трубу" << endl << '\n';
	}
}

void printStation(const stationproperties& st) {
	if (!st.empty()) {
		cout << '\n' << "Свойства КС:" << endl;
		cout << "1) Название: " << st.name << endl;
		cout << "2) Количество всех цехов: " << st.allcex << endl;
		cout << "3) Количество рабочих цехов: " << st.workcex << endl;
		cout << "4) Класс станции " << st.specification << endl;
	}
	else {
		cout << '\n' << "Вы не создали КС" << endl << '\n';
	}
}

void editPipe(pipeproperties& p) {
	if (p.empty()) {
		cout << "Сначала создайте трубу!" << endl;
		return;
	}
	cout << "Текущий статус: " << (p.status ? "В ремонте" : "Работает") << endl;
	cout << "1) Отправить в ремонт" << endl;
	cout << "2) Завершить ремонт" << endl;
	cout << "Ваш выбор: ";

	int choice;
	readValue(choice);
	while (choice != 1 && choice != 2) {
		cout << "Ошибка. Введите 1 или 2: ";
		readValue(choice);
	}

	if (choice == 1) {
		p.status = true;
		cout << "Труба отправлена в ремонт." << endl;
	}
	else {
		p.status = false;
		cout << "Ремонт завершен, труба работает." << endl;
	}
}

void editStation(stationproperties& st) {
	if (st.empty()) {
		cout << "Сначала создайте КС!" << endl;
		return;
	}
	cout << "Сейчас работает цехов: " << st.workcex << " из " << st.allcex << endl;
	cout << "1) Запустить один цех" << endl;
	cout << "2) Остановить один цех" << endl;
	cout << "Ваш выбор: ";

	int choice;
	readValue(choice);
	while (choice != 1 && choice != 2) {
		cout << "Ошибка. Введите 1 или 2: ";
		readValue(choice);
	}

	if (choice == 1) {
		if (st.workcex < st.allcex) {
			st.workcex++;
			cout << "Цех запущен. Теперь работает: " << st.workcex << endl;
		}
		else {
			cout << "Нельзя запустить! Все цеха уже работают." << endl;
		}
	}
	else {
		if (st.workcex > 0) {
			st.workcex--;
			cout << "Цех остановлен. Теперь работает: " << st.workcex << endl;
		}
		else {
			cout << "Нельзя остановить! Все цеха уже стоят." << endl;
		}
	}
}

void savePipe(ofstream& out, const pipeproperties& p) {
	out << p.name << "\n";
	out << p.length << "\n";
	out << p.diametr << "\n";
	out << p.status << "\n";
}

void saveStation(ofstream& out, const stationproperties& st) {
	out << st.name << "\n";
	out << st.allcex << "\n";
	out << st.workcex << "\n";
	out << st.specification << "\n";
}

void saveToFile(const pipeproperties& p, const stationproperties& st) {
	ofstream out("data.txt");
	if (!out.is_open()) {
		cout << "Ошибка: не удалось открыть файл для записи!" << endl;
		return;
	}
	savePipe(out, p);
	saveStation(out, st);
	out.close();
	cout << "Данные успешно сохранены в файл!" << endl;
}

void loadPipe(ifstream& in, pipeproperties& p) {
	getline(in, p.name);
	in >> p.length >> p.diametr >> p.status;
	in.ignore(1000000, '\n');
}

void loadStation(ifstream& in, stationproperties& st) {
	getline(in, st.name);
	in >> st.allcex >> st.workcex >> st.specification;
}

void loadFromFile(pipeproperties& p, stationproperties& st) {
	ifstream in("data.txt");
	if (!in.is_open()) {
		cout << "Ошибка: файл data.txt не найден! Сначала сохраните данные." << endl;
		return;
	}

	pipeproperties tempP;
	stationproperties tempSt;

	loadPipe(in, tempP);
	loadStation(in, tempSt);
	in.close();

	if (!tempP.empty()) {
		p = tempP;
		cout << "Данные о трубе загружены." << endl;
	}
	else {
		cout << "В файле нет данных о трубе." << endl;
	}

	if (!tempSt.empty()) {
		st = tempSt;
		cout << "Данные о КС загружены." << endl;
	}
	else {
		cout << "В файле нет данных о КС." << endl;
	}
}

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	pipeproperties p;
	stationproperties st;

	while (true) {
		cout << "---------------------------------------------------------------------------------";
		cout << '\n' << "1) Добавить трубу" << endl;
		cout << "2) Добавить КС" << endl;
		cout << "3) Просмотр всех объектов" << endl;
		cout << "4) Редактировать трубу" << endl;
		cout << "5) Редактировать КС" << endl;
		cout << "6) Сохранить в файл" << endl;
		cout << "7) Загрузить из файла" << endl;
		cout << "0) Выход" << endl;
		cout << "Введите число от 0 до 7: ";

		int vvod;
		readValue(vvod);

		if (vvod < 0 || vvod > 7) {
			cout << "Неверный пункт меню! Введите число от 0 до 7." << endl;
			continue;
		}

		cout << "---------------------------------------------------------------------------------" << '\n';
		switch (vvod) {
		case 1:
			inputPipe(p);
			break;
		case 2:
			inputStation(st);
			break;
		case 3:
			cout << "Ваша труба и КС:" << endl;
			printPipe(p);
			printStation(st);
			break;
		case 4:
			editPipe(p);
			break;
		case 5:
			editStation(st);
			break;
		case 6:
			saveToFile(p, st);
			break;
		case 7:
			loadFromFile(p, st);
			break;
		case 0:
			cout << "Выход из программы. До свидания!" << endl;
			return 0;
		}
	}
}