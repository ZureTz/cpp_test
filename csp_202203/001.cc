#include <iostream>
using namespace std;

struct var_stat {
  bool *stats;
  var_stat(int n_vars) {
    stats = new bool[n_vars + 1]();
    stats[0] = true;
  }
};

int main(int argc, char const *argv[]) {
  int n_exps, n_var;
  cin >> n_var >> n_exps;
  var_stat status(n_var);

  int uninitialzaiton_count(0);
  for (int i = 0; i < n_exps; i++) {
    int l_value, r_value;
    cin >> l_value >> r_value;
    uninitialzaiton_count += status.stats[r_value] ? 0 : 1;
    status.stats[l_value] = true;
  }
  cout << uninitialzaiton_count;

  return 0;
}