
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_Q 15
#define MARKS 1
#define PASS_PERCENT 40.0

struct Question
{
    char text[100];
    char option[4][40];
    int correct;
};

/* Renamed Result to QuizResult to avoid structure conflicts */
typedef struct QuizResult
{
    char name[50];
    int score;
    float percent;
} QuizResult;

/* Quiz Questions */
struct Question quiz[TOTAL_Q] = {

    /* Unit 1: Fundamentals and Control Structures */

    {"Which header file is needed for printf() and scanf()?",
     {"stdio.h", "string.h", "stdlib.h", "math.h"},
     0},

    {"Which of these is a valid C identifier?",
     {"2total", "my-name", "total_marks", "int"},
     2},

    {"Which data type is used to store a single character?",
     {"int", "char", "float", "double"},
     1},

    {"What is the value of 10 % 3?",
     {"0", "3", "1", "3.33"},
     2},

    {"What is stored in x after: int x = 7 / 2;?",
     {"3.5", "4", "2", "3"},
     3},

    {"Which loop always executes its body at least once?",
     {"for", "while", "do-while", "nested if"},
     2},

    {"Which statement is used to exit a loop immediately?",
     {"continue", "break", "exit loop", "stop"},
     1},

    /* Unit 2: Arrays, Strings, Functions and Pointers */

    {"The first element of an array has the index:",
     {"1", "-1", "0", "10"},
     2},

    {"Which built-in function returns the length of a string?",
     {"strlen()", "strcpy()", "strcmp()", "strcat()"},
     0},

    {"Which operator gives the value stored at a pointer's address?",
     {"&", "*", "->", "%"},
     1},

    {"A function that calls itself is known as:",
     {"Library function", "Nested function",
      "Recursive function", "Inline loop"},
     2},

    /* Unit 3: Advanced Programming Concepts */

    {"Which function allocates memory and sets it to zero?",
     {"malloc()", "calloc()", "free()", "realloc()"},
     1},

    {"Which keyword is used to define a structure?",
     {"union", "typedef", "struct", "record"},
     2},

    {"In a union, all the members:",
     {"Have separate memory", "Share the same memory",
      "Are always int", "Are read-only"},
     1},

    {"Which file mode is used to add data at the end of a file?",
     {"r", "w", "a", "x"},
     2}};

/* Recursive function to calculate maximum marks */

int maxScore(int n)
{
    if (n == 0)
        return 0;

    return MARKS + maxScore(n - 1);
}

/* Read and validate user option */

char readOption(void)
{
    char ch;

    while (1)
    {
        printf("Your answer (A/B/C/D): ");

        if (scanf(" %c", &ch) != 1)
            exit(0);

        if (ch >= 'a' && ch <= 'z')
            ch = ch - 32;

        if (ch >= 'A' && ch <= 'D')
            return ch;

        printf("Invalid choice! Please enter A, B, C or D.\n");
    }
}

/* Display question using pointer */

int askQuestion(const struct Question *q, int number)
{
    int i;

    printf("\nQ%d. %s\n", number, q->text);

    for (i = 0; i < 4; i++)
    {
        printf("   %c) %s\n", 'A' + i, q->option[i]);
    }

    return readOption() - 'A';
}

/* Calculate grade */

char getGrade(float p)
{
    if (p >= 90)
        return 'A';
    else if (p >= 75)
        return 'B';
    else if (p >= 60)
        return 'C';
    else if (p >= 40)
        return 'D';
    else
        return 'F';
}

/* Save result in file */

void saveResult(const QuizResult *r)
{
    FILE *fp = fopen("scores.txt", "a");

    if (fp == NULL)
    {
        printf("Could not save the score.\n");
        return;
    }

    fprintf(fp, "%s,%d,%.1f\n",
            r->name, r->score, r->percent);

    fclose(fp);

    printf("Your score has been saved.\n");
}

/* View previously saved scores */

