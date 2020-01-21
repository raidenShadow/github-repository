#include <iostream>
#include <fstream>
#include <conio.h>
#include <cmath>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <windows.h>
#define KEY_UP 72
#define KEY_DOWN 80
#define GREEN 2
#define WHITE 7
using namespace std;
struct account{
  string username, password;
}; account shopKeeper;
struct category{
  string name = "";
}; category dasteHa;
struct product{
  string name, anotherName;
  int id, anotherId;
  long double amount, price, anotherAmount, anotherPrice;
}; product kala;
string menuItemsForDynamics[100];
bool loginCheck = false;
bool boughtFromShopByCustomer = false;
//Utilities (Declare)
int dynamicMenu(string menu[], int n);
void underScoreAdder(string &changeable);
void underScoreRemover(string &changeable);
void arrayCleaner(string cleanIt[]);
string numberToString(double number);
void sortByAlphabet(string list[], string changed[], int n);
void sortByPrice(double list[], string changed[], int n, int choice);
void notification();
void login();
//Shopkeeper Section (Declare)
void shopkeeperMenu();
void addNewProduct();
void changeTheProperties();
void deleteAProduct();
void showAll();
void category();
void changeACategory();
void deleteACategory();
//Customer Se ction (Declare)
void customerMenu();
void addNewProductToCart();
void changeAProductFromCart();
void finishTheShopping();
//Global Functions (Declare)
void searchBetweenProducts(char comingFrom);
void showAllCustomer(char comingFrom);
void showAllByAlphabetSeperated(char comingFrom);
void showByPrice(char comingFrom);
//Main And Login
int main() {
  //
  system("cls");
  //Menu
  int controller = 0;
  char decision;
  string dummySpace = "  ";
  string mainMenuItems[] = {"1. As Shopkeeper", "2. As Customer", "3. Exit"};
  while (decision != '\r') {
    if (controller < 0) {
      controller = 2;
    } else if(controller > 2){
      controller = 0;
    }
    system("cls");
    for (int i = 0; i < 3; i++) {
      if (controller == i) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, GREEN);
        cout << dummySpace << mainMenuItems[i] << endl;
        SetConsoleTextAttribute(hConsole, WHITE);
        continue;
      }
      cout << mainMenuItems[i] << endl;
    }
    decision = getch();
    switch (decision) {
      case KEY_UP:
        controller--;
        break;
      case KEY_DOWN:
        controller++;
        break;
    }
  }
  switch (controller) {
    case 0:
      shopkeeperMenu();
      break;
    case 1:
      customerMenu();
      break;
    case 2:
      system("cls");
      remove("cart.txt");
      cout << "Good Luck!" << endl;
      Sleep(150);
      break;
  }
  return 0;
}
//Utilities
int dynamicMenu(string menu[], int n){
  int controller = 0;
  char decision;
  string dummySpace = "  ";
  if (menu[0][0] == 0) {
    system("cls");
    cout << "It's Empty\n";
    system("pause");
    return -1;
  }
  while (decision != '\r' && decision != 27) {
    if (controller < 0) {
      controller = n-1;
    } else if(controller > n-1){
      controller = 0;
    }
    system("cls");
    int numberOfLine = 1;
    cout << "Entekhab Konid:\n";
    for (int i = 0; i < n; i++, numberOfLine++) {
      if (controller == i) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, GREEN);
        cout << dummySpace << numberOfLine << ". " << menu[i] << endl;
        SetConsoleTextAttribute(hConsole, WHITE);
        continue;
      }
      cout << numberOfLine << '.' << menu[i] << endl;
    }
    decision = getch();
    switch (decision) {
      case KEY_UP:
        controller--;
        break;
      case KEY_DOWN:
        controller++;
        break;
    }
  }
  if (decision == 27) {
    return -1;
  }
  return controller;
}
void underScoreAdder(string &changeable){
  for(int i = 0; i < changeable.length(); i++){
    if(changeable[i] == ' '){
      changeable[i] = '_';
    }
  }
}
void underScoreRemover(string &changeable){
  for(int i = 0; i < changeable.length(); i++){
    if(changeable[i] == '_'){
      changeable[i] = ' ';
    }
  }
}
void arrayCleaner(string cleanIt[]){
  for (int i = 0; cleanIt[i][0] != 0; i++) {
    cleanIt[i].clear();
  }
}
string numberToString(double number){
  ostringstream temp;
  temp << number;
  return temp.str();
}
void sortByAlphabet(string list[], string changed[], int n){
  for (int i = 0; i < n-1; i++) {
    for (int j = i+1; j < n; j++) {
      for (int k = 0; list[j][k] != 0; k++) {
        if (list[i][k] < list[j][k]) {
          break;
        } else if (list[i][k] > list[j][k]) {
          swap(list[i], list[j]);
          swap(changed[i], changed[j]);
          break;
        }
      }
    }
  }
}
void sortByPrice(double list[], string changed[], int n, int choice){
  switch (choice) {
    case 1: //Rising
      for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
          if (list[j] > list[i]) {
            double tempOne; string tempTwo;
            tempOne = list[j];
            list[j] = list[i];
            list[i] = tempOne;
            tempTwo = changed[j];
            changed[j] = changed[i];
            changed[i] = tempTwo;
          }
        }
      }
      break;
    case 2: //Falling
      for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
          if (list[j] < list[i]) {
            double tempOne; string tempTwo;
            tempOne = list[j];
            list[j] = list[i];
            list[i] = tempOne;
            tempTwo = changed[j];
            changed[j] = changed[i];
            changed[i] = tempTwo;
          }
        }
      }
      break;
  }
}
void notification(){
  bool isUnderTheMinimum = false;
  cout << "-----------\n";
  cout << "Products that should be bought:\n";
  ifstream openCategoryList("categoryList.txt");
  if (openCategoryList.is_open()) {
    while (!openCategoryList.eof()) {
      while (openCategoryList >> dasteHa.name) {
        underScoreRemover(dasteHa.name); dasteHa.name += ".txt";
        ifstream openACategory(dasteHa.name);
        while (!openACategory.eof()) {
          while (openACategory >> kala.id >> kala.name >> kala.price >> kala.amount) {
            if (kala.amount <= 5) {
              isUnderTheMinimum = true;
              underScoreRemover(kala.name);
              cout << "#" << kala.id << ' ' << kala.name << ' ' << kala.price << "T " << kala.amount << endl;
            }
          }
        }
      }
    }
    if (isUnderTheMinimum == false) {
      cout << "Everything is okay!\n";
    }
  } else {
    return;
  }
}
void login(){
  system("cls");
  char decision;
  string username, password;
  ifstream loginInfo("userpass.txt", ios::in);
  DWORD attributes = GetFileAttributes("userpass.txt");
  SetFileAttributes("userpass.txt", attributes + FILE_ATTRIBUTE_HIDDEN);
  while (loginCheck != true && decision != 'n') {
    cout << "Enter Username:\n";
    cin >> username;
    cout << "Enter Password:\n";
    cin >> password;
    while (!loginInfo.eof()) {
      while (loginInfo >> shopKeeper.username >> shopKeeper.password) {
        if (shopKeeper.username == username && shopKeeper.password == password) {
          loginCheck = true;
          cout << "Login was successful!\n";
          loginInfo.close();
          return shopkeeperMenu();
        }
      }
      cout << "Wanna try more?[y][n]\n";
      cin >> decision;
      switch (decision) {
        case 'y':
          return login();
          break;
        case 'n':
          main();
          break;
      }
    }
  }
}
//Global Functions
void searchBetweenProducts(char comingFrom){
  system("cls");
  bool isFound = false, firstTime = true;
  string search; char decision;
  cout << "Enter a name:\n";
  cin >> ws;
  getline(cin, search);
  system("cls");
  ifstream openCategoryList("categoryList.txt");
  while (!openCategoryList.eof()) {
    while (openCategoryList >> dasteHa.name) {
      underScoreRemover(dasteHa.name);
      string forShow = dasteHa.name;
      dasteHa.name += ".txt";
      ifstream openACategory(dasteHa.name);
      if (firstTime == false) {
        cout << "-----------\n";
      }
      cout << "From " << forShow << " category:\n";
      cout << "-----------\n";
      while (!openACategory.eof()) {
        while (openACategory >> kala.id >> kala.name >> kala.price >> kala.amount) {
          underScoreRemover(kala.name);
          if (kala.name.find(search) != string::npos) {
            isFound = true;
            cout << "#" << kala.id << ' ' << kala.name << ' ' << kala.price << "T " << kala.amount << endl;
          }
        }
      }
      firstTime = false;
      openACategory.close();
    }
  }
  openCategoryList.close();
  if (isFound == false) {
    system("cls");
    cout << "Nothing exists under this name (anymore)!\n";
    system("pause");
  }
  if (isFound == true) {
    system("pause");
  }
  decision = 't';
  while (decision != 's' && decision != 'r') {
    system("cls");
    cout << "Ok, wanna search again or return to the menu?[s][r]";
    decision = getch();
    if (decision == 's') {
      return searchBetweenProducts(comingFrom);
    } else if (decision == 'r') {
      if (comingFrom == 'c') {
        return customerMenu();
      } else if (comingFrom == 's') {
        return shopkeeperMenu();
      }
    }
  }
}
void showAll(char comingFrom){
  system("cls");
  ifstream categoryList("categoryList.txt");
  while (!categoryList.eof()) {
    cout << "ID Name Price Amount\n";
    cout << "---------------" << endl;
    while (categoryList >> dasteHa.name) {
      underScoreRemover(dasteHa.name);
      cout << dasteHa.name << ":" << endl;
      dasteHa.name += ".txt";
      ifstream printInput(dasteHa.name);
      while (printInput >> kala.id >> kala.name >> kala.price >> kala.amount) {
        underScoreRemover(kala.name);
        cout << "#" << kala.id << " " << kala.name << " " <<  kala.price << "T " << kala.amount << endl;
      }
      cout << "---------------" << endl;
      printInput.close();
    }
  }
  categoryList.close();
  system("pause");
  if (comingFrom == 'c') {
    return customerMenu();
  } else if (comingFrom == 's') {
    return shopkeeperMenu();
  }
}
void showAllByAlphabetSeperated(char comingFrom){
  system("cls");
  string namesList[100];
  int counter = 0, choice, j = 1;
  ifstream categoryList("categoryList.txt");
  while (categoryList >> dasteHa.name) {
    underScoreRemover(dasteHa.name);
    menuItemsForDynamics[counter] = dasteHa.name;
    counter++;
  }
  categoryList.close();
  choice = dynamicMenu(menuItemsForDynamics, counter);
  if (choice == -1) {
    return customerMenu();
  }
  choice++;
  ifstream categoryListMatch("categoryList.txt");
  while (categoryListMatch >> dasteHa.name) {
    if (j == choice) {
      break;
    }
    j++;
  }
  categoryListMatch.close();
  underScoreRemover(dasteHa.name); dasteHa.name += ".txt";
  arrayCleaner(menuItemsForDynamics);
  ifstream openACategory(dasteHa.name);
  counter = 0;
  while (openACategory >> kala.id >> kala.name >> kala.price >> kala.amount) {
    namesList[counter] = kala.name;
    underScoreRemover(kala.name);
    string dummyId = numberToString(kala.id),
     dummyPrice = numberToString(kala.price),
     dummyAmount = numberToString(kala.amount);
    string combined = "#" + dummyId + " " + kala.name + " " + dummyPrice + "T " + dummyAmount;
    menuItemsForDynamics[counter] = combined;
    counter++;
  }
  openACategory.close();
  sortByAlphabet(namesList, menuItemsForDynamics, counter);
  system("cls");
  cout << "ID Name Price Amount\n";
  cout << "--------------------\n";
  for (int i = 0; i < counter; i++) {
    cout << menuItemsForDynamics[i] << endl;
  }
  system("pause");
  if (comingFrom == 'c') {
    return customerMenu();
  } else if (comingFrom == 's') {
    return shopkeeperMenu();
  }
}
void showByPrice(char comingFrom){
  system("cls");
  int choice;
  ifstream openCategoryList("categoryList.txt");
  string menu[] = {"Descending", "Ascending"};
  choice = dynamicMenu(menu, 2);
  if (choice == -1) {
    switch (comingFrom) {
      case 'c':
       return customerMenu();
       break;
      case 's':
       return shopkeeperMenu();
       break;
    }
  }
  choice++;
  system("cls");
  while (openCategoryList >> dasteHa.name){
    double prices[100];
    underScoreRemover(dasteHa.name);
    cout << dasteHa.name << ":" << endl;
    cout << "-----------" << endl;
    dasteHa.name += ".txt";
    ifstream openACategory(dasteHa.name, ios::app);
    int counter = 0;
    while (openACategory >> kala.id >> kala.name >> kala.price >> kala.amount) {
      prices[counter] = kala.price;
      string id = numberToString(kala.id), price = numberToString(kala.price), amount = numberToString(kala.amount);
      menuItemsForDynamics[counter] = "#" + id + " " + kala.name + " " + price + "T " + amount;
      counter++;
    }
    openACategory.close();
    sortByPrice(prices, menuItemsForDynamics, counter, choice);
    for (int i = 0; i < counter; i++) {
      cout << menuItemsForDynamics[i] << endl;
    }
    cout << "-----------" << endl;
  }
  openCategoryList.close();
  system("pause");
  switch (comingFrom) {
    case 'c':
     return customerMenu();
     break;
    case 's':
     return shopkeeperMenu();
     break;
  }
}
//Shopkeeper Section
void shopkeeperMenu(){
  system("cls");
  if (loginCheck == false) {
    return login();
  }
  int controller = 0;
  char decision, go = 's';
  string dummySpace = "  ";
  string shopkeeperMenuItems[] = {"1. Add a new product", "2. Change an existing product",
                                  "3. Delete a product", "4. Add a new category", "5. Change an existing category",
                                  "6. Delete a category", "7. Search between products",
                                  "8. Show all categories and products",
                                  "9. Show all products alphabetical", "10. Show by price",
                                  "11. Return to main menu"
                                 };
  while (decision != '\r' && decision != 27) {
    if (controller < 0) {
      controller = 10;
    } else if(controller > 10){
      controller = 0;
    }
    system("cls");
    for (int i = 0; i < 11; i++) {
      if (controller == i) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, GREEN);
        cout << dummySpace << shopkeeperMenuItems[i] << endl;
        SetConsoleTextAttribute(hConsole, WHITE);
        continue;
      }
      cout << shopkeeperMenuItems[i] << endl;
    }
    notification();
    decision = getch();
    switch (decision) {
      case KEY_UP:
        controller--;
        break;
      case KEY_DOWN:
        controller++;
        break;
    }
  }
  switch (controller) {
    case 0:
      addNewProduct();
      break;
    case 1:
      changeTheProperties();
      break;
    case 2:
      deleteAProduct();
      break;
    case 3:
      category();
      break;
    case 4:
      changeACategory();
      break;
    case 5:
      deleteACategory();
      break;
    case 6:
      searchBetweenProducts(go);
      break;
    case 7:
      showAll(go);
      break;
    case 8:
      showAllByAlphabetSeperated(go);
      break;
    case 9:
      showByPrice(go);
      break;
    case 10:
      main();
      break;
  }
}
void addNewProduct(){
  system("cls");
  int choice, j = 1, counter = 0, dummyInt0, dummyInt1, dummyInt2;
  char decision;
  string dummyName;
  ifstream categoryList("categoryList.txt", ios::in);
  while (categoryList >> dasteHa.name) {
    underScoreRemover(dasteHa.name);
    menuItemsForDynamics[counter] = dasteHa.name;
    counter++;
  }
  categoryList.close();
  choice = dynamicMenu(menuItemsForDynamics, counter);
  if (choice == -1) {
    return shopkeeperMenu();
  }
  choice++;
  ifstream categoryListMatch("categoryList.txt", ios::in);
  while (categoryListMatch >> dasteHa.name) {
    if (j == choice) {
      break;
    }
    j++;
  }
  categoryListMatch.close();
  system("cls");
  underScoreRemover(dasteHa.name);
  dasteHa.name += ".txt";
  ofstream inputData(dasteHa.name, ios::app);
  ifstream checkData(dasteHa.name);
  cout << "Enter The Name Of Your Product:\n";
  cin >> ws;
  getline(cin, kala.name);
  cout << "Enter The Price:\n";
  cin >> kala.price;
  cout << "Enter The Amount:\n";
  cin >> kala.amount;
  cout << "Enter An ID:\n";
  cin >> kala.id;
  while (checkData >> dummyInt0 >> dummyName >> dummyInt1 >> dummyInt2) {
    while (dummyInt0 == kala.id) {
      cout << "Sorry, But Already There Is Another Product With Same ID, Please Enter Another One:\n";
      cin >> kala.id;
      system("cls");
    }
  }
  checkData.close();
  underScoreAdder(kala.name);
  inputData << kala.id << ' ' << kala.name << ' ' << kala.price << ' ' << kala.amount << endl;
  inputData.close();
  system("pause");
  shopkeeperMenu();
}
void changeTheProperties(){
  system("cls");
  string findName, dummyName;
  int choice, j = 1, dummyInt0, dummyInt1, dummyInt2, counter = 0;
  bool isFound = false;
  string check;
  char decision;
  ifstream categoryList("categoryList.txt", ios::in);
  while (categoryList >> dasteHa.name) {
    underScoreRemover(dasteHa.name);
    menuItemsForDynamics[counter] = dasteHa.name;
    counter++;
  }
  categoryList.close();
  choice = dynamicMenu(menuItemsForDynamics, counter);
  if (choice == -1) {
    return shopkeeperMenu();
  }
  choice++;
  ifstream categoryListMatch("categoryList.txt", ios::in);
  while (categoryListMatch >> dasteHa.name) {
    if (j == choice) {
      break;
    }
    j++;
  }
  categoryListMatch.close();
  underScoreRemover(dasteHa.name);
  dasteHa.name += ".txt";
  ifstream originalForCategory(dasteHa.name, ios::in);
  ofstream resultForCategory("tempForCategory.txt", ios::out | ios::app);
  system("cls");
  int controller = 0; char secondDecision; string dummySpace = "  ";
  string constantMenuItems[] = {"1. Name", "2. Price",
                                "3. ID"  , "4. Amount"
                               };
  while (secondDecision != '\r' && secondDecision != 27) {
    if (controller < 0) {
      controller = 3;
    } else if(controller > 3){
      controller = 0;
    }
    system("cls");
    cout << "What Do You Want To Change:\n";
    for (int i = 0; i < 4; i++) {
      if (controller == i) {
         HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
         SetConsoleTextAttribute(hConsole, GREEN);
         cout << dummySpace << constantMenuItems[i] << endl;
         SetConsoleTextAttribute(hConsole, WHITE);
         continue;
       }
       cout << constantMenuItems[i] << endl;
     }
     secondDecision = getch();
     switch (secondDecision) {
       case KEY_UP:
         controller--;
         break;
       case KEY_DOWN:
         controller++;
         break;
     }
  }
  if (secondDecision == 27) {
    originalForCategory.close();
    resultForCategory.close();
    return changeTheProperties();
  }
  system("cls");
  cout << "Enter A Name:\n";
  cin >> ws;
  getline(cin, findName);
  underScoreAdder(findName);
  switch (controller) {
    case 0:{
      while (!originalForCategory.eof()) {
        while (originalForCategory >> kala.id >> kala.name >> kala.price >> kala.amount) {
          while ((kala.name.find(findName) != string::npos) && isFound == false) {
            system("cls");
            cout << "ID " << "Name" << " Price" << " Amount" << endl;
            cout << "---------------" << endl;
            cout << "#" << kala.id << " " << kala.name << " " <<  kala.price << "T " << kala.amount << endl;
            cout << "Is this the correct product?[y][n]:";
            cin >> decision;
            if (decision == 'y') {
              isFound = true;
              system("cls");
              cout << "Enter A New Name For This Product:\n";
              cin >> ws;
              getline(cin, kala.name);
              underScoreAdder(kala.name);
              system("cls");
              break;
            } else if(decision == 'n'){
              break;
            }
          }
          resultForCategory << kala.id << ' ' << kala.name << ' ' << kala.price << ' ' << kala.amount << endl;
        }
        if (isFound == false) {
          system("cls");
          cout << "Nothing under that name exists! (anymore)" << endl;
          break;
        }
      }
      originalForCategory.close();
      resultForCategory.close();
      const char * oldFile = dasteHa.name.c_str();
      remove(oldFile);
      rename("tempForCategory.txt", oldFile);
      break;
      }
    case 1:
      {
      while (!originalForCategory.eof()) {
        while (originalForCategory >> kala.id >> kala.name >> kala.price >> kala.amount) {
          while ((kala.name.find(findName) != string::npos) && isFound == false) {
            system("cls");
            cout << "ID " << "Name" << " Price" << " Amount" << endl;
            cout << "---------------" << endl;
            cout << "#" << kala.id << " " << kala.name << " " <<  kala.price << "T " << kala.amount << endl;
            cout << "Is this the correct product?[y][n]:";
            cin >> decision;
            if (decision == 'y') {
              isFound = true;
              system("cls");
              cout << "Enter A New Price For This Product:\n";
              cin >> kala.price;
              system("cls");
            } else if(decision == 'n'){
              break;
            }
          }
          resultForCategory << kala.id << ' ' << kala.name << ' ' << kala.price << ' ' << kala.amount << endl;
        }
        if (isFound == false) {
          system("cls");
          cout << "Nothing under that name exists! (anymore)" << endl;
          break;
        }
      }
      originalForCategory.close();
      resultForCategory.close();
      const char * oldFile = dasteHa.name.c_str();
      remove(oldFile);
      rename("tempForCategory.txt", oldFile);
      break;}
    case 2:
      {
      while (!originalForCategory.eof()) {
        while (originalForCategory >> kala.id >> kala.name >> kala.price >> kala.amount) {
          while ((kala.name.find(findName) != string::npos) && isFound == false) {
            system("cls");
            cout << "ID " << "Name" << " Price" << " Amount" << endl;
            cout << "---------------" << endl;
            cout << "#" << kala.id << " " << kala.name << " " <<  kala.price << "T " << kala.amount << endl;
            cout << "Is this the correct product?[y][n]:";
            cin >> decision;
            if (decision == 'y') {
              isFound = true;
              system("cls");
              cout << "Enter A New ID For This Product:\n";
              cin >> kala.id;
              ifstream checkData(dasteHa.name);
              while (checkData >> dummyInt0 >> dummyName >> dummyInt1 >> dummyInt2) {
                while (dummyInt0 == kala.id) {
                  cout << "Sorry, But Already There Is Another Product With Same ID, Please Enter Another One:\n";
                  cin >> kala.id;
                  system("cls");
                }
              }
              checkData.close();
              system("cls");
            } else if(decision == 'n'){
              break;
            }
          }
          resultForCategory << kala.id << ' ' << kala.name << ' ' << kala.price << ' ' << kala.amount << endl;
        }
        if (isFound == false) {
          system("cls");
          cout << "Nothing under that name exists! (anymore)" << endl;
          break;
        }
      }
      originalForCategory.close();
      resultForCategory.close();
      const char * oldFile = dasteHa.name.c_str();
      remove(oldFile);
      rename("tempForCategory.txt", oldFile);
      break;}
    case 3:
      {
      while (!originalForCategory.eof()) {
        while (originalForCategory >> kala.id >> kala.name >> kala.price >> kala.amount) {
          while ((kala.name.find(findName) != string::npos) && isFound == false) {
            system("cls");
            cout << "ID " << "Name" << " Price" << " Amount" << endl;
            cout << "---------------" << endl;
            cout << "#" << kala.id << " " << kala.name << " " <<  kala.price << "T " << kala.amount << endl;
            cout << "Is this the correct product?[y][n]:";
            cin >> decision;
            if (decision == 'y') {
              isFound = true;
              system("cls");
              cout << "Enter A New Amount For This Product:\n";
              cin >> kala.amount;
              system("cls");
            } else if(decision == 'n'){
              break;
            }
          }
          resultForCategory << kala.id << ' ' << kala.name << ' ' << kala.price << ' ' << kala.amount << endl;
        }
        if (isFound == false) {
          system("cls");
          cout << "Nothing under that name exists! (anymore)" << endl;
          break;
        }
      }
      originalForCategory.close();
      resultForCategory.close();
      const char * oldFile = dasteHa.name.c_str();
      remove(oldFile);
      rename("tempForCategory.txt", oldFile);
      break;}
  }
  system("pause");
  system("cls");
  cout << "Do You Want To Change More Or Not:[y][n]\n";
  cin >> decision;
  switch (decision) {
    case 'y':
      changeTheProperties();
      break;
    case 'n':
      shopkeeperMenu();
      break;
  }
}
void deleteAProduct(){
  int choice, j = 1, counter = 0;
  char decision;
  system("cls");
  ifstream categoryList("categoryList.txt", ios::in);
  while (categoryList >> dasteHa.name) {
    underScoreRemover(dasteHa.name);
    menuItemsForDynamics[counter] = dasteHa.name;
    counter++;
  }
  categoryList.close();
  choice = dynamicMenu(menuItemsForDynamics, counter);
  if (choice == -1) {
    return shopkeeperMenu();
  }
  choice++;
  ifstream categoryListMatch("categoryList.txt", ios::in);
  while (categoryListMatch >> dasteHa.name) {
    if (j == choice) {
      break;
    }
    j++;
  }
  categoryListMatch.close();
  underScoreRemover(dasteHa.name);
  dasteHa.name += ".txt";
  ifstream showProductList(dasteHa.name);
  arrayCleaner(menuItemsForDynamics);
  counter = 0;
  while (showProductList >> kala.id >> kala.name >> kala.price >> kala.amount) {
    string dummyId = numberToString(kala.id), dummyPrice = numberToString(kala.price), dummyAmount = numberToString(kala.amount);
    string combined = "";
    underScoreRemover(kala.name);
    combined = "#" + dummyId + " " + kala.name + " " + dummyPrice + "T " + dummyAmount;
    menuItemsForDynamics[counter] = combined;
    counter++;
  }
  showProductList.close();
  choice = dynamicMenu(menuItemsForDynamics, counter);
  if (choice == -1) {
    return deleteAProduct();
  }
  choice++;
  ifstream openingForDeleting(dasteHa.name);
  ofstream resulfAfterDeleting("temp.txt", ios::out | ios::app);
  j = 1;
  while (!openingForDeleting.eof()) {
    while (openingForDeleting >> kala.id >> kala.name >> kala.price >> kala.amount) {
      if (choice == j) {
        resulfAfterDeleting << endl;
        j++;
        continue;
      }
      resulfAfterDeleting << kala.id << ' ' << kala.name << ' ' << kala.price << ' ' << kala.amount << endl;
      j++;
    }
  }
  openingForDeleting.close();
  resulfAfterDeleting.close();
  const char * oldOne = dasteHa.name.c_str();
  remove(oldOne);
  rename("temp.txt", oldOne);
  shopkeeperMenu();
}
void category(){
  system("cls");
  cout << endl;
  string unChangedOne;
  cout << "Enter New Category Name:\n";
  cin >> ws;
  getline(cin, dasteHa.name);
  unChangedOne = dasteHa.name;
  underScoreAdder(unChangedOne);
  dasteHa.name += ".txt";
  ofstream categoryList("categoryList.txt", ios::out | ios::app);
  ofstream newFile(dasteHa.name);
  categoryList << unChangedOne << endl;
  categoryList.close();
  newFile.close();
  system("pause");
  shopkeeperMenu();
}
void changeACategory(){
  system("cls");
  string newName;
  int choice, j = 1, counter = 0;
  char decision;
  ifstream categoryList("categoryList.txt", ios::in);
  ofstream categoryListResult("temp.txt", ios::app | ios::out);
  while (categoryList >> dasteHa.name) {
    underScoreRemover(dasteHa.name);
    menuItemsForDynamics[counter] = dasteHa.name;
    counter++;
  }
  categoryList.close();
  choice = dynamicMenu(menuItemsForDynamics, counter);
  system("cls");
  if (choice == -1) {
    return shopkeeperMenu();
  }
  choice++;
  cout << "Enter a new name:\n";
  cin >> ws;
  getline(cin, newName);
  string newNameFile = newName;
  underScoreAdder(newName);
  system("cls");
  ifstream categoryListMatch0("categoryList.txt", ios::in);
  while (categoryListMatch0 >> dasteHa.name) {
    if (j == choice) {
      categoryListResult << newName << endl;
      underScoreRemover(dasteHa.name);
      dasteHa.name += ".txt";
      newNameFile += ".txt";
      const char * oldOne = dasteHa.name.c_str();
      const char * newOne = newNameFile.c_str();
      rename(oldOne, newOne);
      j++;
      continue;
    }
    categoryListResult << dasteHa.name << endl;
    j++;
  }
  categoryListMatch0.close();
  categoryListResult.close();
  remove("categoryList.txt");
  rename("temp.txt", "categoryList.txt");
  cout << "The name has been changed successfully!\n";
  system("pause");
  shopkeeperMenu();
}
void deleteACategory(){
  system("cls");
  string haveToDelete;
  int choice, j = 1, counter = 0;
  ifstream categoryList("categoryList.txt", ios::in);
  while (categoryList >> dasteHa.name) {
    underScoreRemover(dasteHa.name);
    menuItemsForDynamics[counter] = dasteHa.name;
    counter++;
  }
  categoryList.close();
  choice = dynamicMenu(menuItemsForDynamics, counter);
  if (choice == -1) {
    return shopkeeperMenu();
  }
  choice++;
  system("cls");
  ifstream categoryListMatch("categoryList.txt");
  ofstream categoryListResult("temp.txt", ios::app | ios::out);
  while (!categoryListMatch.eof()) {
    while (categoryListMatch >> dasteHa.name) {
      if (j == choice) {
        haveToDelete = dasteHa.name;
        categoryListResult << endl;
        j++;
        continue;
      }
      categoryListResult << dasteHa.name << endl;
      j++;
    }
  }
  categoryListMatch.close();
  categoryListResult.close();
  remove("categoryList.txt");
  rename("temp.txt", "categoryList.txt");
  underScoreRemover(haveToDelete);
  haveToDelete += ".txt";
  const char * deletedOne = haveToDelete.c_str();
  remove(deletedOne);
  cout << "The category has been deleted successfully!\n";
  system("pause");
  shopkeeperMenu();
}
//Customer Section
void customerMenu(){
  system("cls");
  int controller = 0;
  char decision, go = 'c';
  string dummySpace = "  ";
  string shopkeeperMenuItems[] = {"1. Add a new product to cart", "2. Delete an existing product from cart",
                                  "3. Finish the shopping", "4. Search between products",
                                  "5. Show all categories and products", "6. Show list of products alphabetical",
                                  "7. Show by price","8. Return to main menu"
                                 };
  while (decision != '\r' && decision != 27) {
    if (controller < 0) {
      controller = 7;
    } else if(controller > 7){
      controller = 0;
    }
    system("cls");
    for (int i = 0; i < 8; i++) {
      if (controller == i) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, GREEN);
        cout << dummySpace << shopkeeperMenuItems[i] << endl;
        SetConsoleTextAttribute(hConsole, WHITE);
        continue;
      }
      cout << shopkeeperMenuItems[i] << endl;
    }
    decision = getch();
    switch (decision) {
      case KEY_UP:
        controller--;
        break;
      case KEY_DOWN:
        controller++;
        break;
    }
  }
  switch (controller) {
    case 0:
      addNewProductToCart();
      break;
    case 1:
      changeAProductFromCart();
      break;
    case 2:
      finishTheShopping();
      break;
    case 3:
      searchBetweenProducts(go);
      break;
    case 4:
      showAll(go);
      break;
    case 5:
      showAllByAlphabetSeperated(go);
      break;
    case 6:
      showByPrice(go);
      break;
    case 7:
      main();
      break;
  }
}
void addNewProductToCart(){
  system("cls");
  double amount, dummyAmount, dummyPrice;
  char decision;
  int j = 1, choice, secondChoice, counter = 0, dummyId;
  ifstream categoryList("categoryList.txt", ios::in);
  while (categoryList >> dasteHa.name) {
    underScoreRemover(dasteHa.name);
    menuItemsForDynamics[counter] = dasteHa.name;
    counter++;
  }
  categoryList.close();
  choice = dynamicMenu(menuItemsForDynamics, counter);
  if (choice == -1) {
    return customerMenu();
  }
  choice++;
  ifstream categoryListMatch("categoryList.txt");
  while (categoryListMatch >> dasteHa.name) {
    if (j == choice) {
      break;
    }
    j++;
  }
  categoryListMatch.close();
  string categoryName = dasteHa.name;
  underScoreRemover(dasteHa.name);
  dasteHa.name += ".txt";
  ofstream cart("cart.txt", ios::out | ios::app);
  counter = 0;
  system("cls");
  ifstream showItem(dasteHa.name);
  while (showItem >> kala.id >> kala.name >> kala.price >> kala.amount) {
    string dummyId = numberToString(kala.id), dummyPrice = numberToString(kala.price), dummyAmount = numberToString(kala.amount);
    string combined = "";
    underScoreRemover(kala.name);
    combined = "#" + dummyId + " " + kala.name + " " + dummyPrice + "T " + dummyAmount;
    menuItemsForDynamics[counter] = combined;
    counter++;
  }
  showItem.close();
  secondChoice = dynamicMenu(menuItemsForDynamics, counter);
  if (secondChoice == -1) {
    return addNewProductToCart();
  }
  secondChoice++;
  ifstream chooseAProduct(dasteHa.name);
  j = 1;
  while (chooseAProduct >> kala.id >> kala.name >> kala.price >> kala.amount) {
    if (j == secondChoice) {
      cout << "----------\n";
      cout << "Enter the amount:\n";
      cin >> amount;
      while (kala.amount - amount < 0) {
        cout << "You can't buy that much, Please enter new amount:\n";
        cin >> amount;
      }
      cart << kala.id << ' ' << kala.name << ' ' << kala.price << ' ' << amount << ' ' << categoryName << endl;
      break;
    }
    j++;
  }
  boughtFromShopByCustomer = true;
  chooseAProduct.close();
  cart.close();
  cout << "The product has been added successfully to the cart!\n";
  system("pause");
  decision = 't';
  while (decision != 'y' && decision != 'n') {
    system("cls");
    cout << "Wanna add more?[y][n]\n";
    decision = getch();
    if (decision == 'y') {
      return addNewProductToCart();
    } else if(decision == 'n') {
      return customerMenu();
    }
  }
}
void changeAProductFromCart(){
  system("cls");
  int counter = 0, j = 1;
  int choice;
  char decision;
  cout << "Do you want to delete or change the amount?[d][a][esc]";
  decision = getch();
  if (decision == 27) {
    return customerMenu();
  }
  system("cls");
  ifstream showCartItems("cart.txt");
  while (showCartItems >> kala.id >> kala.name >> kala.price >> kala.amount) {
    string dummyId = numberToString(kala.id), dummyPrice = numberToString(kala.price), dummyAmount = numberToString(kala.amount);
    string combined = "";
    underScoreRemover(kala.name);
    combined = "#" + dummyId + " " + kala.name + " " + dummyPrice + "T " + dummyAmount;
    menuItemsForDynamics[counter] = combined;
    counter++;
  }
  showCartItems.close();
  choice = dynamicMenu(menuItemsForDynamics, counter);
  if (choice == -1) {
    return changeAProductFromCart();
  }
  choice++;
  if (decision == 'd') {
    ifstream beforeEditCart("cart.txt");
    ofstream afterEditCart("temp.txt", ios::out | ios::app);
    while (beforeEditCart >> kala.id >> kala.name >> kala.price >> kala.amount) {
      if (j == choice) {
        afterEditCart << endl;
        j++;
        continue;
      }
      afterEditCart << kala.id << ' ' << kala.name << ' ' << kala.price << ' ' << kala.amount << endl;
      j++;
    }
    cout << "The product has been deleted successfully!\n";
    beforeEditCart.close();
    afterEditCart.close();
    remove("cart.txt");
    rename("temp.txt", "cart.txt");
    system("pause");
    return customerMenu();
  } else {
    ifstream beforeEditCart("cart.txt");
    ofstream afterEditCart("temp.txt", ios::out | ios::app);
    while (beforeEditCart >> kala.id >> kala.name >> kala.price >> kala.amount) {
      if (choice == j) {
        system("cls");
        cout << "Enter new amount:\n";
        cin >> kala.amount;
        afterEditCart << kala.id << ' ' << kala.name << ' ' << kala.price << ' ' << kala.amount << endl;
        j++;
        continue;
      }
      afterEditCart << kala.id << ' ' << kala.name << ' ' << kala.price << ' ' << kala.amount << endl;
      j++;
    }
    beforeEditCart.close();
    afterEditCart.close();
    remove("cart.txt");
    rename("temp.txt", "cart.txt");
    system("pause");
  }
  return customerMenu();
}
void finishTheShopping(){
  system("cls");
  string dummyName; int dummyId;
  double difference, dummyAmount, dummyPrice;
  long double sum = 0;
  char decision;
  if (boughtFromShopByCustomer == true) {
    ifstream showCartItems("cart.txt");
    while (!showCartItems.eof()) {
      cout << "ID Name Price Amount\n";
      cout << "---------------" << endl;
      while (showCartItems >> kala.id >> kala.name >> kala.price >> kala.amount >> dasteHa.name) {
        underScoreRemover(kala.name);
        sum += kala.price*kala.amount;
        cout << "#" << kala.id << " " << kala.name << " " << kala.price << "T " << kala.amount << endl;
      }
    }
    showCartItems.close();
    cout << "Are you sure?[y][n]";
    decision = getch();
    if (decision == 27) {
      return customerMenu();
    }
    if (decision == 'y') {
      ifstream applyingChanges("cart.txt");
      while (!applyingChanges.eof()) {
        while (applyingChanges >> kala.id >> kala.name >> kala.price >> kala.amount >> dasteHa.name) {
          underScoreRemover(dasteHa.name); dasteHa.name += ".txt";
          ifstream openACategory(dasteHa.name);
          ofstream result("temp.txt", ios::out | ios::app);
          while (openACategory >> dummyId >> dummyName >> dummyPrice >> dummyAmount) {
            if (dummyId == kala.id && dummyName == kala.name) {
              difference = dummyAmount - kala.amount;
              result << dummyId << ' ' << dummyName << ' ' << dummyPrice << ' ' << difference << endl;
              continue;
            }
            result << dummyId << ' ' << dummyName << ' ' << dummyPrice << ' ' << dummyAmount << endl;
          }
          openACategory.close();
          result.close();
          const char * oldName = dasteHa.name.c_str();
          remove(oldName);
          rename("temp.txt", oldName);
        }
      }
      applyingChanges.close();
      cout << "---------------" << endl;
      cout << "Total cost: " << sum << 'T' << endl;
      system("pause");
      system("cls");
      cout << "Thank you! Have a good time" << endl;
      remove("cart.txt");
      boughtFromShopByCustomer = false;
    } else if(decision == 'n'){
      cout << "Do you want to add something or change?[a][c]";
      cin >> decision;
      if (decision == 'a') {
        return addNewProductToCart();
      } else if(decision == 'c'){
        return changeAProductFromCart();
      }
    }
    system("pause");
    main();
  } else {
    cout << "You haven't bought anything yet!\n";
    system("pause");
    return customerMenu();
  }
}
