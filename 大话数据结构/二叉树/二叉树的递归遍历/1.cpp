void preorder(TreeNode* root) {
    if (!root) return;
    stack<TreeNode*> s;
    s.push(root);                           
    while (!s.empty()) {
        TreeNode* node = s.top();
        s.pop();
        cout << node->val << " ";
        if (node->right) s.push(node->right);
        if (node->left) s.push(node->left);
    }
}