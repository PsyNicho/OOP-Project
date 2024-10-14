#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int MAX_MEALS = 100;

// Abstract base class for meals
class Meal {
	protected:
	    string name;
	    double calories,protein;
	public:
	    Meal(string n, double c,double p) {
	    	name=n;
	    	calories=c;
	    	protein=p;
		} 
	    virtual void displayMeal()=0;  // Pure virtual function for meal display
	    double getCalories() {
	        return calories;
	    }
		double getProtein()  {
	        return protein;
	    }
	    virtual ~Meal() {}
};

// Derived class for Breakfast
class Breakfast:public Meal {
	public:
	    Breakfast(string n, double c,double p) :Meal(n,c,p) {}
	    void displayMeal() {
	        cout<<"Breakfast : "<<endl<<name<<" , " <<calories<<"kCal , "<<protein<<" g"<< endl;
	    }
};

// Derived class for Lunch
class Lunch:public Meal {
	public:
	    Lunch(string n, double c,double p) :Meal(n,c,p) {}
	    void displayMeal() {
	        cout<<"Lunch : "<<endl<<name<<" , " <<calories<<"kCal , "<<protein<<" g"<< endl;
	    }
};

// Derived class for Dinner
class Dinner:public Meal {
	public:
	    Dinner(string n, double c,double p) :Meal(n,c,p) {}
	    void displayMeal() {
	        cout<<"Dinner : "<<endl<<name<<" , " <<calories<<"kCal , "<<protein<<" g"<< endl;
	    }
};

class Snacks:public Meal {
	public:
	    Snacks(string n, double c,double p) :Meal(n,c,p) {}
	    void displayMeal() {
	        cout<<"Snacks : "<<endl<<name<<" , " <<calories<<"kCal , "<<protein<<" g"<< endl;
	    }
};

// UserProfile class to store and manage user information
class UserProfile {
	private:
	    double age,height,weight,goalCalorie,goalProtein;
	    int activity;
		string gender;	
	public:
	    UserProfile() {
	    	age=height=weight=goalCalorie=goalProtein=0;
		}
		void setProfile() {
	    	cout<<"Enter your age : ";
	        cin>>age;
	        cout<<"Enter your gender : ";
	        cin>>gender;
	        cout<<"Enter your height (in cm): ";
	        cin>>height;
	        cout<<"Enter your weight (in kg): ";
	        cin>>weight;
	        cout<<"Choose your activity level :\n1. Sedentary\n2. Light\n3. Moderate\n4. Very active\n5. Custom\nEnter your choice : ";
	        cin>>activity;
	        setCalorieGoal();
	        setProteinGoal();
	    }
	    void setCalorieGoal() {
	        int goal;
	        cout<<"Choose your goal :\n1. Lose weight\n2. Maintain weight\n3. Gain weight\n4. Set a custom calorie goal\nEnter your choice : ";
	        cin>>goal;
	        switch(goal)
	        {
	        	case 1:
	        		goalCalorie=calculateCalories()-500;
	        		break;
	        	case 2:
	        		goalCalorie=calculateCalories();
	        		break;
	        	case 3:
	        		goalCalorie=calculateCalories()+500;
	        		break;
	        	case 4:
	        		cout<<"Enter custom calorie goal (in kCal) : ";
	        		cin>>goalCalorie;
	        		break;
			}
	        cout<<"Your daily calorie goal is set to "<<goalCalorie<<" calories.\n";
	    }
	    int calculateCalories() {
	        double bmr;
	        if(gender=="male")
	        	bmr=10*weight+6.25*height-5*age+5; 
	        else
	        	bmr=10*weight+6.25*height-5*age-161;
	        switch(activity)
	        {
	        	case 1:
	        		return(bmr*1.2);
	        	case 2:
	        		return(bmr*1.375);
	        	case 3:
	        		return(bmr*1.55);
	        	case 4:
	        		return(bmr*1.725);
	        	case 5:
	        		double customFactor;
	        		cout<<"Enter custom activity factor : ";
	        		cin>>customFactor;
	        		return(bmr*customFactor);
			}
	    }
		 void setProteinGoal() {
	        switch(activity)
	        {
	        	case 1:
	        		goalProtein=0.1*weight*2.205;
	        		break;
	        	case 2:
	        		goalProtein=0.5*weight*2.205;
	        		break;
	        	case 3:
	        		goalProtein=0.6*weight*2.205;
	        		break;
	        	case 4:
	        		goalProtein=0.8*weight*2.205;
	        		break;
	        	case 5:
	        		cout<<"Enter custom protein goal (in g) : ";
	        		cin>>goalProtein;
			}
	        cout<<"Your daily protein goal is set to "<<goalProtein<<" grams.\n";
	    }
	    double getCalorieGoal()  {
	        return goalCalorie;
	    }
	    double getProteinGoal()  {
	        return goalProtein;
	    }
};