void viewScores(void)
{
    QuizResult r;
    int count = 0;

    FILE *fp = fopen("scores.txt", "r");

    if (fp == NULL)
    {
        printf("\nNo scores saved yet. Play the quiz first!\n");
        return;
    }

    printf("\n%-20s %-8s %-10s\n",
           "Name", "Score", "Percent");

    printf("------------------------------------------\n");

    while (fscanf(fp, " %49[^,],%d,%f",
                  r.name, &r.score, &r.percent) == 3)
    {

        printf("%-20s %-8d %.1f%%\n",
               r.name, r.score, r.percent);

        count++;
    }

    if (count == 0)
        printf("The score file is empty.\n");

    fclose(fp);
}

/* Display instructions */

void showInstructions(void)
{
    printf("\n----------- INSTRUCTIONS -----------\n");

    printf("1. The quiz has %d multiple-choice questions.\n", TOTAL_Q);
    printf("2. Each correct answer gives %d mark.\n", MARKS);
    printf("3. There is no negative marking.\n");
    printf("4. Enter A, B, C or D to answer.\n");
    printf("5. You pass with %.0f%% or more.\n", PASS_PERCENT);
}

/* Main quiz function */

void playQuiz(void)
{
    QuizResult r;

    int i, total = maxScore(TOTAL_Q);

    int *answers = (int *)calloc(TOTAL_Q, sizeof(int));

    if (answers == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("\nEnter your name: ");

    if (scanf(" %49[^\n]", r.name) != 1)
    {
        printf("Invalid name input.\n");
        free(answers);
        return;
    }

    r.score = 0;

    for (i = 0; i < TOTAL_Q; i++)
    {

        answers[i] = askQuestion(&quiz[i], i + 1);

        if (answers[i] == quiz[i].correct)
        {

            printf("Correct! +%d mark\n", MARKS);

            r.score += MARKS;
        }
        else
        {

            printf("Wrong! Correct answer: %c) %s\n",
                   'A' + quiz[i].correct,
                   quiz[i].option[quiz[i].correct]);
        }
    }

    /* Calculate percentage */

    r.percent = (float)r.score / total * 100;

    /* Display final result */

    printf("\n=========== FINAL RESULT ===========\n");

    printf("Name       : %s\n", r.name);

    printf("Score      : %d / %d\n", r.score, total);

    printf("Percentage : %.1f%%\n", r.percent);

    printf("Grade      : %c\n", getGrade(r.percent));

    /* Pass or fail */

    if (r.percent >= PASS_PERCENT)
    {

        if (r.percent == 100)
            printf("Result     : PASS - Perfect score!\n");

        else
            printf("Result     : PASS - Well done!\n");
    }
    else
    {

        printf("Result     : FAIL - Keep practising!\n");
    }

    /* Display incorrect answers */

    printf("\n--- Questions you missed ---\n");

    i = 0;

    while (i < TOTAL_Q)
    {

        if (answers[i] == quiz[i].correct)
        {
            i++;
            continue;
        }

        printf("Q%d: You chose %c, correct is %c\n",
               i + 1,
               'A' + answers[i],
               'A' + quiz[i].correct);

        i++;
    }

    if (r.score == total)
        printf("None - you answered everything correctly!\n");

    /* Save result and release memory */

    saveResult(&r);

    free(answers);
}

/* Main function */

int main(void)
{
    int choice;

    printf("====================================\n");
    printf("       C PROGRAMMING QUIZ APP\n");
    printf("====================================\n");

    do
    {

        printf("\n1. Start Quiz\n");
        printf("2. Instructions\n");
        printf("3. View Saved Scores\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
            break;

        switch (choice)
        {

        case 1:
            playQuiz();
            break;

        case 2:
            showInstructions();
            break;

        case 3:
            viewScores();
            break;

        case 4:
            printf("\nThank you for playing. Goodbye!\n");
            break;

        default:
            printf("Invalid choice! Please select 1-4.\n");
        }

    } while (choice != 4);

    return 0;
}
