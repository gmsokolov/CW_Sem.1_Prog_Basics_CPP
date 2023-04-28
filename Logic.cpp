#include "Calendar.cpp"
#include "CarTable.cpp"
#include "ClientList.cpp"
#include "RentalList.cpp"

using namespace std;

/*
struct Logic - отговаря за логически действия с всички
гореизредени структури. Чрез нея се изпълняват
основните функции на програмата.
*/
struct Logic{

	Calendar c;
	CarTable ct;
	ClientList cl;
	RentalList rl;
	
    //addCar - добавя кола
	bool addCar(string inps[3]){
		if (ct.carCount<100&&ct.find(inps[0])==-1){
			ct.add(inps);
			return true;
		}
		return false;
	}

    ////addCar - добавя n коли (overloaded)
	bool addCar(int n, string inps[100][3]){
		if (ct.carCount+n>5){
			return false;
		}
		for(int i=0;i<n;i++)
			if(ct.find(inps[i][0])!=-1){
				return false;
			}
		for(int i=0;i<n;i++)
			addCar(inps[i]);
		return true;
	}

    //addClient - добавя клиент в списъка с клиенти
	bool addClient(string personalData[3]){
		if(cl.find(personalData)==NULL){
			cl.add(personalData);
			return true;
		}
		return false;
	}

    //addRental - добавя наемане на кола в сп. с наемания
	bool addRental(Client* client, string reg, int loanDate[3]){
		Rental* found = rl.find(client,reg);
		if (found==NULL||found->isReturned==true){
			rl.add(client,reg,loanDate);
			return true;
		}
		return false;
	}
	
    //loanCar - отдава кола от записаните под наем и ако трябва добавя и нов клиент
	int loanCar(string personalData[3], string carModelInfo[2], int loanDate[3]){
		Client* client = cl.find(personalData);
		if (c.doDateCheck(loanDate)&&(client==NULL||(client!=NULL&&client->isDriving==false))){
			int index = ct.findFree(carModelInfo);
			if (index!=-1){
				if(client==NULL){
					if(!addClient(personalData)){
						return -2;
					}
						
					client = cl.head;
				}
				c.updateCalendar(loanDate);
				cl.changeState(client,true);
				ct.changeState(ct.carTable[index][0],true);
				addRental(client,ct.carTable[index][0],loanDate);
				return -1;
			} else {
				index = ct.findFree();
				if (index!=-1)
					return index;
			}
		}
		return -2;
	}

    //returnCar - връща кола по наемане
	bool returnCar(Rental* found, int returnDate[3]){
		int carIndex = -1;
		if(found!=NULL&&c.doDateCheck(returnDate))
			carIndex=ct.find(found->reg);
			if(found->isReturned==false&&found->client->isDriving==true&&carIndex!=-1){
				cl.changeState(found->client,false);
				ct.changeState(found->reg,false);
				ct.rentalCount[carIndex]++;
				int difference = c.calcDaysBetweenDates(returnDate,found->loanDate);
				if(difference>ct.maxRentalDays[carIndex])
					ct.maxRentalDays[carIndex] = difference;
				rl.returnRental(found, returnDate);
				c.updateCalendar(returnDate);

				return true;
			}
		return false;
	}

    //returnCarByReg - връща кола по рег. номер
	bool returnCarByReg(string reg, int returnDate[3]){
		Rental* found = rl.findNotRet(reg);
		return returnCar(found,returnDate);
	}

    //returnCarByNames - вр. кола по имена на клиент
	bool returnCarByNames(string names[2], int returnDate[3]){
		Client* clientFound = cl.findByName(names);
		if (clientFound!=NULL){
			Rental* rentalFound = rl.findNotRet(clientFound);
			return returnCar(rentalFound,returnDate);
		}
		return false;
	}

    //listSortedMaxRentalDays - връща подредени колите с най-дълго наемане
	CarTable listSortedMaxRentalDays(CarTable ct){
		CarTable sorted;
		int count = ct.carCount;
		int max = ct.getLongestRental();
		for(int i=0;i<count;i++){
			if (max==ct.maxRentalDays[i]){
				sorted.maxRentalDays[sorted.carCount]=ct.maxRentalDays[i];
				sorted.add(ct.carTable[i]);
			}
		}
		return sorted;
	}

    //listSortedBrand - връща подредени колите от зададена марка
	CarTable listSortedBrand(CarTable ct, string brand){
		CarTable sorted;
		int count = ct.carCount;
		for(int i=0;i<count;i++){
			if(brand==ct.carTable[i][1]){
				//sorted.add(ct.carTable[i]);
				for (int j = 0; j <3; j++)
					sorted.carTable[sorted.carCount][j] = ct.carTable[i][j];
				sorted.maxRentalDays[sorted.carCount] = ct.maxRentalDays[i];
				sorted.carCount++;
			}
		}
		return sorted;
	}

    //listSortedClientAndDate - връща всички наемания на даден кл. сорт. по дата
	RentalList listSortedClientAndDate(RentalList* rl, ClientList* cl, string names[2]){
		RentalList sorted;
		Client* client = cl->findByName(names);
		Rental* rental = rl->head;
		for(int j=0;j<rl->rentalCount;j++){
			if(client==rental->client)
				sorted.add(rental->client,rental->reg,rental->loanDate);
			rental=rental->next;
		}
		return sorted;
	}
};
