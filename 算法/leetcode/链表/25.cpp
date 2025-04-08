/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
    public:
        ListNode* reverseKGroup(ListNode* head, int k) {
            int n = 0;
            for(ListNode* cur = head;cur;cur = cur -> next){
                n++;
            }
            ListNode dummy(0,head);
            ListNode* p0 = &dummy;
            ListNode* prev = nullptr;
            ListNode* cur = head;
            for(; n >= k;n -= k){
                for(int i = 0; i < k;i++){
                    ListNode* next = cur -> next;
                    cur -> next = prev;
                    prev = cur;
                    cur = next;
                }
                ListNode* nxt = p0 -> next;
                p0->next->next = cur;
                p0 -> next = prev;
                p0 = nxt;
            }
            return dummy.next;
    }
};