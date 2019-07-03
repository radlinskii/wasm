import React, { useEffect } from 'react';
import ReactDOM from 'react-dom';
import Input from './components/Input/Input';

const App = () => {
    useEffect(() => {
        const greetJS = window.cwrap('greet', 'string', ['string']);

        window.Module.onRuntimeInitialized = () => {
            // eslint-disable-next-line no-console
            console.log(greetJS('ignacy'));
        };
    });

    return (
        <div>
            <h1>Hello World!!!</h1>
            <Input />
        </div>
    );
};

ReactDOM.render(<App />, document.getElementById('app'));
