class MyQueue {
    public:
        stack<int> stIn;
        stack<int> stOut;
        /** Initialize your data structure here. */
        MyQueue() {
    
        }
        /** Push element x to the back of queue. */
        void push(int x) {
            stIn.push(x);
        }
    
        /** Removes the element from in front of queue and returns that element. */
        int pop() {
            // 只有当stOut为空的时候，再从stIn里导入数据（导入stIn全部数据）
            if (stOut.empty()) {
                // 从stIn导入数据直到stIn为空
                while(!stIn.empty()) {
                    stOut.push(stIn.top());
                    stIn.pop();
                }
            }
            int result = stOut.top();
            stOut.pop();
            return result;
        }
    
        /** Get the front element. */
        int peek() {
            int res = this->pop(); // 直接使用已有的pop函数
            stOut.push(res); // 因为pop函数弹出了元素res，所以再添加回去
            return res;
        }
    
        /** Returns whether the queue is empty. */
        bool empty() {
            return stIn.empty() && stOut.empty();
        }
    };