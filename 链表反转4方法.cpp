

struct ListNode* reverseList(struct ListNode* head) {
    if (head == NULL) {
        return head;
    }
    struct ListNode* cur = head->next; 
    struct ListNode* pre = head; 
    while (cur) {
        pre->next = cur->next; 
        cur->next = head; 
        head = cur;   
        cur = pre->next; 
    }
    return head; 
}

struct ListNode* reverse(struct ListNode* pre, struct ListNode* cur) {
    if (!cur){
        return pre;
    }
    struct ListNode* temp = cur->next;
    cur->next = pre;
    //将cur作为pre传入下一层
    //将temp作为cur传入下一层，改变其指针指向当前cur
    return reverse(cur, temp);
}

struct ListNode* reverseList(struct ListNode* head) {
    return reverse(NULL, head);
}


struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* pre = NULL;
    struct ListNode* cur = head;
    while (cur != NULL) {
        struct ListNode* temp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = temp;
    }
    return pre;
}


struct ListNode* reverse(struct ListNode* pre, struct ListNode* cur) {
    if (!cur){
        return pre;
    }
    struct ListNode* temp = cur->next;
    cur->next = pre;
    //将cur作为pre传入下一层
    //将temp作为cur传入下一层，改变其指针指向当前cur
    return reverse(cur, temp);
}

struct ListNode* reverseList(struct ListNode* head) {
    return reverse(NULL, head);
}
