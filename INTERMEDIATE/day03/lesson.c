/*
 * Intermediate Day 03 — Binary Search Tree
 * Compile: gcc lesson.c -o lesson.exe
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct BTNode {
    int data;
    struct BTNode *left, *right;
} BTNode;

BTNode* bt_new(int val) {
    BTNode *n = malloc(sizeof(BTNode));
    n->data=val; n->left=n->right=NULL;
    return n;
}

BTNode* bst_insert(BTNode *root, int val) {
    if (!root) return bt_new(val);
    if (val < root->data)      root->left  = bst_insert(root->left,  val);
    else if (val > root->data) root->right = bst_insert(root->right, val);
    return root;
}

BTNode* bst_search(BTNode *root, int val) {
    if (!root || root->data == val) return root;
    if (val < root->data) return bst_search(root->left, val);
    return bst_search(root->right, val);
}

BTNode* bst_min(BTNode *root) {
    while (root && root->left) root = root->left;
    return root;
}

BTNode* bst_delete(BTNode *root, int val) {
    if (!root) return NULL;
    if      (val < root->data) root->left  = bst_delete(root->left,  val);
    else if (val > root->data) root->right = bst_delete(root->right, val);
    else {
        if (!root->left)  { BTNode *r = root->right; free(root); return r; }
        if (!root->right) { BTNode *l = root->left;  free(root); return l; }
        BTNode *succ = bst_min(root->right);
        root->data  = succ->data;
        root->right = bst_delete(root->right, succ->data);
    }
    return root;
}

void inorder(const BTNode *root)   { if(!root)return; inorder(root->left); printf("%d ",root->data); inorder(root->right); }
void preorder(const BTNode *root)  { if(!root)return; printf("%d ",root->data); preorder(root->left); preorder(root->right); }
void postorder(const BTNode *root) { if(!root)return; postorder(root->left); postorder(root->right); printf("%d ",root->data); }

int bt_height(const BTNode *root) {
    if (!root) return 0;
    int l = bt_height(root->left), r = bt_height(root->right);
    return 1 + (l > r ? l : r);
}

int bt_count(const BTNode *root) {
    if (!root) return 0;
    return 1 + bt_count(root->left) + bt_count(root->right);
}

void bt_free(BTNode *root) {
    if (!root) return;
    bt_free(root->left); bt_free(root->right); free(root);
}

void print_tree(const BTNode *root, int level) {
    if (!root) return;
    print_tree(root->right, level + 1);
    for (int i = 0; i < level; i++) printf("    ");
    printf("%d\n", root->data);
    print_tree(root->left, level + 1);
}

int main(void) {
    printf("=== Intermediate Day 03: Binary Search Tree ===\n\n");

    BTNode *root = NULL;
    int vals[] = {50, 30, 70, 20, 40, 60, 80, 10, 25};
    for (int i = 0; i < 9; i++) root = bst_insert(root, vals[i]);

    printf("Tree (rotated, right=up):\n");
    print_tree(root, 0);

    printf("\nIn-order   (sorted): "); inorder(root);   printf("\n");
    printf("Pre-order           : "); preorder(root);  printf("\n");
    printf("Post-order          : "); postorder(root); printf("\n");
    printf("Height: %d  Count: %d\n", bt_height(root), bt_count(root));

    printf("\nSearch 40: %s\n", bst_search(root, 40) ? "found" : "not found");
    printf("Search 55: %s\n", bst_search(root, 55) ? "found" : "not found");

    root = bst_delete(root, 30);
    printf("\nAfter delete(30) in-order: "); inorder(root); printf("\n");

    bt_free(root);
    return 0;
}
