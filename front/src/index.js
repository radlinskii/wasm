import React, { useEffect } from 'react';
import ReactDOM from 'react-dom';
import Input from './Input';

const App = () => {
    useEffect(() => {
        window.greetFromJS = name => `Hello ${name}, from JS!`;
        const greetJS = window.cwrap('greet', 'string', ['string']);

        window.Module.onRuntimeInitialized = () => {
            // eslint-disable-next-line no-console
            console.log(greetJS('ignacy'));
        };
    });

    return (
        <div>
            <h1>Hello World!!!!</h1>
            <Input />
        </div>
    );
};

ReactDOM.render(<App />, document.getElementById('app'));
