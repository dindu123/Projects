#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct CustomerDetails{
	int customerId;
	int accountNo;
	char Name[50];
	float balance;
	char password[18];
	int noOfGiftCards;
	struct GiftCardDetails{
		int giftCardNo;
		int PIN;
		float giftCardBalance;
		int gifted;
		int blocked;
		char history[30][30];
		int transactionsCount;
	}giftCards[20];
}customer[50];

int noOfCustomers;
int loggedInId;
int pinForGiftCard=2000;
int giftCardNumber=10000;
int loggedCustIndex=-1;

int AccountLogin(int LoginCustId,char LoginPassword[])
{
	int loggedCustIndex;
	int checkCustId,i,j,ind;
	for(i=0;i<noOfCustomers;i++)
	{
		if(customer[i].customerId==LoginCustId)
		{
			loggedCustIndex=i;
			for(j=0;j<strlen(customer[i].password);j++)
			{
				//printf("%c",(char)(((int)LoginPassword[j])-1));
				if(customer[i].password[j]!=(char)(((int)LoginPassword[j])-1))
				{
					return -1;
				}
			}
			
			break;
		}
	}
	//printf("\n");
	if(i==noOfCustomers)
		return -1;
	return loggedCustIndex;
}

void Purchase()
{
	int i,j,flag1=0,flag2=0;
	char ch[30];
	float billAmountToPurchase;
	int collectGiftCardNoToPurchase,collectGiftCardPINToPurchase;
	printf("Enter Bill Amt: ");
	scanf("%f",&billAmountToPurchase);
	printf("Enter Gift Card No.: ");
	scanf("%d",&collectGiftCardNoToPurchase);
	printf("Enter Gift Card PIN.: ");
	scanf("%d",&collectGiftCardPINToPurchase);
	for(i=0;i<noOfCustomers;i++)
	{
		for(j=0;j<customer[i].noOfGiftCards;j++)
		{
			if(customer[i].giftCards[j].giftCardNo==collectGiftCardNoToPurchase)
			{
				flag1=1;
				if(customer[i].giftCards[j].PIN==collectGiftCardPINToPurchase)
				{
					flag2=1;
					if(customer[i].giftCards[j].giftCardBalance>=billAmountToPurchase)
					{
						if(customer[i].giftCards[j].blocked==1)
						{
							printf("Gift Card Blocked. Can't process purchase\n");
							continue;
						}
						customer[i].giftCards[j].giftCardBalance-=billAmountToPurchase;
						printf("Available balance: %f\n\n",customer[i].giftCards[j].giftCardBalance);
						strcpy(ch,"Paid with gift card");
						strcpy(customer[i].giftCards[j].history[customer[i].giftCards[j].transactionsCount++],ch);
					}
				}
			}
		}
	}
	if(flag1==0)
	{
		printf("Ïncorrect Gift Card Number\n");
	}
	if(flag1==0)
	{
		printf("Incorrect Gift Card PIN\n");
	}
}

void CreateANewGiftCard()
{
	float giftCardBuy;
	int choice2;
	printf("Enter the value of gift card: ");
	scanf("%f",&giftCardBuy);
	if(customer[loggedCustIndex].balance>=giftCardBuy)
	{
		if(customer[loggedCustIndex].noOfGiftCards==0)
		{
			customer[loggedCustIndex].giftCards[0].transactionsCount=0;
			customer[loggedCustIndex].giftCards[0].giftCardNo=giftCardNumber;
			customer[loggedCustIndex].giftCards[0].PIN=pinForGiftCard;
			customer[loggedCustIndex].giftCards[0].giftCardBalance=giftCardBuy;
			customer[loggedCustIndex].giftCards[0].gifted=0;
			customer[loggedCustIndex].giftCards[0].blocked=0;
			customer[loggedCustIndex].noOfGiftCards++;
			printf("Gift Card Created Successfully\n");
			printf("Gift Card Number : %d\n",customer[loggedCustIndex].giftCards[0].giftCardNo);
			printf("Gift Card PIN: %d\n",customer[loggedCustIndex].giftCards[0].PIN);
			printf("Do you want to gift the card:\n");
			printf("1.YES\n2.NO\n");
			printf("Enter your choice: ");
			scanf("%d",&choice2);
			if(choice2==1)
			{
				customer[loggedCustIndex].giftCards[0].gifted=1;
			}
		}
		else if(customer[loggedCustIndex].noOfGiftCards>0)
		{
			customer[loggedCustIndex].giftCards[customer[loggedCustIndex].noOfGiftCards].transactionsCount=0;
			customer[loggedCustIndex].giftCards[customer[loggedCustIndex].noOfGiftCards].giftCardNo=giftCardNumber;
			customer[loggedCustIndex].giftCards[customer[loggedCustIndex].noOfGiftCards].PIN=pinForGiftCard;
			customer[loggedCustIndex].giftCards[customer[loggedCustIndex].noOfGiftCards].giftCardBalance=giftCardBuy;
			customer[loggedCustIndex].giftCards[customer[loggedCustIndex].noOfGiftCards].gifted=0;
			customer[loggedCustIndex].giftCards[customer[loggedCustIndex].noOfGiftCards].blocked=0;
			customer[loggedCustIndex].noOfGiftCards++;
			printf("Gift Card Created Successfully\n");
			printf("Gift Card No: %d\n",customer[loggedCustIndex].giftCards[customer[loggedCustIndex].noOfGiftCards].giftCardNo);
			printf("Gift Card PIN: %d\n",customer[loggedCustIndex].giftCards[customer[loggedCustIndex].noOfGiftCards].PIN);
						printf("Do you want to gift the card:\n");
			printf("1.YES\n2.NO\n");
			printf("Enter your choice: ");
			scanf("%d",&choice2);
			if(choice2==1)
			{
				customer[loggedCustIndex].giftCards[0].gifted=1;
			}
		}
	}
	else
	{
		printf("Insufficient Balance\n");
	}
}

