#include "ContactSignalHub.h"

ContactSignalHub* ContactSignalHub::instance() {
    // 静态变量，只会创建一个实例
    static ContactSignalHub hub;
    return &hub;
}
