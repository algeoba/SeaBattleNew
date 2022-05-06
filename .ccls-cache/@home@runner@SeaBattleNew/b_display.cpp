void b_display() {
  system("clear");
  cout << brdr << "|";
  for (y = 0; y < s; y++) {
    for (x = 0; x < s; x++) {
      cout << b[x][y] << "|";
    }
    (y < s - 1) ? cout << endl << brdr << "|" : cout << endl;
  }
  cout << brdr;
}