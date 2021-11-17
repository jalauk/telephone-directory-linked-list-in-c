#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
    char name[30];
    char num[15];
    struct node *left;
    struct node *right;
}node;

void write(FILE *fp,node **head)
{
    char content[50],no[13];
    node *newnode,*temp = *head;

    if(fp == NULL)
    {
        printf("file not found");
        return;
    }
    else
    {
        while(fgets(content,sizeof(content),fp))
        {
            newnode = (node*)malloc(sizeof(node));
            strncpy(newnode->name,content,strlen(content)-1);
            fgets(no,sizeof(no),fp);
            strncpy(newnode->num,no,strlen(no)-1);
            newnode->right = NULL;
            newnode->left = NULL;
            if(*head == NULL)
                temp = *head = newnode;
            else
            {
                newnode->left = temp;
                temp->right = newnode;
                temp = newnode;
            }
        }
    }
}

void enter(node **head)
{
    char str[30];
    char n;
    node *newnode,*temp;
    newnode = (node*)malloc(sizeof(node));
    printf("Enter the name of person = ");
    scanf("%c",&n);
    gets(newnode->name);
    printf("Enter the phone number of person = ");
    scanf("%s",&newnode->num);
    newnode->left = newnode->right = NULL;
    if(*head == NULL)
        *head = newnode;
    else
    {
        int c=0;
        node *temp1;
        for(temp = *head;temp!=NULL;temp=temp->right)
        {
            int i = strcmp(newnode->name,temp->name);
            if(i<0)
            {
                if(temp == *head)
                {
                    newnode->right = temp;
                    newnode->left = temp->left;
                    temp->left = newnode;
                    *head = newnode;
                }
                else
                {
                    newnode->right = temp;
                    newnode->left = temp->left;
                    temp->left->right = newnode;
                    temp->left = newnode;
                }
                c++;
                break;
            }
            temp1 = temp;
        }
        if(c == 0)
        {
            temp1->right = newnode;
            newnode->left = temp1;
        }
    }
}

void rearrange(node ***head,node *newnode)
{
    //remove the node from the list
    node *temp1,*temp;
    if(newnode == **head)
    {
        **head = newnode->right;
        newnode->right->left = newnode->left;
    }
    else if(newnode->right == NULL)
    {
        newnode->left->right == NULL;
    }
    else
    {
        temp1 = newnode->left;
        newnode->left->right = newnode->right;
        newnode->right->left = temp1;
    }
    newnode->left = newnode->right = NULL;
    //re-inserting the removed node
    int c=0;
    for(temp = **head;temp!=NULL;temp=temp->right)
    {
        int i = strcmp(newnode->name,temp->name);
        if(i<0)
        {
            if(temp == **head)
            {
                newnode->right = temp;
                newnode->left = temp->left;
                temp->left = newnode;
                **head = newnode;
            }
            else
            {
                newnode->right = temp;
                newnode->left = temp->left;
                temp->left->right = newnode;
                temp->left = newnode;
            }
            c++;
            break;
        }
        temp1 = temp;
    }
    if(c == 0)
    {
        temp1->right = newnode;
        newnode->left = temp1;
    }
}

node *find(node ***head,char a[])
{
    node *temp = **head;
    while(temp!=NULL)
    {
        if(strcmp(a,temp->name) == 0)
        {
            printf("Name : %s \nPhone number : %s",temp->name,temp->num);
            return temp;
        }
        temp = temp->right;
    }
    printf("NOT FOUND!");
    return NULL;
}

void del(node **head)
{
    node *temp,*temp1;
    char name[25],n,ans;
    if(*head == NULL)
    {
        printf("list empty");
        return;
    }
    printf("Enter the name of person you want to delete = ");
    scanf("%c",&n);
    gets(name);
    temp = find(&head,name);
    if(temp == NULL)
        return;
    printf("\nAre you sure :\tY/N\n");
    scanf("%c",&ans);
    if(ans == 'Y' || ans == 'y')
    {
        if(*head == NULL && temp == NULL)
            return;
        else if(*head == temp || temp->right == NULL)
            *head = NULL;
        else if(temp == *head)
        {
            *head = temp->right;
            temp->right->left = temp->left;
        }
        else if(temp->right == NULL)
        {
            temp->left->right == NULL;
        }
        else
        {
            temp1 = temp->left;
            temp->left->right = temp->right;
            temp->right->left = temp1;
        }
        free(temp);
        printf("\n%s has been successfully deleted",name);
    }
    else
        return;
}

