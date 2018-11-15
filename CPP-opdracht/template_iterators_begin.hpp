#include <array>
#include <iostream>
#include <vector>

class Enemy {
public:
  Enemy(const char *name, int hp) : name_{name}, hp_{hp} {}
  int hp() const { return hp_; }
  const char *name() const { return name_; }

private:
  const char *name_;
  int hp_;
};

template<class It>
void print_big(It begin, It end) {
	for (It it = begin; it != end; ++it)
		if((*it).hp() >= 30)
			std::cout << (*it).name() << '\n';
}
