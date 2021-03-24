typedef struct{
    node *first;
    int len;
    node *last;
}list;
typedef struct{
    node *next;
    int val;
    node *past;
}node;
void create(list *l){
    l->len=0;
    l->first=-1;
    l->last=-1;
}
node *get_last(list l){
    return l.last;
}
void add(list *l,int val){
    node *n=malloc(sizeof(node));
    if(n==-1)perror();
    n->val=val;
    n->past=l->last;
    if(l->len==0)
        l->first=l->last=n;
    else
        l->last->next=n;
    l->len++;
}
