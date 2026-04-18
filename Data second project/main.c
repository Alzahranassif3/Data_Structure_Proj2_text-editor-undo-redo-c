#include <stdio.h>
#include <stdlib.h>
/*Al-zahra Ahmad Nassif
1220168
sec 1 */
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
            gets(sent);//in case the user entered more than one word
            char*ptr=strtok(sent," ");//to cut the sentence based on the space
            while (ptr!=NULL)
            {
                Q = enqueue(Q,ptr);//insert the words on the queue
                ptr=strtok(NULL," ");// to cut the next word
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
                struct Queue*res;//i use it to save the word after delete it from the queue
                struct node*p=makeEmpty(p);
                struct node*head=p;
                while (Q->next!=NULL) //while queue not empty
                {
                    res=NULL;
                    res=dequeue(Q);//dequeue the word from the queue
                    s=push(s,res->str,n,0);//push the deleted word to the stack

                    struct node*x= putNewNode(res->str,n);//put the word in a node so i can insert it to the linked list
                    Insertt(p,x);//insert the new node to the linked list
                    p = p->next;//move the pointer to the next node in the list so the next insert operation done after it
                    n++;// n mean the position of the word in the linked list
                }
                //add the string to the original list m
                head=head->next;//اول كلمة في السترينغ اللي بدنا نضيفها
                p->next=m->next;//بي اللي هي بتأشر على اخر كلمة
                m->next=head;
                newPos(m);//update the position after the insertion


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
                    struct node*x= putNewNode(res->str,0);//the above as same as sel==1 the different in the insertion below
                    while (head->next!=NULL)head=head->next;//to make the pointer point to the last node so we can insert after it
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
                    if (num==t->num) //found the node i want to insert after it
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
                        head=head->next;//اول كلمة في السترينغ اللي بدنا نضيفها
                        p->next=t->next;
                        t->next=head;
                        r++;
                        break;
                    }
                }

                newPos(m);
                if (r==0) printf("Not found!");//if the loop end and r still 0 this means that there is no word match what the user entered
            }
            else printf("Not found !");//in case the operation was not 0 or 1 (insert or delete )

            break;
        case 4:
            printf("Enter the word you want to delete it :\n");
            scanf("%s",del);
            struct node*prev=m;
            struct node*w=prev->next;
            int count=0;
            while (w!=NULL)
            {
                int  n = strcasecmp(del,w->text);//to find the word
                if (n == 0) //if you found increment the count and break because we want to delete the first occurance
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
            struct node* pre=m;//pointer to the previous of the node
            struct node*d=pre->next;//pointer to
            if (op==0) //mean insert,and it has three cases at first at last at middle
            {
                if (i==-1)  //at last
                {
                    while(d->next!=NULL)
                    {
                        d=d->next;    //loop to point to the last node
                        pre=pre->next;
                    }
                    pre->next=NULL;
                    Redo=push(Redo,sa->addedStr,sa->index,sa->state);//push to redo
                    s=pop(s);//pop from undo
                    free(d);//delete it
                }
                else  //case at first or middle
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
            else  //here op =1 mean the operation was delete so in undo we need to insert it
            {
                struct node* a=putNewNode(sa->addedStr,i);//put the word in a node so i can insert it to the list
                while(d!=NULL)
                {
                    if (d->num==i) //if you find where it was then insert it
                    {
                        pre->next=a;
                        a->next=d;
                        Redo=push(Redo,sa->addedStr,sa->index,sa->state);//push to Redo
                        s=pop(s);//pop from undo
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

        case 6://this case same as undo but the difference if the operation was insert then insert it again insted of deleting it and if it was delete delete it again insted of insert it as undo do
            if (Redo->next!=NULL){
            struct UndoStack*ra =Redo->next;
            op =ra->state;
            i6 =ra->index;
            struct node* pre6=m;
            struct node*d6=pre6->next;
            if (op==0) //mean insert
            {
                if (i6==-1)  //insert at last
                {
                    while(pre6->next!=NULL)
                    {
                        pre6=pre6->next;
                    }
                    struct node* a=putNewNode(ra->addedStr,i6);
                    a->next=pre6->next;
                    pre6->next=a;
                    s=push(s,ra->addedStr,ra->index,ra->state);//here push to the undo
                    Redo=pop(Redo);//pop from Redo
                }
                else //insert at first or middle based on the index
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
            else  //op=1 mean delete
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
    if(Q->next==NULL) //يعني اذا كانت فاضية بس قيها الهيد دغري بنضيف
    {
        newNode->next=Q->next;
        Q->next=newNode;
        return temp;
    }
    else
    {
        while(Q->next != NULL)
            Q=Q->next; //اوجدنا rear عشان يضيف عليه
        newNode->next=Q->next;
        Q->next=newNode;
        return temp;
    }
}
struct Queue* dequeue(struct Queue* Q)
{

    struct Queue* front=Q->next;

    struct Queue* res=makeEmptyQ(res);
    strcpy(res->str,front->str);//عشان اعرف ارجع قيمة اللي انحذفت حتى ادخلها على الستاك
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
    else if(Q->next->next==NULL)   //has one element
    {
        Q->next=front->next;
        free(front);
    }
    else //عندها اكثر من عنصرين
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
    struct UndoStack* S=s->next;// the first node after the header (the top of s)
    if(s->next==NULL)//check if the stack is empty
    {
        printf("Stack is empty, nothing to print!\n");
        return;
    }
    struct UndoStack* temp=makeEmptyS(temp);//new stack temp
    while (s->next!=NULL)//while the list is not empty
    {
        temp=push(temp,S->addedStr,S->index,S->state);//push the first node after the header (top of s) to temp
        printf("%s ",S->addedStr);
        if (S->state==0)
            printf("Insert   ");
        else
            printf("remove   ");
        printf("%d\n",S->index);
        s=pop(s);//delete the top so we can reach the next node to print it
        S=s->next;//the new node that after the header
    }//at the end of this loop s will be empty so we need to fill it again
    struct UndoStack*T=temp->next;
    while(temp->next!=NULL){

        s=push(s,T->addedStr,T->index,T->state);//push to s so it come back as it was before the loop above
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
