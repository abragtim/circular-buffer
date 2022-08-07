# circular-buffer
 
create a new queue with a given size

    queue_t* create_queue(int capacity);

delete the queue and all allocated memory

    void delete_queue(queue_t *queue);

insert a reference to the element into the queue
return: true on success; false otherwise

    bool push_to_queue(queue_t *queue, void *data);

get the first element from the queue and removes it from the queue
return: the first element on success; NULL otherwise

    void* pop_from_queue(queue_t *queue);

get idx-th element from the queue, i.e., it returns the element that 
will be popped after idx calls of the pop_from_queue()
return: the idx-th element on success; NULL otherwise

    void* get_from_queue(queue_t *queue, int idx);

get number of stored elements

    int get_queue_size(queue_t *queue);

copy data from one queue to the new queue

    int copy_data(queue_t *queue, TYPE** from, TYPE** to);
    
P.S. Сompleted as part of the homework for the subject "BAB36PRGA - Programování v C" 23.04.2022
