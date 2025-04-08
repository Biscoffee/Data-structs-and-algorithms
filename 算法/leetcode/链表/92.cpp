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
        ListNode* reverseBetween(ListNode* head, int left, int right) {
            ListNode* dummy = new ListNode(0);
            dummy->next = head;
            ListNode* p0 = dummy;  // 指向left的前一个节点
            for(int i = 1; i < left; i++){
               p0 = p0->next;   // 找到left的前一个节点
            }
            // 此时prev指向left的前一个节点，curr指向left节点
            // 开始反转
            ListNode* prev = nullptr;
            ListNode* curr = p0->next;
            for(int i = left; i <= right; i++){
                ListNode* next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }
            p0 -> next ->next = curr;
            p0 -> next = prev;
            return dummy->next;

        }
    };