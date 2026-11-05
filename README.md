# C-programming-Quiz-project

My project title is Quiz Application in C Programming.

The main purpose of developing this project was to create an automated quiz system using the concepts of C programming.

I noticed that when quizzes are conducted manually, checking answers and calculating marks takes time. So, I decided to develop a program that can automatically conduct a quiz, evaluate answers and generate results.

My application contains 15 multiple-choice questions divided into three units of the C programming syllabus.

Each correct answer carries one mark, and there is no negative marking.

The application also stores previous quiz results in a text file so that users can view their scores later.

Now, I would like to explain the implementation of my project.

### 1\. Technologies and concepts used

I developed this project using the C programming language.

While developing it, I implemented several programming concepts:

| Concept              | Why I used it                                     |
| -------------------- | ------------------------------------------------- |
| Arrays               | To store multiple questions and options           |
| Structures           | To group question-related information             |
| Functions            | To divide the program into smaller modules        |
| Pointers             | To access structure data through memory addresses |
| Recursion            | To calculate maximum marks                        |
| Dynamic memory       | To allocate memory for user answers               |
| File handling        | To save and retrieve quiz results                 |
| Loops and conditions | To control quiz execution and evaluate answers    |

I chose these concepts because they allow me to demonstrate the major topics covered in my C programming syllabus.

### 2\. Implementation of the code

