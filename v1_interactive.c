
#include "MDB-c.c"	

void getTitleStudioYear(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int *year)
{
  // This function reads the movie's name, title, and year from the terminal.
  // It's needed for inserting new reviews, for search, updating, and deletion.
  printf("Please enter the movie's title:\n");
  fgets(title,1024,stdin);
  printf("Please enter the movie's studio:\n");
  fgets(studio,1024,stdin);
  printf("Please enter the movie's year:\n");
  scanf("%d",year);
  getchar();
}

void getBOtotalScore(float *BO_total, int *score)
{
  // This function reads the movie's Box-Office total and its score from 
  // the terminal. Required for inserting a new movie review, or for
  // updating an existing review.
  printf("Please enter the Box Office total:\n");
  scanf("%f",BO_total);
  getchar();
  printf("Please enter the review score:\n");
  scanf("%d",score);
  getchar();
}
			
int main()
{
  ReviewNode *MDB_head=NULL;
  ReviewNode *temp=NULL;
  int choice=0;
  char title[MAX_STR_LEN];
  char studio[MAX_STR_LEN];
  int year;
  float BO_total;
  int score;
 
  while(choice!=9)
  {
     printf("Please choose one of the following options:\n");
     printf("1 - Insert a new movie review.\n");
     printf("2 - Search for a movie review.\n");
     printf("3 - Modify an existing movie review.\n");
     printf("4 - Delete a movie review.\n");
     printf("5 - Print out existing reviews.\n");
     printf("6 - Query reviews by studio.\n");
     printf("7 - Query reviews by score.\n");
     printf("8 - Sort reviews by movie title.\n");
     printf("9 - Delete list of reviews and exit.\n");
     scanf("%d",&choice);
     getchar();

     // Read in review information from terminal where needed.
     if (choice>=1&&choice<=4)
     {
       getTitleStudioYear(title,studio,&year);
     }
     if (choice==1||choice==3) 
     {
       getBOtotalScore(&BO_total, &score);
     }
     if (choice==1) 
     {
       MDB_head=insertMovieReview(title,studio,year,BO_total,score,MDB_head);
     }
     else if (choice==2)
     {
       temp=findMovieReview(title,studio,year,MDB_head);
       if (temp!=NULL)
       {
	 printf("Found the query movie:\n");
	 printf("It had a box office total of %f\n",temp->review.BO_total);
	 printf("And has a score of %d\n",temp->review.score);
       }
       else
       {
	 printf("No such movie in the current list\n");
       }
     }
     else if (choice==3)
     {
       updateMovieReview(title,studio,year,BO_total,score,MDB_head);
     }
     else if (choice==4)
     {
       MDB_head=deleteMovieReview(title,studio,year,MDB_head);
     }
     else if (choice==5)
     {
       printMovieReviews(MDB_head);
     }
     else if (choice==6)
     {
       printf("Please enter the name of the studio you want to list movies for:\n");
       fgets(studio,1024,stdin);
       queryReviewsByStudio(studio,MDB_head);
     }
     else if (choice==7)
     {
       printf("Enter the minimum score to be used to search for movies:\n");
       scanf("%d",&score);
       getchar();
       queryReviewsByScore(score,MDB_head);
     }
     else if (choice==8)
     {
       printf("Sorting movies by title!\n");
       MDB_head=sortReviewsByTitle(MDB_head);
     }
            
  }
  
  MDB_head=deleteReviewList(MDB_head);
  printf("Done!\n");
  return 0;
}
