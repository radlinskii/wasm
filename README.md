# WASM

Web Assembly in actual project!

## Getting Started

### Dependencies

- [node](https://nodejs.org/en/)
- [go](https://golang.org/)
- [emscripten](https://emscripten.org/)

### Installation

1. `git clone https://github.com/radlinskii/wasm.git`
2. `cd wasm`
3. `npm ci`

> *go* will install it's dependencies automatically while running the server for the first time.

### Local Development

1. Specify `PORT` environment variable to number of your choice.
2. Run `go run server.go` to serve static files and handle requests.
3. In new terminal tab run `npm run dev` to start off *webpack* watching for file changes in `/src/app` directory.

### WASM development

After making changes to `src/lib` files run `emcc` tool to compile them to `.wasm` files.

Examples:

```sh
emcc ./src/lib/prime.c -s FORCE_FILESYSTEM=1 -s WASM=1 -O2 -s EXPORTED_FUNCTIONS="['_isPrime', '_checkPrimes']" -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' -o ./public/wasm/prime.js
```

```sh
emcc ./src/lib/canvas.c -s WASM=1 -s EXPORTED_FUNCTIONS="['_main', '_getCircles']" -o ./public/wasm/canvas.js
```

```sh
emcc ./src/lib/demo.c -s FORCE_FILESYSTEM=1 -s WASM=1 -O2 -s EXPORTED_FUNCTIONS="['_getNum', '_main', '_getDoubleNum', '_greet']" -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' -o ./public/wasm/demo.js
```

> Be sure to import generated scripts to the `.html` files.
