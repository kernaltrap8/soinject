MAIN_SRC="src/main.c"
SO_SRC="src/libso.c"
MAIN_OUT="./build/main"
SO_OUT="./build/libso.so"
SO_OUT32="./build/libso32.so"

all:
	mkdir -p ./build
	gcc -m64 -shared -fPIC -ldl $(SO_SRC) -o $(SO_OUT)
	gcc -m32 -shared -fPIC -ldl $(SO_SRC) -o $(SO_OUT32)
	gcc $(MAIN_SRC) -o $(MAIN_OUT)
run: all
	LD_PRELOAD=$(SO_OUT) $(MAIN_OUT) 
