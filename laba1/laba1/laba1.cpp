#include <iostream>
#include <string>
#include <windows.h>
#include <ctype.h>
#include <fstream> 
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

void readPositiveDouble(double& x) {
	while (true) {
		cin >> x;
		if (cin.fail() || x <= 0) {
			cin.clear();
			cin.ignore(1000000, '\n');
			cout << "Вы ввели неправильные данные, введите число" << endl;
			continue;
		}
		else {
			cin.ignore(1000000, '\n');
			return;
		}
	}
}

void readPositiveInt(int& x) {
	while (true) {
		cin >> x;
		if (cin.fail() || x <= 0) {
			cin.clear();
			cin.ignore(1000000, '\n');
			cout << "Вы ввели неправильные данные, введите число" << endl;
			continue;
		}
		else {
			cin.ignore(1000000, '\n');
			return;
		}
	}
}

void readNonEmptyString(string& s) {
	cin.ignore(1000000, '\n');
	while (true) {
		getline(cin, s);
		int count = 0;
		for (int i = 0;i < s.size();i++) {
			if (isspace(static_cast<unsigned char>(s[i]))) {
				count += 1;
			}
		}
		if (s.empty() || count == s.size()) {
			cout << "Вы ввели неправильное название или пустую строку, введите снова:" << endl;
		}
		else {
			return;
		}
	}
}

void inputPipe(pipeproperties& p) {
	cout << "Введите название трубы:";
	readNonEmptyString(p.name);
	cout << "Введите длину трубы:";
	readPositiveDouble(p.length);
	cout << "Введите диаметр трубы:";
	readPositiveDouble(p.diametr);
	p.status = false;
	cout << "Данные успешно записаны" << '\n';
}

void inputStation(stationproperties& st) {
	cout << "Введите название КС:";
	readNonEmptyString(st.name);
	cout << "Введите количество цехов:";
	readPositiveInt(st.allcex);
	cout << "Введите количество работающих цехов:";
	while (true) {
		readPositiveInt(st.workcex);
		if (st.workcex > st.allcex) {
			cout << "Ошибка! Работающих цехов не может быть больше общего количества. Введите снова:" << endl;
		}
		else {
			break;
		}
	}
	cout << "Введите класс станции:";
	readPositiveInt(st.specification);
	cout << "Данные успешно записаны" << '\n';
}

void printPipe(const pipeproperties& p) {
	if (!p.empty()) {
		cout << '\n' << "У вас есть труба." << endl;
		cout << "Свойства трубы:" << endl;
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
	cout << "2) Завершить ремонт (ввести в эксплуатацию)" << endl;
	cout << "Ваш выбор: ";
	int choice;
	cin >> choice;
	if (cin.fail() || (choice != 1 && choice != 2)) {
		cin.clear();
		cin.ignore(1000000, '\n');
		cout << "Ошибка ввода. Статус не изменен." << endl;
		return;
	}
	cin.ignore(1000000, '\n');
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
	cin >> choice;
	if (cin.fail() || (choice != 1 && choice != 2)) {
		cin.clear();
		cin.ignore(1000000, '\n');
		cout << "Ошибка ввода. Ничего не изменено." << endl;
		return;
	}
	cin.ignore(1000000, '\n');
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
void saveToFile(const pipeproperties& p, const stationproperties& st) {
	ofstream out("data.txt");
	if (!out.is_open()) {
		cout << "Ошибка: не удалось открыть файл для записи!" << endl;
		return;
	}
	out << p.name << "\n";
	out << p.length << "\n";
	out << p.diametr << "\n";
	out << p.status << "\n";
	out << st.name << "\n";
	out << st.allcex << "\n";
	out << st.workcex << "\n";
	out << st.specification << "\n";
	out.close();
	cout << "Данные успешно сохранены в файл data.txt" << endl;
}

void loadFromFile(pipeproperties& p, stationproperties& st) {
	ifstream in("data.txt");
	if (!in.is_open()) {
		cout << "Ошибка: файл data.txt не найден! Сначала сохраните данные." << endl;
		return;
	}
	getline(in, p.name);
	in >> p.length >> p.diametr >> p.status;
	in.ignore(1000000, '\n');
	getline(in, st.name);
	in >> st.allcex >> st.workcex >> st.specification;
	in.close();
	cout << "Данные успешно загружены из файла!" << endl;
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
		cout << "Введите число от 0 до 7" << endl;

		int vvod;
		cin >> vvod;

		if (cin.good()) {
			cout << "---------------------------------------------------------------------------------" << '\n';
			switch (vvod) {
			case 1:
				/*
				if (!p.empty()) {
					cout << "Труба уже создана!" << endl;
				}
				else {
					inputPipe(p);
				}
				*/
				inputPipe(p);
				break;
			case 2:
				/*
				if (!st.empty()) {
					cout << "КС уже создана!" << endl;
				}
				else {
					inputStation(st);
				}
				*/
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
			default:
				cout << "Неверный пункт меню! Введите число от 0 до 7." << endl;
				break;
			}
		}
		else {
			cin.clear();
			cin.ignore(10000000, '\n');
			cout << "Вы ввели неправильный символ, введите число от 0 до 7" << endl;
			continue;
		}
	}
}