#include <iostream>
#include <memory>
#include <utility>
#include <vector>

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
    std::cout << "HUEEEWM " << (needs_shave_ ? "I need a shave!" : "I'm cold!") << "\n";
  }
private:
  bool needs_shave_{};
};

class Farm {
	using iterator = std::vector<std::unique_ptr<Animal>>::const_iterator;
	using riterator = std::reverse_iterator<std::vector<std::unique_ptr<Animal>>::const_iterator>;
public:
	void add_llama(std::unique_ptr<Llama> p) {
		animals_.push_back(std::move(p));
	}
	void add_alpaca(std::unique_ptr<Alpaca> p) {
		animals_.push_back(std::move(p));
	}

	template <typename T, typename... Args>
	void add_animal(Args &&... args) {
		animals_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	}
	void inspect() const {
		for (iterator it = animals_.begin(); it != animals_.end(); ++it)
			(*it)->make_noise();
	}
	void reverse_inspect() const {
		for (riterator it = animals_.rbegin(); it != animals_.rend(); ++it)
			(*it)->make_noise();
	}
private:
  std::vector<std::unique_ptr<Animal>> animals_{};
};

