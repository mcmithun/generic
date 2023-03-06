#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <functional>
#include <mutex>
#include <vector>
/*
 * This is a simple subscription class for horizontal
 * communication, between different threads.
 */
template<typename T>
class Subscription {
public:
    // Default function pointer for callback
    using Callback = std::function<void(const T*)>;

    // Used by the subscriber - parent class
    // Example:
    // main-> Subscription<MyClass> *sub = new Subscription<MyClass>
    // sub->subscribe(/*callback/*[](any object){});
    void subscribe(Callback callback) {
        std::lock_guard<std::mutex> lock(mutex_);
        callbacks_.push_back(callback);
    }

    // Used by the client class.
    // Example:
    // MyClass *mo = new MyClass(o)
    // and in
    // MyClass::func() {... sub->notify() ...}
    void notify(const T* data) {
        std::lock_guard<std::mutex> lock(mutex_);
        for (auto& callback : callbacks_) {
            callback(data);
        }
    }

private:
    std::vector<Callback> callbacks_;
    std::mutex mutex_;
};


#endif // SUBSCRIPTION_H
