const path = require('path');

module.exports = {
    entry: './src/app/index.js',
    output: {
        path: path.resolve(__dirname, 'public'),
        filename: 'bundle.js',
    },
    module: {
        rules: [
            { test: /src\/app\/.*\.(js)$/, use: 'babel-loader' },
            { test: /src\/app\/.*\.(css)$/, use: ['style-loader', 'css-loader'] },
        ],
    },
    mode: 'development',
};
