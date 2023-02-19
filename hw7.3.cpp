
//https://gist.github.com/rmartinho/5231565

#include<iostream>
#include<future>
#include<cmath>
#include<functional>
#include<memory>
#include<condition_variable>
#include<mutex>


using namespace std;

class shared_future_state {
public:
	shared_future_state() :result(0.0), ready(false) {}

	void set_value(double d) {
		unique_lock<mutex> lk(m);
		ready = false;
		result = d;
		ready = true;
		lk.unlock();
		cv.notify_all();
	}

	bool is_ready() { return ready; }

	double get() {
		unique_lock<mutex> lk(m);
		cv.wait(lk, is_ready());
		lk.unlock();
		return result;
	}
	
private:
	mutex m;
	condition_variable cv;
	double result;
	bool ready;
	
};


class my_future { //consumer
public:
	my_future(shared_ptr<shared_future_state> fs_sp) : futstate_sp(fs_sp) {} //construct with the shared_ptr to shared_future_state

	double get() {
		//InternalState<Result, Type>* state = state_.get();
		return futstate_sp->get();
	}

	bool valid() const noexcept {}

	void wait() const {}

private:
	shared_ptr<shared_future_state> futstate_sp;
};


class my_promise { //producer
public:
	my_promise() {
		//creates a shared_future_state
		//make a shared pointer to that shared_future_state
		futstate_sp = make_shared<shared_future_state>();
	};

	auto get_future() {
		my_future fut = my_future(futstate_sp);
		return fut; //returns a shared pointer to the shared_future_state object
	}

	void set_value(double d) {
		futstate_sp->set_value(d);
	}

private:
	shared_ptr<shared_future_state> futstate_sp;

};




double pow_of(int x, int y) { return pow(x, y); }


int main() {
	//my_promise p;
	//my_future f = p.get_future();
	//cout << f.get();
	return 0;
}