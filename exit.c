#ifndef __structs_h_
#define __structs_h_

#include "structs.h"
#endif

#include "exit.h"
#include<stdio.h>
#include<stdlib.h>
void free_tree(struct gramma*** now)
{
	struct posting_list* my_post=(*(*now))->my_list;//freeing its posting list if exists
	if(my_post!=NULL)
	{
		struct vision* start=my_post->beg;
		struct vision* seira=start;
		while(1)
		{
			start=start->next;
			free(seira);
			seira=start;
			if(seira==NULL)
				break;
		}
		free(my_post);
	}
	if((*(*now))->paidi!=NULL)//freeing the child of the node
	{
		struct gramma ** tr=&(*(*now))->paidi;
		free_tree(&tr);
	}
	if((*(*now))->next!=NULL)//freeing the next of the node
	{
		struct gramma ** tr=&(*(*now))->next;
		free_tree(&tr);
	}
	free(**now);//freeing node
}
void exit_f(struct gramma** arxi,char** path,struct keimeno** line,FILE* f,char** leksi,int size,int *t)
{
	free(t);
	fclose(f);
	int i;
	for(i=0;i<11;i++)
	{	
		free(leksi[i]);
		leksi[i]=NULL;
	}
	free(*path);
	*path=NULL;
	for(i=0;i<size;i++)
		free((*line+i)->symbols);
	free(*line);
	*line=NULL;
	free_tree(&arxi);
	*arxi=NULL;
}