#include <functional>
#include <ios>
#include <iostream>
#include <limits>
#include <ostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using std::cin;
using std::cout;

#define DEBUG false

inline bool NOT(const bool s, const bool dup = 0) { return ~s; }
inline bool AND(const bool s1, const bool s2) { return s1 & s2; }
inline bool OR(const bool s1, const bool s2) { return s1 | s2; }
inline bool XOR(const bool s1, const bool s2) { return s1 ^ s2; }
inline bool NAND(const bool s1, const bool s2) { return ~(s1 & s2); }
inline bool NOR(const bool s1, const bool s2) { return ~(s1 | s2); }

const std::string strNOT("NOT"), strAND("AND"), strOR("OR"), strXOR("XOR"),
    strNAND("NAND"), strNOR("NOR");
const std::unordered_map<std::string, std::function<bool(bool, bool)>>
    jumpTable{
        {strAND, std::function<bool(bool, bool)>(AND)},
        {strOR, std::function<bool(bool, bool)>(OR)},
        {strXOR, std::function<bool(bool, bool)>(XOR)},
        {strNAND, std::function<bool(bool, bool)>(NAND)},
        {strNOR, std::function<bool(bool, bool)>(NOR)},
    };

struct operation {
  int programCounter;
  std::string operationCode;
  std::vector<std::string> sources;

  explicit operation(int programCounter, std::string operationCode,
                     const int sourceCount)
      : programCounter(programCounter),
        operationCode(std::move(operationCode)) {
    sources.resize(sourceCount);
    for (std::string &source : sources) {
      (cin >> source).get();
    }
  }
};

void execute(std::vector<bool> &outputs, const operation &op,
             const std::vector<bool> &srcInputs) {
  // decode
  const std::string &opCode = op.operationCode;
  std::vector<bool> tempInputs;
  // decode specific input (either from I and O)
  auto decode = [&](const std::string &source) {
    if (source.front() == 'I') {
      tempInputs.push_back(srcInputs[source.back() - '0' - 1]);
      return;
    }
    // else front == 'O'
    tempInputs.push_back(outputs[source.back() - '0' - 1]);
    return;
  };

  // assume two inputs
  if (opCode == strNOT) {
    // doing NOT
    decode(op.sources.front());
    outputs[op.programCounter] =
        jumpTable.find(opCode)->second(tempInputs.front(), 0);
    return;
  }
  // doing other instructions
  decode(op.sources.front());
  decode(op.sources.back());
  outputs[op.programCounter] =
      jumpTable.find(opCode)->second(tempInputs.front(), tempInputs.back());
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);
  cin.tie(0);

  int qQuestions;
  (cin >> qQuestions).get();
  for (int i = 0; i < qQuestions; i++) {
    int mInputs, nOperations;
    cin >> mInputs >> nOperations;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // operations, vary by questions
    std::vector<operation> operations;
    operations.reserve(nOperations);
    for (int j = 0; j < nOperations; j++) {
      std::string opCode;
      int sourceCount;
      cin >> opCode >> sourceCount;
      operations.push_back(operation(j, opCode, sourceCount));
    }

#if DEBUG
    for (const auto &op : operations) {
      cout << op.operationCode << ' ' << op.programCounter << ' ';
      for (const auto &in : op.sources) {
        cout << in << ' ';
      }
      cout << std::endl;
    }
#endif

    int sTimes;
    (cin >> sTimes).get();

    // inputs, outputs, vary by cycle time
    std::vector<std::vector<bool>> inputVals(sTimes);
    std::vector<std::vector<bool>> outputVals(sTimes);
    for (int j = 0; j < sTimes; j++) {
      inputVals[j].reserve(mInputs);
      for (int k = 0; k < mInputs; k++) {
        bool inputTemp;
        (cin >> inputTemp).get();
        inputVals[j].push_back(inputTemp);
      }
      outputVals[j].resize(nOperations);
      for (const auto &op : operations) {
        execute(outputVals[j], op, inputVals[j]);
      }
#if DEBUG
      int count = 0;
      for (const bool result : outputVals[j]) {
        cout << count << ": " << result << ' ';
        count++;
      }
      cout << std::endl;
#endif
    }
    for (int j = 0; j < sTimes; j++) {
      // print the result based on istream
      int nResultToPrint;
      (cin >> nResultToPrint).get();
      for (int k = 0; k < nResultToPrint; k++) {
        int outputIndex;
        (cin >> outputIndex).get();
        cout << outputVals[j][--outputIndex] << ' ';
      }
      cout << std::endl;
    }
  }

  return 0;
}