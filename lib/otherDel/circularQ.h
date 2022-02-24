#include<iostream>
using namespace std;

class CQ{
    private:
        int size;
        int front = -1, rear =-1;
    
    public:
        int *arr;
        CQ(int s){
            size = s;
            arr = new (int[s]);
        }
        ~CQ(){
            delete []arr;
        }


        bool isFull() {
            if (front == 0 && rear == size - 1) {
                return true;
            }
            if (front == rear + 1) {
                return true;
            }
            return false;
        }

        bool isEmpty() {
            if (front == -1)
                return true;
            else
                return false;
        }

        int push(int data){
            if (isFull()) {
                cout << "Error: Queue is full";
                return -1;

            } else {
                if (front == -1) front = 0;
                rear = (rear + 1) % size;
                arr[rear] = data;
                return 0;
            }
            return -1;
        }

        int top(){
            return arr[front];

        }

        int pop(){
            if(isEmpty()){
                return -1;
            }
            int k = arr[front];
            if(front==rear){
                front = -1;
                rear = -1;
            }
            else{
                front = (front+1)%size;
            }
            return k;

        }

};