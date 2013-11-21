#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_MAX 100

struct s_btree_node
{
    char *value;

    struct s_btree_node *left;
    struct s_btree_node *right;
};

struct s_btree_node *btree_find_closet(struct s_btree_node *root, char *value)
{
    if (strcmp(value, root->value) > 0)
    {
        if (root->right == 0)
        {
            return root;
        }
        return btree_find_closet(root->right, value);
    }
    if (strcmp(value, root->value) < 0)
    {
        if (root->left == 0)
        {
            return root;
        }
        return btree_find_closet(root->left, value);
    }

    printf("FUCKING EQUALS\n");
    exit(-1);
}

void btree_add(struct s_btree_node *root, char *value)
{
    struct s_btree_node *new_node;
    struct s_btree_node *cl_node;
    char *value_copy;

    new_node = (struct s_btree_node *) malloc(sizeof (struct s_btree_node));
    new_node->left = 0;
    new_node->right = 0;
    value_copy = malloc(sizeof(char) * strlen(value));
    strcpy(value_copy, value);
    new_node->value = value_copy;

    cl_node = btree_find_closet(root, value);
    if (strcmp(value, cl_node->value) > 0)
    {
        printf("adding [%s] on the right of [%s]\n", new_node->value, cl_node->value);
        cl_node->right = new_node;
    }
    else if (strcmp(value, cl_node->value) < 0)
    {
        printf("adding [%s] on the left of [%s]\n", new_node->value, cl_node->value);
        cl_node->left = new_node;
    }
    else {
        printf("FUCKING EQUALS (2)[%s] [%s]\n", value, cl_node->value);
        exit(-1);
    }
}


int main(int argc, char **argv)
{
    struct s_btree_node *btree_root;
    int nb_read;
    char buffer[BUFFER_MAX];

    btree_root = (struct s_btree_node *) malloc(sizeof (struct s_btree_node));
    btree_root->left = 0;
    btree_root->right = 0;
    btree_root->value = "0";


    while ((nb_read = read(0, buffer, BUFFER_MAX)) > 0)
    {
        buffer[nb_read] = '\0';
        printf("buffer [%s]\n", buffer);
        btree_add(btree_root, buffer);
    }

    return 0;
}

