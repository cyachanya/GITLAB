/*
  main.c
  BankAccount
  This program make for doing the transaction in the bank.
  This program could calculate bonus and fee when you doing the transaction.
  This program will print the translip for telling the user what money that they have in Bank Account and what transaction that they did.
  And at the end of the day it will print the summary of every transaction and every Bank Account.
*/

/*
  Created by CHANYA NINLAPHAT ID:55070503460
  Department of Computer Engineering Class:D
  On 10/18/55 BE.
 Copyright (c) 2555 CHANYA NINLAPHAT All rights reserved.
*/

#include <stdio.h>
#include <string.h>

/* this function print end of the day */
void printEndOfTheDay(int TotalAllAccount,double TotalAllDeposit,double TotalAllWithdrawal,double TotalAllBonus,double TotalAllFee) 
{
    printf("All Account %d\n",TotalAllAccount);
    printf("Total All Deposit  %.2lf Baht\n",TotalAllDeposit);
    printf("Total AllWithdrawal %.2lf Baht\n",TotalAllWithdrawal);
    printf("Total Bonus %.2lf Baht\n",TotalAllBonus);
    printf("Total Fee %.lf Baht\n",TotalAllFee);
}

/* this function print end transaction */
void printEndTransaction(char AccountNum[],double TotalBeforeBalance,double TotalDeposit,double TotalWithdrawal,double TotalBonus,double TotalFee,double Balance)
{
    printf("Account Number %s\n",AccountNum);
    printf("Before Balance %.2lf Bath\n",TotalBeforeBalance);
    printf("Total Deposit  %.2lf Baht\n",TotalDeposit);
    printf("Total Withdrawal %.2lf Baht\n",TotalWithdrawal);
    printf("Total Bonus %.2lf Baht\n",TotalBonus);
    printf("Total Fee %.lf Baht\n",TotalFee);
    printf("Balance %.2lf Baht\n",Balance);
}

/* this function print transction */
void printTransactions(char AccountNum[],double BeforeBalance,double transactionMoney,double Bonus,double Fee,double Balance)
{
    printf("Account Number %s\n",AccountNum);
    printf("Before Balance %.2lf Bath\n",BeforeBalance);
    if(transactionMoney > 0)
    {
        printf("Deposit  %.2lf Baht\n",transactionMoney);
        if(Bonus > 0)
        {
            printf("Bonus %.2lf Baht\n",Bonus);
        }
    }
    if(transactionMoney < 0)
    {
        printf("Withdrawal %.2lf Baht\n",transactionMoney);
        if(Fee < 0)
        {
            printf("Fee %.lf Baht\n",Fee);
        }
    }
    printf("Balance %.2lf Baht\n",Balance);
    
}

