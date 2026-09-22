#include <android/log.h>

#define LOG_TAG "CursorIndicator"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

__attribute__((constructor))
void mod_init() {
    LOGI("Cursor Indicator preload-native library loaded");
}
