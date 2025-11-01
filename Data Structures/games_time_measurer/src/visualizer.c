#include <stdio.h>

#include "visualizer.h"

void avlGenerateDotRecursive(AvlNode *r, FILE *f) {
    if (r != NULL) {
        // Define the current node's appearance, with Balance Factor
        fprintf(f, "  \"%p\" [label=\"%s\\n(BF: %d)\"];\n",
                r, r->info.name, r->bf);

        if (r->left) {
            fprintf(f, "  \"%p\" -> \"%p\";\n", r, r->left);
            avlGenerateDotRecursive(r->left, f);
        } else {
            fprintf(f, "  \"null_l_%p\" [label=\"NULL\", shape=point];\n", r);
            fprintf(f, "  \"%p\" -> \"null_l_%p\";\n", r, r);
        }

        if (r->right) {
            fprintf(f, "  \"%p\" -> \"%p\";\n", r, r->right);
            avlGenerateDotRecursive(r->right, f);
        } else {
            fprintf(f, "  \"null_r_%p\" [label=\"NULL\", shape=point];\n", r);
            fprintf(f, "  \"%p\" -> \"null_r_%p\";\n", r, r);
        }
    }
}

void avlGenerateDotFile(AvlNode *r, char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Could not open file %s for writing.\n", filename);
        return;
    }

    fprintf(f, "digraph AVL {\n");
    fprintf(f, "  node [fontname=\"Arial\"];\n");
    if (r == NULL) {
        fprintf(f, "  empty [label=\"NULL\", shape=point];\n");
    } else {
        avlGenerateDotRecursive(r, f);
    }
    fprintf(f, "}\n");
    fclose(f);
}

void bstGenerateDotRecursive(BstNode *r, FILE *f) {
    if (r != NULL) {
        // Define the current node's appearance
        // Using the pointer as a unique ID
        fprintf(f, "  \"%p\" [label=\"%s\"];\n", r, r->info.name);

        if (r->left) {
            fprintf(f, "  \"%p\" -> \"%p\";\n", r, r->left);
            bstGenerateDotRecursive(r->left, f);
        } else {
            fprintf(f, "  \"null_l_%p\" [label=\"NULL\", shape=point];\n", r);
            fprintf(f, "  \"%p\" -> \"null_l_%p\";\n", r, r);
        }

        if (r->right) {
            fprintf(f, "  \"%p\" -> \"%p\";\n", r, r->right);
            bstGenerateDotRecursive(r->right, f);
        } else {
            fprintf(f, "  \"null_r_%p\" [label=\"NULL\", shape=point];\n", r);
            fprintf(f, "  \"%p\" -> \"null_r_%p\";\n", r, r);
        }
    }
}

void bstGenerateDotFile(BstNode *r, char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Could not open file %s for writing.\n", filename);
        return;
    }

    fprintf(f, "digraph BST {\n");
    fprintf(f, "  node [fontname=\"Arial\"];\n");
    if (r == NULL) {
        fprintf(f, "  empty [label=\"NULL\", shape=point];\n");
    } else {
        bstGenerateDotRecursive(r, f);
    }
    fprintf(f, "}\n");
    fclose(f);
}

void rbtGenerateDotRecursive(RbtNode *r, FILE *f) {
    if (r != NULL) {
        // Define the current node's appearance, with color!
        const char* color = isRed(r) ? "red" : "black";
        fprintf(f, "  \"%p\" [label=\"%s\", color=%s, fontcolor=%s];\n",
                r, r->info.name, color, color);

        if (r->left) {
            fprintf(f, "  \"%p\" -> \"%p\";\n", r, r->left);
            rbtGenerateDotRecursive(r->left, f);
        } else {
            fprintf(f, "  \"null_l_%p\" [label=\"NULL\", shape=point, color=black];\n", r);
            fprintf(f, "  \"%p\" -> \"null_l_%p\";\n", r, r);
        }

        if (r->right) {
            fprintf(f, "  \"%p\" -> \"%p\";\n", r, r->right);
            rbtGenerateDotRecursive(r->right, f);
        } else {
            fprintf(f, "  \"null_r_%p\" [label=\"NULL\", shape=point, color=black];\n", r);
            fprintf(f, "  \"%p\" -> \"null_r_%p\";\n", r, r);
        }
    }
}

void rbtGenerateDotFile(RbtNode *r, char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Could not open file %s for writing.\n", filename);
        return;
    }

    fprintf(f, "digraph RBT {\n");
    fprintf(f, "  node [fontname=\"Arial\"];\n");
    if (r == NULL) {
        fprintf(f, "  empty [label=\"NULL\", shape=point, color=black];\n");
    } else {
        rbtGenerateDotRecursive(r, f);
    }
    fprintf(f, "}\n");
    fclose(f);
}
