class MyLinkedList {
    private:
        struct Listnode{
            int val;
            Listnode* next;
    
            Listnode():val(0),next(nullptr){}
            Listnode(int v):val(v),next(nullptr){}
            Listnode(int v,Listnode* n):val(v),next(n){}
        };
        int len;
        Listnode* dummyhead;
    public:
        MyLinkedList() {
            len=0;
            dummyhead=new Listnode();
        }
        
        int get(int index) {
            if(index<0||index>len-1) return -1;
            Listnode* head=dummyhead->next;
            while(index--) head=head->next;
            return head->val;
        }
        
        void addAtHead(int val) {
            if(val<0||val>1000) return;
            Listnode* n=new Listnode(val);
            n->next=dummyhead->next;
            dummyhead->next=n;
            len++;
        }
        
        void addAtTail(int val) {
            if(val<0||val>1000) return;
            Listnode* n=new Listnode(val),*cur=dummyhead;
            while(cur->next) cur=cur->next;
            cur->next=n;
            len++;
        }
        
        void addAtIndex(int index, int val) {
            if(val<0||val>1000||index>len) return;
            if(index<=0) addAtHead(val);
            else if(index==len) addAtTail(val);
            else{
                Listnode* n=new Listnode(val),*cur=dummyhead;
                while(index--) cur=cur->next;
                n->next=cur->next;
                cur->next=n;
                len++;
            }
        }
        
        void deleteAtIndex(int index) {
            if(index<0||index>len-1) return;
            Listnode* cur=dummyhead,*t=nullptr;
            while(index--) cur=cur->next;
            t=cur->next;
            cur->next=t->next;
            delete t;
            len--;
        }
    };
    
    /**
     * Your MyLinkedList object will be instantiated and called as such:
     * MyLinkedList* obj = new MyLinkedList();
     * int param_1 = obj->get(index);
     * obj->addAtHead(val);
     * obj->addAtTail(val);
     * obj->addAtIndex(index,val);
     * obj->deleteAtIndex(index);
     */
    