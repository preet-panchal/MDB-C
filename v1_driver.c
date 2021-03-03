
#include "MDB-c.c"	
			
int main()
{
  ReviewNode *MDB_head=NULL;
  ReviewNode *temp=NULL;
  int length;
  
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
        MDB_head->review.BO_total!=(float)203630630.0||\
        MDB_head->review.score!=85)
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
  // to the old head of the list
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
  
  // Test #3: Insert another node and check linkage of the list
  // Expects: The list should have 3 nodes, in the right order, with the right content.
  temp=MDB_head;
  MDB_head=insertMovieReview("Back to the Future","Universal Studios", 1985,  381189762.00, 85, MDB_head);
  // Check that the head node contains the new review.
  if (strcmp("Back to the Future",MDB_head->review.movie_title)!=0)
  {
    printf("Failed Test #3: Movie data looks incorrect!\n");
    return 1;
  }  
  if (MDB_head->next!=temp)
  {
    printf("Failed Test #3, the new head node is not linked to the old head node!\n");
    return 1;
  }
  else
  {
    // Check the LAST node (there should be 3 now)
    temp=MDB_head->next;
    temp=temp->next;
    if (temp->next!=NULL)
    {
     printf("Failed Test #3, the last node has a non-NULL pointer in the *next field!\n");
     return 1;
    }
    if (strcmp("Alien",temp->review.movie_title)!=0)
    {
     printf("Failed Test #3, the last node movie title is not correct!\n");
     return 1;
    }
  }
  printf("Passed Test #3\n");

  // Test #4: Test the countReviews() function
  // Expects: The correct list length must be returned
  length=countReviews(MDB_head);
  if (length!=3)
  {
    printf("Failed Test #4: There should be 3 reviews at this point, countReviews() returned %d\n",length);
    return 1;
  }
  printf("Passed Test #4\n");

  // Test #5: Insert a duplicate review
  // Expects: No duplicate should be inserted into the list
  temp=MDB_head;
  MDB_head=insertMovieReview("Raiders of the Lost Ark","20th Century Fox", 1981, 389925971.00, 85, MDB_head);
  if (temp!=MDB_head||countReviews(MDB_head)!=length)
  {
    printf("Failed Test #5: The insert function updated the list with a duplicate\n");
    return 1;
  }
  printf("Passed Test #5\n");
  
  // Test #6: Insert a near-duplicate
  // Expects: Near duplicates are allowed, so a new node must be added, length should be 4
  temp=MDB_head;
  MDB_head=insertMovieReview("Alien","20th Century Fox",1978,203630630.0,85, MDB_head);
  length=countReviews(MDB_head);
  if (length!=4||MDB_head->next!=temp||MDB_head->review.year!=1978)
  {
    printf("Failed Test 6: The list does not have the right length, or it's not properly linked, or has the wrong content\n");
    return 1;
  }
  printf("Passed test #6\n");
  
  // Test #7: Test the search function for an existing movie
  // Expects: The search function must return a pointer to the movie review matching the query
  temp=findMovieReview("Alien","20th Century Fox",1979,MDB_head);
  if (temp==NULL)
  {
    printf("Failed Test #7: the find function did not find the movie.\n");
    return 1;
  }
  else
  {
    if (strcmp("Alien",temp->review.movie_title)!=0||\
	strcmp("20th Century Fox",temp->review.movie_studio)!=0||\
	temp->review.year!=1979)
    {
      printf("Failed Test #7: the find function did not check all fields match\n");
      return 1;
    }
  }
  printf("Passed Test #7\n");
  
  // Test #8: Test the search function for a non-existing movie
  // Expects: The search function must return NULL
  temp=findMovieReview("Alienized","21st Century Fox",2979,MDB_head);
  if (temp!=NULL)
  {
    printf("Failed Test #8: The search function returned a non-NULL node for a non-existing movie!\n");
    return 1;
  }
  printf("Passed Test #8\n");
  
  // Test #9: Test the update review function
  // Expected: The requested review must have its information updated
  updateMovieReview("Back to the Future","Universal Studios",1985,5000000000,99,MDB_head);
  temp=findMovieReview("Back to the Future","Universal Studios", 1985, MDB_head);
  if (temp==NULL)
  {
    printf("Failed Test #9: Can't find updated review\n");
    return 1;
  }
  else
  {
    if (temp->review.BO_total!=(float)5000000000||temp->review.score!=99)
    {
      printf("Failed Test #9: Review information was not updated\n");
      return 1;
    }    
  }
  printf("Passed Test #9\n");
  
  // Test #10: Test deletion of a review within the linked list (not head, not tail)
  // Expected: The review should be deleted, list length should be 3 after deletion
  temp=MDB_head;
  MDB_head=deleteMovieReview("Raiders of the Lost Ark","20th Century Fox",1981,MDB_head);
  length=countReviews(MDB_head);
  if (temp!=MDB_head)
  {
    printf("Failed Test #10: The list head changed\n");
    return 1;
  }
  if (length!=3)
  {
    printf("Failed Test #10: The list has the wrong length\n");
    return 1;
  }
  temp=findMovieReview("Raiders of the Lost Ark","20th Century Fox", 1981,MDB_head);
  if (temp!=NULL)
  {
    printf("Failed Test #10: The requested movie was found in the list - the wrong thing got deleted!\n");
    return 1;
  }
  printf("Passed Test #10\n");
    
  // Test #11: Test deletion of a review at the head of the list
  // Expected: The review should be deleted, list length should be 2.
  temp=MDB_head;
  MDB_head=deleteMovieReview("Alien","20th Century Fox",1978,MDB_head);
  length=countReviews(MDB_head);
  if (temp==MDB_head)
  {
    printf("Failed Test #11: The delete function did not remove the head node\n");
    return 1;
  }
  if (length!=2)
  {
    printf("Failed Test #11: The list length is wrong\n");
    return 1;
  }
  if (strcmp("Back to the Future",MDB_head->review.movie_title)!=0)
  {
    printf("Faied Test #11: The wrong node is at the head of the list\n");
  }
  printf("Passed Test #11\n");
  
  // Test #12: Query functions - queryReviewsByScore()
  // Expected: The function should print any reviews with a score equal to or greater than
  //  the query value
  queryReviewsByScore(95,MDB_head);
  // Check that the output contains exactly 1 movie, the *updated* Back to the Future with
  // a score of 99.
  
  // Test #13: Deleting a linked list
  // Expected: The list should be deleted and the MDB_head pointer should be NULL 
  MDB_head=deleteReviewList(MDB_head);
  if (MDB_head!=NULL)
  {
    printf("Failed Test #13: The list head pointer is not NULL\n");
    return 1;
  }
  else if (countReviews(MDB_head)!=0)
  {
    printf("Failed Test #13: countReviews() returns %d reviews still in the list\n",countReviews(MDB_head));
    return 1;
  }
  printf("Passed Test #13\n");

  
  printf("Congratulations! your solution passed all the tests you un-commented!\n");
  printf("Remember to run your own tests as well to make sure your code works under all conditions\n");
  
  return 0;		// All good!  
}