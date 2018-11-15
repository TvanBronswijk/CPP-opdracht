#include "alpacallama.hpp"
#include "template_iterators_begin.hpp"

void part_1() {
	Farm f{};
	f.add_llama(std::make_unique<Llama>(10));
	f.add_alpaca(std::make_unique<Alpaca>(true));
	f.add_animal<Llama>(12);
	f.inspect();
	f.reverse_inspect();
}

void part_2() {
	std::vector<Enemy> enemies{};
	enemies.emplace_back("Bandit", 10);
	enemies.emplace_back("Rover", 20);
	enemies.emplace_back("Dragon", 50);
	enemies.emplace_back("Cow", 20);
	enemies.emplace_back("Potato", 30);
	std::array<Enemy, 5> foes{ Enemy{"Bandit", 10}, Enemy{"Rover", 20},
							  Enemy{"Dragon", 50}, Enemy{"Cow", 20},
							  Enemy{"Potato", 30} };
	print_big(enemies.begin(), enemies.end());
	print_big(foes.cbegin(), foes.cend());
}

int main() {
	part_1();
	part_2();

	char a;
	std::cin >> a;
}

