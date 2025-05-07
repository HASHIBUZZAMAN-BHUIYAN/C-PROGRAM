#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Define the Korean Question struct
typedef struct {
    int question_id;
    char question_content[255];
    char correct_answer[255];
} KoreanQuestion;

// Define the Trainee struct
typedef struct {
    char name[50];
    char nickname[50];
    char nationality[20];
    int quiz_score;
    int pass_status; // 1 for pass, 0 for fail
} Trainee;

// Define the Quiz Answer struct
typedef struct {
    int question_id;
    char correctness; // 'O' for correct, 'X' for incorrect
} QuizAnswer;

// Initialize the Korean question bank
KoreanQuestion question_bank[10] = {
    {1, "What is the Korean word for 'Hello'?", "안녕하세요"},
    {2, "What is the Korean word for 'Goodbye'?", "안녕히 가세요"},
    {3, "How do you say 'Thank you' in Korean?", "감사합니다"},
    {4, "What is the Korean word for 'Friend'?", "친구"},
    {5, "How do you say 'Yes' in Korean?", "네"},
    {6, "What is the Korean word for 'No' in Korean?", "아니요"},
    {7, "How do you say 'Please' in Korean?", "제발"},
    {8, "What is the Korean word for 'Food'?", "음식"},
    {9, "How do you say 'Excuse me' in Korean?", "죄송합니다"},
    {10, "What is the Korean word for 'Good Morning'?", "좋은 아침"}
};

// Initialize the trainee data
Trainee trainees[4] = {
    {"John Doe", "John", "American", 0, 0},
    {"Park Ji-yeon", "Ji-yeon", "Korean", 0, 0},
    {"Alice Smith", "Alice", "Canadian", 0, 0},
    {"Carlos Sanchez", "Carlos", "Mexican", 0, 0}
};

// Function to randomly select a trainee who is not Korean
void selectRandomTakers() {
    srand(time(NULL));
    int random_index = rand() % 4;
    while (strcmp(trainees[random_index].nationality, "Korean") == 0) {
        random_index = rand() % 4;
    }
    printf("Welcome, %s, to the Korean quiz session!\n", trainees[random_index].name);
}

// Function to serve the quiz by selecting 5 random questions
void serveRandomQuiz(KoreanQuestion *question_bank, int *selected_questions) {
    srand(time(NULL));
    printf("The quiz will start in 30 seconds.\n");
    sleep(30); // Wait for 30 seconds before starting the quiz

    printf("Starting the quiz...\n");
    int question_count = 0;

    // Randomly select 5 unique questions
    while (question_count < 5) {
        int random_question = rand() % 10;
        if (!selected_questions[random_question]) {
            selected_questions[random_question] = 1;
            printf("Question %d: %s\n", question_bank[random_question].question_id, question_bank[random_question].question_content);
            question_count++;
        }
    }
}

// Function to check the answer and store the result
void isAnswer(int question_id, const char *answer, QuizAnswer *quiz_answers) {
    // Find the correct answer for the given question ID
    for (int i = 0; i < 10; i++) {
        if (question_bank[i].question_id == question_id) {
            if (strcmp(answer, question_bank[i].correct_answer) == 0) {
                quiz_answers[question_id - 1].correctness = 'O'; // Correct answer
            } else {
                quiz_answers[question_id - 1].correctness = 'X'; // Incorrect answer
            }
            break;
        }
    }
}

// Function to update the trainee's score and pass status
void updateTraineeScores(Trainee *trainee, QuizAnswer *quiz_answers) {
    int total_score = 0;
    for (int i = 0; i < 10; i++) {
        if (quiz_answers[i].correctness == 'O') {
            total_score += 20; // Each question is worth 20 points
        }
    }
    trainee->quiz_score = total_score;
    trainee->pass_status = (total_score >= 80) ? 1 : 0;
    printf("Total Score: %d\n", total_score);
    printf("Pass Status: %s\n", (trainee->pass_status == 1) ? "Passed" : "Failed");
}

int main() {
    // Step 1: Select a random trainee who is not Korean
    selectRandomTakers();

    // Step 2: Randomly select 5 questions for the quiz
    int selected_questions[10] = {0}; // To track selected questions
    QuizAnswer quiz_answers[10]; // Store the answers

    serveRandomQuiz(question_bank, selected_questions);

    // Step 3: hb Simulate answering the questions
    for (int i = 0; i < 5; i++) {
        int question_id = rand() % 10 + 1; // Random question ID between 1 and 10
        char answer[255];
        printf("Enter answer for question %d: ", question_id);
        scanf("%s", answer);
        isAnswer(question_id, answer, quiz_answers);
    }

    // Step 4: After answering all questions, update the trainee's scores and pass status
    updateTraineeScores(&trainees[0], quiz_answers); // You can select the specific trainee here

    return 0;
}
