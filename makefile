.PHONY: clean

aptdbms: $(shell find src -type f -iname '*.c')
	gcc -Iinclude -lm -o $@ $^
	
clean:
	rm aptdbms
