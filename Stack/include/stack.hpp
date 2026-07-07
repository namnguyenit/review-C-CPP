#ifndef STACK_HPP
#define STACK_HPP

#include <vector>
#include <stdexcept>

template <typename T>

class Stack{
    private: 
        std::vector<T> elms;

    public:
        size_t size() const{
            return elms.size();
        }
        void push(const T& elm){
            elms.push_back(elm);
        }
        const T& top() const{
            if(elms.empty()){
                throw std::out_of_range("Stack trong");
            };
            return elms.back();
        }
        void pop(){
            if (elms.empty()){
                throw std::out_of_range("Stack trong");
            }
            elms.pop_back();
        }
        bool isEmpty() const {
            return elms.empty();
        }

};



#endif
