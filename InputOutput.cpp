#include <iostream>
#include "Logic.cpp"

using namespace std;

/*
struct InputOutput - отговаря за входа и изхода на
програмата.
*/
struct InputOutput{

	Logic l;
	const string S_MSG = "OK\n";
	const string E_MSG = "Error, bad input!\n";

    //printMainMenu - изписва опциите за взаимодействие с програмата
	void printMainMenu(){

		cout<<"Hello, you have the following options: \n";

		cout<<"Press q to quit \n";

		cout<<"Press 1 to add car(s) \n";

			cout<<"	You can then press b to go back \n";
			cout<<"	Or press 1 to add a car \n";
			cout<<"	Or press 2 to add n cars \n";

		cout<<"Press 2 to loan a car \n";
				
		cout<<"Press 3 to return a car \n";

			cout<<"	You can then press b to go back \n";
			cout<<"	Or press 1 to return a car by registration \n";
			cout<<"	Or press 2 to retrun a car by person \n";
				
		cout<<"Press 4 to list cars \n";

			cout<<"	You can then press b to go back \n";
			cout<<"	Or press 1 to list cars by max days\n";
			cout<<"	Or press 2 to list cars by brand\n";
			cout<<"	Or press 4 to list cars by person and date\n";
	}

    //mainMenu - отговаря за избора на опция от менюто
	bool mainMenu(char in){

		switch(in){
			case 'q':
				cout<<"quit\n";
				return false;
			case '1':
				cout<<S_MSG;
				
				menuOne(receiveChar());
				break;
			case '2':
				cout<<S_MSG;
				menuTwo();
				break;
			case '3':
				cout<<S_MSG;
				
				menuThree(receiveChar());
				break;
			case '4':
				cout<<S_MSG;
				
				menuFour(receiveChar());
				break;
			default:
				cout<<E_MSG;
		}
		return true;
	}

    //menuOne - 1-во подменю на mainMenu
	void menuOne(char in){
		string sInps[5][3];
		int iIn;
		switch(in){
			case 'b':
				cout<<"back\n";
				break;
			case '1':
				cout<<S_MSG;
				cout<<"Write 3 inputs, seperated by space or enter:\n <car registration> <car brand> <car model>\n";
				cin>>sInps[0][0]>>sInps[0][1]>>sInps[0][2];
				if(!l.addCar(sInps[0])){
					cout<<E_MSG;
					break;
				}
				cout<<S_MSG;
				break;
			case '2':
				cout<<S_MSG;
				cout<<"Write 3n+1 inputs, seperated by space or enter:\n <number of cars> <car1 registration> <car1 brand> <car1 model> ...\n";
				iIn = receivePositive();
				for(int i=0; i<iIn; i++){
					cin>>sInps[i][0]>>sInps[i][1]>>sInps[i][2];			
				}
				if(!l.addCar(iIn,sInps)){
					cout<<E_MSG;
					break;
				}
				cout<<S_MSG;
				break;
			default:
				cout<<E_MSG;
		}
	}

    //menuTwo - 2-ро подменю
	void menuTwo(){
		cout<<"Write 8 inputs, seperated by space or enter:\n";
		cout<<"<ID card number> <first name> <family name>\n";
		cout<<"<car brand> <car model>\n";
		cout<<"<day> <month> <year>\n";
		cout<<"If an alternative is offered press y to accept and n to decline\n";

		string sInps1[3];
		string sInps2[2];
		int iInps[3];
		int carIndex;
		for(int i=0;i<3;i++)
			cin>>sInps1[i];
		for(int i=0;i<2;i++)
			cin>>sInps2[i];
		for(int i=0;i<3;i++)
			iInps[i]=receivePositive();
		carIndex = l.loanCar(sInps1,sInps2,iInps);
			switch (carIndex){
				case -1:
					cout<<S_MSG;
					break;
				case -2:
					cout<<E_MSG;
					break;
				default:
					cout<<"We offer an alternative: "<<l.ct.carTable[carIndex][1]<<' '<<l.ct.carTable[carIndex][2]<<endl;
					switch(receiveChar()){
						case 'y':
							cout<<S_MSG;
							sInps2[0]=l.ct.carTable[carIndex][1];
							sInps2[1]=l.ct.carTable[carIndex][2];
							l.loanCar(sInps1,sInps2,iInps);
							break;
						case 'n':
							cout<<S_MSG;
							break;
						default:
							cout<<E_MSG;
					}
			}
	}

