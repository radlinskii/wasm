const path = require('path');
const webpack = require('webpack');

module.exports = env => ({
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
    plugins: [
        new webpack.DefinePlugin({
            'process.env.NODE_ENV': JSON.stringify(env),
        }),
    ],
    mode: env,
});
