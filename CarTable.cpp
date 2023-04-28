using namespace std;

/*
struct CarTable - помни важната информация на
записаните коли.
*/
struct CarTable{

	string carTable [100][3];
	bool isDriven [100];
	int rentalCount [100];
	int maxRentalDays [100];
	int carCount = 0;

    //add - за добавяне на нова кола
	void add(string carInfo[3]){
		for (int i = 0; i <3; i++)
			carTable[carCount][i] = carInfo[i];
		isDriven[carCount] = false;
		rentalCount[carCount] = maxRentalDays[carCount] = 0;
		carCount++;
	}

    //find - за намиране на индекса на търсена по рег. номер кола
	int find(string reg){
		for (int i=0;i<carCount;i++)
			if (carTable[i][0]==reg)
				return i;
		return -1;
	}

    //findFree - търси свободна кола
	int findFree(){
		for (int i=0;i<carCount;i++)
			if (isDriven[i]==false)
				return i;
		return -1;
	}

    //findFree - търси свободна кола по марка и модел или просто свободна (overloaded)
	int findFree(string carInfo[2]){
		for (int i=0;i<carCount;i++)
			if (carTable[i][1]==carInfo[0]&&carTable[i][2]==carInfo[1]&&isDriven[i]==false)
				return i;
		return -1;
	}

    //changeState - сменя статуса на кола карана/некарана
	bool changeState(string reg, bool state){
		for(int i=0;i<carCount;i++)
			if(reg==carTable[i][0])
				if(isDriven[i]!=state){
					isDriven[i]=state;
					return true;
				}
		return false;	
	}

    //getLongestRental - връща най-дългото заемане на кола от таблицата
	int getLongestRental(){
		if(carCount>0){
			int max = maxRentalDays[0];
			for(int i=1;i<carCount;i++)
				if(max<maxRentalDays[i])
					max=maxRentalDays[i];
			return max;
		}
		return -1;
	}
};