void edit(node **head)
{
    char name[30],n;
    int choice,ans;
    if(*head == NULL)
    {
        printf("list empty");
        return;
    }
    printf("\nenter the name of the person to be edited = ");
    scanf("%c",&n);
    gets(name);
    node *temp = find(&head,name);
    if(temp == NULL)
        return;
    printf("\nare you sure :\t1.YES\t2.NO\n");
    scanf("%d",&ans);
    if(ans == 1)
    {
        printf("what you want to edit :\t1.Name\t2.Phone number\n");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            printf("enter new name = ");
            scanf("%s",temp->name);
            break;
        case 2:
            printf("enter new phone number = ");
            scanf("%s",temp->num);
            break;
        }
        rearrange(&head,temp);
    }
    else
        return;
}

void search(node **head)
{
    node *temp = *head;
    char str[30],z;
    int n,choice,c=0,a;
    if(*head == NULL)
    {
        printf("list empty");
        return;
    }
    printf("By which you want to search :\t1.Name\t2.Phone No.\n");
    scanf("%d",&choice);
    if(choice == 1)
    {
        int i=1;
        printf("Enter the name you want to search = ");
        scanf("%c",&z);
        gets(str);
        n = strlen(str);
        printf("\nSuggestion based on %s are :\n",str);
        printf("       CONTACTS      \n");
        printf("***********************\n");
        while(temp != NULL)
        {
            if(strncmp(temp->name,str,n) == 0)
            {
                printf("%d.Name : %s \n  Phone No. : %s\n\n",i++,temp->name,temp->num);
                c++;
            }
            temp = temp->right;
        }
        if(c == 0)
        {
            printf("NOT FOUND!\n");
        }
        printf("***********************\n");
    }
    else
    {
        int i=1;
        printf("Enter the phone no. you want to search = ");
        printf("       CONTACTS      \n");
        printf("***********************\n");
        scanf("%s",&str);
        while(temp != 0)
        {
            if(strcmp(temp->name,str) == 0);
            {
                printf("%d.Name : %s \n  Phone No. : %s\n\n",i++,temp->name,temp->num);
                c++;
            }
            temp = temp->right;
        }
            if(c == 0)
            {
                printf("NOT FOUND!");
            }
        printf("***********************\n");
    }
}

void print(node **head)
{
    int i=1;
    node *temp = *head;
    printf("       CONTACTS      \n");
    printf("***********************\n");
    if(*head == NULL)
        printf("  NO CONTACT FOUND\n");
    else
    {
        while(temp != NULL)
        {
            printf("%d.Name : %s \n  Phone No. : %s\n\n",i++,temp->name,temp->num);
            temp = temp->right;
        }
    }
    printf("***********************\n");
}

void tofile(FILE *fp1,node *head)
{
    node *temp = head;
    if(head == NULL)
    {
        return;
    }
    else
    {
        while(temp != NULL)
        {
            fputs(temp->name,fp1);
            fputs("\n",fp1);
            fputs(temp->num,fp1);
            fputs("\n",fp1);
            temp = temp->right;
        }
    }
}

int main()
{
    node *head = NULL;
    int choice;
    FILE *fp,*fp1;
    fp = fopen("contact.txt","r");
    write(fp,&head);
    fclose(fp);
	do
    {
        system("cls");
        printf("       PHONEBOOK      \n");
        printf("***********************\n");
        printf("1.Add contact\n2.Edit\n3.Delete\n4.Print list\n5.Search\n***********************\nENTER YOUR CHOICE (1-5,0 FOR EXIT) = ");
        scanf("%d",&choice);
        printf("\n");
        switch(choice)
        {
            case 1:
            enter(&head);break;
            case 2:
            edit(&head);break;
            case 3:
            del(&head);break;
            case 4:
            print(&head);break;
            case 5:
            search(&head);break;
            case 0:
            system("cls");
            printf("\n BYE BYE....");
            break;
            default:
            printf("\n ##INVALID CHOICE##");
        }
        printf("\n PRESS ANY KEY...");
        getch();
    }while(choice!=0);

    fp1 = fopen("contact.txt","w");
    if(fp1 == NULL)
    {
        printf("no file found");
        exit(0);
    }
   else
        tofile(fp1,head);

    fclose(fp1);

    printf("\ndata is updated");

    return 0;
}


