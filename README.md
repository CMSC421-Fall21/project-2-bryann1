Author: Bryan Nguyen
Date: 10/28/2021
CMSC 421 Project 2

/****************
*****README*****
****************/

init_buffer_421: 
	I declared a global static node pointer variable for the circular 
	buffer to hold all nodes. 
	I also made sure to have the program exit in case if the circular 
	buffer already exists. 
	Then I had the program loop 20 times (SIZE_OF_BUFFER) to 
	create 20 nodes. We add each node using the head and a temp node. 
	The read and write node will point to head initially so we can later 
	use write to traverse in insert.

insert_buffer_421: 
	We have a write node that points to head initially and we use that 
	to traverse. Have if statements to prevent insertion if size is maxed
	and if the buffer does not exist. If buffer exists and size is not maxed, 
	then have a write node starting at read, change data of current node,
	then iterate write to its next node.

print_buffer_421: 
	I made the program exit in case if the circular buffer does not exist. 
	Made a temp node to point to head so we could iterate. 
	We have a loop where we check to see if temp->next is equal to head 
	node and print each node as we go. Then we have to do one last 
	iteration of print for the node right before head. 

delete_buffer_421: 
	I had an if statement to prevent delete_buffer_421 from running in 
	case if the buffer did not exist or if the head node did not exist. 
	Created a while loop in which the program checks whether temp->next 
	is head (finding the tail node). Then the tail->next will be 
	the node after head. After deleting the original head node we will 
	declare the tail->next to be the new head. We also free nodes as 
	we go, do one more iteration of deletion of the head 
	node itself, and free the circular buffer object.

