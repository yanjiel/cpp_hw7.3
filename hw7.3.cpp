#include<iostream>
#include<future>
#include<cmath>
#include<functional>
#include<memory>

using namespace std;

template<typename T>
class my_promise {
public:
	my_promise() {};
	auto get_future() {
		p.set_value(10.0);
		return p.get_future();///////////
	}
private:
	promise<double> p; /////////////
};


template<typename T>
class my_future {
public:
	my_future() {};
	double get() {
		return 1.5;
	}

private:
	double result;
	
};

double pow_of(int x, int y) { return pow(x, y); }


int main() {
	my_promise<double> p;
	future<double> f = p.get_future();
	cout << f.get();
	return 0;
}