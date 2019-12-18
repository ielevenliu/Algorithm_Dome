/*
*@Author:lwl
*@Date:2019-12-08
*@Description:牛客网BSTree转有序双向链表
*             技巧：递归中序遍历 + 记住前一个节点
*/
class Solution {
public:
    TreeNode* preNode = NULL;
    TreeNode* res = NULL;
    void Process(TreeNode* pRootOfTree) {
        if (pRootOfTree == NULL) {
            return;
        }
        Process(pRootOfTree->left);
        if (preNode == NULL) {
            pRootOfTree->left = NULL;
            res = pRootOfTree;
        }
        else {
            pRootOfTree->left = preNode;
            preNode->right = pRootOfTree;
        }
        preNode = pRootOfTree;
        Process(pRootOfTree->right);
    }
    
    TreeNode* Convert(TreeNode* pRootOfTree){
        if (pRootOfTree != NULL) {
            Process(pRootOfTree);
        }
        return res;
    }
};
