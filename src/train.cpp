// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : first(nullptr), countOp(0) {}

Train::~Train() {
  if (!first) return;
  Car* current = first;
  do {
    Car* temp = current;
    current = current->next;
    delete temp;
  } while (current != first);
}

int Train::getOpCount() {
  return countOp;
}

void Train::addCar(bool light) {
  Car* newCar = new Car{light, nullptr, nullptr};
  if (!first) {
    first = newCar;
    first->next = first;
    first->prev = first;
    return;
  }
  Car* last = first->prev;
  newCar->next = first;
  newCar->prev = last;
  last->next = newCar;
  first->prev = newCar;
}

int Train::getLength() {
  countOp = 0;
  Car* current = first;
  current->light = true;

  while (true) {
    int steps = 0;
    do {
      current = current->next;
      countOp++;
      steps++;
    } while (!current->light);

    current->light = false;

    for (int i = 0; i < steps; i++) {
      current = current->prev;
      countOp++;
    }

    if (!current->light) {
      return steps;
    }
  }
}
