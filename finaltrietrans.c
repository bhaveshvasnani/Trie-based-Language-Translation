#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//structure for the nodes of the trie
struct trie_node
{
	char data;// stores the letters of the words
	struct trie_node *child[27];// array of pointers
};
struct language
{
	char eng[20];
	char fr[20];
}word[10]={{"eat","manger"},{"head","tête"},{"hello","bonjour"},{"help","aidez"},{"sleep","dormir"},{"slope","pente"},{"there","là"},{"they","ils"},{"word","mot"},{"work","travail"}};
int binsearch(char key[])
{
    int low, high, mid, result;
    low = 0;
    high = 10 - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        result = strcmp(word[mid].eng,key);
        if (result > 0) {
            high = mid - 1;
        } else if (result < 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
}
//function for creating new nodes and assigning values to them
struct trie_node* newnode(char x)
{
	int i;
	struct trie_node *n;
	n=(struct trie_node*)malloc(sizeof(struct trie_node));
	n->data=x;
		for (i=0;i<27;i++)
			n->child[i]=NULL;//assigning the 26 pointers of the node to NULL
	return n;//returning the pointer to structure
}
//function for inserting words into the trie for storage and manipulation

struct trie_node* insert(struct trie_node * root,char x[])
{
	int index,l,length=strlen(x),i=0,k;
	char a[10];
	struct trie_node* temp=root;
	for (l=0;l<length;l++)
	{
		index=(int)x[l]-(int)'a';/*Calculating the index of a letter eg. index of 'e' will be 70-65=5*/
		if(temp->child[index]==NULL)
		{
			temp->child[index]=newnode(x[l]);/*passing the letter and creating a new node in the trie*/
			temp=temp->child[index];
			a[i++]=x[l];
		}
		else
        {
            a[i++]=x[l];
            temp=temp->child[index];
        }
	}
	a[i]='\0';/*after traversing the trie we make the node after the last letter as NULL,this marks the end of a word*/
	k=binsearch(a);
	temp->child[26]=newnode(k);
	return root;
}
//function to search for the inserted words in the trie
int search(struct trie_node *root,char key[])
{
	int lvl,length=strlen(key),index;
	struct trie_node *temp=root;
	for(lvl=0;lvl<length;lvl++)
	{
		index=(int)key[lvl]-(int)'a';
		if(temp->child[index]!=NULL)
		{
        temp=temp->child[index];
        }
        else
            return 0;
	}
	if(temp->child[26]==NULL)
		return 0;
	return 1;
}
//function to display the words in the trie
void display(struct trie_node *root)
{
	int i;
	if(root->child[26]==NULL)
	{
		for (i=0;i<26;i++)
		{
			if (root->child[i]!=NULL)
			{
				printf("%c",root->child[i]->data);
				display(root->child[i]);/*recursively calling the display function so as to reach the end of the word*/
			}
		}
	}
	printf("\n");
}
//function which prints the rest of the substring for words which are present in the trie
void autocomplete (struct trie_node *root)
{
	char key[10];
	printf("Enter the substring:");
	scanf("%s",key);
	int index,l,c=0,i,j;
	l=strlen(key);
	struct trie_node *ptr=root;
	while (ptr->data!=key[l-1] && c<l)/*run the while loop till we hit the last letter of the word*/
	{
		for (j=0;j<l;j++)
		{
			index=(int)key[j]-(int)'a';
			if(ptr->child[index]!=NULL)
    		{
    			ptr=ptr->child[index];
    			c++;
			}
		}
	}
	printf("%s---->\n",key);//printing the initial substring
	display(ptr);//displaying the rest of the word
}
void translate(struct trie_node *root,char key[])
{
	int lvl,length=strlen(key),index,i=0;
	struct trie_node *temp=root;
	for(lvl=0;lvl<length;lvl++)//traversing through the word in the trie
	{
		index=(int)key[lvl]-(int)'a';
		if(temp->child[index]!=NULL)
		{
        	temp=temp->child[index];
		}
        else /*at every iteration we check for the next letter of the word and if it is not [resent we print that the word was not found*/
        {
            printf("\nWord not in the trie\n");
            return;
        }
	}
	if (temp->child[26]==NULL)/*if the node after the last letter is NULL then the word does not exist in the trie*/
    {
        printf("\nWord not in the trie\n");
        return;
    }
    printf("%s\n",word[temp->child[26]->data].fr);/*if the above condition is false we print the translated french word*/
}
//driver program for the code
void main()
{
	system("color 4a");
	int choice,i,n,ch=1;
	char str[10];
	struct trie_node* root=NULL;
	root=newnode('\0');
	printf("\n\t\t\t\tTRIE and its application\n\n");
	while(1)
	{
		printf("1--->INSERT\n");
		printf("2--->SEARCH\n");
		printf("3--->DISPLAY\n");
		printf("4--->AUTOCOMPLETE\n");
		printf("5--->TRANSLATE\n");
		printf("6--->EXIT\n");
		printf("Enter your choice: ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			    printf("Insert words from 'eat','head','hello','help','sleep','slope','there','they','word','work'\n");
				printf("How many words would you like to insert:");
				scanf("%d",&n);
				for(i=1;i<=n;i++)
				{
					printf("Enter word:");
					scanf("%s",str);
					root=insert(root,str);
				}
				break;
			case 2:
				while(ch)
				{
					printf("Enter the word you would like to search:");
					scanf("%s",str);
					if(search(root,str)==1)
						printf("Word Found");
					else
						printf("Word Not Found");
					printf("\n");
					printf("Press\n");
					printf("1->CONTINUE\n");
					printf("0->EXIT\n");
					scanf("%d",&ch);
				}
				break;
			case 3:
				display(root);
				break;
			case 4:
				autocomplete(root);
				break;
			case 5:
				printf("Enter the word you would like to translate:");
				scanf("%s",str);
				translate(root,str);
				break;
			case 6:
				exit(0);
		}
	}
}