    //menuThree - 3-то подменю
	void menuThree(char in){
		string sInps[2];
		int iInps[3];
		switch(in){
			case 'b':
				cout<<"back\n";
				break;
			case '1':
				cout<<S_MSG<<"Write 4 inputs: <car registration> <day> <month> <year>\n";
				cin>>sInps[0];
				for(int i=0;i<3;i++)
					iInps[i]=receivePositive();
				if(!l.returnCarByReg(sInps[0],iInps)){
					cout<<E_MSG;
				}
				cout<<S_MSG;
				break;
			case '2':
				cout<<S_MSG<<"Write 5 inputs: <first name> <family name> <day> <month> <year>\n";
				for(int i=0; i<2; i++){
					cin>>sInps[i];			
				}
				for(int i=0;i<3;i++)
					iInps[i]=receivePositive();
				if(!l.returnCarByNames(sInps,iInps)){
					cout<<E_MSG;
				}
				cout<<S_MSG;
				break;
			default:
				cout<<E_MSG;
		}
	}

    //menuFour - 4-то подменю
	void menuFour(char in){
		CarTable sortedCT;
		RentalList sortedRL;
		Rental* curr;
		string sInps[2];
		switch(in){
			case 'b':
				cout<<"back\n";
				break;
			case '1':
				cout<<S_MSG;
				sortedCT = l.listSortedMaxRentalDays(l.ct);
				for(int i=0;i<sortedCT.carCount;i++){
					cout<<i+1<<". ";
					for(int j=0;j<3;j++)
						cout<<sortedCT.carTable[i][j]<<' ';
					cout<<endl;
				}
				break;
			case '2':
				cout<<S_MSG<<"Write 1 input: <brand>\n";
				cin>>sInps[0];
				sortedCT = l.listSortedBrand(l.ct,sInps[0]);
				for(int i=0;i<sortedCT.carCount;i++){
					cout<<i+1<<". ";
					for(int j=0;j<3;j++)
						cout<<sortedCT.carTable[i][j]<<' ';
					cout<<endl;
				}
				break;
			case '4':
				cout<<S_MSG<<"Write 2 inputs: <first name> <last name>\n";
				cin>>sInps[0]>>sInps[1];
				sortedRL = l.listSortedClientAndDate(&l.rl,&l.cl,sInps);
				curr = sortedRL.head;
				for(int i=0;i<sortedRL.rentalCount;i++){
					cout<<i+1<<". "<<curr->client->personalData[1]<<' '<<curr->client->personalData[2]<<' ';
					cout<<curr->reg<<" "<<curr->loanDate[0]<<" "<<curr->loanDate[1]<<" "<<curr->loanDate[2]<<endl;
					curr = curr->next;
				}
				break;
			
			default:
				cout<<E_MSG;
		}
	}

    //receiveChar - проверява дали входър е char
	char receiveChar(){
		string in;
		cin>>in;
		if(in.length()!=1){
			cout<<flush;
			return '0';
		}
		return in[0];
	}

    //receivePositive - проверява дали входът е пол. число
	int receivePositive(){
		string in;
		int received = 0;
		cin>>in;
		for(int i=0;i<in.length();i++){
			switch(in[i]){
				case'0':
					break;
				case'1':
					received+=1;
					break;
				case'2':
					received+=2;
					break;
				case'3':
					received+=3;
					break;
				case'4':
					received+=4;
					break;
				case'5':
					received+=5;
					break;
				case'6':
					received+=6;
					break;
				case'7':
					received+=7;
					break;
				case'8':
					received+=8;
					break;
				case'9':
					received+=9;
					break;
				default:
					return -1;
			}
			received*=10;
		}
		return received/=10;;
	}

};

