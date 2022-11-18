#include "statement.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define the_max(x, y) (((x) >= (y)) ? (x) : (y))

int statement(char *result, struct Invoice *invoice, int numberOfPerformances,
              struct Play **plays, int numberOfPlays) {
    float total_amount = 0;
    int volume_credits = 0;
    float this_amount = 0;
    struct Play *play;

    sprintf(result, "Statement for %s\n", invoice->customer);

    for (int i = 0; i < numberOfPerformances; i++) {
        this_amount = 0;
        for (int j = 0; j < numberOfPlays; j++) {
            if (strcmp(plays[j]->playID, invoice->performances[i]->playID) == 0) {
                play = plays[j];
            }
        }
        if (strcmp(play->type, "tragedy") == 0) {
            this_amount = 40000;
            if (invoice->performances[i]->audience > 30) {
                this_amount += 1000 * (invoice->performances[i]->audience - 30);
            }
        } else if (strcmp(play->type, "comedy") == 0) {
            this_amount = 30000;
            if (invoice->performances[i]->audience > 20) {
                this_amount += 10000 + 500 * (invoice->performances[i]->audience - 20);
            }

            this_amount += 300 * invoice->performances[i]->audience;
        } else {
            sprintf(result, "ERROR: unknown play type %s\n", play->type);
            printf("ERROR: unknown play type %s", play->type);
            return UNKNOWN_PLAY_TYPE;
        }

        // add volume credits
        volume_credits += the_max(invoice->performances[i]->audience - 30, 0);

        // add extra credit for every ten comedy attendees
        if (strcmp(play->type, "comedy") == 0) {
            volume_credits += invoice->performances[i]->audience / 5;
        }

        // print line for this order
        sprintf(result, "%s %s: $%s (%d seats)\n", result, play->name,
                format_currency_number(this_amount / 100),
                invoice->performances[i]->audience);
        total_amount += this_amount;
    }

    sprintf(result, "%sAmount owed is $%s\n", result,
            format_currency_number(total_amount / 100));
    sprintf(result, "%sYou earned %d credits", result, volume_credits);
    return NO_ERROR;
}

struct Invoice *Invoice_create(char *customer, struct Performance **performances) {
    struct Invoice *invoice = malloc(sizeof(struct Invoice));
    strncpy(invoice->customer, customer, sizeof(invoice->customer) - 1);
    memcpy(invoice->performances, performances, sizeof(invoice->performances));

    return invoice;
}

struct Play *Play_create(char *playID, char *name, char *type) {
    struct Play *play = malloc(sizeof(struct Play));
    strncpy(play->playID, playID, sizeof(play->playID) - 1);
    strncpy(play->name, name, sizeof(play->name) - 1);
    strncpy(play->type, type, sizeof(play->type) - 1);
    return play;
}

struct Performance *Performance_create(char *playID, int audience) {
    struct Performance *performance = malloc(sizeof(struct Performance));
    strncpy(performance->playID, playID, sizeof(performance->playID) - 1);
    performance->audience = audience;
    return performance;
}

void commafy(char *buffer, double n) {
    if (n < 1000) {
        sprintf(buffer, "%.2f", n);
        return;
    }

    long floor = (long) n;
    double smallest_part = (n - (double) floor) + (double) (floor % 1000);

    if (n < 1000 * 1000) {
        long d = floor / 1000;
        sprintf(buffer, "%ld,%06.2f", d, smallest_part);
    } else if (n < 1000 * 1000 * 1000) {
        long d1 = floor / (1000 * 1000);
        long d2 = (floor / 1000) % 1000;
        sprintf(buffer, "%ld,%03ld,%06.2f", d1, d2, smallest_part);
    }
}

char *format_currency_number(double number) {
    static char buffer[200];
    commafy(buffer, number);

    return buffer;
}
