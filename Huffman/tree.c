#include "tree.h"

Node  *merge_nodes(Heap *heap) {
	if(heap->size != 1){
		Node *left = dequeue(heap);
		Node *right = dequeue(heap);
		lli new_frequency = left->frequency +right->frequency;
		Node *new_node = create_node('*',new_frequency);
		new_node->left = left;
		new_node->right = right;
		enqueue(heap,new_node);
	}else{
		Node *tree = heap->data[1];
        return tree;
	}

}

Node *create_tree_compact(Heap *heap) {
    int i;
    Node *tree = NULL;
	for(i = heap->size; i >= 1; i--){
		tree = merge_nodes(heap);
	}
    return tree;
}