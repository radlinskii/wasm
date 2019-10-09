import React from 'react';
import ReactDOM from 'react-dom';
import Input from './components/Input/Input';

const greetFromCpp = window.cwrap('greet', 'string', ['string']);

const App = () => {
    // eslint-disable-next-line no-console
    console.log(greetFromCpp('Browser'));

    return (
        <div>
            <h1>WebAssembly Demo in React</h1>
            <Input />
        </div>
    );
};

ReactDOM.render(<App />, document.getElementById('app'));
