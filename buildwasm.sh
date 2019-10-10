emcc -c ./src/lib/main.cpp -o ./build/main.o
emcc -c ./src/lib/Animal.cpp -o ./build/Animal.o
emcc ./build/Animal.o ./build/main.o  -s FORCE_FILESYSTEM=1 -s WASM=1 -O2 -s EXPORTED_FUNCTIONS="['_getNum', '_main', '_getDoubleNum', '_greet']" -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' -o ./public/wasm/main.js
