
#include "MDB-pro.c"	

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
  //ReviewNode *temp=NULL;
  int choice=0;
  char title[MAX_STR_LEN];
  char studio[MAX_STR_LEN];
  int year;
  float BO_total;
  float avg;
  int score;
 
  while(choice!=5)
  {
     printf("Please choose one of the following options:\n");
     printf("1 - Insert a new movie review.\n");
     printf("2 - Print out a movie's review list.\n");
     printf("3 - Get a movie's average score.\n");
     printf("4 - Query movies by average score.\n");
     printf("5 - Delete list of reviews and exit.\n");
     scanf("%d",&choice);
     getchar();

     // Read in review information from terminal where needed.
     if (choice>=1&&choice<=3)
     {
       getTitleStudioYear(title,studio,&year);
     }
     if (choice==1)
     {
       getBOtotalScore(&BO_total, &score);
       MDB_head=insertMovieReview(title,studio,year,BO_total,score,MDB_head);
     }
     else if (choice==2)
     {
       printf("Review scores:\n");
       printReviewScores(title,studio,year,MDB_head);
     }
     else if (choice==3)
     {
       avg=getAverageScore(title,studio,year,MDB_head);
       if (avg!=-1)
       {
	 printf("The average score for the movie is %f\n",avg);
       }
       else
       {
	 printf("No such movie in the review database\n");
       }
     }
     else if (choice==4)
     {
       printf("Please input the minimum score you want to look for\n");
       scanf("%d",&score);
       getchar();
       queryReviewsByScore(score,MDB_head);
     }
  }
  
  MDB_head=deleteReviewList(MDB_head);
  printf("Done!\n");
  return 0;
}