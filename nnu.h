#ifndef TAL_NNU_H
#define TAL_NNU_H

#include <nan.h>

namespace nnu {
    v8::Local<v8::String> newString(const char *str) {
        return Nan::New(str).ToLocalChecked();
    }

    template <typename T, typename O, NAN_METHOD((O::*FN))> NAN_METHOD(wrapFunction) {
        T* pThis = Nan::ObjectWrap::Unwrap<T>(info.This());
        (pThis->*FN)(info);
    }

    template <typename T> class ClassWrap : public Nan::ObjectWrap {
    public:
        template<NAN_METHOD((T::*FN))> inline static NAN_METHOD(wrapFunction) {
            nnu::wrapFunction<T, T, FN>(info);
        }

        void static setup(v8::Handle<v8::Object> exports) {
            v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(T::ctor);
            tpl->SetClassName(Nan::New(T::CLASS_NAME).ToLocalChecked());
            tpl->InstanceTemplate()->SetInternalFieldCount(1);

            T::setupMember(tpl);

            exports->Set(Nan::New(T::CLASS_NAME).ToLocalChecked(), tpl->GetFunction());
            _ctor.Reset(tpl->GetFunction());
        }

        static v8::Local<v8::Object> newInstance() {
            return Nan::NewInstance(Nan::New(_ctor)).ToLocalChecked();
        }

        static v8::Local<v8::Object> newInstance(int argc, v8::Local<v8::Value> argv[]) {
            return Nan::NewInstance(Nan::New(_ctor), argc, argv).ToLocalChecked();
        }

    private:
        static Nan::Persistent<v8::Function> _ctor;
    };

    template<typename T> Nan::Persistent<v8::Function> ClassWrap<T>::_ctor;
}

#endif // TAL_NNU_H