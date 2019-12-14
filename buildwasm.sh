emcc -std=c++17 -c ./src/lib/main.cpp -o ./build/main.o
emcc -std=c++17 -c ./src/lib/Individual/Individual.cpp -o ./build/Individual.o
emcc -std=c++17 -c ./src/lib/FitnessFunctions/FitnessFunction.cpp -o ./build/FitnessFunction.o
emcc -std=c++17 -c ./src/lib/Parameters/Parameters.cpp -o ./build/Parameters.o
emcc -std=c++17 -c ./src/lib/Population/Population.cpp -o ./build/Population.o
emcc -std=c++17 -c ./src/lib/DifferentialEvolution/DifferentialEvolution.cpp -o ./build/DifferentialEvolution.o

emcc \
./build/DifferentialEvolution.o \
./build/Population.o \
./build/Parameters.o \
./build/FitnessFunction.o \
./build/Individual.o \
./build/main.o \
\
-s FORCE_FILESYSTEM=1 \
-s WASM=1 -O2 \
-s ASSERTIONS=1 \
-s EXPORTED_FUNCTIONS="['_main', '_greet', '_calcSphere', '_calcElliptic', '_calcRastrigin', '_calcRosenbrock']" \
-s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
\
-o ./public/wasm/main.js
