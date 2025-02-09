struct node{
    int data;
    struct node* next;
};

typedef struct node node;

void add_beg(node** head,int data){
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = *head;
    *head = new_node;
}

int hashFn(int val,int table_size){
    int index = abs(val%table_size);
    return index;
}

int repeated(node* head,int val){
    int count = 0;
    while(head){
        if(head->data==val){
            count++;
        }
        if(count>1){
            return 1;
        }
        head = head->next;
    }
    return 0;
}

void freeList(node* head){
    node* temp = head;
    while(head){
        head = head->next;
        free(temp);
        temp = head;
    }
}

bool containsDuplicate(int* nums, int numsSize) {
    node** hashMap = (node**)malloc(numsSize*sizeof(node*));
    int index = 0;
    for(int i=0;i<numsSize;i++){
        hashMap[i] = NULL;
    }
    for(int i=0;i<numsSize;i++){
        index = hashFn(nums[i],numsSize);
        add_beg(&hashMap[index],nums[i]);
        if(repeated(hashMap[index],nums[i])){
            for(int i=0;i<numsSize;i++){
                freeList(hashMap[i]);
            }
            free(hashMap);
            return true;
        }
    }

    for(int i=0;i<numsSize;i++){
        freeList(hashMap[i]);
    }
    free(hashMap);
    return false;
}