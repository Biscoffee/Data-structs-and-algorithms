class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* dummy = new ListNode(0); // 虚拟头节点
        ListNode* newCur = dummy; // 新链表的当前节点
        ListNode* cur = head; // 原链表的当前节点

        while(cur){
            if(cur->val != newCur->val){
                newCur->next = cur;
                newCur = newCur->next;
            }
            cur = cur->next;
        }

        return dummy->next; // 返回新链表的头节点
    }
};

