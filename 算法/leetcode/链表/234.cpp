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
        bool isPalindrome(ListNode* head) {
            ListNode* fast = head;
            ListNode* slow = head;
            while(fast && fast->next){
                ListNode* temp = fast -> next;
                fast = temp -> next;
                slow = slow -> next;
            }
            //反转后半部分
            ListNode* prev = nullptr;
            ListNode* cur = slow;
            while(cur){
                ListNode*next = cur->next;
                cur -> next = prev;
                prev = cur;
                cur = next;
            }
            //比较
            ListNode* temp1 = head;
            ListNode* temp2 = prev;
            while(temp2){
                if(temp1->val!=temp2->val){
                    return false;
                }
                temp1 = temp1->next;
                temp2 = temp2->next;
            }
            return true;
        }
    };