#include <nnu.h>

using namespace v8;

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

NAN_METHOD(wrapRaw) {
	NanScope();
	NanReturnValue(NnuWrapPointer(NULL));
}

NAN_METHOD(unwrapRaw) {
	NanScope();
	NnuUnwrapPointer<void>(args[0]);
	NanReturnUndefined();
}

void InitAll(Handle<Object> exports) {
	NODE_SET_METHOD(exports, "wrapRaw", wrapRaw);
	NODE_SET_METHOD(exports, "unwrapRaw", unwrapRaw);
	IntPtr::setup(exports);
}

NODE_MODULE(nnu_example, InitAll);
