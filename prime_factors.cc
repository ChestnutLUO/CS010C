#include <iostream>
#include <string>
#include "multiset.h"

bool ParseIntStrict(const std::string& text, int* value) {
  try {
    std::size_t pos = 0;
    int parsed = std::stoi(text, &pos);
    if (pos != text.size()) {
      return false;
    }
    *value = parsed;
    return true;
  } catch (const std::exception&) {
    return false;
  }
}

bool ParseUnsignedIntStrict(const std::string& text, unsigned int* value) {
  try {
    std::size_t pos = 0;
    long long parsed = std::stoll(text, &pos);
    if (pos != text.size() || parsed < 0) {
      return false;
    }
    *value = static_cast<unsigned int>(parsed);
    return true;
  } catch (const std::exception&) {
    return false;
  }
}

void ComputePrimeFactors(unsigned int n, Multiset<int>& factors) {
  while (n % 2 == 0) {
    factors.Insert(2);
    n /= 2;
  }

  for (unsigned int i = 3; i * i <= n; i += 2) {
    while (n % i == 0) {
      factors.Insert(i);
      n /= i;
    }
  }

  if (n > 1) {
    factors.Insert(n);
  }
}

bool IsPrime(unsigned int n) {
  if (n <= 1) return false;
  if (n <= 3) return true;
  if (n % 2 == 0 || n % 3 == 0) return false;
  for (unsigned int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) return false;
  }
  return true;
}

void PrintAll(const Multiset<int>& factors_const) {
  Multiset<int> factors = factors_const;
  if (factors.Empty()) {
    std::cout << "No prime factors" << std::endl;
    return;
  }

  int current = factors.Min();

  while (!factors.Empty()) {
    int count = factors.Count(current);
    std::cout << current << " (x" << count << ")";
    
    for (int i = 0; i < count; i++) {
      factors.Remove(current);
    }
    
    if (!factors.Empty()) {
      std::cout << ", ";
      current = factors.Min();
    }
  }
  std::cout << "," << std::endl;
}

void PrintMin(const Multiset<int>& factors) {
  if (factors.Empty()) {
    std::cout << "No prime factors" << std::endl;
    return;
  }
  int min_val = factors.Min();
  std::cout << min_val << " (x" << factors.Count(min_val) << ")" << std::endl;
}

void PrintMax(const Multiset<int>& factors) {
  if (factors.Empty()) {
    std::cout << "No prime factors" << std::endl;
    return;
  }
  int max_val = factors.Max();
  std::cout << max_val << " (x" << factors.Count(max_val) << ")" << std::endl;
}

void PrintNear(const Multiset<int>& factors, const std::string& arg) {
  if (factors.Empty()) {
    std::cout << "No prime factors" << std::endl;
    return;
  }

  if (arg.empty()) {
    std::cerr << "Command 'near' expects another argument: [+/-]prime" << std::endl;
    exit(1);
  }

  int prime;
  if (arg[0] == '+') {
    if (!ParseIntStrict(arg.substr(1), &prime)) {
      std::cerr << "Invalid prime" << std::endl;
      exit(1);
    }
    try {
      int result = factors.Ceil(prime + 1);
      std::cout << result << " (x" << factors.Count(result) << ")" << std::endl;
    } catch (const std::exception&) {
      std::cout << "No match" << std::endl;
    }
  } else if (arg[0] == '-') {
    if (!ParseIntStrict(arg.substr(1), &prime)) {
      std::cerr << "Invalid prime" << std::endl;
      exit(1);
    }
    try {
      int result = factors.Floor(prime - 1);
      std::cout << result << " (x" << factors.Count(result) << ")" << std::endl;
    } catch (const std::exception&) {
      std::cout << "No match" << std::endl;
    }
  } else {
    if (!ParseIntStrict(arg, &prime)) {
      std::cerr << "Invalid prime" << std::endl;
      exit(1);
    }
    if (factors.Contains(prime)) {
      std::cout << prime << " (x" << factors.Count(prime) << ")" << std::endl;
    } else {
      std::cout << "No match" << std::endl;
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <number> <command> [<args>]" << std::endl;
    return 1;
  }

  unsigned int number;
  if (!ParseUnsignedIntStrict(argv[1], &number)) {
    std::cerr << "Invalid number" << std::endl;
    return 1;
  }

  std::string command = argv[2];

  if (IsPrime(number)) {
    std::cout << "No prime factors" << std::endl;
    return 0;
  }

  Multiset<int> factors;
  ComputePrimeFactors(number, factors);

  if (command == "all") {
    PrintAll(factors);
  } else if (command == "min") {
    PrintMin(factors);
  } else if (command == "max") {
    PrintMax(factors);
  } else if (command == "near") {
    std::string arg = (argc >= 4) ? argv[3] : "";
    PrintNear(factors, arg);
  } else {
    std::cerr << "Command '" << command << "' is invalid" << std::endl;
    std::cerr << "Possible commands are: all|min|max|near" << std::endl;
    return 1;
  }

  return 0;
}
