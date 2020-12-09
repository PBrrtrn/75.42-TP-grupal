//
// Created by alejo on 26/11/20.
//

#ifndef PRUEBA_SDL_BLOCKINGQUEUE_H
#define PRUEBA_SDL_BLOCKINGQUEUE_H
#include <mutex>
#include <queue>
#include <condition_variable>
#include <exception>

template <class T> class BlockingQueue {
private:
    bool isClosed;
    std::mutex m;
    std::queue<T> queue;
    std::condition_variable cv;

public:
    BlockingQueue() : isClosed(false) {}

    void push(T t){
        std::unique_lock<std::mutex> lock(m);
        queue.push(t);
        cv.notify_all();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(m);
        while (queue.empty()){
            if (isClosed){
                //throw ClosedQueueException();
                throw std::exception();
            }
            cv.wait(lock);
        }
        T t = queue.front();
        queue.pop();
        return t;
    }

    void close() {
        std::unique_lock<std::mutex> lock(m);
        isClosed = true;
        cv.notify_all();
    }

    ~BlockingQueue() {}

};


#endif //PRUEBA_SDL_BLOCKINGQUEUE_H
