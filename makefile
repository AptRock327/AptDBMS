.PHONY: clean

aptdbms: $(shell find src -type f -iname '*.c')
	gcc -Iinclude -o $@ $^ -lm
	
clean:
	rm aptdbms
