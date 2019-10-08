emcc ./src/lib/prime.c -s FORCE_FILESYSTEM=1 -s WASM=1 -O2 -s EXPORTED_FUNCTIONS="['_isPrime', '_checkPrimes']" -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' -o ./public/wasm/prime.js
emcc ./src/lib/canvas.c -s WASM=1 -s EXPORTED_FUNCTIONS="['_main', '_getCircles']" -o ./public/wasm/canvas.js
emcc ./src/lib/demo.cpp -s FORCE_FILESYSTEM=1 -s WASM=1 -O2 -s EXPORTED_FUNCTIONS="['_getNum', '_main', '_getDoubleNum', '_greet']" -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' -o ./public/wasm/demo.js
