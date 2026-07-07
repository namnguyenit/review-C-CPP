#ifndef STACK_HPP
#define STACK_HPP

#include <vector>
#include <stdexcept>

template <typename T>

class Stack{
    private: 
        std::vector<T> elms;

    public:
        
        Stack() = default;

        Stack(const Stack &other){
            this->elms = other.elms;
        }

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
        void clear(){
            elms.clear();
        }
        void print(){
            for (const auto& item:elms){
                cout << item << " ";
            }
            cout << endl;
        }
        void resize (size_t nsize){
            elms.resize(nsize);
        }
        size_t capacity() const{
            return elms.capacity();
        }

        Stack& operator= (const Stack& other){
            if (this != &other){
                this->elms = other.elms;
            }
            return *this;
        }

};



#endif
