/*
 * Int Day 03 Mini-Project — BST-based word frequency counter
 * Compile: gcc mini_project.c -o mini_project.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct WNode {
    char word[64]; int count;
    struct WNode *left, *right;
} WNode;

WNode* wnode_new(const char *w) {
    WNode *n = calloc(1, sizeof(WNode));
    strncpy(n->word, w, 63); n->count = 1;
    return n;
}

WNode* wbst_insert(WNode *root, const char *w) {
    if (!root) return wnode_new(w);
    int cmp = strcmp(w, root->word);
    if      (cmp < 0) root->left  = wbst_insert(root->left,  w);
    else if (cmp > 0) root->right = wbst_insert(root->right, w);
    else              root->count++;
    return root;
}

void wbst_print(const WNode *root) {
    if (!root) return;
    wbst_print(root->left);
    printf("  %-20s : %d\n", root->word, root->count);
    wbst_print(root->right);
}

void wbst_free(WNode *root) {
    if (!root) return;
    wbst_free(root->left); wbst_free(root->right); free(root);
}

int main(void) {
    char line[1024];
    WNode *root = NULL;
    printf("=== Word Frequency Counter ===\n");
    printf("Enter text (blank line to finish):\n");
    while (fgets(line, sizeof(line), stdin)) {
        if (line[0]=='\n' || line[0]=='\r') break;
        char *tok = strtok(line, " \t\n\r.,!?;:");
        while (tok) {
            char lc[64]; int i;
            for (i=0; tok[i] && i<63; i++) lc[i]=(char)tolower((unsigned char)tok[i]);
            lc[i]='\0';
            root = wbst_insert(root, lc);
            tok = strtok(NULL, " \t\n\r.,!?;:");
        }
    }
    printf("\nWord frequencies (alphabetical):\n");
    wbst_print(root);
    wbst_free(root);
    return 0;
}
