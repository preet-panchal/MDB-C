
#include "MDB-pro.c"	

int main()
{
  ReviewNode *MDB_head=NULL;
  ReviewNode *temp=NULL;
  //int length;

  // Test #1: With an initially empty list, insert a new movie review. 
  // Expects: The linked list should contain the new review after the test.
  MDB_head=insertMovieReview("Alien","20th Century Fox",1979,203630630.0,85,MDB_head);
  // Check whether the movie went into the linked list by accessing the
  // head node directly
  if (MDB_head==NULL)
  {
      printf("Failed Test #1 - insertMovieReview() returned NULL\n");
  }
  else
  {
    if (strcmp(MDB_head->review.movie_title,"Alien")!=0||\
        strcmp(MDB_head->review.movie_studio,"20th Century Fox")!=0||\
        MDB_head->review.year!=1979||\
        MDB_head->review.BO_total!=(float)203630630.0)
    {
      printf("Failed Test #1 - The movie information is incorrect\n");
      return 1;
    }
    // Check this node has a NULL pointer for the *next field 
    if (MDB_head->next!=NULL)
    {
      printf("Failed Test #1 - Head node's *next field is not NULL\n");
      return 1;
    }
  }
  printf("Passed Test #1\n");
  
  // Test #2: Insert another node into the list (which now has one movie)
  // Expects: The list should contain two reviews, in the right order
  temp=MDB_head;
  MDB_head=insertMovieReview("Raiders of the Lost Ark","20th Century Fox", 1981,  389925971.00, 85, MDB_head);
  
  // Check that the head node contains the new review.
  if (strcmp("Raiders of the Lost Ark",MDB_head->review.movie_title)!=0)
  {
    printf("Failed Test #2: Movie data is incorrect!\n");
    return 1;
  }
  // Check linkage. The new head node's *next field should contain a pointer
  // to the old head of the list (which we conveniently saved)
  if (MDB_head->next!=temp)
  {
    printf("Failed Test #2, the new head node is not linked to the old head node!\n");
    return 1;
  }
  else
  {
    // Check that the last node in the list has a NULL pointer in the *next field
    temp=MDB_head->next;
    if (temp->next!=NULL)
    {
     printf("Failed Test #2, the last node has a non-NULL pointer in the *next field!\n");    
     return 1;
    }
  }
  printf("Passed Test #2\n");
  
  // Test #3: Insert a new score for an existing movie
  // Expects: The movie should now have two scores in its list
  MDB_head=insertMovieReview("Alien","20th Century Fox",1979,203630630.0,75,MDB_head);
  printReviewScores("Alien","20th Century Fox",1979,MDB_head);
  // This should print:
  // 75
  // 85
  
  // Test #4: Insert a new score for an existing movie
  // Expects: The movie should now have three scores in its list
  MDB_head=insertMovieReview("Alien","20th Century Fox",1979,203630630.0,95,MDB_head);
  printReviewScores("Alien","20th Century Fox",1979,MDB_head);
  // This should print:
  // 95
  // 75
  // 85

  // Test #5: Get the average score for a movie
  // Expects: The correct average score should be returned
  if ((int)getAverageScore("Alien","20th Century Fox",1979,MDB_head)!=85)
  {
    printf("Failed Test #5: The average score is not correct\n");
    return 1;
  }
  printf("Passed Test #5\n");

  // Test #6: Query reviews by score
  // Expects: Movies whose average score is greater than the query value must be printed
  MDB_head=insertMovieReview("Raiders of the Lost Ark","20th Century Fox", 1981,  389925971.00, 15, MDB_head);
  queryReviewsByScore(75,MDB_head);
  // Should only print the Aliens movie - we just made sure above that Raiders of the Lost Ark is toast.
  
  printf("Done! this is a very light tasting script, so you should go and test more! make sure your code is solid!\n");
  return 0;	 
}