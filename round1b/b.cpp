#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>

// #include <gtest/gtest.h>
using namespace std;
/**
 *

 1. find the first digit both score is clear, and they are different
   1.1. if the difference != 5: good, we know which one should be bigger
   1.2. if the difference == 5: awo, not so good. looking forward.
     1.2.1. If I can find any non-zero in either score, the larger one win
     1.2.2. Otherwise, we look backward. If the chance of all non-clear for the larger one is all 9, the bigger win, otherwise the smaller win.

 2. Now we know which one should be bigger.
   from the non-equal digit:
   2.1 go back, try to set the lowest number to keep the property
   2.2 go forward, the same
 */

/**
 * return true if C should > J
 */
bool bigger(std::string C, std::string J, int pivot) {
  bool swapped=false;
  if (C[pivot] < J[pivot]) {
    std::string tmp = C;
    C=J;J=tmp;swapped=true;
  }
  bool expect = false;
  if (C[pivot] - J[pivot] < 5) {
    expect = true;
  } else if (C[pivot] - J[pivot] == 5) {
    expect = true;
    for (int i=pivot+1;i<(int)C.size();i++) {
      if (C[i] != '?' && C[i] != '0') expect = false;
      if (J[i] != '?' && J[i] != '0') expect = false;
    }
    if (expect) cout << "\nXXX "  << "\n";
  } else {
    // C[pivot]  J[pivot] > 5
    expect = false;
  }
  // look backward
  if (expect == true) {
    return !swapped;
  }
  // look backward to see if J can be larger
  bool possible = false;
  for (int i=pivot-1;i>=0;i--) {
    if (C[i] == '?' && J[i] == '?') {
      // possible
      possible = true;
      break;
    } else if (C[i] == '?' && J[i] != '0') {
      // possible
      possible = true;
      break;
    } else if (J[i] == '?' && C[i] != '9') {
      //possible
      possible = true;
      break;
    }
  }
  if (possible) return swapped;
  else return !swapped;
  
}

/**
 * C > J
 */
void fill(std::string &C, std::string &J, int pivot) {
  if (C[pivot] > J[pivot]) {
    for (int i=pivot-1;i>=0;i--) {
      if (C[i] == '?' && J[i] == '?') {
        C[i] = '0';
        J[i] = '0';
      } else if (C[i] == '?') C[i] = J[i];
      else if (J[i] == '?') J[i] = C[i];
    }
    for (int i=pivot+1;i<(int)C.size();i++) {
      if (C[i] == '?') C[i] = '0';
      if (J[i] == '?') J[i] = '9';
    }
  } else if (C[pivot < J[pivot]]) {
    // Need to try reverse!
    for (int i=pivot-1;i>=0;i--) {
      if (C[i] == '?' && J[i] == '?') {
        C[i] = '1';
        J[i] = '0';
        break;
      } else if (C[i]=='?') {
        if (J[i] == '9') C[i] = '9';
        else {
          C[i] = J[i]+1;
          break;
        }
      } else if (J[i] == '?') {
        if (C[i] == '0') J[i] = '0';
        else {
          J[i] = C[i] - 1;
          break;
        }
      }
    }
    // copy
    for (int i=pivot-1;i>=0;i--) {
      if (C[i] == '?' && J[i] == '?') {
        C[i] = '0';
        J[i] = '0';
      } else if (C[i] == '?') C[i] = J[i];
      else if (J[i] == '?') J[i] = C[i];
    }
    for (int i=pivot+1;i<(int)C.size();i++) {
      if (C[i] == '?') C[i] = '0';
      if (J[i] == '?') J[i] = '9';
    }
  }
}

std::string solve(std::string C, std::string J) {
  std::string ret;
  int pivot = 0;
  for (pivot=0;pivot<(int)C.size();pivot++) {
    if (C[pivot] != '?' && J[pivot] != '?' && C[pivot] != J[pivot]) {
      break;
    }
  }
  if (pivot == (int)C.size()) {
    // just set everything to 0
    for (int i=0;i<(int)C.size();i++) {
      if (C[i] == '?' && J[i] == '?') {
        C[i] = '0';
        J[i] = '0';
      } else {
        if (C[i] == '?') C[i] = J[i];
        if (J[i] == '?') J[i] = C[i];
      }
    }
  } else {
    // found pivot where the two digits are clear and not same
    // decide which one is bigger
    bool res = bigger(C,J,pivot);
    if (res) {
      // C > J
      fill(C,J,pivot);
    } else {
      // C < J
      fill(J,C,pivot);
    }
  }
  // return
  ret += C;
  ret += " ";
  ret += J;
  return ret;
}

int main(int argc, char* argv[]) {
  int T;
  cin >> T;
  for (int i=0;i<T;i++) {
    std::string C,J;
    cin >> C;
    cin >> J;
    std::string res = solve(C,J);
    cout << "Case #" << i+1 << ": " << res << "\n";
  }
  // ::testing::InitGoogleTest(&argc, argv);
  // return RUN_ALL_TESTS();
}
