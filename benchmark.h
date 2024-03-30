#ifndef clox__benchmark_h
#define clox__benchmark_h

#include "object.h"
#include "table.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

void benchmarkTableInsertion(Table *table, int numberOfInsertions);
void benchmarkTableRetrieval(Table *table, int numberOfRetrievals);
void benchmarkTableDeletion(Table *table, int numberOfDeletions);
void benchmarkTableCopy(Table *from, Table *to, int numberOfCopies);

#endif
