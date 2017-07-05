#ifndef TAL_NNU_H
#define TAL_NNU_H

#include <nan.h>

namespace nnu {
    template <typename T> class ClassWrap : public Nan::ObjectWrap {
    public:
        typedef NAN_METHOD(NNU_METHOD);
        typedef NAN_METHOD((T::*NNU_MEMBER_METHOD));

        template<NNU_MEMBER_METHOD FN> static NAN_METHOD(wrapFunction) {
            T* pThis = Nan::ObjectWrap::Unwrap<T>(info.This());
            (pThis->*FN)(info);
        }

        void static setup(v8::Handle<v8::Object> exports) {
            v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(T::ctor);
            tpl->SetClassName(Nan::New(T::CLASS_NAME).ToLocalChecked());
            tpl->InstanceTemplate()->SetInternalFieldCount(1);

            T::setupMember(tpl);

            exports->Set(Nan::New(T::CLASS_NAME).ToLocalChecked(), tpl->GetFunction());
            _ctor.Reset(tpl->GetFunction());
        }

    private:
        static Nan::Persistent<v8::Function> _ctor;
    };

    template<typename T> Nan::Persistent<v8::Function> ClassWrap<T>::_ctor;
}

#endif // TAL_NNU_H