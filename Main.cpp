#include "InputOutput.cpp"

using namespace std;

/*
функция main - съдържа безкраен цикъл докато не се
получи команда за прекратяване изпълнението на
програмата.
*/
int main(){
	InputOutput io;
	bool run = true;

	while(run){
		io.printMainMenu();
		run = io.mainMenu(io.receiveChar());
	}
	return 0;
}
