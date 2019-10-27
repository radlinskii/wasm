import React, { useState } from 'react';
import styles from './Input.scss';

const Input = () => {
    const [inputValue, setInputValue] = useState('');

    const handleValueChange = e => {
        setInputValue(e.target.value);
    };

    const handleButtonClick = () => {
        window.socket.send(inputValue);
        setInputValue('');
    };

    return (
        <div className={styles.root}>
            <label htmlFor="input">Type your message here: </label>
            <input id="input" name="input" onChange={handleValueChange} type="text" />
            <button id="button" onClick={handleButtonClick}>
                Send
            </button>
        </div>
    );
};

export default Input;
