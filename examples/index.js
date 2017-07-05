const binding = require('./build/Release/nnu-example.node');

console.log((new binding.SampleClass).incVal().incVal().getVal());