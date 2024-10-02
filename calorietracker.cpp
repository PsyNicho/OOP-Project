#include<iostream>
#include<fstream>
#include<string>

using namespace std;
int CalCalc();

class FoodLog{
    private:
        string fileName, foodName, tempname;
        double calorieValue;
    public:

        FoodLog(const string& file):fileName(file){}

        void addFood(){
            ofstream outFile(fileName, ios::app);  
            if (!outFile){
                cout << "Error opening file!" << endl;
                return;
            }
            cout << "Enter food name: ";
            cin.ignore();  
            getline(cin, foodName);
            cout << "Enter calorie value per 100g: ";
            cin >> calorieValue;
            outFile << foodName << " " << calorieValue << endl;
            outFile.close();
            cout << "Food added!" << endl;
        }

        void viewFoodLog(){
            ifstream inFile(fileName); 
            if(!inFile){
                cout << "Error opening file!" << endl;
                return;
            }
            cout << "\nFood Log:" << endl;
            while(inFile >> foodName >> calorieValue){
                cout << foodName << " - " << calorieValue << " calories per 100g" << endl;
            }

            inFile.close();
        }
        
        bool findFood(const string& targetFood, double& foundCalories) {
            ifstream inFile(fileName);
            bool found = false;
            while (inFile >> foodName >> calorieValue) {
                if (foodName == targetFood) {
                    foodName = targetFood;
                    foundCalories = calorieValue;
                    found = true;
                    break;
                }
            }
            inFile.close();
            return found;
        }

        void searchFood() {
            string targetFood;
            double foundCalories;
            cout << "Enter the food name to search: ";
            cin.ignore();
            getline(cin, targetFood);
            if (findFood(targetFood, foundCalories)) {
                cout << "Food found: " << targetFood << " - " << foundCalories << " calories per 100g" << endl;
            } else {
                cout << "Food not found in the log!" << endl;
            }
        }

        void deleteFood() {
            ifstream inFile(fileName);
            ofstream tempFile("temp.txt");
            if (!inFile || !tempFile) {
                cout << "Error opening file!" << endl;
                return;
            }
            string targetFood, foodName;
            double calorieValue;
            cout << "Enter the food name to delete: ";
            cin.ignore();
            getline(cin, targetFood);
            bool found = false;
            while (inFile >> foodName >> calorieValue) {
                if (foodName != targetFood) {
                    tempFile << foodName << " " << calorieValue << endl;  // Write other records
                } else {
                    found = true;  // Mark as found, do not write this record
                }
            }
            inFile.close();
            tempFile.close();
            if (found) {
                remove(fileName.c_str());
                rename("temp.txt", fileName.c_str());
                cout << "Food record deleted successfully!" << endl;
            } else {
                remove("temp.txt");  // Delete the temp file if no food was found
                cout << "Food not found in the log!" << endl;
            }
        }
};

int main(){
    int ch, req;
    string fileName = "food_log.txt";  
    FoodLog foodLog(fileName);        
    cout<<"\nEnter 1 To calculate your required calorie per day.";
    cout<<"\nEnter 2 To view food list.";
    cout<<"\nEnter 3 To add food to food list.";
    cout<<"\nEnter 4 To delete food from list.";
    cout<<"\nEnter 5 To write your food log for the day.";
    cout<<"\nEnter 6 To calculate calorie intake of the day.";
    cout<<"\nEnter your choice: ";
    cin>>ch;
    switch(ch){
        case 1:
            cout<<"Calorie Calculator";
            req = CalCalc();
            cout<<"Your required calorie is: "<<req;
            break;
        case 2:
            foodLog.viewFoodLog();
            break;
        case 3:
            foodLog.addFood();
            break;     
        case 4:
            break;
    }
}

int CalCalc(){
    int age, weight, height, goal, bmr, al, wgl;
    char gender;
    cout<<"Enter Weight in Kilograms(kg): ";
    cin>>weight;
    cout<<"Enter Height in Centimeters(cm): ";
    cin>>height;
    cout<<"Enter Age in Years: ";
    cin>>age;
    cout<<"Enter Gender(M or male, F for female): ";
    cin>>gender;
    cout<<"Enter Your activity level \n1 For lightly active(physical activity 1-3 days a week) \n2 For moderately active(physical activivity 3-5 days a week) \n3 For highly active(high physical activivity 6-7 days a week)\n";
    cout<<"Enter Your Choice: ";
    cin>>al;
    cout<<"Enter your goal \n1 For Weight Maintain \n2 For weight Loss \n3 For Weight Gain\n";
    cout<<"Enter your choice: ";
    cin>>wgl;
    switch(gender){
        case 'M':
        case 'm':
            bmr=(10 * weight) + (6.25 * height) - (5 * age) + 5;
            break;
        case 'F':
        case 'f':    
            bmr=(10 * weight) + (6.25 * height) - (5 * age) - 161;
            break;
        default:
            cout << "Invalid choice!" << endl;    
    }
    switch(al){
        case 1:
            bmr = bmr * 1.375;
            break;
        case 2:
            bmr = bmr * 1.55;
            break;
        case 3:
            bmr = bmr * 1.725;
            break;
        default:
            cout << "Invalid choice!" << endl;    
    }
    switch(wgl){
        case 1:
            goal = bmr;
            break;
        case 2:
            goal = bmr * 0.87;
            break;
        case 3:
            goal = bmr * 1.25;
            break;
        default:
            cout << "Invalid choice!" << endl;    
    }
    return goal;
}
