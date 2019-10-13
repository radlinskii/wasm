emcc -std=c++17 -c ./src/lib/main.cpp -o ./build/main.o
emcc -std=c++17 -c ./src/lib/Individual/Individual.cpp -o ./build/Individual.o
emcc -std=c++17 -c ./src/lib/FitnessFunctions/FitnessFunction.cpp -o ./build/FitnessFunction.o
emcc ./build/FitnessFunction.o ./build/Individual.o ./build/main.o  -s FORCE_FILESYSTEM=1 -s WASM=1 -O2 -s EXPORTED_FUNCTIONS="['_getNum', '_main', '_getDoubleNum', '_greet']" -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' -o ./public/wasm/main.js
