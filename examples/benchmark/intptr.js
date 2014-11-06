var binding = require('../build/Release/nnu-example.node');

suite('create', function () {
    bench('create', function () {
        binding.createIntPtr();
    });

    bench('wrap raw', function () {
        binding.wrapRaw();
    });

    var ptr = binding.wrapRaw();
    bench('unwrap raw', function () {
        binding.unwrapRaw(ptr);
    });
});

suite('unwrap', function () {
    var ptr = binding.createIntPtr();

    bench('unwrap', function () {
        binding.unwrap(ptr);
    });

    bench('val', function () {
        binding.val(ptr);
    });

    bench('set val', function () {
        binding.val(ptr, 3);
    });
});