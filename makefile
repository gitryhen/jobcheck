jobcheck:
	g++ -std=c++20 -c stringsplit.cpp -o stringsplit.o
	g++ -std=c++20 -Wall -Wpedantic -Werror -Wextra jobcheck.cpp stringsplit.o -o jc
jc:
	g++ -std=c++20 -Wall -Wpedantic -Werror -Wextra -Wshadow jobcheck.cpp -fsanitize=address -fsanitize=undefined stringsplit.o -o jc
	./jc hello world