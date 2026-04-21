#include <stdio.h>
#include <stdlib.h>

void displayMainMenu();
struct node* makeEmpty(struct node* L);
struct Queue* makeEmptyQ(struct Queue* L);
struct UndoStack* makeEmptyS(struct UndoStack* L);
struct node* readFile(struct node* x);
void Insertt (struct node* l,struct node* temp);
struct node* putNewNode(char text[50],int number);
void printList (struct node* L);
int IsEmpty(struct node* x);
struct Queue* enqueue(struct Queue* Q, char t[50]);
struct Queue* dequeue(struct Queue* Q);
struct UndoStack* push(struct UndoStack* top, char r [50],int index,int state);
struct UndoStack* pop(struct UndoStack* top);
void printStackpoppush(struct UndoStack*s);
void newPos(struct node*m);
struct UndoStack
{
    char addedStr[50];
    int index ;
    int state ;
    struct UndoStack*next ;
};
struct Queue
{
    char str[50];
    struct Queue* next ;
};
struct node
{
    char text[50];
    int num;
    struct node* next;
};
int main()
{

    struct node*m=makeEmpty(m);
    char sent[100];
    struct Queue*Q=makeEmptyQ(Q);
    struct UndoStack*s=makeEmptyS(s);
    int choice;
    char del[50];
    int op;
    int i;
    int op6;
    int i6;
    struct UndoStack* Redo=makeEmptyS(Redo);
    do
    {
        displayMainMenu();
        scanf ("%d",&choice );
        switch (choice)
        {
        case 1:
            m= readFile(m);
            printf("the input file loaded successfully\n");
            break;
        case 2:
            printList(m);
            printf("\n");
            break;
        case 3:
            printf("Enter the string you want to insert it: \n");
            getchar();
            gets(sent);
            char*ptr=strtok(sent," ");
            while (ptr!=NULL)
            {
                Q = enqueue(Q,ptr);
                ptr=strtok(NULL," ");
            }
            printf("select where you want to insert it:\n");
            int sel=0;
            printf("1- At first\n");
            printf("2- At last\n");
            printf("3- Between two words\n");
            scanf("%d",&sel);
            if (sel==1)
            {
                int n=1;
                struct Queue*res;
                struct node*p=makeEmpty(p);
                struct node*head=p;
                while (Q->next!=NULL) 
                {
                    res=NULL;
                    res=dequeue(Q);
                    s=push(s,res->str,n,0);

                    struct node*x= putNewNode(res->str,n);
                    Insertt(p,x);
                    p = p->next;
                    n++;
                }
                //add the string to the original list m
                head=head->next;
                p->next=m->next;
                m->next=head;
                newPos(m);


            }
            else if (sel==2)
            {
                struct Queue*res;
                struct node*head=m;
                while (Q->next!=NULL)
                {
                    res=NULL;
                    res=dequeue(Q);
                    s=push(s,res->str,-1,0);
                    struct node*x= putNewNode(res->str,0);
                    while (head->next!=NULL)head=head->next;
                    x->next=head->next;
                    head->next=x;
                }
                newPos(m);
            }
            else if (sel==3)
            {
                int num=0;
                struct node*t=m;
                printf("Enter the number of the word you want to insert the string after it:\n");
                scanf("%d",&num);
                int r=0;
                while (t->next!=NULL)
                {
                    t=t->next;
                    if (num==t->num)
                    {
                        struct Queue*res;
                        struct node*p=makeEmpty(p);
                        struct node*head=p;
                        while (Q->next!=NULL)
                        {
                            num++;
                            res=NULL;
                            res=dequeue(Q);
                            s=push(s,res->str,num,0);
                            struct node*x= putNewNode(res->str,num);
                            Insertt(p,x);
                            p = p->next;
                        }
                        head=head->next;
                        p->next=t->next;
                        t->next=head;
                        r++;
                        break;
                    }
                }

                newPos(m);
                if (r==0) printf("Not found!");
            }
            else printf("Not found !");

            break;
        case 4:
            printf("Enter the word you want to delete it :\n");
            scanf("%s",del);
            struct node*prev=m;
            struct node*w=prev->next;
            int count=0;
            while (w!=NULL)
            {
                int  n = strcasecmp(del,w->text);
                if (n == 0) 
                {
                    count++;
                    break;
                }
                w=w->next;
                prev=prev->next;
            }
            if (count!=0) //here to delete it
            {
                s=push(s,w->text,w->num,1);
                prev->next=w->next;
                free(w);

                newPos(m);
            }
            else printf("Not found!\n");
            break;
        case 5:
            if (s->next!=NULL){
            if(1){
           struct UndoStack*sa =s->next;
            op=sa->state;
            i =sa->index;
            struct node* pre=m;
            struct node*d=pre->next;
            if (op==0) 
            {
                if (i==-1)  
                {
                    while(d->next!=NULL)
                    {
                        d=d->next;   
                        pre=pre->next;
                    }
                    pre->next=NULL;
                    Redo=push(Redo,sa->addedStr,sa->index,sa->state);
                    s=pop(s);
                    free(d);
                }
                else 
                {
                    while(d->next!=NULL)
                    {
                        if (d->num==i)
                        {
                            pre->next=d->next;
                            Redo=push(Redo,sa->addedStr,sa->index,sa->state);
                            s=pop(s);
                            free(d);
                            newPos(m);
                            break;
                        }
                        d=d->next;
                        pre=pre->next;
                    }
                }
            }
            else  
            {
                struct node* a=putNewNode(sa->addedStr,i);
                while(d!=NULL)
                {
                    if (d->num==i) 
                    {
                        pre->next=a;
                        a->next=d;
                        Redo=push(Redo,sa->addedStr,sa->index,sa->state);
                        s=pop(s);
                        break;
                    }
                    d=d->next;
                    pre=pre->next;
                }
            }
            newPos(m);
            printf("Undo last operation done!\n");
            //printList(m);
            }}
            else printf("undo stack is Empty!\n");
            break;

        case 6:
            if (Redo->next!=NULL){
            struct UndoStack*ra =Redo->next;
            op =ra->state;
            i6 =ra->index;
            struct node* pre6=m;
            struct node*d6=pre6->next;
            if (op==0) 
            {
                if (i6==-1)  
                {
                    while(pre6->next!=NULL)
                    {
                        pre6=pre6->next;
                    }
                    struct node* a=putNewNode(ra->addedStr,i6);
                    a->next=pre6->next;
                    pre6->next=a;
                    s=push(s,ra->addedStr,ra->index,ra->state);
                    Redo=pop(Redo);
                }
                else 
                {
                    struct node* a=putNewNode(ra->addedStr,i6);
                    while(d6!=NULL)
                    {
                        if (d6->num==i6)
                        {
                            pre6->next=a;
                            a->next=d6;
                            s=push(s,ra->addedStr,ra->index,ra->state);
                            Redo=pop(Redo);
                            break;
                        }
                        d6=d6->next;
                        pre6=pre6->next;
                    }
                }
            }
            else  
            {
                while(d6->next!=NULL)
                {
                    if (d6->num==i6)
                    {
                        pre6->next=d6->next;
                        s=push(s,ra->addedStr,ra->index,ra->state);
                        Redo=pop(Redo);
                        free(d6);
                        break;
                    }
                    d6=d6->next;
                    pre6=pre6->next;
                }
            }
            newPos(m);
            printf("Redo last operation done!\n");
            //printList(m);}
        }
            else printf("Redo stack is empty!\n");
            break;
        case 7:

            printf("The Undo Stack:\n");
            printStackpoppush(s);
            //printStack(Redo);

            printf("\nThe Redo Stack:\n");
            printStackpoppush(Redo);
            // printf("%s\n",Redo->addedStr);
            // printStack(Redo);

            break;
        case 8:
            SaveToFile(m);

            break;
        case 9:
            printf("Thank you");
            break ;
        default:
            printf("No such operation ? please try again. \n ");
        }
    }
    while (choice !=9);

}
void SaveToFile(struct node* m)
{
    FILE* out = fopen("updated_text.txt", "w");
    while (m->next!=NULL)
    {
        m=m->next;
        fprintf(out,"%s",m->text);
        fprintf(out," ");
    }
    fclose(out);
    printf("saved !\n");
}
void displayMainMenu()
{
    printf("\nPlease Select an Operation\n\n");
    printf("1. Load the input file which contains the initial text.\n");
    printf("2. Print the loaded text.\n");
    printf("3. Insert strings to the text.\n");
    printf("4. Remove strings from the text.\n");
    printf("5. Perform Undo operation.\n");
    printf("6. Perform Redo operation.\n");
    printf("7. Print the Undo Stack and the Redo stack \n");
    printf("8. Save the updated text to the output file. \n");
    printf("9. Exit\n");
}
struct node* makeEmpty(struct node* L)
{
    L = (struct node*)malloc(sizeof(struct node));
    L->next = NULL;
    return L;
}
struct Queue* makeEmptyQ(struct Queue* L)
{
    L = (struct Queue*)malloc(sizeof(struct Queue));
    L->next = NULL;
    return L;
}
struct UndoStack* makeEmptyS(struct UndoStack* L)
{
    L = (struct UndoStack*)malloc(sizeof(struct UndoStack));
    L->next = NULL;
    return L;
}
struct node* readFile(struct node* x)
{

