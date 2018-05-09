void testTreeSearch(int treeSize, int numTest) {
  TreeAVL<int, DNI> tree;
  vector<DNI> vec(treeSize);

  for (int i = 0; i < treeSize; i++) {
    tree.insert(0, vec[i]);
  }

  for (int i = 0; i < numTest; i++) {
    DNI::counter.start();
    tree.search(vec[rand() % treeSize]);
    DNI::counter.stop();
  }
  cout << DNI::counter.getMin() << " "
       << DNI::counter.getAccum()/numTest << " "
       << DNI::counter.getMax() << endl;
  DNI::counter.reset();
}

void testTreeInsertion(int treeSize, int numTest) {
  TreeAVL<int, DNI> tree;
  vector<DNI> vec(2*treeSize);

  for (int i = 0; i < treeSize; i++) {
    tree.insert(0, vec[i]);
  }

  for (int i = 0; i < numTest; i++) {
    DNI::counter.start();
    tree.search(vec[treeSize + rand() % treeSize]);
    DNI::counter.stop();
  }
  cout << DNI::counter.getMin() << " "
       << DNI::counter.getAccum()/numTest << " "
       << DNI::counter.getMax() << endl;
  DNI::counter.reset();
}


void testBench(int numTest) {
  cout << "TreeAVL numero de pruebas " << numTest << endl;
  cout << "busqueda" << endl;
  for (int i : {10,25,50,75,100,125,150,175,200,250,300}) {
    cout << i << " ";
    testTreeSearch(i, numTest);
  }
  cout << "insercion" << endl;
  for (int i : {10,25,50,75,100,125,150,175,200,250,300}) {
    cout << i << " ";
    testTreeInsertion(i, numTest);
  }
}
