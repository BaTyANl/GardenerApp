#include <jni.h>

JNIEXPORT jstring JNICALL Java_com_example_mylibrary_NativeLib_getMessage(JNIEnv* env, jobject obj) {
    return (*env)->NewStringUTF(env, "text");
}