    char line[100];
    x = makeEmpty(x);
    struct node* p =x;
    FILE* in;
    in = fopen("intialText.txt", "r");
    if (in == NULL)
    {
        printf("file is empty\n");
        return;
    }
    struct node*head=p;
    while (fgets(line, 100, in))
    {
        char text[50];
        int number=0;
        char* ptrr = strtok(line, " ");
        while(ptrr != NULL)
        {
            strcpy(text, ptrr);
            number++;
            x=putNewNode(text,number);
            Insertt(p,x);
            p = p->next;
            //  printf("%s ",p->text);
            //  printf("%d\n",p->num);
            ptrr=strtok(NULL, " ");
        }

        fclose(in);
        return head;
    }
}
void Insertt (struct node* l,struct node* temp)
{
    l->next = temp;
    temp->next=NULL;
}
struct node* putNewNode(char text[50],int number)
{
    struct node*theNew=NULL;
    theNew=makeEmpty(theNew);
    strcpy(theNew->text,text);
    theNew->num=number;
    theNew->next = NULL;
    return theNew;

}
void printList (struct node* L)
{
    struct node* p=L;
    do
    {
        p= p->next;
        printf("%s",p->text);
        printf(" ");
    }
    while (!IsEmpty(p));

}
int IsEmpty(struct node* x)
{
    return x->next==NULL;
}
struct Queue* enqueue(struct Queue* Q, char t[50])
{
    struct Queue* newNode = (struct Queue*)malloc(sizeof(struct Queue));
    strcpy(newNode->str,t);
    struct Queue* temp=Q;
    if(Q==NULL)
    {
        printf("Queue Not Found..\n");
        return;
    }
    if(Q->next==NULL) 
    {
        newNode->next=Q->next;
        Q->next=newNode;
        return temp;
    }
    else
    {
        while(Q->next != NULL)
            Q=Q->next; 
        newNode->next=Q->next;
        Q->next=newNode;
        return temp;
    }
}
struct Queue* dequeue(struct Queue* Q)
{

