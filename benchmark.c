#include "benchmark.h"

void benchmarkTableInsertion(Table *table, int numberOfInsertions) {
  clock_t start, end;
  double time_taken;

  start = clock();
  for (int i = 0; i < numberOfInsertions; ++i) {
    // generate a key
    char key[50];
    sprintf(key, "key%d", i);

    ObjString *keyString = copyString(key, strlen(key));

    Value value = NUMBER_VAL(i);
    tableSet(table, keyString, value);
  }

  end = clock();
  time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Insertion of %d elements took %f seconds\n", numberOfInsertions,
         time_taken);

  // insertion of already existing keys
  start = clock();
  for (int i = 0; i < numberOfInsertions; ++i) {
    // generate a key
    char key[50];
    sprintf(key, "key%d", i);

    ObjString *keyString = copyString(key, strlen(key));

    Value value = NUMBER_VAL(i);
    tableSet(table, keyString, value);
  }

  end = clock();
  time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Insertion of %d already existing elements took %f seconds\n",
         numberOfInsertions, time_taken);
}

void benchmarkTableRetrieval(Table *table, int numberOfRetrievals) {
  clock_t start, end;
  double time_taken;

  // populate the table
  for (int i = 0; i < numberOfRetrievals; ++i) {
    char key[50];
    sprintf(key, "key%d", i);

    ObjString *keyString = copyString(key, strlen(key));

    Value value = NUMBER_VAL(i);
    tableSet(table, keyString, value);
  }

  // benchmark successful retrievals
  start = clock();
  for (int i = 0; i < numberOfRetrievals; ++i) {
    char key[50];
    sprintf(key, "key%d", i);

    ObjString *keyString = copyString(key, strlen(key));

    Value value = NUMBER_VAL(i);
    tableGet(table, keyString, &value);
  }
  end = clock();
  time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Retrieval of %d existing keys took %f seconds\n", numberOfRetrievals,
         time_taken);

  // benchmark failed retrievals
  start = clock();
  for (int i = 0; i < numberOfRetrievals; ++i) {
    char key[50];
    sprintf(key, "nonexistent%d", i);

    ObjString *keyString = copyString(key, strlen(key));

    Value value = NUMBER_VAL(i);
    tableGet(table, keyString, &value);
  }
  end = clock();
  time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Retrieval of %d non-existent keys took %f seconds\n",
         numberOfRetrievals, time_taken);
}

void benchmarkTableDeletion(Table *table, int numberOfDeletions) {
  clock_t start, end;
  double time_taken;

  // deleting non-existent keys
  start = clock();
  for (int i = 0; i < numberOfDeletions; ++i) {
    char key[50];
    sprintf(key, "key%d", i);

    ObjString *keyString = copyString(key, strlen(key));
    tableDelete(table, keyString);
  }
  end = clock();
  time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Deletions of %d non-existent keys took %f seconds\n",
         numberOfDeletions, time_taken);

  // populate the table
  for (int i = 0; i < numberOfDeletions; ++i) {
    char key[50];
    sprintf(key, "key%d", i);

    ObjString *keyString = copyString(key, strlen(key));

    Value value = NUMBER_VAL(i);
    tableSet(table, keyString, value);
  }

  // deleting existing keys
  start = clock();
  for (int i = 0; i < numberOfDeletions; ++i) {
    char key[50];
    sprintf(key, "key%d", i);

    ObjString *keyString = copyString(key, strlen(key));
    tableDelete(table, keyString);
  }
  end = clock();
  time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Deletions of %d existing keys took %f seconds\n", numberOfDeletions,
         time_taken);
}

void benchmarkTableCopy(Table *from, Table *to, int numberOfCopies) {
  clock_t start, end;
  double time_taken;

  // populate the first table
  for (int i = 0; i < numberOfCopies; ++i) {
    char key[50];
    sprintf(key, "key%d", i);

    ObjString *keyString = copyString(key, strlen(key));

    Value value = NUMBER_VAL(i);
    tableSet(from, keyString, value);
  }

  start = clock();
  for (int i = 0; i < numberOfCopies; ++i) {
    tableAddAll(from, to);
  }
  end = clock();
  time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Copying one table %d times took %f seconds\n", numberOfCopies,
         time_taken);
}
