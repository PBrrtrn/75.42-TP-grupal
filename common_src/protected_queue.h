#ifndef PROTECTED_QUEUE_H
#define PROTECTED_QUEUE_H
#include <mutex>
#include <queue>
#include <condition_variable>
#include <exception>

template <class T> class ProtectedQueue {
private:
    bool isClosed;
    std::mutex m;
    std::queue<T> queue;
    std::condition_variable cv;

public:
    ProtectedQueue() : isClosed(false) {}

    void push(T t){
        std::unique_lock<std::mutex> lock(m);
        queue.push(t);
        cv.notify_all();
    }
	
	std::vector<T> popSync(){
		T t = queue.front();
		queue.pop();
		return t;
	} //devolver por movimiento

    T pop() {
        std::unique_lock<std::mutex> lock(m);
        T t = queue.front();
        queue.pop();
        return t;
    }

    std::vector<T> popAll() {
        std::unique_lock<std::mutex> lock(m);
        std::vector<T> v;
        while (!queue.empty()){
			v.push_back(queue.front());
			queue.pop();
		}
        return v;
    }
    
    void close() {
        std::unique_lock<std::mutex> lock(m);
        isClosed = true;
        cv.notify_all();
    }

    ~ProtectedQueue() { 
		this->close();
	}

};


#endif
