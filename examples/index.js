const binding = require('./build/Release/nnu-example.node');

const obj = new binding.SampleClass;
const cloned = obj.clone();

obj.printPriv();

console.log(obj.incVal().incVal().getVal());
console.log(cloned.getVal());

console.log(binding.newSample());