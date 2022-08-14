#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../string_utils.hpp"

int acc = 0;
int instruction_pointer = 0;

enum InstructionType {
  NOP,
  ACC,
  JMP
};

struct instruction {
  InstructionType instruction;
  int arg;
};

void execute_instruction(instruction& instruction) {
  char sign = instruction.arg >= 0 ? '+' : '-';
  switch (instruction.instruction) {
    case NOP:
      std::cout << "nop " << sign << abs(instruction.arg) << std::endl;
      instruction_pointer++;
      break;
    case ACC:
      std::cout << "acc " << sign << abs(instruction.arg) << std::endl;
      acc += instruction.arg;
      instruction_pointer++;
      break;
    case JMP:
      std::cout << "jmp " << sign << abs(instruction.arg) << std::endl;
      instruction_pointer += instruction.arg;
      break;
    default:
      break;
  }
  std::cout << "acc: " << acc << "\t" << "ip: " << instruction_pointer << std::endl;
}

void execute_program(std::vector<instruction>& program) {
  int executed_instructions[700] = { -1 };
  while (instruction_pointer < program.size() && executed_instructions[instruction_pointer] < 2) {
    execute_instruction(program[instruction_pointer]);
    executed_instructions[instruction_pointer]++;
  }
}

void parse_instruction(std::string& line, std::vector<instruction>& program) {
  std::vector<std::string> tokens = string_utils::split(line);
  std::string instruction_str = tokens[0];
  InstructionType instruction_type;
  if (instruction_str == "nop") {
    instruction_type = NOP;
  } else if (instruction_str == "acc") {
    instruction_type = ACC;
  } else if (instruction_str == "jmp") {
    instruction_type = JMP;
  } else {
    return;
  }
  program.push_back(instruction{instruction_type, std::stoi(tokens[1])});
}

int parse_file(std::ifstream& file) {
  std::vector<instruction> program;
  while (!file.eof()) {
    std::string line;
    std::getline(file, line);
    parse_instruction(line, program);
  }
  execute_program(program);
  return 0;
}

int main() {
  std::ifstream file("input.txt", std::ios::in);
  std::cout << parse_file(file) << std::endl;
  file.close();
  return 0;
}