First, I included the required header files.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
```

I used `stdio.h` for input, output and file operations, `stdlib.h` for memory allocation and `string.h` for string-handling functionality.

Next, I defined three constants.

```c
#define TOTAL_Q 15
#define MARKS 1
#define PASS_PERCENT 40.0
```

These constants define the total questions, marks per correct answer and minimum passing percentage.

I used constants so that if I want to change these values in the future, I can do so easily.

Next comes the structure.

```c
struct Question
{
    char text[100];
    char option[4][40];
    int correct;
};
```

I created a structure named `Question` because every question requires three pieces of information: the question itself, four options and the correct answer.

For example, if a question has four options, I store the correct answer as an index from 0 to 3.

I also created another structure.

```c
typedef struct QuizResult
{
    char name[50];
    int score;
    float percent;
} QuizResult;
```

This structure stores the participant's name, obtained score and percentage.

I used `typedef` so I can write `QuizResult` instead of repeatedly writing `struct QuizResult`.

### 3\. How the application actually works

Now, ma'am, I will explain the working of the application through its functions.

### Function 1: `main()`

This is the starting point of my program.

```c
int main(void)
```

I used a `do-while` loop to repeatedly display the menu.

The menu provides four options:

* Start Quiz

* Instructions

* View Saved Scores

* Exit

I used a `switch` statement to execute the selected operation.

For example, if the user enters 1, the program calls `playQuiz()`.

### Function 2: `playQuiz()`

This is the main function responsible for conducting the quiz.

When the user selects Start Quiz:

* The program asks for the participant's name.

* It allocates memory for storing answers.

* It displays all 15 questions.

* It checks each answer.

* It calculates the final result.

This function connects most of the other functions in my application.

### Function 3: `askQuestion()`

```c
int askQuestion(const struct Question *q, int number)
```

I created this function to display one question and its four options.

Here, I used a pointer to the structure instead of passing the complete structure.

I used the `->` operator to access the question and its options through the pointer.

### Function 4: `readOption()`

This function accepts the user's answer.

I wanted the application to accept both uppercase and lowercase letters.

For example, if someone enters `a`, the program converts it into `A`.

If the user enters an invalid option, such as `X`, the program asks again until a valid answer is entered.

### Function 5: `getGrade()`

This function calculates the grade according to the percentage.

For example:

* 90% or above: A

* 75% or above: B

* 60% or above: C

* 40% or above: D

* Below 40%: F

I used `if-else` conditions to implement this grading system.

### Function 6: `maxScore()`

```c
int maxScore(int n)
{
    if (n == 0)
        return 0;

    return MARKS + maxScore(n - 1);
}
```

This is one of the important functions in my project because I implemented recursion here.

Recursion means a function calls itself.

The function keeps calling itself until `n` becomes zero. Then it returns the maximum possible marks.

For my 15-question quiz, the result is 15.

### Function 7: `saveResult()`

After completing the quiz, I save the result in a file named `scores.txt`.

I used:

```c
FILE *fp = fopen("scores.txt", "a");
```

I selected append mode (`"a"`) because I don't want new results to overwrite previously saved results.

I used `fprintf()` to write the participant's name, score and percentage into the file.

### Function 8: `viewScores()`

This function reads previously saved results.

I used file reading mode (`"r"`) and `fscanf()` to retrieve the saved information.

The program then displays the previous results in a table.

### Function 9: `showInstructions()`

This function simply displays the rules of the quiz, including the total questions, marks, negative marking policy and passing percentage.

### 4\. How scoring works

Suppose a participant answers 12 questions correctly.

The program calculates the percentage using:

\\text{Percentage}=\\frac{\\text{Score}}{\\text{Total Marks}}\\times100=\\frac{12}{15}\\times100=80\\%

The grade will be B, and the participant will pass.

The program also displays which questions were answered incorrectly.

### 5\. Demonstration of the project

Now, ma'am, I would like to demonstrate my application.

Step 1 — Main menu

![GitHub - Rushi21-kesh/C-Programming-Quiz-Game: This 'C' programming quiz game is made by using basic knowledge of C and written in C programming language . · GitHub](https://images.openai.com/static-rsc-4/BOYdgOdXQS8eOKZE5wEr8XKZmPTkU802hDSYdGL5w1_obaPh0Knr946Kgf3TSSVsiG0zpXMEtKkIggWWecjH6Sof12DSTBDUOeHFHFrnwaXgbb7XGzwjKcOfUw2oYiig_urA8JhbmFS6-TScn_PBOEFPBMo3BRj3G_2yGE8-3l9kPENWbMr_8YEnHmy1MC3P?purpose=fullsize)

The application displays four menu options.

Step 2 — Answer evaluation

![Fun Quiz Game Using C Programming | C Programming Assignment Help](https://images.openai.com/static-rsc-4/-IKUp84L3sAQnimTDFjZPqN6QJzwRdyyBD7r7cLb8iOVpo9DGRCpYOZfImNoIvOwOk-XQkyW3SMil8fe_8Dq1Tljb5XX_ktOvmMa3iENuch9cylMoL_zM0D7sl8oupVZe9UlC79wE6W5hHB8YHGDD7X9r5yDZrKC2Zpcr1GuHj_jc4-4ZocqaBuCuJjfA9GH?purpose=fullsize)

The program accepts answers and immediately displays feedback.

Step 3 — Final result

![Solved Write a simple C++ program that quizzes the user. You | Chegg.com](https://images.openai.com/static-rsc-4/Hj8h-EAPISWvPP9j8xeZogZFy4tQ-YNfHs40cFfAmFplMvYtYFwrKSRbdrPVfi-EPqAfXgWO2bK3lazmp3updNy0SImd8BlxsadM5kaWPPKPEFOrjwpb81PT--UrhYlC71o-thtlz4eUKqR2gsH2yYNo_5Q0Mt3mdguWWekmmN_EhBB82JsI9fETKwh8BduM?purpose=fullsize)

The program displays the score, percentage, grade and result.

I would also demonstrate the saved scores option to show that file handling is working.

### 6\. Conclusion

To conclude, I successfully developed a menu-driven quiz application using C programming.

Through this project, I was able to implement different programming concepts in one practical application.

The application can conduct quizzes, evaluate answers, calculate results and store previous scores.

In the future, I would like to improve it by adding randomized questions, difficulty levels, a timer and a graphical user interface.
