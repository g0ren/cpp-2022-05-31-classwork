#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

/*
 * Singleton
 */

class Unit {
	Unit() {
		this->a = rand();
		this->b = rand();
	}
public:
	int a, b;
	int getA() {
		return this->a;
	}
	int getB() {
		return this->b;
	}
	friend class SingletonUnit;
};

class SingletonUnit {
	static Unit *unit;
public:
	static Unit* getUnit() {
		if (!unit)
			unit = new Unit();
		return unit;
	}
};

Unit *SingletonUnit::unit = nullptr;

//////////////////////////////////////////////
/*
 * Proxy
 */

class Restaurant {
public:
	string name, url;
	int adres;
	void show() {
		cout << "Restaurant: " << name << "\tfor adres: " << adres;
	}

};

class DeliveryFoodInterface {
public:
	virtual void deliveryFood() = 0;
	virtual void show() = 0;
	virtual int getAdres() = 0;
};

class TOKIO_CITY: public Restaurant, public DeliveryFoodInterface {
public:
	TOKIO_CITY(int _adres) {
		name = "tokio city";
		adres = _adres;
		url = "https://www.tokyo-city.ru/";
	}
	void deliveryFood() {
		cout << "verification order in restaurant " << name << endl;
	}
	void show() {
		Restaurant::show();
	}
	int getAdres() {
		return adres;
	}
};

class KFC: public Restaurant, public DeliveryFoodInterface {
public:
	KFC(int _adres) {
		name = "kfc";
		adres = _adres;
		url = "https://www.kfc.ru/";
	}
	void deliveryFood() {
		cout << "verification order in restaurant " << name << endl;
	}
	void show() {
		Restaurant::show();
	}
	int getAdres() {
		return adres;
	}

};

class LilttlePotatoes: public Restaurant, public DeliveryFoodInterface {
public:
	LilttlePotatoes(int _adres) {
		name = "крошка картошка";
		adres = _adres;
		url = "https://www.kartoshka.com/";
	}
	void deliveryFood() {
		cout << "verification order in restaurant " << name << endl;
	}
	void show() {
		Restaurant::show();
	}
	int getAdres() {
		return adres;
	}

};

class DeliveryClub: public DeliveryFoodInterface {
public:
	vector<DeliveryFoodInterface*> foods;
	DeliveryClub() {
		foods.push_back(new TOKIO_CITY(9));
		foods.push_back(new KFC(15));
		foods.push_back(new LilttlePotatoes(2));
	}
	void deliveryFood() {
		for (int i = 0; i < foods.size(); ++i) {
			cout << i + 1 << ":\t";
			foods[i]->show();
			cout << endl;
		}
		int change = 0;
		while (change < 1 || change > foods.size()) {
			cout << "Change Rest:\t";
			cin >> change;
		}
		int adres = 0;
		cout << "Please, give me input adres: \t";
		cin >> adres;
		if (abs(adres - foods[change - 1]->getAdres()) < 5) {
			foods[change - 1]->deliveryFood();
			return;
		} else {
			cout << "Sorry, this Rest in out range distance" << endl;
		}
	}
	void show() {
		cout<<"enter address: ";
		int adres;
		cin >> adres;
		vector<DeliveryFoodInterface*> tmp(foods);
		remove_if(tmp.begin(), tmp.end(), [adres](DeliveryFoodInterface *food) {
			return adres - food->getAdres() >= 5;
		});
		for (auto x : tmp) {
			x->show();
			cout << endl;
		}

	}
	int getAdres() {
		return 0;
	}
};

int main() {
	DeliveryFoodInterface *rest = new LilttlePotatoes(100);
	DeliveryFoodInterface *restClub = new DeliveryClub();
	//rest->deliveryFood();
	//system("pause");
	//restClub->deliveryFood();
	restClub->show();
}
