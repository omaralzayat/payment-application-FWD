#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include "server.h"

extern ST_cardData_t cardData;
extern ST_cardData_t* cardDataptr;
extern ST_terminalData_t termData;
extern ST_terminalData_t* termDataptr;
extern ST_transaction_t transData;
extern ST_transaction_t* transDataptr;


ST_accountsDB_t AccountsDB[255] = { {23432, RUNNING, "4003830171874018"},
									{3453, RUNNING, "5496198584584769"},
									{563324, BLOCKED, "2223520043560014"},
									{485, BLOCKED, "3530111333300000"},
									{5239857, RUNNING, "69384295385194873"},
									{9320, BLOCKED, "9384293857394857382"},
};

ST_transaction_t transactionDB[255] = { 0 };
ST_accountsDB_t userAccount;
ST_accountsDB_t* userAccountptr = &userAccount;
uint8_t message[35];

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	transData->transState = APPROVED;
	strcpy(message, "Approved");

	if (isValidAccount(&transData->cardHolderData)) {
		if (isValidAccount(cardDataptr) == BLOCKED_ACCOUNT) {
			strcpy(message, "DECLINED: BLOCKED ACCOUNT");
			printf("\n%s\n", message);
			transData->transState = DECLINED_STOLEN_CARD;
			saveTransaction(transData);
			return DECLINED_STOLEN_CARD;
		}
		else
		{
			strcpy(message, "Declined: Invalid account");
			printf("\n%s\n", message);
			transData->transState = DECLINED_STOLEN_CARD;
			saveTransaction(transData);
			return FRAUD_CARD;
		}
	}
	else if (isAmountAvailable(&transData->terminalData)) {
		strcpy(message, "Declined: INSUFFECIENT FUND");
		printf("\n%s\n", message);
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		saveTransaction(transData);
		return DECLINED_INSUFFECIENT_FUND;
	}
	else if (saveTransaction(transData)) {
		strcpy(message, "INTERNAL SERVER ERROR");
		printf("\n%s\n", message);
		transData->transState = INTERNAL_SERVER_ERROR;
		return INTERNAL_SERVER_ERROR;
	}
	else {
		userAccountptr->balance -= transData->terminalData.transAmount;
		int j;
		for (j = 0; j < 255; j++) {
			if (strcmp(userAccountptr->primaryAccountNumber, AccountsDB[j].primaryAccountNumber) == 0) {
				AccountsDB[j] = *userAccountptr;
				break;
			}
		}
		printf("\nApproved: transaction saved\nYour balance is %f\n",userAccount.balance);
		return APPROVED;
	}
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	int i;
	for (i = 0; i < 255; i++) {
		if (strcmp(cardData->primaryAccountNumber, AccountsDB[i].primaryAccountNumber) == 0) {
			if (AccountsDB[i].state == RUNNING) {
				*userAccountptr = AccountsDB[i];
				return OK_S;
			}
			else
			{
				return BLOCKED_ACCOUNT;
			}
		}
	}
	return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if (termData->transAmount > userAccountptr->balance) {
		return LOW_BALANCE;
	}
	else {
		return OK_S;
	}
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	FILE* tn = fopen("trans.txt", "r");
	int transNum = 0;
	int* transNumptr = &transNum;
	fscanf(tn, "%d", transNumptr);
	if (transNum > 254) {
		printf("\nsaving failed\n");
		transData->transState = SAVING_FAILED;
		return SAVING_FAILED;
	}
	else {
		FILE* transDB = fopen("transactionDB.txt", "a");
		transactionDB[transNum] = *transData;
		transactionDB[transNum].transactionSequenceNumber = transNum;
		if (transData->transState != APPROVED) {
			fprintf(transDB, "%d: %s, %s\n", transNum, message, transData->cardHolderData.primaryAccountNumber);
		}
		else {
			fprintf(transDB, "%d: %s, %s, %f\n", transNum, message, transData->cardHolderData.primaryAccountNumber, transData->terminalData.transAmount);
		}
		fclose(transDB);
		fclose(tn);
		FILE* tn = fopen("trans.txt", "w");
		*transNumptr += 1;
		fprintf(tn, "%d", transNum);
		fclose(tn);
		return OK_S;
	}
}