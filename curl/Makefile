default: build

build: clean
	gcc -Wall main.c -l curl -o curl

clean:
	rm -rf curl

test: build
	./curl https://httpbin.org/get
