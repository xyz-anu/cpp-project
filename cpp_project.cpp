#include <iostream> 
#include <string> 
#include <vector> 
#include <cstdlib> 
#include <ctime> 

using namespace std;

class Lesson {
private:
    string title;
    string content;

public:
    Lesson(const string& lessonTitle, const string& lessonContent)
        : title(lessonTitle), content(lessonContent) {}

    void displayLesson() const {
        cout << "\nLesson: " << title << "\n";
        cout << content << "\n";
    }

    const string& getTitle() const {
        return title;
    }
};

class QuizQuestion {
private:
    string question;
    string correctAnswer;
    vector<string> choices;

public:
    QuizQuestion(const string& quizQuestion, const string& correctAns,
        const vector<string>& answerChoices)
        : question(quizQuestion), correctAnswer(correctAns), choices(answerChoices) {}

    bool checkAnswer(const string& userAnswer) const {
        return userAnswer == correctAnswer;
    }

    void displayQuestion() const {
        cout << "Question: " << question << "\n";
        for (size_t i = 0; i < choices.size(); ++i) {
            cout << i + 1 << ". " << choices[i] << "\n";
        }
    }

    const vector<string>& getChoices() const {
        return choices;
    }
};

class LanguageLearningApp {
private:
    vector<Lesson> lessons;
    vector<QuizQuestion> quizQuestions;

public:
    void addLesson(const Lesson& lesson) {
        lessons.push_back(lesson);
    }

    void addQuizQuestion(const QuizQuestion& question) {
        quizQuestions.push_back(question);
    }

    void startLearning() {
        int choice;
        while (true) {
            cout << "Language Learning App\nLearning C++ now made easy!\nBy,\nAnushka Nevgi\nSwayam Jadhav\nYashodip Randive\nAdhithya Dhanwade\n\nMenu:\n";
            cout << "1. Display Lesson Titles\n";
            cout << "2. Answer a random question\n";
            cout << "3. Take Timed Quiz\n";
            cout << "4. View All Quiz Questions\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cout << endl;
            switch (choice) {
            case 1: {
                displayLessonTitles();
                break;
            }
            case 2: {
                if (quizQuestions.empty()) {
                    cout << "No quiz questions available.\n";
                }
                else {
                    size_t randomIndex = rand() % quizQuestions.size();
                    QuizQuestion& selectedQuestion = quizQuestions[randomIndex];
                    selectedQuestion.displayQuestion();
                    int userChoice;
                    cout << "Enter your choice: ";
                    cin >> userChoice;
                    if (userChoice >= 1 && userChoice <= static_cast<int>(selectedQuestion.getChoices().size())) {
                        if (selectedQuestion.checkAnswer(selectedQuestion.getChoices()[userChoice - 1])) {
                            cout << "Correct! Well done!\n";
                        }
                        else {
                            cout << "Incorrect answer. Try again.\n";
                            cout << "The correct answer is: " << selectedQuestion.getChoices()[0] << "\n";
                        }
                    }
                    else {
                        cout << "Invalid choice.\n";
                    }
                }
                break;
            }
            case 3: {
                takeTimedQuiz();
                break;
            }
            case 4: {
                if (quizQuestions.empty()) {
                    cout << "No quiz questions available.\n";
                }
                else {
                    cout << "All Quiz Questions:\n";
                    for (const QuizQuestion& question : quizQuestions) {
                        question.displayQuestion();
                        cout << "\n";
                    }
                }
                break;
            }
            case 5: {
                cout << "Exiting the app. Goodbye!\n";
                return;
            }
            default: {
                cout << "Invalid choice. Try again.\n";
                break;
            }
            }
            cout << "\nPress Enter to go back to the start...";
            cin.ignore();
            cin.get();
            system("clear || cls");
        }
    }

private:
    void takeTimedQuiz() {
        int numQuestions;
        cout << "Enter the number of quiz questions: ";
        cin >> numQuestions;
        if (numQuestions > quizQuestions.size()) {
            cout << "Not enough quiz questions available.\n";
            return;
        }
        int totalTime;
        cout << "Enter the total time for the quiz (in seconds): ";
        cin >> totalTime;
        int questionIndex = 0;
        int correctAnswers = 0;
        time_t startTime = time(nullptr);
        while (questionIndex < numQuestions && time(nullptr) - startTime < totalTime) {
            QuizQuestion& currentQuestion = quizQuestions[questionIndex];
            cout << "\nQuestion " << questionIndex + 1 << ":\n";
            currentQuestion.displayQuestion();
            int userChoice;
            cout << "Enter your choice: ";
            cin >> userChoice;
            if (userChoice >= 1 && userChoice <= static_cast<int>(currentQuestion.getChoices().size()))
            {
                if (currentQuestion.checkAnswer(currentQuestion.getChoices()[userChoice - 1])) {
                    cout << "Correct!\n";
                    correctAnswers++;
                }
                else {
                    cout << "Incorrect.\n";
                }
            }
            else {
                cout << "Invalid choice.\n";
            }
            questionIndex++;
        }
        int elapsedTime = time(nullptr) - startTime;
        cout << "\nQuiz completed!\n";
        cout << "Total questions: " << numQuestions << "\n";
        cout << "Correct answers: " << correctAnswers << "\n";
        cout << "Time taken: " << elapsedTime << " seconds\n";
    }

    void displayLessonTitles() {
        if (lessons.empty()) {
            cout << "No lessons available.\n";
        }
        else {
            cout << "All Lesson Titles:\n";
            for (size_t i = 0; i < lessons.size(); ++i) {
                cout << i + 1 << ". " << lessons[i].getTitle() << "\n";
            }
            int lessonChoice;
            cout << "\nEnter the lesson number to learn more: ";
            cin >> lessonChoice;
            if (lessonChoice >= 1 && lessonChoice <= static_cast<int>(lessons.size())) {
                lessons[lessonChoice - 1].displayLesson();
            }
            else {
                cout << "Invalid lesson number.\n";
            }
        }
    }
};

int main() {
    LanguageLearningApp app;

    Lesson lesson1("Introduction to C++", "C++ is a general-purpose programming language used for various applications.");
    Lesson lesson2("Variables and Data Types", "Variables are used to store data, and data types specify what type of data they can hold.");
    Lesson lesson3("Control Structures", "Control structures like if statements and loops control the flow of a program.");

    QuizQuestion quiz1("What does 'cout' do in C++?",
        "Prints output to the console",
        { "Reads input from the user", "Performs mathematical calculations", "Prints output to the console" });

    QuizQuestion quiz2("Which data type is used to store whole numbers?",
        "int",
        { "double", "string", "char", "int" });

    QuizQuestion quiz3("What is a 'for' loop used for?",
        "Repeating a set of instructions a specific number of times",
        { "Reading user input", "Performing arithmetic operations", "Repeating a set of instructions a specific number of times" });

    app.addLesson(lesson1);
    app.addLesson(lesson2);
    app.addLesson(lesson3);
    app.addQuizQuestion(quiz1);
    app.addQuizQuestion(quiz2);
    app.addQuizQuestion(quiz3);
    app.startLearning();

    return 0;
}
