#include <algorithm> // copy
#include <fstream>   // ifstream
#include <iostream>  // cout
#include <iterator>  // input_iterator
#include <numeric>   // accumulate
#include <string>
#include <vector>
#include <functional>

class observable {
	using Observer = std::function<void(int)>;
public:
	observable(int value) : value_{ value } {};
	void value(int value) {
		value_ = value;
		notify_changes(value_);
	}
	void add_observer(Observer o) {
		observers_.push_back(o);
	}

private:
	int value_;
	std::vector<Observer> observers_;
	void notify_changes(int value) {
		std::for_each(observers_.begin(), observers_.end(), [=](auto observer) { observer(value); });
	}
};

template<class It>
void for_all(It begin, It end, std::function<void(const std::string&)> func) {
	std::for_each(begin, end, func);
}


int main() {
  std::ifstream f{"input.txt"};
  std::istream_iterator<int> i_begin{f};
  std::istream_iterator<int> i_end{};
  std::ostream_iterator<int> o_begin{std::cout, "\n"};
  //std::copy_if(i_begin, i_begin, o_begin, [](auto i) { return i % 2 == 0; });
  //std::transform(i_begin, i_end, o_begin, [](auto i) { return i * 2; });

  std::vector<int> v;
  std::copy(i_begin, i_end, std::back_inserter(v));
  std::sort(v.begin(), v.end());
  //std::copy(v.begin(), v.end(), o_begin);

  //*o_begin = std::accumulate(i_begin, i_end, 1, std::multiplies<int>());

  std::vector<std::string> text{ "aap", "noot", "mies" };
  for_all(text.begin(), text.end(), [](const std::string &s) { std::cout << s << "\n"; });

  observable obs{ 10 };
  obs.add_observer([](int val) { std::cout << "Got: " << val << "\n"; });
  obs.value(11);
  obs.add_observer([](int val) { std::cout << "It changed to: " << val << "\n"; });
  obs.value(12);

  char a;
  std::cin >> a;
}

