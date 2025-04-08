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
        bool hasCycle(ListNode *head) {
            ListNode* temp= head;
            unordeded_map<ListNode*,int> map;
            while(temp!=NULL){
                if(map[temp]!=0){
                    return true;
                }
                map[temp]++;
                temp = temp->next;
            }   
            return false;
        }
};