#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <time.h>
#include "terminal.h"

extern ST_cardData_t cardData;
extern ST_cardData_t* cardDataptr;
extern ST_terminalData_t termData;
extern ST_terminalData_t* termDataptr;


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	time_t transtime = time(NULL);
	struct tm transdate = *localtime(&transtime);
	sprintf(termData->transactionDate, "%d/%d/%d", transdate.tm_mday, transdate.tm_mon + 1, transdate.tm_year + 1900);
	return OK_T;
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	int expiration[2];
	int transdate[2];
	char* token = strtok(termData.transactionDate, "/");
	token = strtok(NULL, "/");
	transdate[0] = atoi(token);
	token = strtok(NULL, "/");
	transdate[1] = atoi(token) % 100;
	token = strtok(cardData.cardExpirationDate, "/");
	expiration[0] = atoi(token);
	token = strtok(NULL, "/");
	expiration[1] = atoi(token);

	if (transdate[1] > expiration[1]) {
		return EXPIRED_CARD;
	}
	else if ((transdate[1] == expiration[1]) && (transdate[0] > expiration[0])) {
		return EXPIRED_CARD;
	}
	else
	{
		return OK_T;
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("ENTER TRAANSACTION AMOUNT: ");
	scanf("%f", &termData->transAmount);
	if (termData->transAmount <= 0) {
		return INVALID_AMOUNT;
	}
	else {
		return OK_T;
	}
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount) {
		return EXCEED_MAX_AMOUNT;
	}
	else {
		return OK_T;
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	printf("SET MAX TRANSACTION AMOUNT: ");
	scanf("%f", &termData->maxTransAmount);
	if (termData->maxTransAmount <= 0) {
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		return OK_T;
	}
}