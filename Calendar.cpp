using namespace std;

/*
struct Calendar - помни текуща дата и съдържа функции
за работа с дати.
*/
struct Calendar{
	
	int currentDate [3] = {1,1,1951};

    //updateCalendar - за обновяване на текущата дата
	void updateCalendar(int date [3]){
		for (int i=0;i<3;i++)
			currentDate[i]=date[i];
	}

    //isDateReal - за проверка на валидност на дата
	bool isDateReal(int date [3]){
		if(date[2]>1950 && date[2]<4000000000 && date[0]>0)
			switch (date[1]){
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
					if (date[0]<32)
						return true;
				case 4:
				case 6:
				case 9:
				case 11:
					if (date[0]<31)
						return true;
				case 2:
					if (isFebLonger(date[2])){
						if (date[0]<30)
							return true;
					} else {
						if (date[0]<29) 
							return true;				
					}
			}
		return false;
	}

    //isFebLonger - за проверка за високосна година
	bool isFebLonger(int year){
		if (year%4==0)
			if (year%100!=0||year%400==0)
				return true;
		return false;
	}

    //isDateBigger - за сравнение на 2 дати
	bool isDateBigger(int first[3], int second[3]){
		if (first[2]>second[2])
			return true;
		else 
			if (first[2]==second[2])
				if (first[1]>second[1])
					return true;
				else
					if(first[1]==second[1])
						if (first[0]>=second[0])
							return true;
		return false;
	}

    //calcDaysBetweenYears - брои дните между 2 год.
	int calcDaysBetweenYears(int fromYear, int toYear){
		int sum = 0;
		for (int i=fromYear; i<toYear; i++)
			if (!isFebLonger(i))
				sum+=365;
			else
				sum+=366;
		return sum;
	}

    //calcDaysOngoingYear - брои дните от началото на дадена година
	int calcDaysOngoingYear(int date[3]){
		int sum = date[0];
		for(int i=1;i<date[1];i++)
			switch (i){
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
					sum+=31;
					break;
				case 4:
				case 6:
				case 9:
				case 11:
					sum+=30;
					break;
				case 2:
					if (isFebLonger(date[2]))
						sum+=29;
					else 
						sum+=28;			
				}
		return sum;
	}

    //calcDaysBetweenDates - брои дните между 2 дати
	int calcDaysBetweenDates(int date1[3], int date2[3]){
		if (!isDateBigger(date1,date2)){
			int tmp [3];
			for (int i=0;i<3;i++)
				tmp[i]=date1[i];
			for (int i=0;i<3;i++)
				date1[i]=date2[i];
			for (int i=0;i<3;i++)
				date2[i]=tmp[i];
		}
		int sum = calcDaysBetweenYears(date2[2],date1[2]);
		sum += calcDaysOngoingYear(date1);
		sum -= calcDaysOngoingYear(date2);
		return sum;
	}

    //doDateCheck - прави проверка на дата и я сравнява с настоящата
	bool doDateCheck (int date[3]){
		if(isDateReal(date)&&isDateBigger(date,currentDate))
			return true;
		return false;
	}
};

