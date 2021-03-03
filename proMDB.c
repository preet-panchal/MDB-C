
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STR_LEN 1024

/* Compound data type declarations */
typedef struct ScoreNode_struct
{
	int score;
	struct ScoreNode_struct *next;
}ScoreNode;

ScoreNode *newScoreNode()
{
	ScoreNode * new_score = NULL;
	new_score = (ScoreNode *)calloc(1,sizeof(ScoreNode));
	new_score->score = -1;
	new_score->next = NULL;
	return new_score;
}

ScoreNode *insertIntegerValue(int score, ScoreNode *scores_head)
{
	if (scores_head==NULL)
	{
		scores_head = newScoreNode();
		scores_head->score = score;
		scores_head->next = NULL;
		return scores_head;
	}
	ScoreNode *new_scores_head = NULL;
	new_scores_head = newScoreNode();
	new_scores_head->score = score;
	new_scores_head->next = scores_head;
	return new_scores_head;
}

typedef struct MovieReview_struct
{
	char movie_title[MAX_STR_LEN];
	char movie_studio[MAX_STR_LEN];
	int year;
	float BO_total;
	ScoreNode *scores_head;
} MovieReview;

typedef struct ReviewNode_struct
{
	MovieReview review;
	struct ReviewNode_struct *next;
} ReviewNode;

ReviewNode *newMovieReviewNode()
{
    /*
     * This function allocates a new, empty ReviewNode, and initializes the
     * contents of the MovieReview for this node to empty values.
     * The fields in the MovieReview should be set to:
     *  movie_title=""
     *  movie_studio=""
     *  year = -1
     *  BO_total = -1
     *  score = -1
     * 
     * The *next pointer for the new node MUST be set to NULL
     * 
     * The function must return a pointer to the newly allocated and initialized
     * node. If something goes wrong, the function returns NULL
     */

	ReviewNode * new_review = NULL;
	new_review = (ReviewNode *)calloc(1, sizeof(ReviewNode));
	strcpy(new_review->review.movie_title,"");
	strcpy(new_review->review.movie_studio,"");
	new_review->review.year = -1;
	new_review->review.BO_total = -1;
	new_review->review.scores_head = NULL;
	new_review->next = NULL;
	
	return new_review;	// <--- This should change when after you implement your solution
}

ReviewNode *findMovieReview(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, ReviewNode *head)
{
    /*
     * This function searches through the linked list for a review that matches the input query. 
     * In this case, the movie review must match the title, studio, and year provided in the 
     * parameters for this function.
     * 
     * If a review matching the query is found, this function returns a pointer to the node that
     * contains that review. 
     * 
     * If no such review is found, this function returns NULL
     */

    ReviewNode *p = NULL;   // Traversal pointer
	p = head;
	while (p != NULL)
	{
		if (strcmp(p->review.movie_title,title)==0 && strcmp(p->review.movie_studio,studio)==0 && p->review.year == year)
		{
			// Found the key! Return a pointer to this node
			return p;
		}
		p=p->next;
	}
    return p;	// <--- If no such review is found, this function returns NULL
}

ReviewNode *insertMovieReview(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, float BO_total, int score, ReviewNode *head)
{
    /*
     * This function inserts a new movie review into the linked list.
     * 
     * The function takes as input parameters the data neede to fill-in the review,
     * as well as apointer to the current head of the linked list.
     * 
     * If head==NULL, then the list is still empty.
     * 
     * The function inserts the new movie review *at the head* of the linked list,
     * and returns the pointer to the new head node.
     * 
     * The function MUST check that the movie is not already in the list before
     * inserting (there should be no duplicate entries). If a movie with matching
     * title, studio, and year is already in the list, nothing is inserted and the
     * function returns the current list head.
     */
    
    if (head==NULL)		// If the list is empty
	{
		head = newMovieReviewNode();
		strcpy(head->review.movie_title,title);
		strcpy(head->review.movie_studio,studio);
		head->review.year = year;
		head->review.BO_total = BO_total;
		head->review.scores_head = insertIntegerValue(score, NULL);
		head->next = NULL;
		return head;
	}
	
	// check if the movie review already exists
	ReviewNode *s = NULL;
	s = findMovieReview(title, studio, year, head);
	if (s != NULL)
	{	
		s->review.scores_head = insertIntegerValue(score, s->review.scores_head);
		return head;	// return head if movie already exists in the list
	}
	ReviewNode *new_head = NULL;
	new_head = newMovieReviewNode();
	
	strcpy(new_head->review.movie_title,title);
	strcpy(new_head->review.movie_studio,studio);
	new_head->review.year = year;
	new_head->review.BO_total = BO_total;
	new_head->review.scores_head = insertIntegerValue(score, NULL);
	new_head->next = head;
	
    return new_head;	// <--- This should change when after you implement your solution
}

