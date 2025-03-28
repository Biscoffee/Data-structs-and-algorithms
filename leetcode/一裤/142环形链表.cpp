/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    public:
        ListNode *detectCycle(ListNode *head) {
            ListNode* fast = head;
            ListNode* slow = head;
            while(fast && fast -> next){
                fast = fast -> next -> next;
                slow = slow -> next;
                if(fast == slow){
                    ListNode* temp1 = head;
                    ListNode* temp2 = slow;
                    while(temp1 != temp2){
                        temp1 = temp1->next;
                        temp2 = temp2-> next;
                    }
                    return temp1;
                }
            }
            return NULL;
        }
    };