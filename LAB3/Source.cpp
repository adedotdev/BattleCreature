#include <iostream>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fstream>
using namespace std;

class Creature {
private:
    // member variables
    int strength;
    int health;
    string id;

public:
    // accessor functions
    int getStrength()const;
    int getHealth()const;
    string getID()const;
    int getDamage()const;
    string to_String()const;

    // mutator function
    void setCreature(int strength, int health, string ID);
};

int Creature::getStrength()const {
    return strength;
}

int Creature::getHealth()const {
    return health;
}

string Creature::getID()const {
    return id;
}

int Creature::getDamage()const {
    srand(time(0));
    int damage = (rand() % strength) + 1; //sets a random number between 1 and the
    return damage;                        //amount of strength the creature has left
}

string Creature::to_String()const {       //returns the creature's details
    stringstream ss;
    ss << setw(10) << left << id
        << setw(10) << right << health
        << setw(22) << right << strength << endl;
    return ss.str();
};

void Creature::setCreature(int stren, int heal, string ID) {
    strength = stren;
    health = heal;
    id = ID;
}


// function prototypes
void print(Creature[]);
void reset(Creature[]);
void battle(Creature[]);
int getHealthLeft(int, int);

// constant variables
const int SIZE = 10;
const int MAX = 100;
const int MIN = 10;

enum Options {
    Print = 1, Battle, Quit
};


int main() {
    Creature creatureArr[SIZE] = {};
    int choice;

    do {
        cout << endl;
        cout << "Select one of the following options:\n"
            "1. Print creature info\n"
            "2. Battle between two creatures\n"
            "3. Quit\n";
        cin >> choice;

        switch (choice) {
        case Print:
            print(creatureArr);
            break;

        case Battle:
            print(creatureArr);
            battle(creatureArr);
            break;

        case Quit:
            cout << endl << "Goodbye...";
            break;

        default:
            cout << endl << "Invalid Input!\n";    // catch invalid input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    } while (choice != Quit);
    return 0;
}


//  print creature's details
void print(Creature obj[]) {
    if (obj[0].getHealth() == 0)          //  checks if array is empty
        reset(obj);
    else {
        cout << endl << " ID" << ""
            << setw(22) << right << "Health" << ""
            << setw(22) << right << "Strength" << endl;

        cout << setfill('-') << setw(47) << ""
            << setfill(' ') << endl;

        int i = 0;
        while (i < SIZE && obj[i].getHealth() != 0) {
            cout << (i + 1) << ". " << obj[i].to_String();
            i++;
        }
    }
}


//  update creature's details
void reset(Creature obj[]) {
    int check;
    string id;
    ifstream infile("inputfile.txt");

    if (infile.fail())          // checks for errors when opening file
        cout << "Error opening file!";
    else {
        check = infile.peek();
        if (check == EOF)         // checks if file is empty
            cout << endl << "File is empty!\n";
        else {
            srand(time(0));
            int i = 0;
            while (infile >> id) {    // read file
              // set a random number between 10 and 100 for the strength and health
                obj[i].setCreature((rand() % (MAX - MIN)) + MIN, (rand() % (MAX - MIN)) + MIN, id);
                i++;
            }
            print(obj);
        }
    }
    infile.close();    // close the file
}


void battle(Creature obj[]) {
    int creatureOne, creatureTwo, healthOne, healthTwo, i = 1;;
    cout << endl << "Choose the first creature to battle\n";
    cin >> creatureOne;
    cout << endl << "Choose the second creature to battle\n";
    cin >> creatureTwo;

    creatureOne--;
    creatureTwo--;

    cout << endl << obj[creatureOne].getID() << " will attack first!\n";

    while (obj[creatureOne].getHealth() > 0 && obj[creatureTwo].getHealth() > 0) {
        cout << endl << "ROUND " << i << endl;
        srand(time(0));
        if (i % 2) {
            cout << obj[creatureOne].getID() << " inflicted " << obj[creatureOne].getDamage() << " damage!\n";
            healthTwo = getHealthLeft(obj[creatureOne].getDamage(), obj[creatureTwo].getHealth());
            obj[creatureTwo].setCreature(obj[creatureTwo].getStrength(), healthTwo, obj[creatureTwo].getID());
        }
        else {
            cout << obj[creatureTwo].getID() << " inflicted " << obj[creatureTwo].getDamage() << " damage!\n";
            healthOne = getHealthLeft(obj[creatureTwo].getDamage(), obj[creatureOne].getHealth());
            obj[creatureOne].setCreature(obj[creatureOne].getStrength(), healthOne, obj[creatureOne].getID());
        }

        cout << "NEW STATS:\n" << " ID" << ""
            << setw(20) << right << "Health" << ""
            << setw(22) << right << "Strength" << endl;
        cout << setfill('-') << setw(47) << "" << setfill(' ') << endl;
        cout << obj[creatureOne].to_String() << obj[creatureTwo].to_String() << endl;
        i++;
    }
    if (healthOne == 0)
        cout << "Winner is " << obj[creatureTwo].getID() << endl
        << "Loser is " << obj[creatureOne].getID() << endl;
    else
        cout << "Winner is " << obj[creatureOne].getID() << endl
        << "Loser is " << obj[creatureTwo].getID() << endl;
}


int getHealthLeft(int hitPoints, int totalHealth) {
    int healthLeft = 0;
    healthLeft = totalHealth - hitPoints;

    if (healthLeft <= 0)
        healthLeft = 0;

    return healthLeft;
}