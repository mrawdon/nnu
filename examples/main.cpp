#include <nnu.h>

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
