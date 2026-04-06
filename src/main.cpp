// Copyright 2020 GHA Test Team

#include <iostream>

#include "../include/Automata.h"

int main() {
  setlocale(LC_ALL, "Russian");
  std::cout << "ДЕМОНСТРАЦИЯ\n\n";
  std::cout << "Сц 1: Покупка кофе\n";
  Automata a1;
  a1.on();
  a1.getMenu();
  a1.coin(100);
  a1.choice(1);
  if (a1.check()) {
    a1.cook();
  }
  std::cout << "\n";
  std::cout << "Сц 2: Недостаточно средств\n";
  Automata a2;
  a2.on();
  a2.coin(20);
  a2.choice(1);
  if (!a2.check()) {
    a2.cancel();
  }
  std::cout << "\n";
  std::cout << "Сц 3: Точная сумма\n";
  Automata a3;
  a3.on();
  a3.coin(30);
  a3.choice(2);
  if (a3.check()) {
    a3.cook();
  }
  std::cout << "\n";
  std::cout << "Сц 4: Досрочное выключение\n";
  Automata a4;
  a4.on();
  a4.coin(50);
  a4.off();
  std::cout << "\n";
  return 0;
}
