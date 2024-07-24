#include <Arduino.h>

#include "Cover.hpp"

Cover cover;

Cover::Cover() {}

void Cover::attachMotor(int motor_pos_pin, int motor_neg_pin, int on_time, int off_time) {
  this->pos_pin = motor_pos_pin;
  this->neg_pin = motor_neg_pin;
  this->on_time = on_time;
  this->off_time = off_time;
  
  // Initialize the GPIOs
  pinMode(pos_pin, OUTPUT);
  pinMode(neg_pin, OUTPUT);

  // Make sure the motor is off
  digitalWrite(pos_pin, LOW);
  digitalWrite(neg_pin, LOW);
}

void Cover::attachSwitch(int sw_pos_pin, int sw_neg_pin) {
  this->sw_pos_pin = sw_pos_pin;
  this->sw_neg_pin = sw_neg_pin;
  
  pinMode(sw_pos_pin, INPUT_PULLUP);
  pinMode(sw_neg_pin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(sw_pos_pin), Cover::ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(sw_neg_pin), Cover::ISR, CHANGE);
}

void Cover::ISR() {
  int p = !digitalRead(cover.sw_pos_pin);
  int n = !digitalRead(cover.sw_neg_pin);
  int v = p ? 1 : v ? -1 : 0;
  
  int t = millis();
  if (t - cover.last_edge_time > 10) {
    cover.hit_edge = v;
    
    // Stop immediately when the edge is hit
    cover.stop();
  }
  cover.last_edge_time = t;
}

void Cover::rotatePositive() {
  digitalWrite(neg_pin, LOW);
  digitalWrite(pos_pin, HIGH);
}

void Cover::rotateNegative() {
  digitalWrite(pos_pin, LOW);
  digitalWrite(neg_pin, HIGH);
}

void Cover::rotate(bool dir) {
  if (dir) rotatePositive(); else rotateNegative();
}

void Cover::stop() {
  digitalWrite(pos_pin, LOW);
  digitalWrite(neg_pin, LOW);
}

bool Cover::stepPositive(int steps) {
  if (!digitalRead(sw_pos_pin)) return true;
  while (steps --> 0) {
    rotatePositive();
    delay(on_time);
    stop();
    if (hit_edge == 1) {
      hit_edge = 0;      
      return true;
    }
    delay(off_time);
  }
  return false;
}

bool Cover::stepNegative(int steps) {
  if (!digitalRead(sw_neg_pin)) return true;
  while (steps --> 0) {
    rotateNegative();
    delay(on_time);
    stop();
    if (hit_edge == -1) {
      hit_edge = 0;
      return true;
    }
    delay(off_time);
  }
  return false;
}
