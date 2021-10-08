#include "NativeImpl.h"

#include <memory>
#include <functional>
#include <iostream>

#include <jni.h>
#include "NativeClass.h"

using std::cout;
using std::endl;
using std::function;
using std::shared_ptr;
using std::string;
using std::unique_ptr;

class jstring_deleter
{
    JNIEnv *m_env;
    jstring m_jstr;

public:
    jstring_deleter(JNIEnv *env, jstring jstr)
        : m_env(env), m_jstr(jstr)
    {
    }

    void operator()(const char *cstr)
    {
        m_env->ReleaseStringUTFChars(m_jstr, cstr);
    }
};

const string ToString(JNIEnv *env, jstring jstr)
{
    jstring_deleter deleter(env, jstr); // using a function object
    unique_ptr<const char, jstring_deleter> pcstr(
        env->GetStringUTFChars(jstr, JNI_FALSE),
        deleter);

    return string(pcstr.get());
}

JNIEXPORT void JNICALL Java_NativeClass_sayHello(JNIEnv *env, jobject thisObj, jstring arg)
{
    DoSayHello(ToString(env, arg));
}

void DoSayHello(const string &name)
{
    cout << "Hello, " << name << endl;
}