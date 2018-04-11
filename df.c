#ifndef __structs_h_
#define __structs_h_

#include "structs.h"
#endif
#include "df.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void  df(char *word,struct gramma* tree,struct keimeno* my_li,int max,int grammes)
{
	int i,j;
	if(word==NULL)
	{
		char* result=malloc((max+1)*sizeof(char));
		int position=0;
		int end_of_word=0;
		char xar_mo;
		for(i=0;i<grammes;i++)
		{
			struct gramma* current=tree;
			for(j=0;j<strlen(my_li[i].symbols);j++)
			{
				xar_mo=my_li[i].symbols[j];
				if(xar_mo==' '||xar_mo=='\t')
					continue;
				if(j==strlen(my_li[i].symbols)-1||my_li[i].symbols[j+1]=='\t'||my_li[i].symbols[j+1]==' ')
					end_of_word=1;
				while(1)
				{
					if(current->xaraktiras==xar_mo)
					{
						result[position++]=current->xaraktiras;//creating the word char by char
						if(end_of_word==1)
						{
							if(current->my_list->came==0)//not visited the word from previous line
							{
								result[position]='\0';
								struct vision * m=current->my_list->beg;
								int sum=1;
								while(1)
								{
									if(m->next!=NULL)
										sum++;
									else
									{
										printf("%s %d\n",result,sum);
										break;
									}
									m=m->next;
								}
								current->my_list->came=1;
							}
							current=tree;//starting from the beginning of the node
							position=0;
							strcpy(result,"");
							end_of_word=0;
						}
						else
							current=current->paidi;//found the char goes to next level
						break;
					}
					else 
						current=current->next;
				}
			}
		}
		free(result);
	}
	else
	{
		int vrethike;
		struct gramma* current=tree;
		for(i=0;i<strlen(word);i++)
		{
			vrethike=0;
			while(1)
			{
				if(current==NULL)
					break;	
				if(current->xaraktiras==word[i])
				{
					vrethike=1;
					if(i==(strlen(word)-1))
					{	
						struct posting_list * my_beg=current->my_list;
						if(my_beg==NULL)
							return ;
						struct vision* node=my_beg->beg;
						int sum=1;
						while(1)
						{
							if(node->next!=NULL)
								sum++;
							else
							{
								printf("%s %d\n",word,sum);
								return ;
							}
							node=node->next;
						}
					}
					current=current->paidi;
					break;
				}	
				else
					current=current->next;	
			}
		if(vrethike==0)
			return ;
		}
	}
}
