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

1. Specify `PORT` environment variable to number of your choice. You can use `.env` file.
2. Run `go run server.go` to serve static files and handle requests.
3. In new terminal tab run `npm run dev` to start off *webpack* watching for file changes in `/src/app` directory.

### WASM development

After making changes to `src/lib` files run the `buildwasm.sh` script or use `emcc` tool to compile them to `.wasm` files.

> Be sure to import generated scripts to the `.html` files.
