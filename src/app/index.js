/* eslint-disable no-console */
import React, { useEffect } from 'react';
import ReactDOM from 'react-dom';
import Input from './components/Input/Input';

const greetFromCpp = window.cwrap('greet', 'string', ['string']);

const calcSphere = ({ pointer, length, dimensions, minValue, maxValue }) => {
    const func = window.Module.cwrap('calcSphere', 'string', ['number', 'number', 'number', 'number', 'number']);

    const result = func(pointer, length, dimensions, minValue, maxValue);

    console.log(result);
};

const calcMichalewicz = ({ pointer, length, dimensions, minValue, maxValue }) => {
    const func = window.Module.cwrap('calcMichalewicz', 'string', ['number', 'number', 'number', 'number', 'number']);

    const result = func(pointer, length, dimensions, minValue, maxValue);

    console.log(result);
};

const calcBeale = ({ pointer, length, dimensions, minValue, maxValue }) => {
    const func = window.Module.cwrap('calcBeale', 'string', ['number', 'number', 'number', 'number', 'number']);

    const result = func(pointer, length, dimensions, minValue, maxValue);

    console.log(result);
};

const evaluate = ({ fitnessFunctionType, ...rest }) => {
    switch (fitnessFunctionType) {
        case 'michalewicz':
            calcMichalewicz({ ...rest });
            break;
        case 'beale':
            calcBeale({ ...rest });
            break;
        case 'sphere':
            calcSphere({ ...rest });
            break;

        default:
            throw new Error('Invalid fitness function type');
    }
};

const evaluatePopulation = ({ population, function: fitnessFunctionType, dimensions, minValue, maxValue }) => {
    let pointer;
    const flatPopulation = new Float64Array(population.length * dimensions);

    for (let i = 0, count = 0; i < population.length; i++) {
        for (let j = 0; j < dimensions; j++) {
            flatPopulation[count] = population[i][j];
            count += 1;
        }
    }

    try {
        // Allocate some space in the heap for the data (making sure to use the appropriate memory size of the elements)
        pointer = window.Module._malloc(flatPopulation.length * flatPopulation.BYTES_PER_ELEMENT);

        // Assign the data to the heap - Keep in mind bytes per element
        window.Module.HEAPF64.set(flatPopulation, pointer / flatPopulation.BYTES_PER_ELEMENT);

        // eslint-disable-next-line no-console
        evaluate({
            length: flatPopulation.length,
            pointer,
            dimensions,
            minValue,
            maxValue,
            fitnessFunctionType,
        });
    } catch (e) {
        // eslint-disable-next-line no-console
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
            console.log('Socket Closed Connection: ', event);
            window.socket.send('Client Closed!');
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
