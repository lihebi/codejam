#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>

// #include <gtest/gtest.h>

using namespace std;
int remove_one(std::string &line, char c, std::string s) {
  // cout << "remove " << s << " from " << line  << "\n";
  int ret;
  ret = std::count(line.begin(), line.end(), c);
  for (int i=0;i<ret;i++) {
    for (char cc : s) {
      // cout << line  << "\n";
      line.erase(line.find(cc), 1);
    }
  }
  return ret;
}

std::string solve(std::string line) {
  // cout << "solve"  << "\n";
  int res[10] = {0};
  res[6] = remove_one(line, 'X', "SIX");
  res[0] = remove_one(line, 'Z', "ZERO");
  res[4] = remove_one(line, 'U', "FOUR");
  res[2] = remove_one(line, 'W', "TWO");
  res[8] = remove_one(line, 'G', "EIGHT");
  res[7] = remove_one(line, 'S', "SEVEN");
  res[5] = remove_one(line, 'V', "FIVE");
  res[1] = remove_one(line, 'O', "ONE");
  res[3] = remove_one(line, 'R', "THREE");
  res[9] = remove_one(line, 'I', "NINE");
  std::string ret;
  for (int i=0;i<10;i++) {
    // ret += std::to_string(i);
    for (int j=0;j<res[i];j++) {
      ret += std::to_string(i);
    }
  }
  return ret;
}

using namespace std;
int main(int argc, char* argv[]) {
  int T;
  cin >> T;
  for (int i=0;i<T;i++) {
    std::string line;
    cin >> line;
    std::string res = solve(line);
    cout << "Case #" << i+1 << ": " << res  << "\n";
  }
  // ::testing::InitGoogleTest(&argc, argv);
  // return RUN_ALL_TESTS();
}