// CalorieTracker class to manage meals and total calorie count
class CalorieTracker {
private:
    Meal* meals[MAX_MEALS];  // Array to store meal pointers
    int mealCount;           // Number of meals added
    double totalCalories,totalProtein;       // Total calories consumed
    UserProfile user;        // User profile object

public:
    CalorieTracker() {
    	mealCount=0;
		totalCalories=totalProtein=0;
        user.setProfile();
    }

    // Add a meal to the tracker
    void addMeal(Meal* meal) {
        if(mealCount<MAX_MEALS) {
            meals[mealCount++]=meal;
            totalCalories+=meal->getCalories();
            totalProtein+=meal->getProtein();
            cout<<"Meal added!\n";
        } 
		else {
            cout<<"Meal limit reached!\n";
        }

        // Warn if daily calorie limit is exceeded
        if(totalCalories>user.getCalorieGoal()) {
            cout<<"Warning: You've exceeded your daily calorie goal!\n";
        }
        if(totalProtein>user.getProteinGoal()) {
            cout<<"Warning: You've exceeded your daily protein goal!\n";
        }
    }

    // Display all meals added
    void displayMeals()  {
        if(mealCount==0) {
            cout<<"No meals added yet.\n";
            return;
        }
        cout<<"\nMeals for the day:\n";
        for (int i = 0;i<mealCount;i++) {
            meals[i]->displayMeal();
        }
    }

    // Display total calories consumed
    void displayTotalCalories()  {
        cout<<"Total calories consumed : "<<totalCalories<<endl;
    }
    void displayTotalProtein()  {
        cout<<"Total protein consumed : "<<totalProtein<<endl;
    }

    // Save meals to a file
    void saveMealsToFile() const {
        ofstream outFile("calories.txt");
        if (!outFile) {
            cout << "Error opening file for saving.\n";
            return;
        }
        for (int i = 0; i < mealCount; i++) {
            outFile << meals[i]->getCalories() << endl;
        }
        outFile.close();
        cout << "Meals saved to file.\n";
    }

    // Destructor to free dynamically allocated memory
    ~CalorieTracker() {
        for (int i = 0; i < mealCount; i++) {
            delete meals[i];  // Free each dynamically allocated meal
        }
    }
};

// Function to display the menu and get user choice
int displayMenu() {
    int choice;
    cout << "\n--- Calorie Tracker Menu ---\n";
    cout << "1. Add Breakfast\n";
    cout << "2. Add Lunch\n";
    cout << "3. Add Dinner\n";
    cout << "4. View All Meals\n";
    cout << "5. View Total Calories\n";
    cout << "6. Save Meals to File\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

// Function to handle adding meals
void addMeal(CalorieTracker &tracker, int type) {
    string name;
    double calories,protein;

    cout << "Enter meal name: ";
    cin.ignore();  // To clear newline character from input buffer
    getline(cin, name);
    cout<<"Enter calories and protein: ";
    cin>>calories>>protein;

    Meal* meal ;
    switch (type) {
        case 1:
            meal = new Breakfast(name, calories,protein);
            break;
        case 2:
            meal = new Lunch(name, calories,protein);
            break;
        case 3:
            meal = new Dinner(name, calories,protein);
            break;
        case 4:
        	meal = new Snacks(name, calories,protein);
            break;
        default:
            cout << "Invalid meal type!\n";
            return;
    }

    tracker.addMeal(meal);  // Add meal to the tracker
}

// Main function with menu-based program
int main() {
    CalorieTracker tracker;

    while (true) {
        int choice = displayMenu();

        switch (choice) {
            case 1:
                addMeal(tracker, 1);
                break;
            case 2:
                addMeal(tracker, 2);
                break;
            case 3:
                addMeal(tracker, 3);
                break;
            case 4:
                tracker.displayMeals();
                break;
            case 5:
                tracker.displayTotalCalories();
                break;
            case 6:
                tracker.saveMealsToFile();
                break;
            case 7:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}

