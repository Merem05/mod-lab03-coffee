// Copyright 2020 GHA Test Team

#include <gtest/gtest.h>

#include "../include/Automata.h"

TEST(AutomataTest, InitialState) {
  Automata a;
  EXPECT_EQ(a.getState(), OFF);
  EXPECT_EQ(a.getCash(), 0);
  EXPECT_EQ(a.getChosenDrink(), -1);
}

TEST(AutomataTest, TurnOn) {
  Automata a;
  a.on();
  EXPECT_EQ(a.getState(), WAIT);
}

TEST(AutomataTest, TurnOffNoMoney) {
  Automata a;
  a.on();
  a.off();
  EXPECT_EQ(a.getState(), OFF);
  EXPECT_EQ(a.getCash(), 0);
}

TEST(AutomataTest, Coin) {
  Automata a;
  a.on();
  a.coin(100);
  EXPECT_EQ(a.getState(), ACCEPT);
  EXPECT_EQ(a.getCash(), 100);
}

TEST(AutomataTest, Choice) {
  Automata a;
  a.on();
  a.coin(100);
  a.choice(1);
  EXPECT_EQ(a.getState(), CHECK);
  EXPECT_EQ(a.getChosenDrink(), 0);
}

TEST(AutomataTest, CheckSuccess) {
  Automata a;
  a.on();
  a.coin(100);
  a.choice(1);
  bool result = a.check();
  EXPECT_TRUE(result);
}

TEST(AutomataTest, CheckFail) {
  Automata a;
  a.on();
  a.coin(20);
  a.choice(1);
  bool result = a.check();
  EXPECT_FALSE(result);
  EXPECT_EQ(a.getState(), ACCEPT);
}

TEST(AutomataTest, Cancel) {
  Automata a;
  a.on();
  a.coin(100);
  a.choice(1);
  a.cancel();
  EXPECT_EQ(a.getState(), WAIT);
  EXPECT_EQ(a.getCash(), 0);
  EXPECT_EQ(a.getChosenDrink(), -1);
}

TEST(AutomataTest, Cook) {
  Automata a;
  a.on();
  a.coin(100);
  a.choice(1);
  a.check();
  a.cook();
  EXPECT_EQ(a.getState(), WAIT);
  EXPECT_EQ(a.getCash(), 0);
}

TEST(AutomataTest, ExactAmount) {
  Automata a;
  a.on();
  a.coin(50);
  a.choice(1);
  a.check();
  a.cook();
  EXPECT_EQ(a.getCash(), 0);
}

TEST(AutomataTest, TurnOffWithMoney) {
  Automata a;
  a.on();
  a.coin(50);
  a.off();
  EXPECT_EQ(a.getState(), OFF);
  EXPECT_EQ(a.getCash(), 0);
}

TEST(AutomataTest, InvalidChoice) {
  Automata a;
  a.on();
  a.coin(100);
  a.choice(10);
  EXPECT_EQ(a.getState(), ACCEPT);
  EXPECT_EQ(a.getChosenDrink(), -1);
}

TEST(AutomataTest, MultipleCoins) {
  Automata a;
  a.on();
  a.coin(30);
  a.coin(20);
  EXPECT_EQ(a.getCash(), 50);
}

TEST(AutomataTest, ChoiceWithoutMoney) {
  Automata a;
  a.on();
  a.choice(1);
  EXPECT_EQ(a.getState(), WAIT);
  EXPECT_EQ(a.getChosenDrink(), -1);
}

TEST(AutomataTest, CookWithoutChoice) {
  Automata a;
  a.on();
  a.coin(100);
  a.cook();
  EXPECT_EQ(a.getState(), ACCEPT);
  EXPECT_EQ(a.getCash(), 100);
}
