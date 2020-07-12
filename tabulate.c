#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    // Loop till all the voters
    for (int i = 0; i < voter_count: i++)
    {
        // Assign the candidate number who has given 1st rank
        int no = preferences[i][0];

        // If candidate is not eliminated
        if (candidate[no].eliminated == false)
        {
            // Update the vote
            candidate[no].votes++;
        }

        // If candidate is eliminated
        else
        {
            // Move to next rank
            int no1 = preferences[i][1];
            candidate[no1].votes++;
        }
    }

    // End
    return 0;
}