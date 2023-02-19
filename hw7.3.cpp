//#include<iostream>
//#include<future>
//#include<cmath>
//#include<functional>
//#include<memory>
//#include<condition_variable>
//#include<mutex>
//
//using namespace std;
//
//template<typename T>
//class my_promise { //producer
//public:
//	my_promise() { 
//		result = 0.0;
//
//		pf = nullptr; 
//
//	};
//	auto get_future() {
//		//update f
//		auto f_sp = make_shared<future<double>>(f);
//		return f_sp;
//	}
//
//	void set_value(double d) {
//		//lock_guard lock(m);
//		unique_lock<mutex> lck(m);
//		cv.wait(lck, f.valid());
//		f.result = d;
//		cv.notify_one();//producer notifies
//	}
//
//private:
//	double result;
//	mutex m;
//	condition_variable cv;
//	future<double> f;
//	
//};
//
//
//template<typename T>
//class my_future { //consumer
//public:
//	my_future() {};
//	double get() {
//		return result;////////////////
//	}
//	
//	bool valid() const noexcept {
//	//
//	}
//
//	void wait() const {
//	// sleep till valid is true
//	}
//
//private:
//	double result;
//	condition_variable cv;
//};
//
//
//double pow_of(int x, int y) { return pow(x, y); }
//
//
//int main() {
//	my_promise<double> p;
//	future<double> f = p.get_future();
//	cout << f.get();
//	return 0;
//}