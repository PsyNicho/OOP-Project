#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include<conio.h>
#include<windows.h>
using namespace std;

enum ActivityLevel {
    SEDENTARY,
    LIGHTLY_ACTIVE,
    MODERATELY_ACTIVE,
    VERY_ACTIVE,
    EXTRA_ACTIVE
};

#define MAX_MEALS 4 
#define MAX_DAYS 7

// Cursor Position
int *posx,*posy;

void dash() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width,i;
    if(!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi)) {
        cout<<"Error getting console screen buffer info.";
        return;
    }
    width=csbi.dwSize.X;
    cout<<endl;
    for (i=0;i<width;i++) {
        cout<<"-";
    }
    cout<<endl<<endl;
    fflush(stdout);
}

void gotoxy(int x,int y) {
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    if(hConsole==INVALID_HANDLE_VALUE) {
        cout<<"Error getting console handle.";
        exit(1);
	}
    COORD cursorPos;
    cursorPos.X=x;
    cursorPos.Y=y;
    if(!SetConsoleCursorPosition(hConsole,cursorPos)) {
        cout<<"Error setting console cursor position.";
        exit(1);
    }
}

char confirm(char s[],int *x,int *y) {
	char c;	
	gotoxy(*x,*y);
	cout<<s;
	cin>>c;
	return(c);
}

bool openFile(fstream &file,char* filename,ios::openmode mode) {
    file.open(filename,mode);
    if (file.fail()) {
        cout<<"Error: Could not open file "<<filename<<endl;
        return false;
    }
    return true;
}

// Abstract base class for meals
class Meal {
protected:
    char name[50];
    double calories;
    double protein;
    int day;  // Track which day the meal belongs to

public:
    Meal() {
        strcpy(name,"N/A");
        calories=0;
        protein=0;
        day=0;
    }

    Meal(const char* n, double c, double p, int d) {
        strncpy(name,n,sizeof(name)-1);
        name[sizeof(name)-1]='\0';
        calories=c;
        protein=p;
        day=d;
    }

    virtual void displayMeal()  = 0;  // Pure virtual function

    // Getters
    double getCalories() const { return calories; }
    double getProtein() const { return protein; }
    const char* getName() const { return name; }
    int getDay() const { return day; }

    // Setter for updating meal
    virtual void updateMeal(const char* newName, double newCalories, double newProtein) {
        strncpy(name, newName, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
        calories = newCalories;
        protein = newProtein;
    }

    virtual ~Meal() {}
};

// Derived meal type classes
class Breakfast : public Meal {
public:
    Breakfast() : Meal() {}
    Breakfast(const char* n, double c, double p, int d) : Meal(n, c, p, d) {}

    void displayMeal()   {
        cout << "Day " << day << " - Breakfast: " 
             << name << ", " << calories << " kCal, " << protein << " g\n";
    }
};

class Lunch : public Meal {
public:
    Lunch() : Meal() {}
    Lunch(const char* n, double c, double p, int d) : Meal(n, c, p, d) {}

    void displayMeal()   {
        cout << "Day " << day << " - Lunch: " 
             << name << ", " << calories << " kCal, " << protein << " g\n";
    }
};

class Dinner : public Meal {
public:
    Dinner() : Meal() {}
    Dinner(const char* n, double c, double p, int d) : Meal(n, c, p, d) {}

    void displayMeal()   {
        cout << "Day " << day << " - Dinner: " 
             << name << ", " << calories << " kCal, " << protein << " g\n";
    }
};

class Snacks : public Meal {
public:
    Snacks() : Meal() {}
    Snacks(const char* n, double c, double p, int d) : Meal(n, c, p, d) {}

