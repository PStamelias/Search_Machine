#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifndef __structs_h_
#define __structs_h_

#include "structs.h"
#endif

#include "search.h"
#include "tf.h"
#include "exit.h"
#ifndef __def_h_
#define __def_h_
#include "df.h"
#endif


struct gramma* create_gramma(char xaraktiras_gia_insert)//creating the node for trie 
{
	struct gramma* letter=malloc(sizeof(struct gramma));
	letter->xaraktiras=xaraktiras_gia_insert;
	letter->paidi=NULL;
	letter->next=NULL;
	letter->my_list=NULL;
	return letter;
}
void making_line_without_string(int* p_table_cou,int* p_last_id,int* p_arxiko,char* charactiras)//the case of lines that dont have string-keimeno
{
	(*p_table_cou)++;
	(*p_last_id)++;
	(*p_arxiko)=100;
	(*charactiras)='\0';
}
void cleaning_came(struct gramma * cur)//helping function for df command  
{
	if(cur->paidi!=NULL)
		cleaning_came(cur->paidi);
	if(cur->next!=NULL)
		cleaning_came(cur->next);
	if(cur->my_list!=NULL)
		cur->my_list->came=0;
}
int main(int argc, char *argv[])
{
	double avgdl;
	int sum_words=0;
	int dont_read_char=0;
	struct gramma* epomeno_gramma=NULL;
	struct gramma* current_gramma=NULL;
	int arxi=0;
	int previous_id;
	int end_of_word=0;
	char command[10];
	char *leksi[11];
	int max_size_word=0,size_word=0;
	char xar_mo;
	int met,coun1=0;
	int last_id=-1;
	int K,size=0;//size count only the normal lines
	int plithos_keimenwn=0;//plithos keimenwn count all lines 
	int i,j,k;
	int c;
	int found=0,found1=0,found2=0,found3=0,done=0;
	int arxiko=100;
	char gramma;
	char *path;
	char *word=".txt";
	struct gramma* my_tree=NULL;
	if(!(argc==5))//more or less arguments
	{	
		printf("Error\n");
		return EXIT_FAILURE;
	}
	for(i=1;i<=argc-1;i++)
	{
		if(strncmp(argv[i],"-i",sizeof(argv[i]))==0&&found1==0)
		{
			done++;
			found1=1;
		}	
		else if(strncmp(argv[i],"-k",sizeof(argv[i]))==0&&found2==0)
		{
			done++;
			found2=1;
		}
		else if(strstr(argv[i], word) != NULL&&found3==0)
		{
			found3=1;
			done++;
			path=malloc((strlen(argv[i])+1)*sizeof(char));
			strcpy(path,argv[i]);
		}
		else if(found==0)
			for(j=0;j<10;j++)
			{
				for(k=0;k<strlen(argv[i]);k++)
				{
					gramma=j+'0';	
					if(argv[i][k]==gramma)
					{
						done++;
						found=1;
						break;
					}
				}
				if(found==1)
				{	
					K=atoi(argv[i]);
					break;
				}
			}
	}
	if(done!=4)
	{
		printf("Wrong given values\n");
		return EXIT_FAILURE;
	}
	FILE* f;
	f=fopen(path,"r");
	int prwtos_xaraktiras=1;
	int keno_line=0;
	while(1)
	{
		c=fgetc(f);
		if(c=='\n'&&prwtos_xaraktiras==1)/*new line without id*/
			keno_line=1;
		else
			keno_line=0;
		if(feof(f))
			break;
		if(c=='\n')
		{
			if(keno_line==0)
				size++;
			prwtos_xaraktiras=1;
			plithos_keimenwn++;
		}
		else
			prwtos_xaraktiras=0;
	}
	rewind(f);
	struct keimeno* line=malloc(size*sizeof(struct keimeno));
	int * D=malloc(size*sizeof(int));/*count how many words has keimeno*/
	for(i=0;i<size;i++)
		D[i]=0;
	for(i=0;i<size;i++)
		line[i].symbols=malloc(arxiko*sizeof(char));
	int table_cou=0;
	for(i=0;i<plithos_keimenwn;i++)
	{
		c=fgetc(f);
		if(c=='\n')
			continue;
		int id=0;
		while(1)
		{
			if(c=='\t'||c==' '||c=='\n')
				break;
			id=id*10+ c -'0';/*creting the id of this specific line*/
			c=fgetc(f);
		}
		line[table_cou].id=id;
		if(last_id+1!=line[table_cou].id)
		{
			printf("Error in ID value\n");
			return EXIT_FAILURE;
		}
		met=0;
		if(c=='\n')
		{
			making_line_without_string(&table_cou,&last_id,&arxiko,&line[table_cou].symbols[met]);
			continue;
		}
		while(1)
		{
			c=fgetc(f);
			if(c=='\n')
				break;
			line[table_cou].symbols[met++]=(char)c;/*creating the table char by char*/
			if(met+1==arxiko)
			{
				arxiko*=2;
				line[table_cou].symbols=realloc(line[table_cou].symbols,arxiko*sizeof(char));
			}
		}
		making_line_without_string(&table_cou,&last_id,&arxiko,&line[table_cou].symbols[met]);
	}
	for(i=0;i<size;i++)/*Creating the Trie*/
	{
		for(j=0;j<strlen(line[i].symbols);j++)
		{
			xar_mo=line[i].symbols[j];
			if(xar_mo==' '||xar_mo=='\t')
			{
				if(size_word>=max_size_word)
					max_size_word=size_word;/*keeping the max size of word because of need it for commands*/ 
				size_word=0;
				continue;
			}
			size_word++;
			if(my_tree==NULL)/*creating the first letter in trie*/
			{
				struct gramma* letter=create_gramma(xar_mo);
				my_tree=letter;
				current_gramma=letter;
				epomeno_gramma=letter->paidi;
			}
			else
			{
				if(epomeno_gramma==NULL)/*Nodes on next level does not exist*/
				{
					struct gramma* letter=create_gramma(xar_mo);
					current_gramma->paidi=letter;
					current_gramma=letter;
					epomeno_gramma=letter->paidi;
				}
				else
				{
					struct gramma* t=epomeno_gramma;
					int  iparxei=0;
					while(1)
					{
						if(t->xaraktiras==xar_mo)
						{
							iparxei=1;
							current_gramma=t;
							epomeno_gramma=t->paidi;
							break;
						}
						if(t->next==NULL)
							break;
						t=t->next;
					}
					if(iparxei==0)/*the specific word does not exist on this level*/
					{
						struct gramma* letter=create_gramma(xar_mo);
						current_gramma=letter;
						epomeno_gramma=letter->paidi;
						t->next=letter;
					}
				}
			}
			if(j==strlen(line[i].symbols)-1||line[i].symbols[j+1]=='\t'||line[i].symbols[j+1]==' ')/*End of Word*/
			{	
				end_of_word=1;
				D[i]++;
			}
			else
				end_of_word=0;




			if(end_of_word==1)
			{
				if(current_gramma->my_list==NULL)/* The word does not have posting list*/
				{
					current_gramma->my_list=malloc(sizeof(struct posting_list));
					current_gramma->my_list->counter=1;
					current_gramma->my_list->beg=malloc(sizeof(struct vision));
					current_gramma->my_list->beg->fores_emfanisis=1;
					current_gramma->my_list->beg->grammi_keimenou=i;
					current_gramma->my_list->beg->next=NULL;
					current_gramma->my_list->came=0;
				}
				else
				{
					current_gramma->my_list->counter++;/*word appears one time more*/
					struct vision* search=current_gramma->my_list->beg;/*searching if we have created node for this ID*/
					int vrethike=0;
					while(1)
					{
						if(search->grammi_keimenou==i)
						{
							vrethike=1;
							search->fores_emfanisis++;
							break;
						}
						if(search->next==NULL)
							break;
						search=search->next;
					}
					if(vrethike==0)/*creating the posting list*/
					{
						struct vision* new_node=malloc(sizeof(struct vision));
						new_node->fores_emfanisis=1;
						new_node->grammi_keimenou=i;
						new_node->next=NULL;
						search->next=new_node;
					}
				}
				epomeno_gramma=my_tree;
			}
		}
		if(size_word>=max_size_word)
			max_size_word=size_word;
		size_word=0;
	}
	for(i=0;i<size;i++)
		sum_words+=D[i];
	avgdl=(double)sum_words/(double)size;
	for(i=0;i<11;i++)
		leksi[i]=malloc((max_size_word+1)*sizeof(char));
	while(1)
	{
		int in,rt=0,thesi=0,yer;
		while(1)
		{
			in=fgetc(stdin);/* reading char by char the command and the letters of words of query*/
			if(thesi<=10)
			{
				if(in=='\n')/*read the words and  command*/
				{
					leksi[thesi][rt]='\0';
					break;
				}
				if(in==' ')//read the word or command */
				{
					leksi[thesi][rt]='\0';
					thesi++;
					rt=0;
				}
				else if(in!=' '&&thesi!=11)
					leksi[thesi][rt++]=in;//took the first ten words, no need for more*/
			}
			if(in=='\n')
				break;
		}	
		if(strcmp(leksi[0],"/search")==0)
		{
			if(strcmp(leksi[1],"")==0)/*command without inputs*/
			{
				printf("Error-NO Input\n");
				return EXIT_FAILURE;
			}
			if(thesi==11)
				thesi=10;/* it helping inside search function founding the arquments on case we have 10 arguments or less*/
			int size_of_query=thesi;
			char **p=leksi;
			search(line,p,size,size_of_query,D,avgdl,my_tree,K);
			
		}
		else if(strcmp(leksi[0],"/df")==0)
		{
			if(strcmp(leksi[1],"")==0)
				df(NULL,my_tree,line,max_size_word,size);
			else
				df(leksi[1],my_tree,line,max_size_word,size);
			cleaning_came(my_tree);//in case of calla it again we will face problem , so making came pointer to zero for the same results at any time */
		}
		else if(strcmp(leksi[0],"/tf")==0)
		{
			int my_metr=1;
			while(1)/* we need only two arguments*/
			{
				if(strcmp(leksi[my_metr],"")==0)
				{
					printf("Wrong Arguments\n");
					return EXIT_FAILURE;
				}
				my_metr++;
				if(my_metr==3)
					break;
			}
			int number_ID=atoi(leksi[1]);
			tf(my_tree,number_ID,leksi[2]);
		}
		else if(strcmp(leksi[0],"/exit")==0)
		{
			exit_f(&my_tree,&path,&line,f,leksi,size,D);
			return EXIT_SUCCESS;
		}
		else
		{
			printf("unknown command\n");
			return EXIT_FAILURE;
		}
		for(i=0;i<11;i++)
			strcpy(leksi[i],"");
	}
}
