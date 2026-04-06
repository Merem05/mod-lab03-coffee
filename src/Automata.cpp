// Copyright 2020 GHA Test Team

#include "../include/Automata.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Automata::Automata() {
    cash = 0;
    state = OFF;
    chosenDrink = -1;
    menuSize = 5;
    menu[0] = "Латте";
    prices[0] = 50;
    menu[1] = "Чай";
    prices[1] = 30;
    menu[2] = "Какао";
    prices[2] = 45;
    menu[3] = "Капучино";
    prices[3] = 40;
    menu[4] = "Горячий шоколад";
    prices[4] = 60;
}

bool Automata::loadMenuFromFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) return false;
  std::string line;
  int count = 0;
  while (getline(file, line) && count < MAX_DRINKS) {
    std::stringstream ss(line);
    std::string name;
    int price;
    if (getline(ss, name, ',') && (ss >> price)) {
      menu[count] = name;
      prices[count] = price;
      count++;
    }
  }
  file.close();
  menuSize = count;
  return count > 0;
}

Automata::Automata(const std::string& filename) {
  cash = 0;
  state = OFF;
  chosenDrink = -1;
  menuSize = 0;
  if (!loadMenuFromFile(filename)) {
    menuSize = 5;
    menu[0] = "Кофе";
    prices[0] = 50;
    menu[1] = "Чай";
    prices[1] = 30;
    menu[2] = "Какао";
    prices[2] = 45;
    menu[3] = "Молоко";
    prices[3] = 40;
    menu[4] = "Горячий шоколад";
    prices[4] = 60;
  }
}

void Automata::on() {
  if (state == OFF) {
    state = WAIT;
    std::cout << "Автомат включен\n";
  }
}

void Automata::off() {
  if (state == WAIT || state == ACCEPT || state == CHECK) {
    if (cash > 0) {
      std::cout << "Возврат денег: " << cash << " руб.\n";
      cash = 0;
    }
    state = OFF;
    chosenDrink = -1;
    std::cout << "Автомат выключен\n";
  }
}

void Automata::coin(int money) {
  if ((state == WAIT || state == ACCEPT) && money > 0) {
    cash += money;
    state = ACCEPT;
    std::cout << "Внесено: " << money << " руб. Всего: "
              << cash << " руб.\n";
  }
}

void Automata::getMenu() {
  if (state != OFF) {
    std::cout << "Меню:\n";
    for (int i = 0; i < menuSize; i++) {
      std::cout << i + 1 << ". " << menu[i] << " - "
                << prices[i] << " руб.\n";
    }
  }
}

STATES Automata::getState() {
  return state;
}

void Automata::choice(int drink) {
  if (state == ACCEPT && drink >= 1 && drink <= menuSize) {
    chosenDrink = drink - 1;
    state = CHECK;
    std::cout << "Выбран: " << menu[chosenDrink] << "\n";
  }
}

bool Automata::check() {
  if (state == CHECK && chosenDrink != -1) {
    if (cash >= prices[chosenDrink]) {
      std::cout << "Денег достаточно\n";
      return true;
    } else {
      std::cout << "Не хватает " << prices[chosenDrink] - cash
                << " руб.\n";
      state = ACCEPT;
      return false;
    }
  }
  return false;
}

void Automata::cancel() {
  if (state == ACCEPT || state == CHECK) {
    if (cash > 0) {
      std::cout << "Возврат денег: " << cash << " руб.\n";
      cash = 0;
    }
    chosenDrink = -1;
    state = WAIT;
  }
}

void Automata::cook() {
  if (state == CHECK && chosenDrink != -1) {
    state = COOK;
    std::cout << "Приготовление " << menu[chosenDrink] << "...\n";
    std::cout << "Напиток готов\n";
    cash -= prices[chosenDrink];
    finish();
  }
}

void Automata::finish() {
  if (state == COOK) {
    if (cash > 0) {
      std::cout << "Сдача: " << cash << " руб.\n";
      cash = 0;
    }
    chosenDrink = -1;
    state = WAIT;
  }
}

int Automata::getCash() {
  return cash;
}

int Automata::getChosenDrink() const {
  return chosenDrink;
}

int Automata::getMenuSize() const {
  return menuSize;
}

int Automata::getPrice(int index) const {
  if (index >= 0 && index < menuSize) {
    return prices[index];
  }
  return -1;
}