    void displayMeal()   {
        cout << "Day " << day << " - Snacks: " 
             << name << ", " << calories << " kCal, " << protein << " g\n";
    }
};

class UserProfile {
private:
    char name[50],gender[6];
    double age,height,weight,goalCalorie,goalProtein;
    int x,y,activityChoice;
    ActivityLevel activityLevel;
    double calculateBMR() {
        double bmr;
        if(strcmp(gender,"Male")==0)
            bmr=10*weight+6.25*height-5*age+5;
        else
            bmr=10*weight+6.25*height-5*age-161;
        return bmr;
    }
    double getActivityMultiplier()  {
        switch(activityLevel) {
            case SEDENTARY: return 1.2;
            case LIGHTLY_ACTIVE: return 1.375;
            case MODERATELY_ACTIVE: return 1.55;
            case VERY_ACTIVE: return 1.725;
            case EXTRA_ACTIVE: return 1.9;
            default: return 1.2;
        }
    }
public:
    UserProfile() {
        name[0]='\0';
        age=0;
        gender[0]='\0';
        height=0;
        weight=0;
        goalCalorie=0;
        goalProtein=0;
    }
    void setProfile() {
    	x=35,y=1;
        system("cls");
        gotoxy(x,y);
        cout<<"User Profile Setup :";
        y+=2;
        gotoxy(x,y);
        cout<<"Enter your name : ";
        cin.ignore();
		cin.getline(name,sizeof(name));
        gotoxy(x,++y);
        cout<<"Enter age : ";
        cin>>age;
        cin.ignore();
		gotoxy(x,++y);		
        cout<<"Enter gender (Male/Female) : ";
        cin.getline(gender,sizeof(gender));
        gotoxy(x,++y);
        cout<<"Enter height (cm) : ";
        cin>>height;
        gotoxy(x,++y);
        cout<<"Enter weight (kg) : ";
        cin>>weight;
        y+=2;
        gotoxy(x,y);
        cout<<"Activity Levels:";
        gotoxy(x,++y);
        cout<<"1. Sedentary (little to no exercise)";
		gotoxy(x,++y);
		cout<<"2. Light Activity (light exercise 1-3 days/week)";
		gotoxy(x,++y);
		cout<<"3. Moderate Activity (moderate exercise 3-5 days/week)";
		gotoxy(x,++y);
		cout<<"4. Very Active (hard exercise 6-7 days/week or physical job)";
		gotoxy(x,++y);cout<<
		"5. Custom";
		gotoxy(x,++y);
        cout<<"Select activity level : ";
        cin>>activityChoice;
        calculateGoals();
        saveProfile();
    }

    void calculateGoals() {
    	int goalChoice;
		x=35,y=16;
        double bmr=calculateBMR();
        double activityMultiplier=getActivityMultiplier();
        switch(activityChoice) {
            case 1: activityLevel = SEDENTARY; break;
            case 2: activityLevel = LIGHTLY_ACTIVE; break;
            case 3: activityLevel = MODERATELY_ACTIVE; break;
            case 4: activityLevel = VERY_ACTIVE; break;
            case 5: activityLevel = EXTRA_ACTIVE; break;
            default: activityLevel = SEDENTARY;
        }
        double baseCalories=bmr*activityMultiplier;
        gotoxy(x,++y);
		cout<<"Goal Options:";
		gotoxy(x,++y);
		cout<<"1. Lose Weight";
		gotoxy(x,++y);
		cout<<"2. Maintain Weight";
		gotoxy(x,++y);
		cout<<"3. Gain Weight";
		gotoxy(x,++y);
		cout<<"4. Custom Goal";
		gotoxy(x,++y);
        cout<<"Select goal : ";
		cin>>goalChoice;
        switch(goalChoice) {
            case 1: goalCalorie=baseCalories-500; break;
            case 2: goalCalorie=baseCalories; break;
            case 3: goalCalorie=baseCalories+500; break;
            case 4: 
            	gotoxy(x,y);
                cout<<"Enter custom calorie goal : ";
                cin>>goalCalorie;
                break;
        }
        goalProtein=weight*0.8*2.205;  // Standard protein calculation
        y+=2;
		gotoxy(x,y);
		cout<<"Your daily calorie goal is set to "<<goalCalorie<<" calories.\n";
        gotoxy(x,++y);
		cout<<"Your daily protein goal is set to "<<goalProtein<<" grams.\n";
    	(*posy)=29;
	}

