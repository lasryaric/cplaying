struct btree_node
{
    char *value;

    struct btree_node *left;
    struct btree_node *right;
};
