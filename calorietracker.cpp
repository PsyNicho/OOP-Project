#include<iostream>
#include<fstream>
using namespace std;
int CalCalc();

int main(){
    int req;
    req = CalCalc();
    cout<<"Your required calorie is: "<<req;
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
    cout<<"Enter Your activity level \n1. For lightly active(physical activity 1-3 days a week) \n2. For moderately active(physical activivity 3-5 days a week) \n3. For highly active(high physical activivity 6-7 days a week)\n";
    cout<<"Enter Your Choice: ";
    cin>>al;
    cout<<"Enter your goal \n1. For Weight Maintain \n2.For weight Loss \n3.For Weight Gain\n";
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