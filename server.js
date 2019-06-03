'use strict';

const express = require('express');

const app = express();

app.use(express.static('public', {
    setHeaders: (res, path) => {
        if (path.endsWith('.wasm')) {
            res.set('Content-Type', 'application/wasm');
        }
    },
}));

// eslint-disable-next-line no-console
app.listen(process.env.PORT, () => console.log(`listening on port ${process.env.PORT}!`));