int countReviews(ReviewNode *head)
{
  /*
   * This function returns the length of the current linked list. This requires
   * list traversal.
   */

    int count = 0;
	ReviewNode *p = NULL;
	p = head;
	while (p != NULL)
	{
		count++;
		p=p->next;
	}
    return count;	// <--- This should change when after you implement your solution
}



ReviewNode *deleteMovieReview(char title[MAX_STR_LEN], char studio[MAX_STR_LEN],int year, ReviewNode *head)
{
    /*
     * This function removes a review matching the input query from the linked list. If no such review can
     * be found, it does nothing.
     * 
     * The function returns a pointer to the head of the linked list (which may have changed as a result
     * of the deletion process)
     */

	ReviewNode *tr = NULL;
	ReviewNode *pre = NULL;
	
	if (head==NULL)		// Empty linked list!
		return NULL;	
    
	pre = head;
	tr = head->next;
	// Check if we have to remove the head node
	if (strcmp(pre->review.movie_title,title)==0 && strcmp(pre->review.movie_studio,studio)==0 && pre->review.year == year)
	{
		free(pre);
		return tr;
	}
	
	while(tr!=NULL)
	{
		if (strcmp(tr->review.movie_title,title)==0 && strcmp(tr->review.movie_studio,studio)==0 && tr->review.year == year)
		{
			pre->next = tr->next;	// Update predecessor pointer
			free(tr);	//remove node
			return head;
		}
		tr = tr->next;
		pre = pre->next;
	}
	return head;	// <--- This should change when after you implement your solution
}

void printMovieReviews(ReviewNode *head)
{
    /*
     * This function prints out all the reviews in the linked list, one after another.
     * Each field in the review is printed in a separate line, with *no additional text*
     * (that means, the only thing printed is the value of the corresponding field).
     * 
     * Reviews are separated from each other by a line of
     * "*******************"
     */
    
	ReviewNode *p =NULL;
	p = head;
	while (p!=NULL)
	{
		printf("%s\n",p->review.movie_title);
		printf("%s\n",p->review.movie_studio);
		printf("%d\n",p->review.year);
		printf("%f\n",p->review.BO_total);
		//printf("%d\n",p->review.score);
		printf("*******************\n");
		p=p->next;
	}
}

void printReviewScores(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, ReviewNode *head)
{
    
	ReviewNode *p =NULL;
	p = head;
	while (p!=NULL)
	{
		if (strcmp(p->review.movie_title,title)==0 && strcmp(p->review.movie_studio,studio)==0 && p->review.year == year)
		{
			
			ScoreNode *q= NULL;
			q = p->review.scores_head;
			while (q!= NULL)
			{
				printf("%d\n",q->score);
				q=q->next;
			}
			break;
		}
		p=p->next;
	}
}

float getAverageScore(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, ReviewNode *head)
{
    
	ReviewNode *p =NULL;
	p = head;
	int total = 0;
	int count = 0;
	
	while (p!=NULL)
	{
		if (strcmp(p->review.movie_title,title)==0 && strcmp(p->review.movie_studio,studio)==0 && p->review.year == year)
		{
			
			ScoreNode *q= NULL;
			q = p->review.scores_head;
			while (q!= NULL)
			{
				total = total + (q->score);
				count++;
				q=q->next;
			}
			return (float)total/count;
		}
		p=p->next;
	}
	return -1;
}

