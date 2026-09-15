#include <cmath>
#include <vector>
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
struct pipeproperties {
	string name;
	double length;
	double diametr;
	bool status;
	bool empty() const {
		return name.empty() && length == 0.0 && diametr == 0.0 && status == false;
	}
};
struct stationproperties {
	string name;
	int allcex;
	int workcex;
	int specification;
	bool empty() const {
		return name.empty() && allcex == 0 && workcex == 0 && specification==0;
	}
};
pipeproperties createpipe(pipeproperties p) {
	cout << "Введите название трубы:" << endl;
	cin >> p.name;
	cout << "Введите длину трубы:" << endl;
	cin >> p.length;
	cout << "Введите диаметр трубы:" << endl;
	cin >> p.diametr;
	p.status = true;
	/*bool vizov1 = true;*/
	return p;
}
stationproperties createstation(stationproperties st) {
	cout << "Введите название КС:";
	cin >> st.name;
	cout << "Введите количество цехов:";
	cin >> st.allcex;
	st.workcex = st.allcex;
	cout << "Введите класс станции:";
	cin >> st.specification;
	/*bool vizov2 = true;*/
	return st;
}
void print(const pipeproperties& p, const stationproperties& st) {
	cout << "Ваша труба и КС:" << endl;
	if (p.empty() && st.empty()) {
		cout << "Вы не создавали труб и КС";
	}			
	if (!p.empty()) {
		cout << "У вас есть труба." << endl;
		cout << "Свойства трубы:" << endl;
		cout << "1) Название: " << p.name << endl;
		cout << "2) Длина: " << p.length << endl;
		cout << "3) Диаметр: " << p.diametr << endl;
		cout << "4) Статус работы " << p.status << endl;
	}
	else {
		cout << "Вы не создали трубу";
	}
	if (!st.empty()) {
		cout << "Свойства КС:" << endl;
		cout << "1) Название: " << st.name << endl;
		cout << "2) Количество всех цехов: " << st.allcex << endl;
		cout << "3) Количество рабочих цехов: " << st.workcex << endl;
		cout << "4) Статус работы " << st.specification << endl;
	}
	else {
		cout << "Вы не создали КС";
	}
}
stationproperties st;
pipeproperties p;
int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	while (true) {
		cout << "1) Добавить трубу" << endl;
		cout << "2) Добавить КС" << endl;
		cout << "3) Просмотр всех объектов" << endl;
		cout << "4) Редактировать трубу" << endl;
		cout << "Введите число от 0 до 7" << endl;
		int vvod;
		cin >> vvod;
		if (cin.good()) {
			switch (vvod) {
				case 1:
					p = createpipe(p);
					break;	
				case 2:
					st = createstation(st);	
					break;
				case 3: 
					print(p, st);
					break;

			}
		}
		else {
			cin.clear();
			cin.ignore(10000000,'\n');
			cout << "Вы ввели неправильный символ, введите число от 0 до 7" <<  endl;	
			continue;
		}
	}
}