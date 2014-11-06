var binding = require('./build/Release/nnu-example.node');

var ptr = binding.createIntPtr();
console.log(binding.val(ptr));
binding.val(ptr, 1);
console.log(binding.val(ptr));
