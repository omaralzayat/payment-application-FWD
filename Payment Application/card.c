#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include "card.h"

uint8_t temp[26];
uint8_t* tempptr = &temp;

extern ST_cardData_t cardData;
extern ST_cardData_t* cardDataptr;



EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("ENTER YOUR NAME: ");
	fgets(temp, sizeof(temp), stdin);
	if ((strlen(temp) > 25) || (strlen(temp) < 21) || !(strchr(temp, '\n')))
	{
		return WRONG_NAME;
	}
	else
	{
		char* token = strtok(temp, "\n");
		strcpy(cardData->cardHolderName, token);
		return OK;
	}
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("ENTER CARD EXPIRATION DATE(MM/YY): ");
	fgets(temp, sizeof(temp), stdin);
	int date[2] = { 0 };
	char ex ='\0';
	if ((strlen(temp) != 6) || (temp[2] != '/') || (sscanf(temp, "%d/%d%[^\n]", date, date + 1, &ex) != 2))
	{
		return WRONG_EXP_DATE;
	}
	else
	{
		char* token = strtok(temp, "\n");
		strcpy(cardData->cardExpirationDate, token);
		*tempptr = '\0';
		return OK;
	}
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("ENTER CARD PAN: ");
	fgets(temp, sizeof(temp), stdin);
	if ((strlen(temp) > 20) || (strlen(temp) < 17)) {
		return WRONG_PAN;
	}
	else
	{
		char* token = strtok(temp, "\n");
		strcpy(cardData->primaryAccountNumber, token);
		*tempptr = '\0';
		return OK;
	}
}