#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;
bool loginCheck = false;
void login();
void input();
void searchByName();
void searchById();
void edit();
void showAll();
void quit();
int main() {
  if (loginCheck == false) {
    login();
  }
  system ("cls");
  system ("color f4");
  int option;
  cout << "1. Enter New Information\n";
  cout << "2. Find An Account\n";
  cout << "3. Edit By Name\n";
  cout << "4. Show All Employees\n";
  cout << "5. Exit\n";
  cin >> option;
switch (option) {
  case 1:
    input();
    break;
  case 2:
    system("cls");
      cout << "1. Find By Name\n";
      cout << "2. Find By ID\n";
      cin >> option;
      switch (option) {
        case 1:
        searchByName();
        break;
        case 2:
        searchById();
        break;
      }
    break;
  case 3:
    edit();
    break;
  case 4:
    showAll();
    break;
  case 5:
    system ("cls");
    cout << "Good Luck, Have Fun!\n";
    break;
  }
  exit(1000);
  return 0;
}
void login(){
  system("cls");
  string name, username;
  char decision;
  int id, password;
  ifstream check("userpass.txt", ios::in);
  cout << "Enter Your Username:\n";
  cin >> username;
  cout << "Enter Your Password:\n";
  cin >> password;
    while (check >> name >> id) {
      if (name == username && id == password) {
        loginCheck = true;
        cout << "Login was successful!" << endl;
        check.close();
        system("pause");
        main();
      }
    }
  cout << "Sorry, But Entered Username Or Password Is Invalid.\n";
  cout << "Do You Want To Try Again?[y][n]\n";
  cin >> decision;
  switch (decision) {
    case 'y':
      login();
      break;
    case 'n':
      quit();
      break;
  }
  check.close();
}
void input() {
    string name, nameInput;
    double daramad, daramadInput;
    int check, id;
    system ("cls");
    ofstream newAccount("names.txt", ios::out | ios::app);
    ifstream checkingId("names.txt");
    cout << "Enter Your Name:\n";
    cin >> nameInput;
    cout << "Enter Your Salary:\n";
    cin >> daramadInput;
    cout << "Enter Your ID:\n";
    cin >> check;
    system("pause");
    system ("cls");
    while (checkingId >> name >> id >> daramad) {
        while (id == check) {
          system("cls");
          cout << "Sorry, But Already There Is Another Account With Same ID, Please Enter Another One:\n";
          cin >> check;
        }
    }
    name = nameInput; id = check; daramad = daramadInput;
    checkingId.close();
    newAccount << name << " " << id << " " << daramad << endl;
    newAccount.close();
    main();
}
void searchByName() {
     ifstream employee("names.txt");
     string name;
     string str, decision;
     int id;
     double daramad;
     bool isFound = false;
     system("cls");
     cout << "Enter the account name:\n";
     cin >> str;
     while (!employee.eof()) {
       while (employee >> name >> id >> daramad){
         while (str == name){
           isFound = true;
           system ("cls");
           cout << "Account found!\n\n";
           cout << "ID" << ' ' << "Name" << ' ' << "Salary" << endl;
           cout << "---------------" << endl;
           cout << "#" << id << " " << name << " $" <<  daramad << endl;
           cout << "Is This The Correct Employee[y][n]:";
           cin >> decision;
           if (decision == "y") {
             system("cls");
             cout << "Okay Boomer!" << endl;
             system("pause");
             employee.close();
             break;
           } else if(decision == "n"){
             break;
           }
         }
       }
       if (isFound == false) {
         system("cls");
         cout << "Nobody under that name exists!" << endl;
         break;
       }
     }
     employee.close();
     if (isFound != true) {
       system ("pause");
     }
     main();
 }
void searchById() {
      ifstream employee("names.txt");
      string name, decision;
      int input;
      int id;
      double daramad;
      bool isFound = false;
      system("cls");
      cout << "Enter the ID:\n";
      cin >> input;
      while (!employee.eof()) {
        while (employee >> name >> id >> daramad){
          while (input == id){
            isFound = true;
            system ("cls");
            cout << "Account found!\n\n";
            cout << "Name" << ' ' << "ID" << ' ' << "Daramad" << endl;
            cout << "---------------" << endl;
            cout << name << " #" << id << " $" <<  daramad << endl;
            cout << "Is This The Correct Employee[y][n]:";
            cin >> decision;
            if (decision == "y") {
              system("cls");
              cout << "Okay Boomer!" << endl;
              system("pause");
              employee.close();
              break;
            } else if(decision == "n"){
              break;
            }
          }
        }
        if (isFound != true) {
          system("cls");
          cout << "Nobody under that name exists! (anymore)" << endl;
          break;
        }
      }
      employee.close();
      if (isFound != true) {
        system ("pause");
      }
      main();
  }