void topUpGiftCard()
{
	int inputGiftCardNo;
	float giftCardTopUp;
	printf("Enter Gift Card Number: ");
	scanf("%d",&inputGiftCardNo);
	int j;
	for(j=0;j<customer[loggedCustIndex].noOfGiftCards;j++)
	{
		if(customer[loggedCustIndex].giftCards[j].giftCardNo==inputGiftCardNo)
		{
			printf("Enter topup amount :");
			scanf("%f",&giftCardTopUp);
			customer[loggedCustIndex].giftCards[j].giftCardBalance+=giftCardTopUp;
			customer[loggedCustIndex].balance-=giftCardTopUp;
			printf("TopUp Successful\n");
			printf("Gift Card Balance: %f\n",customer[loggedCustIndex].giftCards[j].giftCardBalance);
			printf("Main Account Balance: %f\n",customer[loggedCustIndex].balance);
			customer[loggedCustIndex].giftCards[j].giftCardBalance+=giftCardTopUp;
			break;
		}
	}
	if(j==customer[loggedCustIndex].noOfGiftCards)
	{
		printf("Incorrect Gift Card Number\n");
	}
	
}

void giftCardTransactionHistory()
{
	int i,j;
	printf("\n***Transaction History***\n\n");
	for(i=0;i<customer[loggedCustIndex].noOfGiftCards;i++)
	{
		printf("***Transaction History of Gift Card: %d***\n",customer[loggedCustIndex].giftCards[i].giftCardNo);
		for(j=0;j<customer[loggedCustIndex].giftCards[i].transactionsCount;j++)
		{
			printf("%s\n",customer[loggedCustIndex].giftCards[i].history[j]);
		}
		printf("\n");
	}
}

int main()
{
	int choice,choice1,collectLoginResult,LoginCustId;
	char LoginPassword[18];
	customer[0].customerId=11;
	customer[0].accountNo=11011;
	customer[0].noOfGiftCards=0;
	strcpy(customer[0].Name,"Kumar");
	customer[0].balance=10000;
	strcpy(customer[0].password,"BpipNvjm");
	customer[1].customerId=22;
	customer[1].accountNo=22022;
	customer[1].noOfGiftCards=0;
	strcpy(customer[1].Name,"Madhu");
	customer[1].balance=20000;
	strcpy(customer[1].password,"CboLjoh");
	noOfCustomers=2;
	do{
	printf("1.Account Login\n");
	printf("2.Purchase\n");
	printf("3.Exit\n");
	printf("Enter your choice: ");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			printf("Enter customer Id: ");
			scanf("%d",&LoginCustId);
			printf("Enter Password: ");
			scanf("%s",LoginPassword);
			collectLoginResult=AccountLogin(LoginCustId,LoginPassword);
			if(collectLoginResult!=-1)
			{
				loggedInId=LoginCustId;
				loggedCustIndex=collectLoginResult;
				//printf("%d\n",loggedInId);		
				printf("\n*****Logged in Succesfully****\n\n");
				do{
					printf("1.Create a New GiftCard\n");
					printf("2.Topup GiftCard\n");
					printf("3.View GiftCard Transactions History\n");
					printf("4.Block the Existing Card\n");
					printf("5.Logout\n");
					scanf("%d",&choice1);
					switch(choice1)
					{
						case 1:
							CreateANewGiftCard();
							giftCardNumber++;
							pinForGiftCard++;
							break;
						case 2:
							topUpGiftCard();
							break;
						case 3:
							giftCardTransactionHistory();
							break;
						case 4:
							//blockGiftCard();
							break;
						case 5:
							loggedInId=-1;	
							loggedCustIndex=-1;
							break;
					}
				}while(choice1!=5);
			}
			else
			{
				printf("Incorrect details");
			}
			break;
		
		case 2:
			Purchase();
			break;
	}
	}while(choice!=3);
	return 0;
}

