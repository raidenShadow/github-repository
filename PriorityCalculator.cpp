#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;
//////
vector<char> calculationSentence;
int save;
struct compute{
  double first;
  double second;
  double answer;
}; compute calculation;
struct coordinate{
  int start;
  int end;
}; coordinate position;
//////
void stringToCharVector(string changeable);
bool operation_left();
bool bothSides(int fromHere, int untillHere);
bool check_multiply_or_divide();
bool is_number(unsigned int position);
bool check_parentheses();
string numberToString(double number);
void updateParanthesesPosition();
void calculate();
//////
int main() {
  string input;
  cout << "Input:\n";
  getline(cin, input);
  stringToCharVector(input);
  calculate();
  cout << "The Result is: ";
  for (unsigned int i = 0; i < calculationSentence.size(); i++) {
    cout << calculationSentence[i];
  }
  return 0;
}
//////
void stringToCharVector(string changeable){
  for (int i = 0; i < changeable.length(); i++) {
    calculationSentence.push_back(changeable[i]);
  }
}
bool operation_left(int fromHere, int untillHere){
  for (; fromHere < untillHere; fromHere++) {
    if (calculationSentence[fromHere] == '+' || calculationSentence[fromHere] == '-' ||
        calculationSentence[fromHere] == '*' || calculationSentence[fromHere] == '/') {
      return true;
    }
  }
  return false;
}
bool check_multiply_or_divide(int fromHere, int untillHere){
  for (; fromHere < untillHere; fromHere++) {
    if (calculationSentence[fromHere] == '*' || calculationSentence[fromHere] == '/') {
      return true;
    }
  }
  return false;
}
bool is_number(int position) {
  if ((calculationSentence[position] >= 48 && calculationSentence[position] <= 57)
      || calculationSentence[position] == 46) {
    return true;
  }
  return false;
}
bool check_parentheses() {
  for (unsigned int i = 0; i < calculationSentence.size(); ++i) {
    if (calculationSentence[i] == '(') {
        return true;
    }
  }
  return false;
}
bool check_nested_parantheses(int checkFromHere, int untillHere){
  checkFromHere++;
  for (; checkFromHere < untillHere; checkFromHere++) {
    if (calculationSentence[checkFromHere] == '(') {
      save = checkFromHere;
      return true;
    }
  }
  return false;
}
bool bothSides(int fromHere, int untillHere){
  int temp = fromHere, counter = 0;
  for (temp; temp < untillHere; temp++) {
    if (calculationSentence[temp] == '+' || calculationSentence[temp] == '-' ||
        calculationSentence[temp] == '*' || calculationSentence[temp] == '/') {
      counter++;
    }
  }
  if (counter > 1) {
    return true;
  }
  for (; fromHere < untillHere; fromHere++) {
    if (calculationSentence[fromHere] == '-') {
      break;
    }
  }
  string leftSide = "";
  for (int i = fromHere - 1; is_number(i); i--) {
    leftSide += calculationSentence[i];
  }
  if (leftSide.length() == 0) {
    return false;
  } else {
    return true;
  }
}
string numberToString(double number){
  ostringstream temp;
  temp << number;
  return temp.str();
}
void updateParanthesesPosition(int startingPosition){
  int endingPosition;
  for (startingPosition; calculationSentence[startingPosition] != '('; startingPosition++) {}
  for (endingPosition = startingPosition + 1; calculationSentence[endingPosition] != ')'; endingPosition++) {}
  if (check_nested_parantheses(startingPosition, endingPosition) == true) {
    return updateParanthesesPosition(save);
  }
  position.start = startingPosition;
  position.end = endingPosition;
}
void calculate(){
  //
  if (operation_left(0, calculationSentence.size()) == true && bothSides(0, calculationSentence.size())) {
    //
    for (int i = 0; i < calculationSentence.size(); i++) {
      if ((calculationSentence[i] == '-' && calculationSentence[i+1] == '+') ||
          (calculationSentence[i] == '+' && calculationSentence[i+1] == '-')) {
        if (calculationSentence[i] == '+') {
          calculationSentence.erase(calculationSentence.begin() + i);
        }
        if (calculationSentence[i++] == '+') {
          calculationSentence.erase(calculationSentence.begin() + i + 1);
        }
      }
    }
    if (check_parentheses() == true) {
      updateParanthesesPosition(0);
      if (operation_left(position.start, position.end) == true && bothSides(position.start, position.end) == true) {
        bool recall = false;
        if (check_multiply_or_divide(position.start, position.end) == true) {
          for (unsigned int i = position.start; i < position.end; i++) {
            switch (calculationSentence[i]) {
              case '*':{
                recall = true;
                string numberSerie = "";
                int start, end;
                for (start = i - 1; is_number(start) == true; start--) {
                  numberSerie += calculationSentence[start];
                } start++;
                reverse(numberSerie.begin(), numberSerie.end());
                calculation.first = stod(numberSerie);
                numberSerie = "";
                for (end = i + 1; is_number(end) == true; end++) {
                  numberSerie += calculationSentence[end];
                }
                calculation.second = stod(numberSerie);
                calculation.answer = calculation.first * calculation.second;
                string resultInStringForm = numberToString(calculation.answer);
                calculationSentence.erase(calculationSentence.begin() + start, calculationSentence.begin() + end);
                for (int i = 0, temp = start; i < resultInStringForm.length(); i++, temp++) {
                  calculationSentence.insert(calculationSentence.begin() + temp, resultInStringForm[i]);
                }
                break;
              }
              case '/':{
                recall = true;
                string numberSerie = "";
                int start, end;
                for (start = i - 1; is_number(start) == true; start--) {
                  numberSerie += calculationSentence[start];
                } start++;
                reverse(numberSerie.begin(), numberSerie.end());
                calculation.first = stod(numberSerie);
                numberSerie = "";
                for (end = i + 1; is_number(end) == true; end++) {
                  numberSerie += calculationSentence[end];
                }
                calculation.second = stod(numberSerie);
                calculation.answer = calculation.first / calculation.second;
                string resultInStringForm = numberToString(calculation.answer);
                calculationSentence.erase(calculationSentence.begin() + start, calculationSentence.begin() + end);
                for (int i = 0, temp = start; i < resultInStringForm.length(); i++, temp++) {
                  calculationSentence.insert(calculationSentence.begin() + temp, resultInStringForm[i]);
                }
                break;
              }
            }
            if (recall == true) {
              return calculate();
            }
          }
        } else {
          for (unsigned int i = position.start; i < position.end; i++) {
            switch (calculationSentence[i]) {
              case '+':{
                recall = true;
                string numberSerie = "";
                int start, end;
                for (start = i - 1; is_number(start) == true; start--) {
                  numberSerie += calculationSentence[start];
                } start++;
                reverse(numberSerie.begin(), numberSerie.end());
                calculation.first = stod(numberSerie);
                numberSerie = "";
                for (end = i + 1; is_number(end) == true; end++) {
                  numberSerie += calculationSentence[end];
                }
                calculation.second = stod(numberSerie);
                calculation.answer = calculation.first + calculation.second;
                string resultInStringForm = numberToString(calculation.answer);
                calculationSentence.erase(calculationSentence.begin() + start, calculationSentence.begin() + end);
                for (int i = 0, temp = start; i < resultInStringForm.length(); i++, temp++) {
                  calculationSentence.insert(calculationSentence.begin() + temp, resultInStringForm[i]);
                }
                break;
              }
              case '-':{
                recall = true;
                string numberSerie = "";
                int start, end;
                for (start = i - 1; is_number(start) == true; start--) {
                  numberSerie += calculationSentence[start];
                } start++;
                reverse(numberSerie.begin(), numberSerie.end());
                calculation.first = stod(numberSerie);
                numberSerie = "";
                for (end = i + 1; is_number(end) == true; end++) {
                  numberSerie += calculationSentence[end];
                }
                calculation.second = stod(numberSerie);
                calculation.answer = calculation.first - calculation.second;
                string resultInStringForm = numberToString(calculation.answer);
                calculationSentence.erase(calculationSentence.begin() + start, calculationSentence.begin() + end);
                for (int i = 0, temp = start; i < resultInStringForm.length(); i++, temp++) {
                  calculationSentence.insert(calculationSentence.begin() + temp, resultInStringForm[i]);
                }
                break;
              }
            }
            if (recall == true) {
              return calculate();
            }
          }
        }
      } else {
        calculationSentence.erase(calculationSentence.begin() + position.start);
        calculationSentence.erase(calculationSentence.begin() + position.end - 1);
        return calculate();
      }
    } else {
      if (check_multiply_or_divide(0, calculationSentence.size()) == true) {
        bool recall = false;
        for (unsigned int i = 0; i < calculationSentence.size(); i++) {
          switch (calculationSentence[i]) {
            case '*':{
              recall = true;
              string numberSerie = "";
              int start, end;
              for (start = i - 1; is_number(start) == true; start--) {
                numberSerie += calculationSentence[start];
              } start++;
              reverse(numberSerie.begin(), numberSerie.end());
              calculation.first = stod(numberSerie);
              numberSerie = "";
              for (end = i + 1; is_number(end) == true && end != calculationSentence.size(); end++) {
                numberSerie += calculationSentence[end];
              }
              calculation.second = stod(numberSerie);
              calculation.answer = calculation.first * calculation.second;
              string resultInStringForm = numberToString(calculation.answer);
              calculationSentence.erase(calculationSentence.begin() + start, calculationSentence.begin() + end);
              for (int i = 0, temporary = start; i < resultInStringForm.length(); i++, temporary++) {
                calculationSentence.insert(calculationSentence.begin() + temporary, resultInStringForm[i]);
              }
              break;
            }
            case '/':{
              recall = true;
              string numberSerie = "";
              int start, end;
              for (start = i - 1; is_number(start) == true; start--) {
                numberSerie += calculationSentence[start];
              } start++;
              reverse(numberSerie.begin(), numberSerie.end());
              calculation.first = stod(numberSerie);
              numberSerie = "";
              for (end = i + 1; is_number(end) == true && end != calculationSentence.size(); ++end) {
                numberSerie += calculationSentence[end];
              }
              calculation.second = stod(numberSerie);
              calculation.answer = calculation.first / calculation.second;
              string resultInStringForm = numberToString(calculation.answer);
              calculationSentence.erase(calculationSentence.begin() + start, calculationSentence.begin() + end);
              for (int i = 0, temporary = start; i < resultInStringForm.length(); i++, temporary++) {
                calculationSentence.insert(calculationSentence.begin() + temporary, resultInStringForm[i]);
              }
              break;
            }
          }
          if (recall == true) {
            return calculate();
          }
        }
      } else {
        bool recall = false;
        for (unsigned int i = 0; i < calculationSentence.size(); i++) {
          switch (calculationSentence[i]) {
            case '+':{
              recall = true;
              string numberSerie = "";
              int start, end;
              for (start = i - 1; is_number(start) == true; --start) {
                numberSerie += calculationSentence[start];
              } start++;
              reverse(numberSerie.begin(), numberSerie.end());
              calculation.first = stod(numberSerie);
              numberSerie = "";
              for (end = i + 1; is_number(end) == true && end != calculationSentence.size(); end++) {
                numberSerie += calculationSentence[end];
              }
              calculation.second = stod(numberSerie);
              calculation.answer = calculation.first + calculation.second;
              string resultInStringForm = numberToString(calculation.answer);
              calculationSentence.erase(calculationSentence.begin() + start, calculationSentence.begin() + end);
              for (int i = 0, temporary = start; i < resultInStringForm.length(); i++, temporary++) {
                calculationSentence.insert(calculationSentence.begin() + temporary, resultInStringForm[i]);
              }
              break;
            }
            case '-':{
              recall = true;
              string numberSerie = "";
              int start, end;
              for (start = i - 1; is_number(start) == true; start--) {
                numberSerie += calculationSentence[start];
              } start++;
              reverse(numberSerie.begin(), numberSerie.end());
              calculation.first = stod(numberSerie);
              numberSerie = "";
              for (end = i + 1; is_number(end) == true && end != calculationSentence.size(); end++) {
                numberSerie += calculationSentence[end];
              }
              calculation.second = stod(numberSerie);
              calculation.answer = calculation.first - calculation.second;
              string resultInStringForm = numberToString(calculation.answer);
              calculationSentence.erase(calculationSentence.begin() + start, calculationSentence.begin() + end);
              for (int i = 0, temporary = start; i < resultInStringForm.length(); i++, temporary++) {
                calculationSentence.insert(calculationSentence.begin() + temporary, resultInStringForm[i]);
              }
              break;
            }
          }
          if (recall == true) {
            return calculate();
          }
        }
      }
    }
  }
}
