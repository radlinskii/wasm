emcc ./src/lib/main.cpp -s FORCE_FILESYSTEM=1 -s WASM=1 -O2 -s EXPORTED_FUNCTIONS="['_getNum', '_main', '_getDoubleNum', '_greet']" -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' -o ./public/wasm/main.js