void queryReviewsByStudio(char studio[MAX_STR_LEN], ReviewNode *head)
{
    /*
     * This function looks for reviews whose studio matches the input query.
     * It prints out the contents of all reviews matching the query in exactly
     * the same format used by the printMovieReviews() function above.
     */

	ReviewNode *p =NULL;
	p = head;
	while (p!=NULL)
	{
		if (strcmp(p->review.movie_studio,studio)==0)
		{
			printf("%s\n",p->review.movie_title);
			printf("%s\n",p->review.movie_studio);
			printf("%d\n",p->review.year);
			printf("%f\n",p->review.BO_total);
			//printf("%d\n",p->review.score);
			printf("*******************\n");
		}
		
		p=p->next;
	}
}

void queryReviewsByScore(int min_score, ReviewNode *head)
{
    /*
     * This function looks for reviews whose score is greater than, or equal to
     * the input 'min_score'.
     * It prints out the contents of all reviews matching the query in exactly
     * the same format used by the printMovieReviews() function above.
     */
    
	ReviewNode *p =NULL;
	p = head;
	float avg = -1;
	ScoreNode *q= NULL;
	int total = 0;
	int count = 0;
	
	while (p!=NULL)
	{
		total = 0;
		count = 0;
		q = p->review.scores_head;
		while (q!= NULL)
		{
			total = total + (q->score);
			count++;
			q=q->next;
		}
		avg = (float)total/count;
		if (avg > min_score)
		{
			printf("%s\n",p->review.movie_title);
			printf("%s\n",p->review.movie_studio);
			printf("%d\n",p->review.year);
			printf("%f\n",p->review.BO_total);
			printf("%f\n",avg);
			printf("*******************\n");
		}
		
		p=p->next;
	}
}

ReviewNode *deleteReviewList(ReviewNode *head)
{
  /*
   * This function deletes the linked list of movie reviews, releasing all the
   * memory allocated to the nodes in the linked list.
   * 
   * Returns a NULL pointer so that the head of the list can be set to NULL
   * after deletion.
   */

	ReviewNode *p = NULL;
	ReviewNode *q = NULL;
	
	p = head;
	while (p!=NULL)
	{
		q=p->next;
		free(p);
		p=q;
	}
    return p;	// <--- This should change when after you implement your solution
}

ReviewNode *sortReviewsByTitle(ReviewNode *head)
{
  /*
   * This function sorts the list of movie reviews in ascending order of movie
   * title. If duplicate movie titles exist, the order is arbitrary (i.e. you
   * can choose which one goes first).
   * 
   * However you implement this function, it must return a pointer to the head
   * node of the sorted list.
   */

	if(head==NULL)
		return NULL;
	ReviewNode *i,*j;
	char temp_movie_title[MAX_STR_LEN];
	char temp_movie_studio[MAX_STR_LEN];
	int temp_year;
	float temp_BO_total;
	int temp_score;
	
	for(i=head;i->next!=NULL;i=i->next)
	{
		for(j=i->next; j!=NULL; j=j->next)
		{
			if(strcmp(i->review.movie_title,j->review.movie_title)>0)
			{
				strcpy(temp_movie_title,i->review.movie_title);
				strcpy(temp_movie_studio ,i->review.movie_studio);
				temp_year = i->review.year;
				temp_BO_total = i->review.BO_total;
				temp_score = i->review.score;
				
				strcpy(i->review.movie_title,j->review.movie_title);
				strcpy(i->review.movie_studio , j->review.movie_studio);
				i->review.year = j->review.year;
				i->review.BO_total = j->review.BO_total;
				i->review.score = j->review.score;
				
				strcpy(j->review.movie_title ,temp_movie_title);
				strcpy(j->review.movie_studio,temp_movie_studio);
				j->review.year=temp_year;
				j->review.BO_total = temp_BO_total;
				j->review.score = temp_score;
				
			}
		}
	}
    return head;
}


