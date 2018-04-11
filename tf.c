#include "tf.h"
#ifndef __structs_h_
#define __structs_h_

#include "structs.h"
#endif
#include<stdio.h>
#include<string.h>
void tf(struct gramma* tree,int ID,char* word)
{
	int i,vrethike;
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
					struct vision* arxi=my_beg->beg;
					while(1)
					{
						if(arxi->grammi_keimenou==ID)
						{
							printf("%d %s %d\n",ID,word,arxi->fores_emfanisis);
							break;
						}	
						arxi=arxi->next;
						if(arxi==NULL)
							break;
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