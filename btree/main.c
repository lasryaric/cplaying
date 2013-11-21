#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct s_btree_node
{
    char *value;

    struct s_btree_node *left;
    struct s_btree_node *right;
};

struct s_btree_node *btree_find_closet(struct s_btree_node *root, char *value)
{
    struct s_btree_node *current_node;
    current_node = root;
    while (1)
    {
        if (strcmp(value, current_node->value) > 0)
        {
            if (current_node->right)
            {
                current_node = current_node->right;
                continue;
            }
            return current_node;
        }
        if (strcmp(value, current_node->value) < 0)
        {
            if (current_node->left)
            {
                current_node = current_node->left;
                continue;
            }
            return current_node;
        }
        break;
    }

    return current_node;
}

void btree_add(struct s_btree_node *node, char *value)
{
    struct s_btree_node *new_node;
    struct s_btree_node *closest_node;
    new_node = (struct s_btree_node *) malloc(sizeof (struct s_btree_node));
    new_node->value = value;
    closest_node = btree_find_closet(node, new_node->value);
    if (strcmp(value, closest_node->value) > 0)
    {
        closest_node->right = new_node;
    }
    if (strcmp(value, closest_node->value) < 0)
    {
        closest_node->left = new_node;
    }
}

int main(int argc, char **argv)
{
    struct s_btree_node *btree_root;
    btree_root = (struct s_btree_node *) malloc(sizeof (struct s_btree_node));
    btree_root->left = 0;
    btree_root->right = 0;
    btree_root->value = "b";
    btree_add(btree_root, "a");
    btree_add(btree_root, "c");
    btree_add(btree_root, "d");
    btree_add(btree_root, "f");
    btree_add(btree_root, "e");
    printf("%s %s %s %s %s %s\n", btree_root->value, btree_root->left->value, btree_root->right->value, btree_root->right->right->value,
        btree_root->right->right->right->value, btree_root->right->right->right->left->value);

    return 0;
}

