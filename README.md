# nnu - Node.js Native Utilities
  Some useful utilities for writing node.js native module.
  
## Usage
  Simply add **NAN** and **NNU** as a dependency in the package.json of your Node addon:
```bash
npm install --save nan nnu
```
  Pull in the path to **NAN** and **NNU** in your binding.gyp so that you can use #include <nan.h> in your .cpp files:
```python
"include_dirs" : [
    "<!(node -e \"require('nan')\")",
    "<!(node -e \"require('nnu')\")"
]
```

## Example
  - NnuPointer
```c++
#include <nnu.h>

// nnu::ClassWrap will simplify the way you write a class.
class SampleClass : public nnu::ClassWrap<SampleClass> {
public:
	static const char * const CLASS_NAME;

	static NAN_METHOD(ctor) {
		SampleClass *sc = new SampleClass;
		sc->Wrap(info.This());

		info.GetReturnValue().Set(info.This());
	}

	static void setupMember(v8::Local<v8::FunctionTemplate>& tpl) {
		Nan::SetPrototypeMethod(tpl, "getVal", wrapFunction<&SampleClass::getVal>);
		Nan::SetPrototypeMethod(tpl, "incVal", wrapFunction<&SampleClass::incVal>);
	}

private:
	SampleClass() : _val(0) { }

  // You can now write member function instead of static, ObjectWrap::Unwrap is no longer needed.
	NAN_METHOD(getVal) {
		info.GetReturnValue().Set(Nan::New(_val));
	}

	NAN_METHOD(incVal) {
		_val++; 
		info.GetReturnValue().Set(info.This());
	}

private:
	int _val;
};

const char * const SampleClass::CLASS_NAME = "SampleClass";

NAN_MODULE_INIT(InitAll) {
	SampleClass::setup(target);
}

NODE_MODULE(nnu_example, InitAll);
```
