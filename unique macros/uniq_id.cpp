#include <string>
#include <vector>
using namespace std;

#define GLUE_HELPER(y) qwe_##y
#define GLUE(x) GLUE_HELPER(x)
#define UNIQ_ID GLUE(__LINE__)

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
}