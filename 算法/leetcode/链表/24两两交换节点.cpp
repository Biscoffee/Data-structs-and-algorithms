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
        ListNode* swapPairs(ListNode* head) {
            ListNode* dummy = new ListNode(0);
            dummy -> next = head;
            ListNode* node0 = dummy;
            ListNode* node1 = head;
            while (node1 && node1 -> next) {
                ListNode* node2 = node1 -> next;
                ListNode* node3 = node2 -> next;
    
                node0 -> next = node2;
                node2 -> next = node1;
                node1 -> next = node3;
    
                node0 = node1;
                node1 = node3;
            }
            return dummy -> next;
        }
    };