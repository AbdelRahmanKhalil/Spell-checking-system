#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COUNT 10

typedef struct node
{
    char* word;
    struct node* left;
    struct node* right;
    int height;
    //struct node* parent;

} node;

typedef struct tree
{
    node* root;
} tree;
node* createNode(char* word)
{
    node* NewNode=malloc(sizeof(node));
    NewNode->word=malloc(sizeof(char)*35);
    strcpy(NewNode->word,word);
    NewNode->left=NULL;
    NewNode->right=NULL;
    return NewNode;
}
void insert(tree* t,char* word)
{
    node* navigator=malloc(sizeof(node));
    node* lagnav=malloc(sizeof(node));
    char direction='w';
    navigator=t->root;

    while(1)
    {
        if(t->root==NULL)
        {
            t->root=createNode(word);
            break;
        }
        if(navigator==NULL)
        {
            if(direction=='r')
            {
                lagnav->right=createNode(word);

                break;
            }
            else if(direction=='l')
            {
                lagnav->left=createNode(word);
                break;
            }
        }
        else if(strcmp(word,navigator->word)<0)
        {
            lagnav=navigator;
            navigator=navigator->left;
            direction='l';
        }
        else if(strcmp(word,navigator->word)>0)
        {
            lagnav=navigator;
            navigator=navigator->right;
            direction='r';
        }

    }
}
// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(node *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%s\n", root->word);

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(node *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}
void buildTree(tree* t)
{
    printf("loading");
    FILE* f=fopen("EN-US-randomized.txt","r");
    int counter=0;
    char word[50];
    while(!feof(f))
    {
        fscanf(f,"%s",word);
        insert(t,word);
        fscanf(f,"\n");
        //printf("\nword=%s",word);
        counter++;
        if(counter%1000==0)
            printf("*");
    }
    printf("\nloaded");
    fclose(f);
    printf("\nSize of Tree=%d",counter);
}
int search(char input[50],tree t,char* word1,char* word2,char* word3,char* word4,char* word5)
{
    node* nav=malloc(sizeof(node));
    //nav->word=malloc(sizeof(char)*50);
    node* lagnav=malloc(sizeof(node));
    node* lagnav2=malloc(sizeof(node));
    node* lagnav3=malloc(sizeof(node));
    nav=t.root;
    while(nav!=NULL)
    {
        if(strcmp(input,nav->word)<0)
        {
            lagnav3=lagnav2;
            lagnav2=lagnav;
            lagnav=nav;
            nav=nav->left;
        }
        else if(strcmp(input,nav->word)>0)
        {
            lagnav3=lagnav2;
            lagnav2=lagnav;
            lagnav=nav;
            nav=nav->right;
        }
        else
        {


            //word1=lagnav->word;
            //word2=lagnav->right->word;
            //word3=lagnav->left;
            return 1;//found
        }

    }
    if(lagnav!=NULL)
    {
        strcpy(word1,lagnav->word);
        if(lagnav2!=NULL)
            strcpy(word2,lagnav2->word);
        if(lagnav3!=NULL)
            strcpy(word3,lagnav3->word);
        if(lagnav->right!=NULL)
            strcpy(word4,lagnav->right->word);
        if(lagnav->left!=NULL)
            strcpy(word5,lagnav->left->word);
    }
    return 0;

}
int maxDepth(node* node)
{
   if (node==NULL)
       return 0;
   else
   {
       /* compute the depth of each subtree */
       int lDepth = maxDepth(node->left);
       int rDepth = maxDepth(node->right);

       /* use the larger one */
       if (lDepth > rDepth)
           return(lDepth+1);
       else return(rDepth+1);
   }
}

int main()
{

    tree t= {NULL};
    char input[50];
    char word1[50]="not found";
    char word2[50]="not found";
    char word3[50]="not found";
    char word4[50]="not found";
    char word5[50]="not found";
    char* token;
    int indicator;
    /*printf("size1=%d",sizeof(word1));
    printf("size1=%d",sizeof(word2));
    printf("size1=%d",sizeof(char*));*/
    buildTree(&t);

    printf("\nHeight=%d",maxDepth(t.root));

    //print2D(t.root);
    printf("\nsentence:");
    while(strcmp(input,"exit")!=0)
    {
        printf("\n");
        scanf("%s",input);
        token = strtok(input, " ");
        while(token!=NULL)
        {
            indicator =search(token,t,word1,word2,word3,word4,word5);
            if(indicator==1)
            {
                printf("\n%s:Correct",token);
            }
            else
            {
                printf("\n%s:Incorrect \n",token);
                if(strcmp(word1,"not found")!=0)
                printf("suggestion=%s\n",word1);
                if(strcmp(word2,"not found")!=0)
                printf("suggestion=%s\n",word2);
                if(strcmp(word3,"not found")!=0)
                printf("suggestion=%s\n",word3);
                if(strcmp(word4,"not found")!=0)
                printf("suggestion=%s\n",word4);
                if(strcmp(word5,"not found")!=0)
                printf("suggestion=%s\n",word5);
                strcpy(word1,"not found");
                strcpy(word2,"not found");
                strcpy(word3,"not found");


            }
            token=strtok(NULL," ");
        }

    }


    return 0;
}
