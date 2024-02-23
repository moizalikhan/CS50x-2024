// Problem 1:
// sort1 uses: bubble sort

// Takes 0.114s to sort reversed5000 list;
// Takes 0.263s to sort reversed10000 list;
// Takes 10.376s to sort reversed50000 list;

// Takes 0.068s to sort random5000 list;
// Takes 0.214s to sort random10000 list;
// Takes 10.043s to sort random50000 list;

// Takes 0.050s to sort sorted5000 list;
// Takes 0.081s to sort sorted10000 list;
// Takes 1.116s to sort sorted50000 list;

// How do you know?: it performs good on the sorted data

// sort2 uses: Merge sort

// Takes 0.031s to sort reversed5000 list;
// Takes 0.075s to sort reversed10000 list;
// Takes 0.952s to sort reversed50000 list;

// Takes 0.041s to sort random5000 list;
// Takes 0.085s to sort random10000 list;
// Takes 2.214s to sort random50000 list;

// Takes 0.044s to sort sorted5000 list;
// Takes 0.110s to sort sorted10000 list;
// Takes 2.604s to sort sorted50000 list;

// How do you know?: it's the fastest

// sort3 uses: Selection sort

// Takes 0.048s to sort reversed5000 list;
// Takes 0.177s to sort reversed10000 list;
// Takes 6.302s to sort reversed50000 list;

// Takes 0.050s to sort random5000 list;
// Takes 0.137s to sort random10000 list;
// Takes 6.009s to sort random50000 list;

// Takes 0.066s to sort sorted5000 list;
// Takes 0.134s to sort sorted10000 list;
// Takes 4.751s to sort sorted50000 list;

// How do you know?: it's performs the worst

// Plurality
// #include <cs50.h>
// #include <stdio.h>
// #include <string.h>

#define MAX 9

typedef struct
{
    string name;
    int votes;
} candidate;

candidate candidates[MAX];

int candidate_count;

bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    print_winner();
}

bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}


void print_winner(void)
{
    int height_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > height_count)
        {
            height_count = candidates[i].votes;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (height_count == candidates[i].votes)
        {
            printf("\n%s\n", candidates[i].name);
        }
    }
    return;
}

// Runoff
// #include <cs50.h>
// #include <stdio.h>
// #include <string.h>

#define MAX_VOTERS 100
#define MAX_CANDIDATES 9


int preferences[MAX_VOTERS][MAX_CANDIDATES];


typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;


candidate candidates[MAX_CANDIDATES];


int voter_count;
int candidate_count;

bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }


    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }


    for (int i = 0; i < voter_count; i++)
    {


        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }


    while (true)
    {

        tabulate();


        bool won = print_winner();
        if (won)
        {
            break;
        }

        int min = find_min();
        bool tie = is_tie(min);


        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }


        eliminate(min);
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}


bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}


void tabulate(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].votes = 0;
    }

    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int preference = preferences[i][j];
            if (!candidates[preference].eliminated)
            {
                candidates[preference].votes++;
                break;
            }
        }
    }
    return;
}


bool print_winner(void)
{
    int More_than_fifty = voter_count / 2 + 1;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > More_than_fifty)
        {
            printf("\n%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}


int find_min(void)
{
    int min_votes = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < min_votes)
        {
            min_votes = candidates[i].votes;
        }
    }
    return min_votes;
}


bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        }
    }
    return true;
}


void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min && !candidates[i].eliminated)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}