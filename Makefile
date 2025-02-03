MAIN_SRC="src/main.c"
SO_SRC="src/libso.c"
MAIN_OUT="./build/main"
SO_OUT="./build/libso.so"

all:
	mkdir -p ./build
	gcc -shared -fPIC -ldl $(SO_SRC) -o $(SO_OUT)
	gcc $(MAIN_SRC) -o $(MAIN_OUT)
run: all
	LD_PRELOAD=$(SO_OUT) $(MAIN_OUT) 
