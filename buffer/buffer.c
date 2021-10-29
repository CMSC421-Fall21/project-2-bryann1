#include "buffer.h"
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/slab.h>

static ring_buffer_421_t *circle = NULL;

SYSCALL_DEFINE0(init_buffer_421){
	int i;
	// if buffer exists then do not create one
	if(circle != NULL){
		printk("Buffer exists!\n");
		return -1;
	}

	// make the buffer
	circle = (ring_buffer_421_t*) kmalloc(sizeof(ring_buffer_421_t), GFP_KERNEL);
	circle->length = 0;
	circle->read = NULL;
	circle->write = NULL;

	// make 20 nodes 
	for(i = 0; i < SIZE_OF_BUFFER; i++){
		// create the node
		node_421_t *node = (node_421_t*) kmalloc(sizeof(node_421_t), GFP_KERNEL);
		node->data = 0;

		// node to iterate
		node_421_t *temp;

		// making the very first node
		if(circle->read == NULL){
			circle->read = node;
			circle->write = node;
			node->next = circle->read;
		}

		else{
			temp = circle->read;
			// find the node right before head
			while(temp->next != circle->read)
				temp = temp->next;

			// new node inserted at tail and points to head
			node->next = circle->read;
			// former tail now points to new tail
			temp->next = node;
		}

	}

	return 0;
}

SYSCALL_DEFINE1(insert_buffer_421, int, i){
	printk("Inserting %d\n", i);
	// if buffer is unitialized do not insert
	if(circle == NULL){
		printk("Uninitialized buffer!\n");
		return -1;
	}

	// check to see if buffer is full or not
	if(circle->length >= SIZE_OF_BUFFER){
		printk("Buffer is full! Cannot insert %d!\n", i);
		return -1;
	}
	
	// buffer is not full	
	else{
		// put data into that node, iterate to next available node
		// then increment length
		circle->write->data = i;
		circle->write = circle->write->next;
		circle->length++;
	}

	return 0;
}

SYSCALL_DEFINE0(print_buffer_421){
	// if buffer is uninitialized
	if(circle == NULL){
		printk("Buffer does not exist!\n");
		return -1;
	}

	if(circle->length == 0){
		printk("You have no nodes to print!\n");
		return -1;
	}

	// temp node to iterate
	node_421_t *temp = circle->read;

	// print each data except last
	while(temp->next != circle->read){
		printk("%d\n", temp->data);
		temp = temp->next;
	}
	
	// print last data
	printk("%d\n", temp->data);

	return 0;
}

SYSCALL_DEFINE0(delete_buffer_421){
	// if buffer does not exist
	if(circle == NULL){
		printk("Nothing circular buffer to delete!\n");
		return -1;
	}

	// if no nodes exist
	else if(circle->read == NULL){
		printk("No nodes to delete!\n");
		return -1;
	}

	// delete like usual
	while(circle->read->next != circle->read){
		node_421_t *temp = circle->read;
		while(temp->next != circle->read)
			temp = temp->next;

		// link the tail to the node after head
		temp->next = circle->read->next;
		kfree(circle->read);
		// new head will be the former head->next node
		circle->read = temp->next;
	}

	// delete last node
	kfree(circle->read);
	circle->read = NULL;

	// delete the buffer itself
	kfree(circle);
	circle = NULL;
	return 0;
}
