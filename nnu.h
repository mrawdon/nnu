#ifndef TAL_NNU_H
#define TAL_NNU_H

#include <nan.h>

template <typename T> class NnuPointer {
public:
	NnuPointer() {

	}

	virtual ~NnuPointer() {

	}

	inline v8::Local<v8::Value> handle() {
		return NanNew(handle_);
	}

	inline v8::Persistent<v8::Value>& persistent() {
		return handle_;
	}

public:
	static inline T* Unwrap(v8::Handle<v8::Value> handle) {
		assert(!handle.IsEmpty() && handle->IsExternal());
		return static_cast<T*>(v8::Handle<v8::External>::Cast(handle)->Value());
	}

protected:
	inline v8::Handle<v8::Value> Wrap() {
		assert(handle_.IsEmpty());

		v8::Handle<v8::Value> handle = NanNew<v8::External>(this);
		NanAssignPersistent(handle_, handle);
		handle_.SetWeak(this, WeakCallback);
		handle_.MarkIndependent();

		return handle;
	}

private:
	static void WeakCallback(const v8::WeakCallbackData<v8::Value, NnuPointer>& data) {
		NanScope();
		NnuPointer* wrap = data.GetParameter();
		wrap->handle_.Reset();
		delete wrap;
	}

private:
	v8::Persistent<v8::Value> handle_;
};

#endif // TAL_NNU_H