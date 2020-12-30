#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

// for circle detection
bool isCircle = false;
void dfsVisit(int node, int visit[], int father[]);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] ++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                int tmp_winner = pairs[i].winner;
                int tmp_loser = pairs[i].loser;
                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;
                pairs[j].winner = tmp_winner;
                pairs[j].loser = tmp_loser;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int visit[candidate_count]; // initialize to 0
    int father[candidate_count]; // initialize to -1
    for (int i = 0; i < candidate_count; i++)
    {
        visit[i] = 0;
        father[i] = -1;
    }

    // TODO
    for (int p = 0; p < pair_count; p++)
    {
        locked[pairs[p].winner][pairs[p].loser] = true;
        // after adding the new edge(arrow), check if there is a circle
        for (int i = 0; i < candidate_count; i++)
        {
            if (visit[i] == 0)
            {
                dfsVisit(i, visit, father);
            }
        }
        if (isCircle)
        {
            locked[pairs[p].winner][pairs[p].loser] = false;
            isCircle = false;
            for (int j = 0; j < candidate_count; j++)
            {
                visit[j] = 0;
                father[j] = -1;
            }
        }
        else
        {
            isCircle = false;
            for (int j = 0; j < candidate_count; j++)
            {
                visit[j] = 0;
                father[j] = -1;
            }
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int winner = 0, i = 0, j = 0;
    for (i = 0; i < candidate_count; i++)
    {
        for (j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                break;
            }
        }
        if (j == candidate_count)
        {
            winner = i;
            printf("%s\n", candidates[winner]);
            return;
        }
    }
    return;
}

// https://www.cnblogs.com/tenosdoit/p/3644225.html
void dfsVisit(int node, int visit[], int father[])
{
    int n = candidate_count;
    visit[node] = 1;
    for (int i = 0; i < n; i++)
    {
        if (i != node && locked[node][i])
        {
            if (visit[i] == 1 && i != father[node])
            {
                isCircle = true;
                break;
            }
            else if (visit[i] == 0)
            {
                father[i] = node;
                dfsVisit(i, visit, father);
            }
        }
    }
    visit[node] = 2;
}