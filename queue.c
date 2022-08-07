#include "queue.h"

#define TYPE int
#define Q_NOT_EXIST_SIZE -333
#define COPY_ERROR_COUNTER -444

#define INCREASE_IN 2
#define DECREASE_IN 3

// TODO - your code
queue_t *create_queue(int capacity)
{
    if (capacity == 0)
    {
        fprintf(stderr, "Error: can't create a queue in zero capacity.\n");
        return NULL;
    }
    queue_t *self = (queue_t *)malloc(sizeof(queue_t));
    if (self == NULL)
    {
        fprintf(stderr, "Error: allocation fault.\n");
        return NULL;
    }
    self->rear = 0;
    self->front = 0;
    self->len = capacity;
    self->data = (TYPE **)malloc(sizeof(TYPE *) * capacity);
    if (self->data == NULL)
    {
        fprintf(stderr, "Error: allocation fault.\n");
        return NULL;
    }

    return self;
}

void delete_queue(queue_t *queue)
{
    if (queue != NULL)
    {
        free(queue->data);
        free(queue);
    }
}

bool push_to_queue(queue_t *queue, void *data)
{
    if (queue->data == NULL || queue == NULL)
    {
        fprintf(stderr, "Error: queue doesn't exist.\n");
        return false;
    }

    int next_rear = (queue->rear + 1) % queue->len;
    if (next_rear == queue->front) // queue is full
    {
        queue->len *= INCREASE_IN;
        TYPE **temp = (TYPE **)realloc(queue->data,
                                       sizeof(TYPE *) * queue->len);
        if (temp == NULL)
        {
            fprintf(stderr, "Error: reallocation fault.\n");
            return false;
        }
        queue->data = temp;
        next_rear = (queue->rear + 1) % queue->len;
    }

    queue->data[queue->rear] = (TYPE *)data;
    queue->rear = next_rear;
    return true;
}

void *pop_from_queue(queue_t *queue)
{
    if (queue == NULL)
    {
        fprintf(stderr, "Error: queue doesn't exist.\n");
        return NULL;
    }
    if (queue->front == queue->rear) // empty queue
    {
        return NULL;
    }
    if (get_queue_size(queue) < queue->len / 3 && get_queue_size(queue) != 0)
    {
        TYPE **temp = malloc(sizeof(TYPE *) * (queue->len / DECREASE_IN + 1));
        if (temp == NULL)
        {
            fprintf(stderr, "Error: decrease allocation faul.\n");
            // no decrease
        }
        int counter = copy_data(queue, queue->data, temp);
        if (counter != COPY_ERROR_COUNTER)
        {
            free(queue->data);
            queue->data = temp; // new data array
            // new indexes:
            queue->len = queue->len / DECREASE_IN + 1;
            queue->front = 0;
            queue->rear = counter - 1; // -1 (rear idx is empty)
        }
        else
        {
            free(temp);
            fprintf(stderr, "Error: can't copy data for decreasing queue.");
            // no decrease
        }
    }

    int next = (queue->front + 1) % queue->len;
    TYPE *data = queue->data[queue->front];
    queue->front = next;

    return data;
}

void *get_from_queue(queue_t *queue, int idx)
{
    if (queue == NULL)
    {
        fprintf(stderr, "Error: queue doesn't exist.\n");
        return NULL;
    }
    if (queue->front == queue->rear) // empty queue
    {
        return NULL;
    }
    if (idx >= queue->len || idx < 0) // index out of range
    {
        return NULL;
    }

    int real_idx = (idx + queue->front) % queue->len; // real idx in array
    if (real_idx >= queue->rear)
    {
        return NULL;
    }

    return queue->data[real_idx];
}

int get_queue_size(queue_t *queue)
{
    if (queue == NULL)
    {
        fprintf(stderr, "Error: queue doesn't exist.\n");
        return Q_NOT_EXIST_SIZE;
    }

    int size;
    size = queue->rear - queue->front;
    if (size < 0) // +full cykle
    {
        return queue->len + size;
    }

    return size;
}

int copy_data(queue_t *queue, TYPE **from, TYPE **to)
{
    if (!queue || !from || !to)
    {
        fprintf(stderr, "Error: copy error.\n");
        return COPY_ERROR_COUNTER;
    }
    int c = 0; // counter for new array (new rear - 1)
    for (int i = queue->front; i != queue->rear + 1; ++i, ++c)
    {
        if (i == queue->len)
        {
            i = 0;
        }
        if (i != queue->rear) // rear position -> no element
        {
            to[c] = from[i];
        }
    }

    return c;
}
