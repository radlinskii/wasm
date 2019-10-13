import React from 'react';
import ReactDOM from 'react-dom';
import Input from './components/Input/Input';

const greetFromCpp = window.cwrap('greet', 'string', ['string']);

const calculate = () => {
    let ptr;
    const arrayDataToPass = [2.2, 1.57];

    const greet = window.Module.cwrap('calculate', 'string', ['number', 'number']);

    // create typed array
    const typedArray = new Float64Array(arrayDataToPass.length);

    // Populate the array with the values
    for (let i = 0; i < arrayDataToPass.length; i++) {
        typedArray[i] = arrayDataToPass[i];
    }

    try {
        // Allocate some space in the heap for the data (making sure to use the appropriate memory size of the elements)
        ptr = window.Module._malloc(typedArray.length * typedArray.BYTES_PER_ELEMENT);

        // Assign the data to the heap - Keep in mind bytes per element
        window.Module.HEAPF64.set(typedArray, ptr / typedArray.BYTES_PER_ELEMENT);

        // eslint-disable-next-line no-console
        console.log(greet(ptr, arrayDataToPass.length));
    } catch (e) {
        // eslint-disable-next-line no-console
        console.error(e);
    } finally {
        window.Module._free(ptr);
    }
};

const App = () => {
    // eslint-disable-next-line no-console
    console.log(greetFromCpp('Browser'));
    calculate();

    return (
        <div>
            <h1>WebAssembly Demo in React</h1>
            <Input />
        </div>
    );
};

ReactDOM.render(<App />, document.getElementById('app'));
