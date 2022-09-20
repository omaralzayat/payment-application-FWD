#define _CRT_SECURE_NO_WARNINGS 1
#include <stdlib.h>
#include "server.h"
#include "app.h"

ST_cardData_t cardData;
ST_cardData_t* cardDataptr = &cardData;
ST_terminalData_t termData;
ST_terminalData_t* termDataptr = &termData;
ST_transaction_t transData;
ST_transaction_t* transDataptr = &transData;


void appStart(void)
{

	//CARD
	
	//Get Card holder informatiom
	if (getCardHolderName(cardDataptr)) {
		printf("\nINVALID USER NAME\n");
		system("pause");
		exit(0);
	}
	if (getCardExpiryDate(cardDataptr)) {
		printf("\nIVALID DATE\n");
		system("pause");
		exit(0);
	}
	if (getCardPAN(cardDataptr)) {
		printf("\nINVALID PAN\n");
		system("pause");
		exit(0);
	}

	//TERMINAL
	
	//Check expiration date
	getTransactionDate(termDataptr);
	if (isCardExpired(cardData, termData)) {
		printf("\nDeclined: expired card\n");
		system("pause");
		exit(0);
	}
	//Check if transaction amount is available in terminal
	if (setMaxAmount(termDataptr)) {
		printf("\nINVALID MAX AMOUNT\n");
		system("pause");
		exit(0);
	}
	if (getTransactionAmount(termDataptr)) {
		printf("\nINVALID TRANSACTION AMOUNT\n");
		system("pause");
		exit(0);
	}
	if (isBelowMaxAmount(termDataptr)) {
		printf("\nDeclined: Amount exceeding limit\n");
		system("pause");
		exit(0);
	}

	

	//SERVER
	
	transDataptr->cardHolderData = cardData;
	transDataptr->terminalData = termData;

	//Check if account is valid
	if (recieveTransactionData(transDataptr)) {
		system("pause");
		exit(0);
	}
	system("pause");
}