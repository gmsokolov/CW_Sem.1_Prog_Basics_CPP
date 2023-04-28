using namespace std;

/*
struct Client - помни важната информация за даден
клиент. Съдържа полета и конструктор.
*/
struct Client{
    string personalData[3];
    bool isDriving= true;   
    Client* next = NULL;

    Client(string pd[3]){
        for(int i=0;i<3;i++)
            personalData[i]=pd[i];
        }
    };

/*
struct ClientList - списък от клиенти.
*/
struct ClientList{

    Client* head = NULL;
    int clientCount = 0;

    //add - добавя нов клиент
    void add(string personalData[3]){
        Client* newClient = new Client(personalData);
        newClient->next = head;
        head = newClient;
        clientCount++;
    }

    //find - намира клиент от списъка по лични данни
    Client* find(string personalData[3]){
        Client* finder = head;
        for(int i=0;i<clientCount;i++){
            if(finder->personalData[0]==personalData[0]||finder->personalData[1]==personalData[1]&&finder->personalData[2]==personalData[2])
                return finder;
            finder = finder->next;
        }
        return NULL;
    }
    
    //findByName - намира кл. от списъка по 2 имена
    Client* findByName(string names[2]){
        Client* finder = head;
        for(int i=0;i<clientCount;i++){
            if(finder->personalData[1]==names[0]&&finder->personalData[2]==names[1])
                return finder;
            finder = finder->next;
        }
        return NULL;
    }

    //changeState - променя статуса ма клиент (каращ/некаращ)
    bool changeState(Client* found, bool drivingState){
        if (found != NULL)
            if(found->isDriving!=drivingState){
                found->isDriving = drivingState;
                return true;
            }
        return false;
    }
};
