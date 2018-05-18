#include "NodeAVL.hpp"
#include "Queue.hpp"


template <class D, class K>
class TreeAVL
{
private:
  NodeAVL<D,K> * root;
  void rotationII(NodeAVL<D,K> *& nodo);
  void rotationDD(NodeAVL<D,K> *& nodo);
  void rotationID(NodeAVL<D,K> *& nodo);
  void rotationDI(NodeAVL<D,K> *& nodo);

  bool searchNode(NodeAVL<D,K> *& node, const K& clave);
  NodeAVL<D,K> getNode(NodeAVL<D,K> *& node, const K& clave);
  void insertar(NodeAVL<D,K> *& nodo, NodeAVL<D,K> *& nuevo, bool & bGrow);

  void deleteTree(NodeAVL<D,K> *& node);
  void insertarRebalanceaIzq(NodeAVL<D,K> *& nodo, bool &crece);
  void insertarRebalanceaDch(NodeAVL<D,K> *& nodo, bool &crece);
  void eliminarRama(NodeAVL<D,K> *& nodo, K clave, bool& crece);
  void sustituye(NodeAVL<D,K> *& eliminado, NodeAVL<D,K> *& sust, bool& decrece);
  void eliminarRebalanceaIzq(NodeAVL<D,K> *& nodo, bool &unGrow);
  void eliminarRebalanceaDch(NodeAVL<D,K> *& nodo, bool &unGrow);
public:
  TreeAVL();
  virtual ~TreeAVL();
  bool search(K clave);
  void insert(D data, K key);
  void byLevels();
  void eliminar(K clave);

};

template <class D, class K>
void TreeAVL<D, K>::rotationII(NodeAVL<D,K> *& nodo) {
  NodeAVL<D, K> * nodo1 = nodo->left();
  nodo->left(nodo1->right());
  nodo1->right(nodo);
  if (nodo1->balance() == 1) {
    nodo->balance(0);
    nodo1->balance(0);
  }
  else { // nodo1->bal == 0
    nodo->balance(1);
    nodo1->balance(-1);
  }
  nodo = nodo1;
}

template <class D, class K>
void TreeAVL<D, K>::rotationDD(NodeAVL<D,K> *& nodo) {
  NodeAVL<D, K> * nodo1 = nodo->right();
  nodo->right(nodo1->left());
  nodo1->left(nodo);
  if (nodo1->balance() == -1) {
    nodo->balance(0);
    nodo1->balance(0);
  }
 else { // nodo1->bal == 0
   nodo->balance(-1);
   nodo1->balance(1);
 }
  nodo = nodo1;
}

template <class D, class K>
void TreeAVL<D, K>::rotationDI(NodeAVL<D,K> *& nodo) {
  NodeAVL<D,K> * nodo1 = nodo->right();
  NodeAVL<D,K> * nodo2 = nodo1->left();
  nodo->right(nodo2->left());
  nodo2->left(nodo);
  nodo1->left(nodo2->right());
  nodo2->right(nodo1);
  if (nodo2->balance() == 1)
    nodo1->balance(-1);
  else nodo1->balance(0);
  if (nodo2->balance() == -1)
    nodo->balance(1);
  else nodo->balance(0);
  nodo2->balance(0);
  nodo = nodo2;
}

template <class D, class K>
void TreeAVL<D, K>::rotationID(NodeAVL<D,K> *& nodo) {
  NodeAVL<D,K> * nodo1 = nodo->left();
  NodeAVL<D,K> * nodo2 = nodo1->right();
  nodo->left(nodo2->right());
  nodo2->right(nodo);
  nodo1->right(nodo2->left());
  nodo2->left(nodo1);
  if (nodo2->balance() == -1)
    nodo1->balance(1);
  else nodo1->balance(0);
  if (nodo2->balance() == 1)
    nodo->balance(-1);
  else nodo->balance(0);
  nodo2->balance(0);
  nodo = nodo2;
}

template <class D, class K>
void TreeAVL<D,K>::insertarRebalanceaIzq(NodeAVL<D,K> *& nodo, bool &crece) {
  switch (nodo->balance()) {
  case -1:
    nodo->balance(0);
    crece = false;
    break;
  case 0:
    nodo->balance(1);
    break;
  case 1:
    if (nodo->left()->balance() == 1)
      rotationII(nodo);
    else rotationID(nodo);
    crece = false;
    break;
  default:  
  	break;
  }
}

template <class D, class K>
void TreeAVL<D,K>::insertarRebalanceaDch(NodeAVL<D,K> *& nodo, bool &crece) {
  switch (nodo->balance()) {
  case 1:
    nodo->balance(0);
    crece = false;
    break;
  case 0:
    nodo->balance(-1);
    break;
  case -1:
    if (nodo->right()->balance() == -1)
      rotationDD(nodo);
    else rotationDI(nodo);
    crece = false;
    break;
  default:  
  	break;  
  }
}

template <class D, class K>
void TreeAVL<D,K>::insertar(NodeAVL<D,K> *& nodo, NodeAVL<D,K> *& toInsert, bool &crece) {
 if (nodo == nullptr) {
   nodo = toInsert;
   crece = true;
 }
 else if (toInsert->key() < nodo->key()) {
   insertar(nodo->left(),toInsert,crece);
   if (crece) insertarRebalanceaIzq(nodo, crece);
 }
 else {
   insertar(nodo->right(),toInsert,crece);
   if (crece) insertarRebalanceaDch(nodo, crece);
 }
}

