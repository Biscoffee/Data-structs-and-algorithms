class Solution {
    public:
        ListNode* removeDuplicateNodes(ListNode* head) {
            sort(head);
            ListNode* curr = head;
            while (curr && curr->next) {
                if (curr->val == curr->next->val) {
                    ListNode* temp = curr->next;
                    curr->next = curr->next->next;
                    delete temp; // 释放内存
                } else {
                    curr = curr->next;
                }
            }
            return head;
        }
    };

    class Solution {
        public:
            ListNode* removeDuplicateNodes(ListNode* head) {
                ListNode* ob = head;
                while (ob != nullptr) {
                    ListNode* oc = ob;
                    while (oc->next != nullptr) {
                        if (oc->next->val == ob->val) {
                            oc->next = oc->next->next;
                        } else {
                            oc = oc->next;
                        }
                    }
                    ob = ob->next;
                }
                return head;
            }
        };
      