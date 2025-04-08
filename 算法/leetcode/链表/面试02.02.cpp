class Solution {
    public:
        int kthToLast(ListNode* head, int k) {
            ListNode* dummy = new ListNode(0);
            ListNode* fast = dummy;
            ListNode* slow = dummy;
            for(int i = 0;i < k;i++){
                fast = fast->next;
            }
            while(fast->next!= nullptr){
                fast = fast->next;
                slow = slow->next;
            }
            return slow->val;
        }
    };