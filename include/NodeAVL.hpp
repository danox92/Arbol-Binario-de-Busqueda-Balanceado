#pragma once
#include <cmath>
#include <iostream>

using namespace std;

template <class D, class K>
class NodeAVL {
private:
  int bal_;
  D data_;
  K key_;
  NodeAVL<D,K> * left_;
  NodeAVL<D,K> * right_;

public:

  NodeAVL(D data, K key):
    bal_(0),
    data_(data),
    key_(key),
    left_(nullptr),
    right_(nullptr) {}

  virtual ~NodeAVL() {};

  int balance(void) const {
    return bal_;
  }

  void balance(int bal) {
    bal_ = bal;
  }

  D data(void) const {
    return data_;
  }

  void data(D data) {
    data_ = data;
  }

  K key(void) const {
    return key_;
  }

  void key(K key) {
    key_ = key;
  }

  NodeAVL<D,K> *& left(void) {
    return left_;
  }

  void left(NodeAVL<D,K> * n) {
      left_ = n;
  }

  NodeAVL<D,K> *& right(void) {
    return right_;
  }

  void right(NodeAVL<D,K> * n) {
      right_ = n;
  }

};