    void saveProfile() {
    ofstream file("profile.txt",ios::binary);
    gotoxy(35,27);
    if (file.is_open()) {
        file.write((char*)this, sizeof(UserProfile));
        file.close();
        cout<<"Profile saved successfully!";
    } else {
        cout<<"Unable to save profile.";
    }
}
    void viewProfile() {
    	x=35,y=4; 	
	    ifstream file("profile.txt", ios::binary);
	    if (file.is_open()) {
	        system("cls");
			gotoxy(x,y);
			dash();
	    	y+=3;
	    	gotoxy(x,y);
	    	cout<<"|\tUser Profile\t|";
	    	gotoxy(x,++y);
	    	dash();
	        UserProfile tempProfile;
	        file.read((char*)&tempProfile,sizeof(UserProfile));
	        y+=3;
			gotoxy(x,y);
	        cout<<"Name : "<<tempProfile.name;
	        gotoxy(x,++y);
	        cout<<"Age : " <<tempProfile.age;
	        gotoxy(x,++y);
	        cout<<"Gender : "<<tempProfile.gender;
	        gotoxy(x,++y);
	        cout<<"Height : "<<tempProfile.height<<" cm";
	        gotoxy(x,++y);
	        cout<<"Weight: "<<tempProfile.weight<<" kg";
	        gotoxy(x,++y);
	        cout<<"Activity Level : "<<tempProfile.activityLevel;
	        gotoxy(x,++y);
	        cout<<"Daily Calorie Goal : "<<tempProfile.goalCalorie<<" kCal";
	        gotoxy(x,++y);
	        cout<<"Daily Protein Goal : "<<tempProfile.goalProtein<<" g";
	        (*posy)+=2;
			file.close();
	    } else {
	        gotoxy(35,22);
			cout << "No profile found. Please set up a profile first.\n";
	    	(*posy)=24;
		}    
	}
    double getGoalCalorie()  { return goalCalorie; }
    double getGoalProtein()  { return goalProtein; }
};

class CalorieTracker {
private:
    Meal* dailyMeals[MAX_DAYS][MAX_MEALS];
    int mealCounts[MAX_DAYS],x,y;
    UserProfile profile;
    double dailyTotalCalories[MAX_DAYS],dailyTotalProtein[MAX_DAYS];
public:
    CalorieTracker() {
        for (int i=0;i<MAX_DAYS;i++) {
            mealCounts[i]=0;
            dailyTotalCalories[i]=0;
            dailyTotalProtein[i]=0;
            for(int j=0;j<MAX_MEALS;j++) {
                dailyMeals[i][j]=NULL;
            }
        }
    }
    // Overloaded += operator for adding calories
    void operator+=(Meal &meal) {
        int day=meal.getDay()-1; // Convert to 0-index
        dailyTotalCalories[day]+=meal.getCalories();
        dailyTotalProtein[day]+=meal.getProtein();
    }
    void addMeal() {
	    EnterDay:
		int day;
	    char choice;
		system("cls");
		gotoxy(35,5);
		cout<<"Enter day (1-"<<MAX_DAYS<<") to add meals : ";
	    cin>>day;
	    if(day<1 || day>MAX_DAYS) {
	        gotoxy(35,7);
			cout<<"Invalid day.";
			(*posy)=9;
			choice=confirm("Try again? [Y/N] : ",posx,posy);
			if(choice=='y' || choice=='Y')
				goto EnterDay;
		}
	    do {
	    	x=35,y=5;
	    	int mealType;
	    	char name[50];
	    	double calories, protein;
	    	Meal* newMeal=NULL;
			gotoxy(x,y+=2);
	        cout<<"1. Breakfast";
			gotoxy(x,++y);
			cout<<"2. Lunch";
			gotoxy(x,++y);
			cout<<"3. Dinner";
			gotoxy(x,++y);
			cout<<"4. Snacks";
	        gotoxy(x,++y);
			cout<<"Select meal type : ";
			cin>>mealType;
			cin.ignore();
			if(mealType<1 || mealType>4) {
	            gotoxy(x,y+=2);
	            cout<<"Invalid choice! Please select a valid meal type (1-4).";
	            (*posy)=15;
				choice=confirm("Try again? [Y/N] : ",posx,posy);
				if(choice=='y' || choice=='Y') {
					system("cls");
					goto EnterMeal;
				}		 
	        }
			gotoxy(x,y+=2);
			cout<<"Enter food name : ";
			cin.getline(name,sizeof(name));
			gotoxy(x,++y);
			cout<<"Enter calories & protein : ";
			cin>>calories>>protein;
	        switch(mealType) {
	            case 1: newMeal=new Breakfast(name,calories,protein,day); break;
	            case 2: newMeal=new Lunch(name,calories,protein,day); break;
	            case 3: newMeal=new Dinner(name,calories,protein,day); break;
	            case 4: newMeal=new Snacks(name,calories,protein,day); break;
	            default: 
	                cout<<"Invalid meal type.\n";
	                if(newMeal) delete newMeal;
	                continue;
	        }
	        // Add meal to the specific day
	        dailyMeals[day-1][mealCounts[day-1]++]=newMeal;
	        *this+=*newMeal;
	
	        gotoxy(x,y+=2);
			cout<<"Meal added successfully!\n";
	        // Check if maximum meals reached after adding
	        if(mealCounts[day-1]>=MAX_MEALS) {
	            cout<<"Maximum meals reached for Day "<<day;
	            break;
	        }
	        gotoxy(x,y+=2);
			choice=confirm("Add another meal? [Y/N]: ",&x,&y); 
			if(choice=='y' || choice=='Y') {
				system("cls");
				EnterMeal:
				gotoxy(35,5);
				cout<<"Day "<<day<<" :";
			}
			else
				(*posy)=20;
	    }while(choice=='y' || choice=='Y');
	}
    void loadMealsFromFile() {
    	system("cls");
        fstream file;
        char* fileName;
        cout<<"Enter filename to load meals from: ";
        cin>>fileName;
        if(openFile(file,fileName,ios::in)) {
            int type;
            Meal* meal=NULL;
            // Clear previous meals before loading
            for(int day=0;day<MAX_DAYS;day++) {
                mealCounts[day]=0;  // Reset the meal count for each day
            }
            for(int day=0;day<MAX_DAYS;day++) {
                for(int i=0;i<MAX_MEALS;++i) {
                    file.read((char*)&type,sizeof(type));
                    switch(type) {
                        case 1: meal=new Breakfast(); break;
                        case 2: meal=new Lunch(); break;
                        case 3: meal=new Dinner(); break;
                        case 4: meal=new Snacks(); break;
                        default: continue;
                    }
                    file.read((char*)meal,sizeof(*meal));
                    dailyMeals[day][mealCounts[day]++]=meal;
                }
            }
            file.close();
            cout<<"Meals loaded successfully from \""<<fileName<<"\"\n";
        }
        else {
        	cout<<"Error loading file.\n";
    	}
    }

