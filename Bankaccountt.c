/************************************************************************************************
 *                                                                                              *
 * Project Name : Bank Account.c                                                                *
 *                                                                                              *
 * Detail : This program allows the user to enter account number and starting balance,          *
 *          If account number is equal to -1, it will print all of transaction and end program  *
 *          Then ask the user about amount. If amount is more than 0, it will be deposit.       *
 *          If amount is less than 0, it will be withdrawal. If amount is equal to 0, it will   *
 *          print the invoice and this user is finished.                                        *
 *                                                                                              *
 * Create By : Benjawan  Junpum                                                                 *
 *             Student ID :                                                                     *
 *                                                                                              *
 * Date : 16-Aug-2010                                                                           *
 *                                                                                              *
 ************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

void getAccount(char account[])
{
    char input[32];
    int check;
    int i;
    do
        {
        check=1;
        printf("Enter your account number (8 digit, not start with 0,1):");
        fgets(input,32,stdin);
        sscanf(input,"%s",account);
        for(i=0;i<strlen(account);i++)
            {
            if(isdigit(account[i])==0)
                {
                check=0;
                }
            }
        if(account[0]=='0'||account[0]=='1'||strlen(account)==0||strlen(account)!=8)
            {
            check=0;
            }
        if(check==0)
            {
            printf("Error\n");
            }
        }
    while(check==0&&!(account[0]=='-'&&account[1]=='1'&&account[2]=='\0'));

}

double getBalance()
{
    char input[32];
    double balance;
    int check;
    int i;
    do
        {
        check=1;
        printf("Enter your balance :");
        fgets(input,32,stdin);
        for(i=0;i<strlen(input)-1;i++)
            {
            if(isdigit(input[i])==0)
                {
                check=0;
                }
            }
        sscanf(input,"%lf",&balance);
        if(strlen(input)-1==0)
            {
            check=0;
            }
        if(check==0)
            {
            printf("Error\n");
            }
        }
    while(check==0);
    return balance;
}

double getTransaction(int count,double balance,double deposit[],double withdraw[],double bonus[],double fee[])
{
    char input[32];
    double trans;
    int check;
    int i;
    deposit[count]=0;
    withdraw[count]=0;
    bonus[count]=0;
    fee[count]=0;


    do
        {
    do
        {
        check=1;
        printf("Enter your transaction (+ deposit, - withdraw) :");
        fgets(input,32,stdin);
        for(i=0;i<strlen(input)-1;i++)
            {
            if(isdigit(input[i])==0&&input[0]!='-')
                {
                check=0;
                }
            }
        sscanf(input,"%lf",&trans);
        if(strlen(input)-1==0)
            {
            check=0;
            }

        if(check==0)
            {
            printf("Error\n");
            }
        }
    while(check==0);
    if(trans>0)
    {
        deposit[count]=trans;
        printf("Balance         : %.2lf\n",balance);
        printf("Deposit         : %.2lf\n",deposit[count]);
        printf("Current balance : %.2lf\n",balance+deposit[count]);
        if(deposit[count]>=500000)
        {
            bonus[count]=100;
            printf("You deposit more than 400000 baht\n");
            printf("You get 300 baht bonus\n"); //Editing Version
=======
            printf("You deposit more than 50000 baht\n");
            printf("You get 100 baht bonus\n"); //Editing Version
>>>>>>> 19ec75d31b41b8b90336ce98d4da535c1e0a3b2a
        }
    }
    if(trans<0)
    {
        if(balance<-1*trans)
        {
            printf("You don't have enough money\n");
            check=0;
        }
        else
        {
            withdraw[count]=-1*trans;
            printf("Balance         : %.2lf\n",balance);
            printf("Withdraw        : %.2lf\n",withdraw[count]);
            printf("Current balance : %.2lf\n",balance-withdraw[count]);
            if(withdraw[count]>=100000)
            {
                fee[count]=10;
                printf("You withdraw more than 100000 baht\n");
                printf("You have to pay fee 10 baht\n");
            }
        }
    }
    }
    while(check==0);
    return trans;
}

void showSlip(char account[],int count,double startBalance,double balance,double deposit[],double withdraw[],double bonus[],double totalBonus,double fee[],double totalFee)
{
    int i;
    printf("Bank account     : %s\n",account);
    printf("Start balance    : %.2lf\n",startBalance);
    for(i=0;i<count;i++)
    {
        if(deposit[i]!=0)
        {
            printf("Deposit          : %.2lf\n",deposit[i]);
        }
        if(withdraw[i]!=0)
        {
            printf("Withdraw         : %.2lf\n",withdraw[i]);
        }
    }
    printf("Total bonus      : %.2lf\n",totalBonus);
    printf("Total fee        : %.2lf\n",totalFee);
    printf("Current balance  : %.2lf\n",balance);
}

void endDay(int customer,double allDeposit,double allWithdraw,double allBonus,double allFee)
{
    printf("Total number of customer : %d\n",customer);
    printf("Total of all deposit     : %.2lf\n",allDeposit);
    printf("Total of all withdraw    : %.2lf\n",allWithdraw);
    printf("Total bonuses            : %.2lf\n",allBonus);
    printf("Total fees               : %.2lf\n",allFee);
}

int main()
{
    char account[32];
    int count=0;
    int customer=0;
    double trans=-1;
    double startBalance=0;
    double balance=0;
    double deposit[MAX]={0};
    double withdraw[MAX]={0};
    double bonus[MAX]={0};
    double fee[MAX]={0};
    double totalBonus=0;
    double totalFee=0;
    double allDeposit=0;
    double allBonus=0;
    double allWithdraw=0;
    double allFee=0;

    getAccount(account);
    while(strcmp(account,"-1"))
        {
        trans=-1;
        startBalance=getBalance();
        balance=startBalance;
        while(trans!=0)
            {
            trans=getTransaction(count,balance,deposit,withdraw,bonus,fee);
            if(trans!=0)
                {
                /*each customer*/
                balance=balance+deposit[count]-withdraw[count]+bonus[count]-fee[count];
                totalBonus=totalBonus+bonus[count];
                totalFee=totalFee+fee[count];

                /*overall*/
                allDeposit=allDeposit+deposit[count];
                allWithdraw=allWithdraw+withdraw[count];
                allBonus=allBonus+bonus[count];
                allFee=allFee+fee[count];

                count++;
                }
            else
                {

                showSlip(account,count,startBalance,balance,deposit,withdraw,bonus,totalBonus,fee,totalFee);
                /*finish customer*/
                customer++;

                /*reset for new customer*/
                count=0;
                startBalance=0;
                balance=0;
                totalBonus=0;
                totalFee=0;
                }
            }


        getAccount(account);
        }
    endDay(customer,allDeposit,allWithdraw,allBonus,allFee);
}
