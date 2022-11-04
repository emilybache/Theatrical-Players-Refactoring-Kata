#ifndef THEATRICALPLAYERS_STATEMENT_H
#define THEATRICALPLAYERS_STATEMENT_H

#define MAX_NAME_LENGTH 120
#define MAX_TYPE_LENGTH 80
#define MAX_PERFORMANCES_PER_YEAR 365

struct Play {
    char playID[MAX_NAME_LENGTH];
    char name[MAX_NAME_LENGTH];
    char type[MAX_TYPE_LENGTH];
};
struct Play* Play_create(char* playID, char* name, char* type);

struct Performance {
    char playID[MAX_NAME_LENGTH];
    int audience;
};
struct Performance* Performance_create(char* playID, int audience);

struct Invoice {
    char customer[MAX_NAME_LENGTH];
    struct Performance* performances[MAX_PERFORMANCES_PER_YEAR];
};
struct Invoice* Invoice_create(char* customer, struct Performance** performances);

void statement(char* result, struct Invoice* invoice, int numberOfPerformances, struct Play **plays, int numberOfPlays);

#endif //THEATRICALPLAYERS_STATEMENT_H
