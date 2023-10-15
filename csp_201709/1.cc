  #include <iostream>
  using std::cin;
  using std::cout;

  inline int numOfSoySauce(int money) {
    const int originalResult = money / 10;
    return originalResult + 2 * (originalResult / 5) + (originalResult % 5 / 3);
  }

  int main(int argc, char const *argv[]) {
    int money;
    cin >> money;
    cout << numOfSoySauce(money);
    return 0;
  }