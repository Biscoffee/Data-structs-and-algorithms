class Solution {
    public:
        ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
            // 特判
            if (!headA || !headB) return nullptr; 
    
            ListNode* temp1 = headA;
            ListNode* temp2 = headB;
            int l1 = 0, l2 = 0;
    
            // 计算链表 A 的长度
            while (temp1) {
                l1++;
                temp1 = temp1->next;
            }
    
            // 计算链表 B 的长度
            while (temp2) {
                l2++;
                temp2 = temp2->next;
            }
    
            // 计算长度差
            int dis = abs(l1 - l2);
            temp1 = headA;
            temp2 = headB;
    
            // 让长链表先走 `dis` 步
            if (l1 > l2) {
                for (int i = 0; i < dis; i++) {
                    if (!temp1) return nullptr; // 避免访问空指针
                    temp1 = temp1->next;
                }
            } else {
                for (int i = 0; i < dis; i++) {
                    if (!temp2) return nullptr; // 避免访问空指针
                    temp2 = temp2->next;
                }
            }
    
            // 找到相交点
            while (temp1 && temp2) {
                if (temp1 == temp2) return temp1; // 返回交点
                temp1 = temp1->next;
                temp2 = temp2->next;
            }
    
            return nullptr; // 无交点
        }
    };