    void viewMeals() {
        loadMealsFromFile();
        for (int day = 0; day < MAX_DAYS; day++) {
            if (mealCounts[day] > 0) {
                cout << "Day " << day + 1 << ":\n";
                for (int i = 0; i < mealCounts[day]; ++i) {
                    Meal* meal = dailyMeals[day][i];
                    cout << "\tMeal " << i + 1 << ": " << meal->getName() << ", Calories: " << meal->getCalories() << ", Protein: " << meal->getProtein() << "g\n";
				}
            } else {
                cout << "Day " << day + 1 << ": No meals recorded.\n";
            }
        }
        (*posx)=0;
        (*posy)=38;
    }

 void saveMealsToFile() {
    char fileName[100];
    x=35,y=22;
    gotoxy(x,y);
	cout<<"Enter filename to save meals: ";
    cin>>fileName;
    fstream file;
    if(openFile(file,fileName,ios::out)) {
        for(int day=0;day<MAX_DAYS;++day) {
            for (int i=0;i<mealCounts[day];i++) {
                Meal* meal=dailyMeals[day][i];
                int type=0;
                if ((Breakfast*)(meal)) type=1;
                else if ((Lunch*)(meal)) type=2;
                else if ((Dinner*)(meal)) type=3;
                else if ((Snacks*)(meal)) type=4;
                file.write((char*)&type,sizeof(type));
                file.write((char*)meal,sizeof(*meal));
            }
        }
        file.close();
        gotoxy(x,++y);
        cout<<"Meals saved successfully to \""<<fileName<<"\"\n";
    } else {
    	gotoxy(x,y+=2);
        cout<<"Error saving file.\n";
    }
    (*posy)=25;

}

    ~CalorieTracker() {
        for (int day = 0; day < MAX_DAYS; day++) {
            for (int i = 0; i < mealCounts[day]; i++) {
                delete dailyMeals[day][i];
            }
        }
    }
};

void displayMenu() {
    system("cls");
    int x=35,y=4;
    gotoxy(x,y);
    dash();
    y+=3;
    gotoxy(x,y);
    cout<<"|\tCalorie Tracker \t|";
    gotoxy(x,++y);
    dash();
    y+=3;
    gotoxy(x,y);
    cout<<"1. Set Up User Profile";
    gotoxy(x,++y);
    cout<<"2. View User Profile";
    gotoxy(x,++y);
    cout<<"3. Add Meals";
    gotoxy(x,++y);
    cout<<"4. Save Meals";
    gotoxy(x,++y);
    cout<<"5. View Meals";
    gotoxy(x,++y);
    cout<<"6. Exit";
}

int main() {
    UserProfile profile;
    CalorieTracker tracker;
    int x=35,y=19;
    char choice;
	posx=&x;
	posy=&y;
    do {
        displayMenu();
        choice=confirm("Which operation do you want to perform? [1-6] : ",&x,&y); 
        switch(choice) {
            case '1':
                profile.setProfile();
                break;
            case '2':
                profile.viewProfile();
                break;
            case '3':
                tracker.addMeal();
                break;
            case '4':
                tracker.saveMealsToFile();
                break;
            case '5':
                tracker.viewMeals();
                break;
            case '6':
            	system("cls");
                gotoxy(x,4);
				dash();
				gotoxy(45,8);
				printf("Thank you for using the program.");
				gotoxy(x,10);
				dash();
				exit(0);
				break;
            default:
            	y+=2;
                gotoxy(x,y);
				printf("Invalid choice. Please choose from 1 - 5.");
				*posy=23;
        }
        choice=confirm("Do you want to continue? [Y/N] : ",posx,posy);
        (*posy)=19;
    } while(choice=='y' || choice=='Y');
    return 0;
}
