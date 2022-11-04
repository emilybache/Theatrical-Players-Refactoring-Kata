#include "statement.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *statement(struct Invoice *invoice, struct Play **plays) {
    return "statement";
}

struct Invoice *Invoice_create(char* customer, struct Performance** performances) {
    struct Invoice* invoice = malloc(sizeof(struct Invoice));
    strncpy(invoice->customer, customer, sizeof(invoice->customer) - 1);
    memcpy(invoice->performances, performances, sizeof(invoice->performances));

    return invoice;
}

struct Play *Play_create(char* playID, char *name, char *type) {
    struct Play* play = malloc(sizeof(struct Play));
    strncpy(play->playID, playID, sizeof(play->playID) - 1);
    strncpy(play->name, name, sizeof(play->name) - 1);
    strncpy(play->type, type, sizeof(play->type) - 1);
    return play;
}

struct Performance *Performance_create(char *playID, int audience) {
    struct Performance* performance = malloc(sizeof(struct Performance));
    strncpy(performance->playID, playID, sizeof(performance->playID) - 1);
    performance->audience = audience;
    return performance;
}