/* this function calculate */
void calculate(char AccountNum[],double* pBalance,double* pBeforeBalance,double* pTotalBeforeBalance,double* pTotalDeposit,double* pTotalWithdrawal,double* pTotalFee,double* pTotalBonus,double* pTotalAllDeposit,double* pTotalAllWithdrawal,double* pTotalAllFee,double* pTotalAllBonus)
{
    char input[32];
    double transactionMoney;
    double Bonus = 0;
    double Fee = 0;
    *pTotalBeforeBalance = *pBalance;
    do
    {
        *pBeforeBalance = *pBalance;
        Bonus = 0;
        Fee = 0;
        printf("How much do you want to deposit or withdrawal ? ");
        fgets(input,32,stdin);
        sscanf(input,"%lf",&transactionMoney);
        if(transactionMoney < 0)
        {
            if(transactionMoney <= -100000)
            {
                Fee = -13;
                if(*pBalance >= -(transactionMoney+Fee))
                {
                    *pBalance += transactionMoney+Fee;
                    *pTotalWithdrawal += transactionMoney;
                    *pTotalFee += Fee;
                    *pTotalAllWithdrawal += transactionMoney;
                    *pTotalAllFee += Fee;
                    printTransactions(AccountNum,*pBeforeBalance,transactionMoney,Bonus,Fee,*pBalance);
                }
                else
                {
                    printf("Balance money is not enough to use\n"); // Editing Version
                }
            }
            else
            {
                if(*pBalance >= -transactionMoney)
                {
                    *pBalance += transactionMoney;
                    *pTotalWithdrawal += transactionMoney;
                    *pTotalAllWithdrawal += transactionMoney;
                    printTransactions(AccountNum,*pBeforeBalance,transactionMoney,Bonus,Fee,*pBalance);
                }
                else
                {
                    printf("Balance money is not enough to withdrawal\n");
                }
            }
        }
        else if(transactionMoney > 0)
        {
            if(transactionMoney >= 500000)
            {
                Bonus = 100;
                *pBalance += transactionMoney+Bonus;
                *pTotalDeposit += transactionMoney;
                *pTotalBonus += Bonus;
                *pTotalAllDeposit += transactionMoney;
                *pTotalAllBonus += Bonus;
            }
            else
            {
                *pBalance += transactionMoney;
                *pTotalDeposit += transactionMoney;
                *pTotalAllDeposit += transactionMoney;
            }
            printTransactions(AccountNum,*pBeforeBalance,transactionMoney,Bonus,Fee,*pBalance);
        }
    }
    while(transactionMoney != 0);
}
/* this function start balance */
void startBalance(double* pBalance)
{
    char input[32];
    int check = 0;
    while(check == 0)
    {
        printf("What start balance? ");
        fgets(input,32,stdin);
        sscanf(input,"%lf",pBalance);
        if(*pBalance >= 0)
        {
            check = 1;
        }
        else
        {
            printf("Balance money must not less than 0 Baht\n");
        }
    }
}

/*  this function get account number */
int getAccount(char AccountNum[])
{
    char input[32];
    int i,a=0;
    printf("Please enter your account number ");
    fgets(input,32,stdin);
    sscanf(input,"%s",AccountNum);
	
    for(i=0;i<8;i++)
    {
        if(AccountNum[i]=='-'&&AccountNum[i+1]=='1'&&strlen(AccountNum)==2) //
            break;
        if((AccountNum[i]>='0'&&AccountNum[i]<='9')==0) 
            a=1;
        if(a==1)
        {
            printf("Account number must not be a letters\n");
            return 0;
        }
    }
    if(strlen(AccountNum) == 8) 
    {
        
        if(AccountNum[0] == '0' || AccountNum[0] == '1') 
        {
            printf("Account number must not start with 0 or 1\n");
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else if(strlen(AccountNum) == 2) 
    {
        if(strcmp(AccountNum,"-1") == 0) 
        {
            return 1;
        }
        else
        {
            printf("Account number must have 8 numbers\n");
            return 0;
        }
    }
    else
    {
        printf("Account number must have 8 numbers\n");
        return 0;
    }
}

int main()
{
    char accountNum[10];
    double balance = 0;
    double beforeBalance = 0;
    double totalBeforeBalance = 0;
    double totalDeposit = 0;
    double totalWithdrawal = 0;
    double totalFee = 0;
    double totalBonus = 0;
    int totalAllAccount = 0;
    double totalAllDeposit = 0;
    double totalAllWithdrawal = 0;
    double totalAllFee = 0;
    double totalAllBonus = 0;
    int i,a=0;
    
    do
    {
        while(getAccount(accountNum) == 0); /* use function getAccount */
        if(strcmp(accountNum,"-1") == 0) /* end of the day */
			{ } 
        else
        {
            totalAllAccount = totalAllAccount+1;
            startBalance(&balance);
            printf("Balance = %lf\n",balance);
            calculate(accountNum,&balance,&beforeBalance,&totalBeforeBalance,&totalDeposit,&totalWithdrawal,&totalFee,&totalBonus,&totalAllDeposit,&totalAllWithdrawal,&totalAllFee,&totalAllBonus);
            printEndTransaction(accountNum,totalBeforeBalance,totalDeposit,totalWithdrawal,totalBonus,totalFee,balance); 
        }
    }
    while(!strcmp(accountNum,"-1") == 0);
    printEndOfTheDay(totalAllAccount, totalAllDeposit, totalAllWithdrawal, totalAllBonus, totalAllFee);

    }