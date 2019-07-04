import React from 'react';
import ReactTestRenderer from 'react-test-renderer';
import InputComponent from './Input';

describe('InputComponent', () => {
    test(`Should match snapshot`, () => {
        const tree = ReactTestRenderer.create(<InputComponent />);

        expect(tree).toMatchSnapshot();
    });
});
