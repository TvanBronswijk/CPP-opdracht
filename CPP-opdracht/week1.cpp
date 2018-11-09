#include <iostream>
#include <memory>
#include <string>
#include <utility>
class Animal {
public:
  Animal() = default;
  virtual ~Animal() = default;
  Animal(const Animal &) = delete;
  Animal(Animal &&) = delete;
  Animal &operator=(const Animal &) = delete;
  Animal &operator=(Animal &&) = delete;
  virtual void make_noise() const = 0;
};

class Llama : public Animal {
public:
  Llama(int milk_production) : milk_production_{milk_production} {}
  void make_noise() const override {
    std::cout << "MWEEEUH, I make " << milk_production_ << " liters a day\n";
  }

private:
  int milk_production_;
};

class Alpaca : public Animal {
public:
  Alpaca(bool needs_shave) : needs_shave_{needs_shave} {}
  void make_noise() const override {
    std::cout << "HUEEEWM ";
    if (needs_shave_) {
      std::cout << "I need a shave!";
    } else {
      std::cout << "I'm cold!";
    }
    std::cout << "\n";
  }

private:
  bool needs_shave_{};
};

class Vampire {
	std::string str;
public:
	// accepteert rvalue reference
	Vampire(std::string &&s) : str{ std::move(s) } {}
	const std::string &get_str() { return str; }
};

class KingJulien { // King Julien
public:
	KingJulien(int i) : it{ new int{i} } {}
	// he doesn't like to copy, copy
	KingJulien(const KingJulien &o) = delete;
	KingJulien &operator=(const KingJulien &o) = delete;
	// he likes to... MOVE IT!
	KingJulien(KingJulien &&o) noexcept : it{ std::exchange(o.it, nullptr) } {}
	KingJulien &operator=(KingJulien &&o) noexcept {
		std::swap(o.it, it);
		return *this;
	}
	~KingJulien() {
		if (it)
			delete it;
	}
	int get_it() { return *it; }
private:
	int *it;
};

void party(const Animal &a) {
	for (int i = 0; i < 3; ++i) {
		a.make_noise();
	}
}

void f(KingJulien k) {
	std::cout << "He has " << k.get_it() << std::endl;
}
void g() {
	KingJulien k{ 3 };
	f(std::move(k));
}

int main() {
  // clang-format off
  std::unique_ptr<Animal> p1 = std::make_unique<Llama>(10);
  std::unique_ptr<Animal> p2 = std::move(p1);
  party(*p2);

  std::string s{ "Llama" };
  std::cout << "Before move, s = " << s << std::endl;
  std::string s2{ std::move(s) };
  std::cout << "After move, s = " << s << std::endl;
  std::cout << " , s2 = " << s2 << std::endl;
  Vampire v{ std::move(s2) };
  std::cout << "After move, s = " << s << std::endl;
  std::cout << " , s2 = " << s2 << std::endl;
  std::cout << " v.get_str() = " << v.get_str() << std::endl;

  g();
  
  char a;
  std::cin >> a;
}

