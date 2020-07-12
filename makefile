jobcheck:
	g++ -std=c++17 -c stringsplit.cpp -o stringsplit.o
	g++ -std=c++17 -Wall -Wpedantic -Werror -Wextra jobcheck.cpp stringsplit.o -o jc
	./jc 20138
jc:
	g++ -std=c++17 -Wall -Wpedantic -Werror -Wextra -Wshadow jobcheck.cpp -fsanitize=address -fsanitize=undefined stringsplit.o -o jc
	./jc hello world
suse:
	g++-8 -std=c++17 -c stringsplit.cpp -o stringsplit.o
	g++-8 -std=c++17 -Wall -Wpedantic -Werror -Wextra jobcheck.cpp stringsplit.o -o jc
