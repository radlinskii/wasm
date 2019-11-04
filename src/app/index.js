/* eslint-disable no-console */
import React, { useEffect } from 'react';
import ReactDOM from 'react-dom';
import Input from './components/Input/Input';

const zip = (list, len, zipLen) => {
    const array2d = [];
    for (let i = 0, count = 0; i < len; i++) {
        const array = [];
        for (let j = 0; j < zipLen; j++) {
            array.push(list[count]);
            count += 1;
        }
        array2d.push(array);
    }

    return array2d;
};

const greetFromCpp = window.cwrap('greet', 'string', ['string']);

const calcSphere = ({ pointer, length, dimensions, minValue, maxValue }) => {
    const func = window.Module.cwrap('calcSphere', 'number', ['number', 'number', 'number', 'number', 'number']);

    return new Float64Array(wasmMemory.buffer, func(pointer, length, dimensions, minValue, maxValue), length);
};

const calcMichalewicz = ({ pointer, length, dimensions, minValue, maxValue }) => {
    const func = window.Module.cwrap('calcMichalewicz', 'number', ['number', 'number', 'number', 'number', 'number']);

    return new Float64Array(wasmMemory.buffer, func(pointer, length, dimensions, minValue, maxValue), length);
};

const calcBeale = ({ pointer, length, dimensions, minValue, maxValue }) => {
    const func = window.Module.cwrap('calcBeale', 'number', ['number', 'number', 'number', 'number', 'number']);

    return new Float64Array(wasmMemory.buffer, func(pointer, length, dimensions, minValue, maxValue), length);
};

const evaluate = ({ fitnessFunctionType, ...rest }) => {
    switch (fitnessFunctionType) {
        case 'michalewicz':
            return calcMichalewicz({ ...rest });
        case 'beale':
            return calcBeale({ ...rest });
        case 'sphere':
            return calcSphere({ ...rest });

        default:
            throw new Error('Invalid fitness function type');
    }
};

const evaluatePopulation = ({ population, function: fitnessFunctionType, dimensions, minValue, maxValue }) => {
    let pointer;
    const flatPopulation = population.flat();
    const typedFlatPopulation = Float64Array.from(flatPopulation);

    try {
        pointer = window.Module._malloc(typedFlatPopulation.length * typedFlatPopulation.BYTES_PER_ELEMENT);

        window.Module.HEAPF64.set(typedFlatPopulation, pointer / typedFlatPopulation.BYTES_PER_ELEMENT);

        const results = evaluate({
            length: typedFlatPopulation.length,
            pointer,
            dimensions,
            minValue,
            maxValue,
            fitnessFunctionType,
        });

        const zippedResults = zip(results, population.length, dimensions);

        window.socket.send(JSON.stringify(zippedResults));
    } catch (e) {
        console.error(e);
    } finally {
        window.Module._free(pointer);
    }
};

const App = () => {
    console.log(greetFromCpp('Browser'));

    useEffect(() => {
        const protocol = process.env.NODE_ENV !== 'production' ? 'ws' : 'wss';

        window.socket = new WebSocket(`${protocol}://${window.location.host}/ws`);
        console.log('Attempting Connection...');

        window.socket.onopen = () => {
            console.log('Successfully Connected');
        };

        window.socket.onclose = event => {
            console.log(`Connection closed with code: ${event.code}, reason: ${event.reason}`);
        };

        window.socket.onmessage = message => {
            if (JSON.parse(message.data).population) {
                evaluatePopulation(JSON.parse(message.data));
            }
        };

        window.socket.onerror = error => {
            console.log('Socket Error: ', error);
        };
    }, []);

    return (
        <div>
            <h1>WebAssembly Demo in React</h1>
            <Input />
        </div>
    );
};

ReactDOM.render(<App />, document.getElementById('app'));
