#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_MAX 100
#define STDIN 0

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

    return root;
}

void btree_add(struct s_btree_node *root, char *value)
{
    struct s_btree_node *new_node;
    struct s_btree_node *cl_node;
    char *value_copy;

    if (root == 0)
    {
        printf("root is null\n");
        exit(-1);
    }
    new_node = (struct s_btree_node *) malloc(sizeof (struct s_btree_node));
    new_node->left = 0;
    new_node->right = 0;

    if ((value_copy = malloc(sizeof(char) * strlen(value) + 10)) == 0)
    {
        printf("Malloc FAILED !!!!\n");
        exit(-1);
    }
    strcpy(value_copy, value);
    new_node->value = value_copy;
    // printf("Trying to add [%s]\n", value_copy);

    cl_node = btree_find_closet(root, value);
    if (strcmp(value, cl_node->value) > 0)
    {
        // printf("adding [%s] on the right of [%s]\n", new_node->value, cl_node->value);
        cl_node->right = new_node;
    }
    else if (strcmp(value, cl_node->value) < 0)
    {
        // printf("adding [%s] on the left of [%s]\n", new_node->value, cl_node->value);
        cl_node->left = new_node;
    }
    else {
        // printf("btree_add: [%s] = [%s] so do nothing\n", value, cl_node->value);
    }
}

struct s_btree_node * btree_find(struct s_btree_node *root, char *value, int *iteration)
{
    (*iteration)++;
    if (strcmp(value, root->value) > 0)
    {
        if (!root->right)
        {
            return 0;
        }
        return btree_find(root->right, value, iteration);
    }
    if (strcmp(value, root->value) < 0)
    {
        if (!root->left)
        {
            return 0;
        }
        return btree_find(root->left, value, iteration);
    }

    return root;
}


int main(int argc, char **argv)
{
    struct s_btree_node *btree_root;
    struct s_btree_node *btree_found;
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;

    btree_root = (struct s_btree_node *) malloc(sizeof (struct s_btree_node));
    btree_root->left = 0;
    btree_root->right = 0;
    btree_root->value = "0";

    fp = fopen(argv[1], "r");
    if (fp == NULL)
       exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        if (read < 2)
    	{
    		printf("read is %zu - exit()\n", read);
    		exit(-1);
    	}
    	line[read - 2] = '\0';
        btree_add(btree_root, line);
    }

    if ((btree_found = btree_find(btree_root, argv[2], &i))) {
        printf("FOUND !!! [%s] in %d iterations\n", btree_found->value, i);
    } else {
        printf("NOT FOUND !!! [%s] in %d iterations\n", argv[2], i);
    }

    return 0;
}