template <class D, class K>
void TreeAVL<D,K>::insert(D data, K key) {
  NodeAVL<D,K> * toInsert = new NodeAVL<D,K>(data, key);
  bool bGrow = false;
  if (search(key) == false){//no permite elementos repetidos
    insertar(root, toInsert, bGrow);
  }
}


template <class D, class K>
void TreeAVL<D,K>::eliminar(K clave) {
  bool unGrow = false;
  eliminarRama(root,clave, unGrow);
}

template <class D, class K>
void TreeAVL<D,K>::eliminarRama(NodeAVL<D,K> *& nodo, K clave, bool & unGrow) {
  if (nodo == nullptr)
    return;
  if (clave < nodo->key()) {
    eliminarRama(nodo->left(), clave, unGrow);
    if (unGrow)
      eliminarRebalanceaIzq(nodo, unGrow);
  }
  else if (clave > nodo->key()) {
    eliminarRama(nodo->right(), clave, unGrow);
    if (unGrow)
      eliminarRebalanceaDch(nodo, unGrow);
  }
  else {
    NodeAVL<D,K> * eliminado = nodo;
    if (nodo->left()==nullptr) {
      nodo = nodo->right();
      unGrow = true;
    }
    else if (nodo->right() == nullptr){
      nodo = nodo->left();
      unGrow = true;
    }
    else {
      sustituye(eliminado, nodo->left(),unGrow);
      if (unGrow)
        eliminarRebalanceaIzq(nodo,unGrow);
    }
    delete eliminado;
    eliminado = nullptr;
  }
}

template <class D, class K>
void TreeAVL<D,K>::sustituye(NodeAVL<D,K> *& eliminado, NodeAVL<D,K> *& sust, bool &unGrow) {
  if (sust->right() != nullptr) {
    sustituye(eliminado, sust->right(), unGrow);
    if (unGrow)
      eliminarRebalanceaDch(sust, unGrow);
  }
  else {
    eliminado->data(sust->data());
    eliminado->key(sust->key());
    eliminado = sust;
    sust = sust->left();
    unGrow = true;
  }
}

template <class D, class K>
void TreeAVL<D,K>::eliminarRebalanceaDch(NodeAVL<D,K> *& nodo, bool &unGrow) {
  switch (nodo->balance()) {
  case 1:
    if (nodo->left()->balance() > 0) {
      rotationID(nodo);
    }
    else if (nodo->left()->balance() == 0) {
      unGrow = false;
      rotationII(nodo);
    }
    break;
  case 0:
    nodo->balance(1);
    unGrow = false;
    break;
  case -1:
    nodo->balance(0);
    break;
  default:  
  	break;  
  }
}

template <class D, class K>
void TreeAVL<D,K>::eliminarRebalanceaIzq(NodeAVL<D,K> *& nodo, bool &unGrow) {
  switch (nodo->balance()) {
  case -1:
    if (nodo->right()->balance() < 0)
      rotationDI(nodo);
    else { if (nodo->right()->balance() == 0)
        unGrow = false;
      rotationDD(nodo);
    }
    break;
  case 0:
    nodo->balance(-1);
    unGrow = false;
    break;
  case 1:
    nodo->balance(0);
    break;
  default:  
  	break;  
  }
}


template <class D, class K>
void TreeAVL<D,K>::byLevels() {
  Queue<NodeAVL<D,K> *> parents;
  Queue<NodeAVL<D,K> *> childrens;
  auto addToChildrens = [&childrens](NodeAVL<D,K> * node){
    if (node!= nullptr) {
      childrens.cons(node->left());
      childrens.cons(node->right());
    }
  };
  parents.cons(root);
  int level = 0;

  while (!parents.isEmpty()) {
    cout << "Nivel " << level << ":";
    while (!parents.isEmpty()) {
      NodeAVL<D,K> * aux = parents.pop();
      if (aux != nullptr) {
            cout << "[" << aux->key() << "]";
      }
      else
        cout << "[.]";

      addToChildrens(aux);
    }
    cout << endl;
    level++;
    swap(parents, childrens);
  }
}

template <class D, class K>
TreeAVL<D,K>::TreeAVL(void):
  root(nullptr) {}

template <class D, class K>
TreeAVL<D,K>::~TreeAVL(void) {
  deleteTree(root);
}

template <class D, class K>
void TreeAVL<D,K>::deleteTree(NodeAVL<D,K> *& node) {
  if (node != nullptr) {
    deleteTree(node->left());
    deleteTree(node->right());
    delete node;
    node = nullptr;
  }
}

template <class D, class K>
bool TreeAVL<D,K>::searchNode(NodeAVL<D,K> *& node, const K& clave) {
  if (node == nullptr)
    return false;
  if (node->key() == clave)
    return true;
  if (node->key() > clave) // Left branch
    return searchNode(node->left(), clave);
  else
    return searchNode(node->right(), clave);
}

template <class D, class K>
NodeAVL<D,K> TreeAVL<D,K>::getNode(NodeAVL<D,K> *& node, const K& clave) {
  if (node->key() == clave)
    return *node;
  if (node->key() > clave) // Left branch
    return getNode(node->left(), clave);
  else
    return getNode(node->right(), clave);
}


template <class D, class K>
bool TreeAVL<D,K>::search(K clave) {
  return searchNode(root, clave);
}


