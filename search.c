#ifndef __structs_h_
#define __structs_h_

#include "structs.h"
#endif
#include "search.h"
#include "df.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
struct result{
	int id_result;
	double score;
};
int frequency_of_word(struct gramma* tree,char word[],int ID)
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
						return 0;
					struct vision* arxi=my_beg->beg;
					while(1)
					{
						if(arxi->grammi_keimenou==ID)
							return arxi->fores_emfanisis;
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
			return 0;
	}
	return 0;
}
int finding_how_manyfounds(char word[],struct gramma* tree)
{
	int vrethike=0,i;
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
					struct posting_list* er=current->my_list;
					if(er==NULL)
						return -1;
					struct vision *node=er->beg;
					int sum=1;
					while(1)
					{
						if(node->next!=NULL)
							sum++;
						else
							return sum;
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
			return 0;
	}
}
int compare(const void* p1,const void* p2)
{
	struct result* elem1=(struct result*)p1;
	struct result* elem2=(struct result*)p2;
	return(elem2->score-elem1->score);
}
void search(struct keimeno* line,char ** word,int size,int size_of_query,int *D,int avgdl,struct gramma* tree,int K)
{
	int ty;
	for(ty=0;ty<=size_of_query;ty++)
		printf("%s\n",word[ty]);
	int beg_value=5;
	struct result* table_results=malloc(beg_value*sizeof(struct result));
	double paronomastis_IDF=0.0;
	double arithmitis_IDF=0.0;
	double klasma1,klasma2;
	double score,IDF;
	double arithmitis=0.0,paronomastis=0.0,ginomeno=0.0;
	int N=size;
	int metritis=0;
	double k1=1.2,b=0.75;
	int i,j;
	for(i=0;i<size;i++)
	{
		score=0.0000;
		for(j=1;j<=size_of_query;j++)
		{
			arithmitis_IDF=N+0.5-finding_how_manyfounds(word[j],tree);
			paronomastis_IDF=finding_how_manyfounds(word[j],tree)+0.5;
			klasma1=arithmitis_IDF/paronomastis_IDF;
			IDF=log10(klasma1);
			arithmitis=(k1+1)*frequency_of_word(tree,word[j],i);
			paronomastis=k1*(1-b+(b*D[i]/avgdl))+frequency_of_word(tree,word[j],i);
			klasma2=arithmitis/paronomastis;
			ginomeno=IDF*klasma2;
			score+=ginomeno;
		}
		table_results[metritis].score=score;
		table_results[metritis++].id_result=i;
		if(metritis==beg_value)
		{	
			beg_value*=2;
			table_results=realloc(table_results,beg_value*sizeof(struct result));
		}
	}
	qsort(table_results,metritis,sizeof(struct result),compare);/* sorting the result based on score*/
	if(metritis>=K)
		metritis=K;
	int coun_result=1;
	int** need;
	int y,k,t;
	need=malloc(metritis*sizeof(int *));
	for(i=0;i<metritis;i++)
		need[i]=malloc((strlen(line[table_results[i].id_result].symbols)+1)*sizeof(int));
	for(i=0;i<metritis;i++)
	{
		for(j=0;j<strlen(line[table_results[i].id_result].symbols);j++)
			need[i][j]=0;
	}
	for(k=1;k<=size_of_query;k++)
    {
        for(i=0;i<metritis;i++)
        {
            int new_word=1;
            int start=0,end=0;
            int prwto_gramma_word;
            int start_word;
            int enter=0;
            int different=0;
            t=0;
            for(j=0;t<strlen(word[k]),j<strlen(line[table_results[i].id_result].symbols);j++)
            {
                if(line[table_results[i].id_result].symbols[j]==' '||line[table_results[i].id_result].symbols[j]=='\t')
                {
                	new_word=1;
                	t=0;
                	continue;
                }
                if(new_word==1)
                {	
                	if(word[k][t]==line[table_results[i].id_result].symbols[j]&&enter==0)
                    {
                    	t=0;
                        start=j;
                        enter=1;
                    }
                   	else if(word[k][t]==line[table_results[i].id_result].symbols[j]&&enter==1)
                    {
                        end=j;
                        if(line[table_results[i].id_result].symbols[j+1]=='\t'||line[table_results[i].id_result].symbols[j+1]==' '||j==strlen(line[table_results[i].id_result].symbols)-1)
                        {
                            for(y=start;y<=end;y++)
                               need[i][y]=1;
                            t=0;
                            enter=0;
                        }
                    }
                    else
                    {
                    	new_word=0;
                    	start=0;
                    	enter=0;
                    	end=0;
                        t=0;
                        continue;
                    }
                    t++;
               	}	
            }
   		}
   	}
	for(i=0;i<metritis;i++)
	{
		printf("%d.(%d)[%f]",coun_result,table_results[i].id_result,table_results[i].score);
		printf("%s\n",line[table_results[i].id_result].symbols);
		for(y=0;y<strlen(line[table_results[i].id_result].symbols);y++)
            if(need[i][y]==1)
            	printf("^");
        printf("\n");
		coun_result++;
	}
	for(i=0;i<metritis;i++)
		free(need[i]);
	free(need);
	free(table_results);
}
/* compare function  with explanation of qsort function found on https://stackoverflow.com/questions/6105513/need-help-using-qsort-with-an-array-of-structs*/
