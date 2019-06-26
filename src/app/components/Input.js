import React, { useEffect } from 'react';

const Input = () => {
    useEffect(() => {
        /* eslint-disable no-console */
        window.socket = new WebSocket(`ws://${window.location.host}/ws`);
        console.log('Attempting Connection...');

        const input = document.getElementById('input');
        const handleButtonClick = () => {
            window.socket.send(input.value);
        };
        const button = document.getElementById('button');
        button.onclick = handleButtonClick;

        window.socket.onopen = () => {
            console.log('Successfully Connected');
            window.socket.send('Hi From the Client!');
        };

        window.socket.onclose = event => {
            console.log('Socket Closed Connection: ', event);
            window.socket.send('Client Closed!');
        };

        window.socket.onmessage = message => {
            console.log(message);
        };

        window.socket.onerror = error => {
            console.log('Socket Error: ', error);
        };
        /* eslint-enable no-console */
    });

    return (
        <div>
            <label htmlFor="input">Type your message here:</label>
            <input id="input" name="input" type="text" />
            <button id="button">Send</button>
        </div>
    );
};

export default Input;
