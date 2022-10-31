#include <iostream>
#include <string>
#include <stdlib.h>
#include <assert.h>
using namespace std;
//Structure for creating a linked list that holds a trivia question,answer and point amount.#include <iostream>
struct triviaGame {
    struct triva_node {
        string question, answer;
        int point;
        triva_node * next;
        //creates a pointer to triva_node.
        triva_node(string userQuestion, string userAnswer, int pointsForUser) {
            question = userQuestion;
            answer = userAnswer;
            point = pointsForUser;
            next = nullptr;
        }
    };

    // Variables
    int length, userScore;
    triva_node * intial;
    triva_node * final;

    triviaGame() {
        length = 0;
        userScore = 0;
        intial = nullptr;
        final = nullptr;
    }

    // Iterator
    struct TriviaIterator {
        triva_node* latest;

        TriviaIterator(triva_node* inputNode) {
            latest = new triva_node("", "", 0);
            latest->next = inputNode;
        }

        bool has_next() {
            return latest->next != nullptr;
        }

        triva_node next() {
            latest = latest->next;
            return (* latest);
        }
    };

    TriviaIterator iterator() {
        return TriviaIterator(intial);
    }

    bool add(string userQuestion, string userAnswer, int userPoints) {
        triva_node * new_node = new triva_node(userQuestion, userAnswer, userPoints);
        if (length == 0) {
            intial = new_node;
        }
        else {
            final->next = new_node;
        }
        final = new_node;
        length++;
        return true;
    }

    //gives user the option to add a question to the linked list. //question is added to the front of the linked list.
    void add_question() {
        string currentQuestion, currentAnswer, pointsAwarded;
        int pointValue;
        //gets data from user.
        cout << "\nEnter a new question: ";
        getline(cin, currentQuestion);
        cout << "Enter an answer: ";
        getline(cin, currentAnswer);
        cout << "Enter award points: ";
        getline(cin, pointsAwarded);
        pointValue = stoi(pointsAwarded);
        add(currentQuestion, currentAnswer, pointValue);
    }

    //gives user the option to add a question to the linked list. //question is added to the front of the linked list.
    bool ask_question(int checkNums) {
        if (checkNums < 1) {
            cout << "Warning - the number of triva_node to be asked must equal to or be larger than 1." << endl;
            return false;
        }
        else if (length < checkNums) {
            cout << "Warning - there (is/are) only " << length << " triva_node question(s) in the list." << endl;
            return false;
        }
        else {
            userScore = 0;
            TriviaIterator itr = iterator();
            int count = 0;
            while (itr.has_next() && count < checkNums) {
                triva_node latest = itr.next();
                string user_answer;
                cout << "\nQuestion: " << latest.question;
                cout << "\nAnswer: ";
                getline(cin, user_answer);
                if (user_answer.compare(latest.answer) == 0) {
                    cout << "Your answer is correct. You receive " << latest.point << " points." << endl;
                    userScore += latest.point;
                }
                else {
                    cout << "Your answer is wrong. The correct answer is: " << latest.answer << endl;
                }
                cout << "Your total points: " << userScore << endl;
                count++;
            }
            return true;
        }
    }

    //initializes the quiz to have these three questions inputted into the linked list.
    void initial_questions(int version) {
        userScore = 0;
        length = 0;
        if (version > 0) {  // version 1 adds this block and the previous
            add("What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)?", "Bank of Germany", 50);
            add("What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)?", "Wii Sports", 20);
        }
        if (version > -1) {  // version 0 selects this list only
            add("How long was the shortest war on record? (Hint: how many minutes)", "38", 100);
        }
    }
};

//#define triva_quiz
#define trivia_quiz

//Creates a new trivia game /
//Sets up three original questions/
//Sets up loop for user to input his or her own questions. 
//Quiz questions are stored in linked list.
int main() {
    triviaGame node_list = triviaGame();
    triviaGame game = triviaGame();

#ifdef trivia_quiz

    cout << "*** Welcome to Jon's triva quiz game ***" << endl;

    string answerFromUser;
    bool add_more = true;
    while (add_more) {
        node_list.add_question();
        cout << "Continue? (Yes/No): ";
        getline(cin, answerFromUser);
        if (answerFromUser.compare("Yes") == 0 || answerFromUser.compare("yes") == 0) {
            add_more = true;
        }
        else {
            add_more = false;
        }
    }

    cout << "\n\nWelcome to the triva Game!" << endl;
    node_list.ask_question(node_list.length);

    //This is start of Trivia quiz game.
    cout << "\n*** Thank you for playing the triva quiz game. Goodbye! ***" << endl;
    #endif

    //Test cases to check whether the methods work.
    #ifdef UNIT_TESTING
    cout << "*** This is a debugging version ***" << endl;
    cout << "Unit Test Case 1: Ask no question. The program should give a warning message." << endl;
    bool warning = game.ask_question(0);
    assert(!warning);
    cout << "\nCase 1 Passed" << endl << endl;

    game.initial_questions(1);
    cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer." << endl;
    game.ask_question(1);
    assert(game.userScore == 0);
    cout << "\nCase 2.1 passed" << endl << endl;

    cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer." << endl;
    game.ask_question(1);
    assert(game.userScore == 50);
    cout << "\nCase 2.2 passed" << endl << endl;

    cout << "Unit Test Case 3: Ask all the questions in the linked list." << endl;
    bool played = game.ask_question(3);
    assert(played);
    cout << "\nCase 3 passed" << endl << endl;

    cout << "Unit Test Case 4: Ask 5 questions in the linked list." << endl;
    warning = game.ask_question(5);
    assert(!warning);
    cout << "\nCase 4 passed" << endl << endl;

    cout << "*** end of Debugging Version ***";
    #endif
    //End program
    return 0;
}
