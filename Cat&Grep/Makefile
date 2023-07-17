CC=gcc
CFLAGS=-Wall -Wextra -Werror

all: cat grep
cat: Cat/cat.c Cat/cat.h 
		$(CC) $(CFLAGS) Cat/cat.c -o cat
grep: Grep/grep.c Grep/grep.h
		$(CC) $(CFLAGS) Grep/grep.c -o grep
test: Cat/cat.c Cat/cat.h Grep/grep.c Grep/grep.h test/diffcat.sh test/diffgrep.sh
	bash test/diffcat.sh
	bash test/diffgrep.sh
style:
	cd Grep/ &&clang-format -style=Google -n *.c *.h
	cd Grep/ &&clang-format -style=Google -i *.c *.h
	cd Cat/ &&clang-format -style=Google -n *.c *.h
	cd Cat/ &&clang-format -style=Google -i *.c *.h
clean:
	rm -rf cat
	rm -rf grep
rebuild: clean all
