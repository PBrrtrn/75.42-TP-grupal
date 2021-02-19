#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H
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

  void push(T t) {
    std::unique_lock<std::mutex> lock(m);
    queue.push(t);
    cv.notify_all();
  }

  void lock(){
	this->m.lock();
	}
	
	T popSync(){
		T t = queue.front();
		queue.pop();
		return t;
	}
	
	bool isEmptySync(){
		return (queue.empty());
	}

  void unlock(){
	  this->m.unlock();
	}

  T pop() {
    std::unique_lock<std::mutex> lock(m);
    while (queue.empty()){
      if (isClosed){
        //throw ClosedQueueException();
        throw std::exception(); //TODO HACER EXCEPCION
      }
      cv.wait(lock);
    }
    T t = queue.front();
    queue.pop();
    return t;
  }
    
  bool isEmpty() {
		std::unique_lock<std::mutex> lock(m);
		return (queue.empty());
	}

  void close() {
    std::unique_lock<std::mutex> lock(m);
    isClosed = true;
    cv.notify_all();
  }

  ~BlockingQueue() { 
		this->close();
	}

};


#endif
