using namespace std;

/*
struct Rental - помни важната информация за едно
наемане. Съдържа полета и конструктор.
*/
struct Rental{
        string reg;
        Client* client;
        int loanDate [3];
        int returnDate [3];
        Rental* next = NULL;
        bool isReturned = false;

        Rental(Client* c, string r, int ld [3]){
            client = c;
            reg = r;
            for (int i=0;i<3;i++)
                loanDate[i]=ld[i];
        }
    };

/*
struct RentalList - списък от наемания.
*/
struct RentalList{ 

    Rental* head;
    int rentalCount = 0;

    //add - добавя наемане
    void add(Client* client, string reg, int loanDate [3]){
        Rental* newRental = new Rental(client, reg, loanDate);
        newRental->next = head;
        head = newRental;
        rentalCount++;
    }

    //returnRental - връща наемане
    void returnRental(Rental* found, int returnDate[3]){
        for(int i=0;i<3;i++)
            found->returnDate[i] = returnDate[i];
        found->isReturned = true; 
    }

    //find - намира последната комбинация от клиент и автомобилна регистрация
    Rental* find(Client* client, string reg){
        if (rentalCount>0){
            Rental* finder = head;
            for (int i=0;i<rentalCount;i++){
                if(finder->client==client&&finder->reg==reg)
                   return finder;
                finder = finder->next;
            }
        }
        return NULL; 
    }

    //findNotRet - намира последното наемане, което не е върнато по регистрация
    Rental* findNotRet(string reg){
        if (rentalCount>0){
            Rental* finder = head;
            for (int i=0;i<rentalCount;i++){
                if(finder->reg==reg&&finder->isReturned==false)
                   return finder;
                finder = finder->next;
            }
        }
        return NULL; 
    }

    //findNotRet - намира последното наемане, което не е върнато по клиент (overloaded)
    Rental* findNotRet(Client* client){
        if (rentalCount>0){
            Rental* finder = head;
            for (int i=0;i<rentalCount;i++){
                if(finder->client==client&&finder->isReturned==false)
                   return finder;
                finder = finder->next;
            }
        }
        return NULL; 
    }
};