    struct Queue* front=Q->next;

    struct Queue* res=makeEmptyQ(res);
    strcpy(res->str,front->str);
    if(Q==NULL)
    {
        printf("Not Found!\n");
        return;
    }
    else if(Q->next==NULL)
    {
        printf("Queue is empty!\n");
        return;
    }
    else if(Q->next->next==NULL)  
    {
        Q->next=front->next;
        free(front);
    }
    else 
    {
        Q->next=front->next;
        free(front);
    }
    return res ;

}
struct UndoStack* push(struct UndoStack* top, char r [50],int index,int state)
{

    struct UndoStack* newNode = (struct UndoStack*)malloc(sizeof(struct UndoStack));
    strcpy(newNode->addedStr,r);
    newNode->index=index;
    newNode->state=state;

    newNode->next=top->next;
    top->next=newNode;
    return top;
}
struct UndoStack* pop(struct UndoStack* top)
{

    struct UndoStack*temp=top;
    struct UndoStack*n=temp->next;
    if(top==NULL)
    {
        printf("stack is empty!\n");
        return;
    }
    temp->next=n->next;

    free(n);
    return top;
}
void printStackpoppush(struct UndoStack* s)
{
    struct UndoStack* S=s->next;
    if(s->next==NULL)
    {
        printf("Stack is empty, nothing to print!\n");
        return;
    }
    struct UndoStack* temp=makeEmptyS(temp);
    while (s->next!=NULL)
    {
        temp=push(temp,S->addedStr,S->index,S->state);
        printf("%s ",S->addedStr);
        if (S->state==0)
            printf("Insert   ");
        else
            printf("remove   ");
        printf("%d\n",S->index);
        s=pop(s);
        S=s->next;
    }
    struct UndoStack*T=temp->next;
    while(temp->next!=NULL){

        s=push(s,T->addedStr,T->index,T->state);
        temp=pop(temp) ;
        T=temp->next;
    }

    }

void newPos(struct node*k)
{
    int pos=1;
    while(k->next!=NULL)
    {
        k=k->next;
        k->num=pos;
        pos++;
    }
}
