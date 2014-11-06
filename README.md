# nnu - Node.js Native Utilities
  Some useful utilities for writing node.js native module.
  
## Usage
  Simply add **NAN** and **NNU** as a dependency in the package.json of your Node addon:
```bash
npm install --save nan,nnu
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
class IntPtr : public NnuPointer<IntPtr> {
public:
	IntPtr() : val_(0) { }
	~IntPtr() { }

	static void setup(Handle<Object>& exports) {
		NODE_SET_METHOD(exports, "createIntPtr", createIntPtr);
		NODE_SET_METHOD(exports, "unwrap", unwrap);
		NODE_SET_METHOD(exports, "val", val);
	}

private:
	static NAN_METHOD(createIntPtr) {
		NanScope();
		IntPtr *ptr = new IntPtr();
		NanReturnValue(ptr->Wrap());
	}

	static NAN_METHOD(unwrap) {
		NanScope();
		IntPtr* ptr = Unwrap(args[0]);
		NanReturnUndefined();
	}

	static NAN_METHOD(val) {
		NanScope();
		IntPtr* ptr = Unwrap(args[0]);

		if (args[1]->IsNumber()) {
			ptr->val_ = args[1]->Int32Value();
			NanReturnUndefined();
		} else {
			NanReturnValue(NanNew(ptr->val_));
		}
	}

private:
	int val_;
};
```
