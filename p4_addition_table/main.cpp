#include <iostream>

//#define DEBUG
//#define TEST_CASE_3

#ifdef TEST_CASE_1
const int N = 1;
int input_table[N][N] = {
  2
};

#elifdef  TEST_CASE_2
const int N = 3;
int input_table[N][N] = {
  {3,4,2},
  {5,2,3},
  {6,3,5}
} ;

#elifdef  TEST_CASE_3
const int N = 6;
int input_table[N][N] = {
  {8,10,5,6,7,4},
  {12,11,10,4,8,2},
  {5,4,6,7,9,8},
  {10,2,4,8,5,12},
  {6,8,7,9,3,5},
  {4,12,8,5,6,10}
} ;

#else
int N;
int **input_table;

#endif

int real_number_amount(int num) {
  if (num <= N + 1) return num - 1;
  return 2*N - num + 1;
}

//calculate amount of num in input_table
int calculate_amount(int num) {
  int amount = 0;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (input_table[i][j] == num) amount ++;
    }
  }
  return amount;
}

int find_mismatch(int amount) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      int item = input_table[i][j];
      if (calculate_amount(item) == amount &&
        real_number_amount(item) != amount) {
        return item;
      }
    }
  }
  return 0; //all matched
}

void swap(int a, int b) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      int item = input_table[i][j];
      if (item == a) input_table[i][j] = b;
      if (item == b) input_table[i][j] = a;
    }
  }
}

void PrintTable(void) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      int item = input_table[i][j];
      std::cout << item << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  std::cin >> N;
  input_table = new int*[N];
  for(int i = 0; i < N; ++i) {
    input_table[i] = new int[N];
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      std::cin >> input_table[i][j];
    }
  }

  for (int i = 2; i < N*2; i++) {
    int real_amount = real_number_amount(i);
    #ifdef DEBUG
    std::cout << i << " real amount should be  " << real_amount << std::endl;
    #endif
    //find a number in input_table, its amount equals real_amount, but it should not be
    int mismatch = find_mismatch(real_amount);
    if (mismatch != 0) {
      #ifdef DEBUG
      std::cout << "swap: " << i << " and " <<  mismatch << std::endl;
      #endif
      //swap mismatch and i in input_table
      swap(i, mismatch);
      #ifdef DEBUG
      PrintTable();
      #endif
    } else {
      #ifdef DEBUG
      std::cout << "no mismatched" << std::endl;
      #endif
    }
  }

  //step2
  bool no_change[2*N] = {true};
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (input_table[i][j] > N+1 && no_change[input_table[i][j]]) {
        no_change[input_table[i][j]] = false;
        swap(2*N + 2 - input_table[i][j], input_table[i][j]);
      }
    }
  }

  //step 3:
  for (int num = 2*N; num > N; num --) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (input_table[i][j] == num) {
          //row
          for (int k = 0; k < N; k++) {
            if (k == j) continue;
            if (input_table[i][k] <= (input_table[i][j] - N)) {
              swap(2*N + 2 - input_table[i][k], input_table[i][k]);
            }
          }
          //columm
          for (int k = 0; k < N; k++) {
            if (k == i) continue;
            if (input_table[k][j] <= (input_table[i][j] - N)) {
              swap(2*N + 2 - input_table[k][j], input_table[k][j]);
            }
          }
        }
      }
    }
  }
  PrintTable();

  return 0;
}