void edit() {
  system("cls");
  string name, input, decision, nameReplace;
  int id, menu;
  double daramad;
  bool isFound = false;
  ifstream editF("names.txt");
  ofstream editExisting("temp.txt", ios::out | ios::app);
  cout << "What Do You Want To Change?:\n";
  cout << "1.Name\n";
  cout << "2.ID\n";
  cout << "3.Salary\n";
  cin >> menu;
  switch (menu) {
    case 1:
      system("cls");
      cout << "Enter A Name:\n";
      cin >> input;
      while (!editF.eof()) {
        while (editF >> name >> id >> daramad) {
          while (input == name && isFound == false) {
            system("cls");
            cout << "ID" << ' ' << "Name" << ' ' << "Salary" << endl;
            cout << "---------------" << endl;
            cout << "#" << id << " " << name << " $" <<  daramad << endl;
            cout << "Is This The Correct Employee[y][n]:";
            cin >> decision;
            if (decision == "y") {
              isFound = true;
              system("cls");
              cout << "Enter A New Name For This Account:\n";
              cin >> name;
              system("cls");
            } else if(decision == "n"){
              break;
            }
          }
        editExisting << name << " " << id << " " << daramad << endl;
        }
        if (isFound != true) {
          system("cls");
          cout << "Nobody under that name exists! (anymore)" << endl;
          break;
        }
      }
      editF.close();
      editExisting.close();
      remove("names.txt");
      rename("temp.txt", "names.txt");
      break;
    case 2:
      system("cls");
      cout << "Enter A Name:\n";
      cin >> input;
      while (!editF.eof()) {
        while (editF >> name >> id >> daramad) {
          while (input == name && isFound == false) {
            system("cls");
            cout << "ID" << ' ' << "Name" << ' ' << "Salary" << endl;
            cout << "---------------" << endl;
            cout << "#" << id << " " << name << " $" <<  daramad << endl;
            cout << "Is This The Correct Employee[y][n]:";
            cin >> decision;
            if (decision == "y") {
              isFound = true;
              system("cls");
              cout << "Enter A New ID For This Account:\n";
              cin >> id;
              system("cls");
            } else if(decision == "n"){
              break;
            }
          }
        editExisting << name << " " << id << " " << daramad << endl;
        }
        if (isFound != true) {
          system("cls");
          cout << "Nobody under that name exists! (anymore)" << endl;
          break;
        }
      }
      editF.close();
      editExisting.close();
      remove("names.txt");
      rename("temp.txt", "names.txt");
      break;
    case 3:
      system("cls");
      cout << "Enter A Name:\n";
      cin >> input;
      while (!editF.eof()) {
        while (editF >> name >> id >> daramad) {
          while (input == name && isFound == false) {
            system("cls");
            cout << "ID" << ' ' << "Name" << ' ' << "Salary" << endl;
            cout << "---------------" << endl;
            cout << "#" << id << " " << name << " $" <<  daramad << endl;
            cout << "Is This The Correct Employee[y][n]:";
            cin >> decision;
            if (decision == "y") {
              isFound = true;
              system("cls");
              cout << "Enter A New Salary For This Account:\n";
              cin >> daramad;
              system("cls");
            } else if(decision == "n"){
              break;
            }
          }
        editExisting << name << " " << id << " " << daramad << endl;
        }
        if (isFound != true) {
          system("cls");
          cout << "Nobody under that name exists!" << endl;
          break;
        }
      }
      editF.close();
      editExisting.close();
      remove("names.txt");
      rename("temp.txt", "names.txt");
      break;
  }
  system ("pause");
  main();
}
void showAll() {
  system("cls");
  string name;
  int id;
  double daramad;
  ifstream show("names.txt", ios::in);
  while (!show.eof()) {
    cout << "ID" << ' ' << "Name" << ' ' << "Salary" << endl;
    cout << "---------------" << endl;
    while (show >> name >> id >> daramad) {
      cout << "#" << id << " " << name << " $" <<  daramad << endl;
    }
  }
  show.close();
  system("pause");
  main();
}
void quit() {
  system ("cls");
  cout << "Good Luck, Have Fun!\n";
  exit(1000);
}
