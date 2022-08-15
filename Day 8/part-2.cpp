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
      std::cout << "nop " << sign << abs(instruction.arg);
      instruction_pointer++;
      break;
    case ACC:
      std::cout << "acc " << sign << abs(instruction.arg);
      acc += instruction.arg;
      instruction_pointer++;
      break;
    case JMP:
      std::cout << "jmp " << sign << abs(instruction.arg);
      instruction_pointer += instruction.arg;
      break;
    default:
      break;
  }
  std::cout <<  "\t\t| ip: " << instruction_pointer << "\t" <<  "acc: " << acc << std::endl;
}

bool execute_program(std::vector<instruction>& program) {
  int executed_instructions[700] = { -1 };
  while (instruction_pointer < program.size() && executed_instructions[instruction_pointer] < 2) {
    execute_instruction(program[instruction_pointer]);
    if (instruction_pointer == program.size()) {
      std::cout << "program terminated successfully" << std::endl;
      return true;
    }
    executed_instructions[instruction_pointer]++;
  }
  return false;
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

  for (auto i = 0; i < program.size(); i++) {
    std::vector<instruction> program_copy = program;
    instruction_pointer = 0;
    acc = 0;
    if (program_copy[i].instruction == NOP) {
      std::cout << "changing NOP " << program_copy[i].arg << " to JMP " << program_copy[i].arg << std::endl;
      program_copy[i].instruction = JMP;
    } else if (program_copy[i].instruction == JMP) {
      std::cout << "changing JMP " << program_copy[i].arg << " to NOP " << program_copy[i].arg << std::endl;
      program_copy[i].instruction = NOP;
    } else {
      continue;
    }
    bool terminated = execute_program(program_copy);
    if (terminated) {
      return acc;
    }
  }
  return -1;
}

int main() {
  std::ifstream file("input.txt", std::ios::in);
  std::cout << parse_file(file) << std::endl;
  file.close();
  return 0;
}
