FROM trzeci/emscripten-slim as build_wasm

ARG APP_PATH=/src

RUN mkdir -p $APP_PATH
WORKDIR $APP_PATH
COPY . .

RUN ./buildwasm.sh

FROM node:12.5.0-alpine AS build_web

ARG APP_PATH=/src

RUN mkdir -p $APP_PATH
WORKDIR $APP_PATH

COPY --from=build_wasm $APP_PATH .

RUN npm ci

RUN npm run build:web

FROM golang:1.12.6-alpine3.10 AS run_server

ARG APP_PATH=/src

RUN apk update && apk upgrade && \
    apk add --no-cache bash git openssh

RUN mkdir -p $APP_PATH
WORKDIR $APP_PATH

RUN mkdir -p public
COPY --from=build_web $APP_PATH/public ./public
RUN mkdir -p server
COPY --from=build_web $APP_PATH/server ./server
COPY --from=build_web $APP_PATH/go.mod ./go.mod
COPY --from=build_web $APP_PATH/go.sum ./go.sum
COPY --from=build_web $APP_PATH/main.go ./main.go

ENV GO111MODULE=on
ENV PORT=8080

RUN go get -d -v ./...
RUN go install -v ./...

CMD ["wasm"]
