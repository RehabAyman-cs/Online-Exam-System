#include <iostream>
#include<cmath>
#include <random>
#include<cstdlib>
#include<cctype>
#include<string>
#include<ctime>
using namespace std;
enum Enlevel { Easy = 1, med = 2, hard = 3, mix = 4 };
enum Entype { Add = 1, Sub = 2, Mul = 3, Div = 4, Mix = 5 };
struct stQuesstion {
	 int Number1 = 0;
	int Number2 = 0;
	Entype operationtype;
	Enlevel Questionlevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};
struct stquiz {
	stQuesstion QuestionArray[100];
	int NumberofQuestions;
	Enlevel  QuestionsLevel;
	Entype optype;
	int NumberofWrongAnswer = 0;
	int NumberofRightAnswer = 0;
	bool ispass=false ;
};
int HowManyRound() {
	int round;
	do {
		cout << "How many Round do you want to answer ?\n";
		cin >> round;
	} while (round < 1 || round>10);
	return round;
}
int Random(int from, int to) {
	int random=( rand() % (to - from + 1)) + from;
	return random;
}
Enlevel levelquestions() {
	int num;
	do {
		cout << "Enter Questions Level [1]Easy,[2]Med,[3]Hard,[4]Mix ?\n ";
		cin >> num;
	} while (num <1 || num>4);
	return (Enlevel)num;
}
Entype typequestios() {
	int num;
	do {
		cout << "Enter Type [1]Add,[2]Sub,[3]Mul,[4]Div,[5] Mix?\n";
		cin >> num;
	} while (num < 1 || num > 5);
	return (Entype)num;
}
void ResetScreen() {
	system("cls");
	system("color 0f");
}
int SimpleCalculator(int Number1, int Number2, Entype optype) {
	switch (optype) {
	case Entype ::Add:
		return Number1 + Number2;
		case Entype ::Mul:
		return Number1 * Number2;
	case Entype ::Sub:
		return Number1 - Number2;
	case Entype ::Div:
		return Number1 / Number2;
	default:return Number1 + Number2;
	}
}
string GetOpTypeText(Entype  OpType)
{
	string arrOperationType[4] = { "+","-","*","/" };
	return arrOperationType[OpType - 1];
}
void printTheQuestion(stquiz& Quizz, int  Question) {
	cout << endl;
	cout << "Question[" << Question + 1 << "]" << "/" << Quizz.NumberofQuestions << "\n";
	cout << Quizz.QuestionArray[Question].Number1 << endl;
	cout << Quizz.QuestionArray[Question].Number2 << " ";
	cout << GetOpTypeText(Quizz.QuestionArray[Question].operationtype);
	cout << "\n--------\n";
}
int ReadQuestionAnswer() {
	int answer;
	cin >> answer;
	return answer;
}
void CorrectThequsitionAnswer(stquiz & Quizz,int Question) {
	if (Quizz.QuestionArray[Question].PlayerAnswer != Quizz.QuestionArray[Question].CorrectAnswer) {
		Quizz.QuestionArray[Question].AnswerResult = false;
		Quizz.NumberofWrongAnswer++;
		cout << "Wrong Answer :-(\n";
		cout << "The right answer is : ";
		system("color 4f");
		cout << Quizz.QuestionArray[Question].CorrectAnswer << endl;

	}
	else {
		Quizz.QuestionArray[Question].AnswerResult = true;
		Quizz.NumberofRightAnswer++;
		system("color 2f");
		cout << "Right Answer :-)\n";
	}
	cout << endl;
}
void AskCorrectQuestion(stquiz & Quizz) {
	for (int Question = 0; Question < Quizz.NumberofQuestions; Question++) {
		printTheQuestion(Quizz, Question);
		Quizz.QuestionArray[Question].PlayerAnswer = ReadQuestionAnswer();
		CorrectThequsitionAnswer(Quizz, Question);


	}
	Quizz.ispass = (Quizz.NumberofRightAnswer >= Quizz.NumberofWrongAnswer);
}
stQuesstion GenerateQuestion(Enlevel level, Entype &optype) {
	stQuesstion Question;
	if (level == Enlevel::mix) {
		level =(Enlevel ) Random(1, 3);
	}
	if (optype == Entype::Mix) {
		optype = (Entype)Random(1, 4);
	}
	Question.operationtype = optype;
	switch (level) {
		case Enlevel ::Easy:
			Question.Number1 = Random(1, 10);
			Question.Number2 = Random(1, 10);
			Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.operationtype);
			Question.Questionlevel = level;
			return Question;
		case Enlevel ::med:
			Question.Number1 = Random(10, 50);
			Question.Number2 = Random(10, 50);
			Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.operationtype);
			Question.Questionlevel = level;
			return Question;
		case Enlevel ::hard:
			Question.Number1 = Random(50, 100);
			Question.Number2 = Random(50, 100);
			Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.operationtype);
			Question.Questionlevel = level;
			return Question;
	}
	return Question;
}
void GenartQuizz(stquiz &Quizz) {
	for (int Question = 0; Question < Quizz.NumberofQuestions; Question++) {
		Quizz.QuestionArray[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.optype);
}
}
string  GetFinalResult(bool ispass) {
	if (ispass) {
		return "Pass-)";
	}
	else { return "Fail-("; }
}
string GetQuistionLevel(Enlevel level) {
	string arr[4] = {"Easy","Med","Hard","Mix"};
	return arr[level - 1];
}

void printQuizzFinalResult(stquiz  Quizz) {
	cout << "\n";
	cout << "-----------------------\n\n";
	cout << "Final Result is : " << GetFinalResult(Quizz.ispass) << "\n";
	cout << "-------------------------\n\n";
	cout << "Number Of Questions  :" << Quizz.NumberofQuestions << "\n";
	cout << "Questions Level      :" << GetQuistionLevel( Quizz.QuestionsLevel) << endl;
	cout << "OpType               :" << GetOpTypeText(Quizz.optype) << endl;
	cout << "Number of Right Answers:" << Quizz.NumberofRightAnswer << endl;
	cout << "Number Of Wrong Answer :" << Quizz.NumberofWrongAnswer << endl;
	cout << "-----------------------------\n\n";
}
void PlayGame() {
	stquiz Quizz;
	Quizz.NumberofQuestions = HowManyRound();
	Quizz.QuestionsLevel = levelquestions();
	Quizz.optype = typequestios();

	GenartQuizz(Quizz);
	AskCorrectQuestion(Quizz);
	printQuizzFinalResult(Quizz);

}
void StartGame() {
	char playagain = 'Y';
	do {
		ResetScreen();
		PlayGame();
		cout << "Do you want to play again?Y/N?\n";
		cin >> playagain;
	} while (toupper(playagain) == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();



	return 0;
}
