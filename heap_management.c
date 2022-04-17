#include <stdio.h>
#include<stdlib.h>

int c1 = 0, c2 = 0;

struct f_list_nodes
{
    int node_num;
    int size;
    struct f_list_nodes *next;
};

struct f_list_nodes *free_head = NULL, *prev_free = NULL;

struct allocate
{
    int id;
    int node_num;
    int size;
    struct allocate *next;
};
struct allocate *allocate_head = NULL, *prev_allocate = NULL;

void create_free_list(int c)
{
    struct f_list_nodes *p = (struct f_list_nodes *)malloc(sizeof(struct f_list_nodes));
    p->size = c;
    p->node_num = c1;
    p->next = NULL;
    if (free_head == NULL)
    {
        free_head = p;
    }
    else
    {
        prev_free->next = p;
    }
    prev_free = p;
    c1++;
}

void create_allocate_list(int c)
{
    struct allocate *q = (struct allocate *)malloc(sizeof(struct allocate));
    q->size = c;
    q->node_num = c2;
    q->next = NULL;
    struct f_list_nodes *p = free_head;

    while (p != NULL)
    {
        if (q->size <= p->size)
            break;
        p = p->next;
    }

    if (p != NULL)
    {
        q->id = p->node_num;
        p->size -= q->size;
        if (allocate_head == NULL)
            allocate_head = q;
        else
        {
            prev_allocate = allocate_head;
            while (prev_allocate->next != NULL)
                prev_allocate = prev_allocate->next;
            prev_allocate->next = q;
        }
        c2++;
    }
    else
        printf("Block of size %d cannot be allocated\n",c);
}

void print_free_list()
{
    struct f_list_nodes *p = free_head;
    printf("Index\tBlock Size\n");
    while (p != NULL)
    {
    	printf("%d\t%d\n",p->node_num,p->size);
        p = p->next;
    }
}

void print_allocate_list()
{
    struct allocate *p = allocate_head;
    printf("Index\tBlock ID\tProcess Size\n");
    while (p != NULL)
    {
    	printf("%d\t%d\t\t%d\n",p->node_num,p->id,p->size);
        p = p->next;
    }
}

void delete_allocate_list(int t)
{
    struct allocate *p = allocate_head, *q = NULL;
    while (p != NULL)
    {
        if (p->node_num == t)
            break;
        q = p;
        p = p->next;
    }
    if (p == NULL)
        printf("Unique ID doesn't exist\n");
    else if (p == allocate_head)
        allocate_head = allocate_head->next;
    else
        q->next = p->next;
    struct f_list_nodes *temp = free_head;
    while (temp != NULL)
    {
        if (temp->node_num == p->id)
        {
            temp->size += p->size;
            break; 
        }
        temp = temp->next;
    }
}

int main()
{
    int i;
    printf("enter the number of blocks in free list of the memory : \n");
    int num_of_blocks;
    scanf("%d",&num_of_blocks);
    int blockSize[num_of_blocks];
    printf("enter the block sizes of the free list : \n");
    for ( i = 0; i < num_of_blocks; i++)
    {
        scanf("%d",&blockSize[i]);
    }

    printf("enter the number of blocks to be allocated :\n");
    int num_of_allocate;
    scanf("%d", &num_of_allocate);
    int processSize[num_of_allocate];
    printf("enter the processes sizes :\n");
    for (i = 0; i < num_of_allocate; i++)
    {
        scanf("%d", &processSize[i]);
    }
	
    for (i = 0; i < num_of_blocks; i++)
    {
        create_free_list(blockSize[i]);
    }
    print_free_list();
    for (i = 0; i < num_of_allocate; i++)
    {
        create_allocate_list(processSize[i]);
    }

    print_allocate_list();
	print_free_list();
    int x;
    printf("enter the index to be deleted: ");
    scanf("%d",&x);
    delete_allocate_list(x);
    print_free_list();
    print_allocate_list();

}