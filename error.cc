#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

struct objectNotDefined : public std::exception {
  const char *what() const noexcept override { return "Object is Undefined"; };
};

class Object {
private:
  bool isDefined;

public:
  Object(std::string str) {
    if (str == "Vector") {
      isDefined = true;
    }

    isDefined = false;
    throw objectNotDefined();
  }
};

int main(int argc, char const *argv[]) {
  try {
    Object object("Myself");
  } catch (const std::exception &err) {
    std::cerr << "Error: " << err.what() << std::endl;
    exit(EXIT_FAILURE);
  }
}