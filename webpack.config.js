const path = require('path');
const webpack = require('webpack');

module.exports = env => {
    const isDevelopment = env === 'development';

    return {
        entry: './src/app/index.js',
        output: {
            path: path.resolve(__dirname, 'public'),
            filename: 'bundle.js',
        },
        module: {
            rules: [
                { test: /src\/app\/.*\.(js)$/, use: 'babel-loader' },
                {
                    test: /src\/app\/.*\.scss$/,
                    loader: [
                        'style-loader',
                        {
                            loader: 'css-loader',
                            options: {
                                modules: true,
                                localIdentName: '[name]__[local]___[hash:base64:5]',
                                camelCase: true,
                                sourceMap: isDevelopment,
                            },
                        },
                        {
                            loader: 'sass-loader',
                            options: {
                                sourceMap: isDevelopment,
                            },
                        },
                    ],
                },
            ],
        },
        plugins: [
            new webpack.DefinePlugin({
                'process.env.NODE_ENV': JSON.stringify(env),
            }),
        ],
        mode: env,
    };
};
