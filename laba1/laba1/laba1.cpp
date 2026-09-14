#include <cmath>
#include <vector>
#include <iostream>
using namespace std;
struct pipeproperties {
	string name;
	double length;
	double diametr;
	bool status;
	bool empty() {
		return name.empty() && lenght == 0.0 && diametr == 0.0 && status == false;
	}
};
struct stationproperties {
	string name;
	int allcex;
	int workcex;
	string specification;
	bool empty() {
		return name.empty() && allcex == 0 && workcex == 0 && specification.empty();
	}
};
pipeproperties createpipe() {
	pipeproperties p;
	cout << "Введите название трубы:";
	cin >> p.name;
	cout << "Введите длину трубы:";
	cin >> p.length;
	cout << "Введите диаметр трубы:";
	cin >> p.diametr;
	p.status = True;
	return p;
}
stationproperties createstation() {
	stationproperties st;
	cout << "Введите название КС:";
	cin >> st.name;
	cout << "Введите количество цехов:";
	cin >> st.allcex;
	st.workcex = st.allcex;
	cout << "Введите класс станции:";
	cin >> st.specification;
	return st;
}
// хз че делать пока с этим, с функцией чек апа, мб потом сделаю две функции empty для кс и трубы
//void checkup(const pipeproperties& p, const stationproperties& st) {
//	cout << "Ваша труба и КС:";
//	if (p.empty() && st.empty()) {
//		cout << "Вы не создавали труб и КС";
//	}
//	if (!p.empty() && !st.empty())
//}

int main()
{
	cout << "Hellow World";
	return 0;
}