//COVID-19 MANAGEMENT SYSTEM


//Header files
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "coord.h" //is an header file to move the pointer to x,y coordinate

//Donation & Distribution Structure
struct donation{
	char Name_of_supply[50];
	char supply_code[5];
	char donator[30];
	int no_of_shipment;
	float quantity_recieved;
	float quantity_distributed;
};
struct donation dona[20];

struct distribute{
	char Name_of_supply[50];
	char supply_code[5];
	char reciever[30];
	int no_of_shipment;
	float quantity_distributed;
};
struct distribute dist[50];

//File pointer declaration
FILE *fp;
FILE *fd;

//Function prototype declaration
char menu();
void add_new_donation();
void update_donation();
void update_distribute();
void delete_donation();
void display_distribution();
void display_donation();

int read_donation();
int read_distribution();
void clear_donation();
void write_to_donation(struct donation d);
int update(char check[5],float update_qty,char rec_get);
void write_to_distribution(struct distribute d);
int search_donation(char search_code[5]);

int main()
{
	system("color 70");
	gotoxy(31,4);printf("Malaysia Red Crescent Society");
	gotoxy(18,6);printf("---------------------------------------------------------");
	gotoxy(29,8);printf("COVID-19 Donation Management System\n");
	gotoxy(18,10);printf("---------------------------------------------------------");
	gotoxy(45,20);printf("Created By:");
	gotoxy(45,22);printf("Name: Dixanta Nath Shrestha");
	gotoxy(45,24);printf("Roll: NP000766");
	gotoxy(25,16);system("pause");
	char flag='1';
	while(flag == '1')
	{
		//flag returns value to know when the user wants to exit
		flag = menu();
	}
	return 0;
}

char menu()
{
	char update_choice;
	char display_choice;
	char menu_choice = '0';
	while(menu_choice != '5')
	{
		system("cls");
		gotoxy(10,12);printf("\n1. Add inventory");
		gotoxy(10,14);printf("\n2. Update Records");
		gotoxy(10,16);printf("\n3. Delete Records");
		gotoxy(10,18);printf("\n4. Display Records");
		gotoxy(10,20);printf("\n5. Exit");
		fflush(stdin);
		printf("\n\nEnter your choice: ");
		scanf("%c",&menu_choice);
		system("cls");
		switch (menu_choice)
		{
			case '1':
				{
					/*User can add new donation
						- The supply code must be unique and can not already exists */
					add_new_donation();
					system("pause");
					break;
				}
				
			case '2':
				{
					fflush(stdin);
					printf("\n1.Update Donation\t2.Update Distribution");
					printf("\nEnter your choice:");
					scanf("%c",&update_choice);
					system("cls");
					switch(update_choice)
					{
						case '1':
							/*User can update the donation quantity
								- User can add or remove the quantity
								- To update the supply code must exist
								- If supply code doesn't exist user can add a new record */
							update_donation();
							system("pause");
							break;
							
						case '2':
							/*User can add distribution quantity
								- To update/add the supply code must exist
								- There must be enough quantity to distribute
								- The donation quantity is also updated */
							update_distribute();
							system("pause");
							break;
							
						default:
							printf("\nInvalid choice.");
							break;
					}
					break;
				}
				
			case '3':
				{
					/*User can delete donation record
						- The supply code must exist
						- Once deleted the record can't be recovered
						- If donation is deleted, distribution will be unchanged */
					delete_donation();
					system("pause");
					break;
				}
				
			case '4':
				{
					fflush(stdin);
					printf("\n1.Display Donation\t2.Display Distribution");
					printf("\nEnter your choice:");
					scanf("%c",&display_choice);
					system("cls");
					switch(display_choice)
					{
						case '1':
							/*User can display the donation record in following ways
								- Ascending order of available quantity
								- Descending order of available quantity
								- Search and display a particular donation
								- Default i.e. chronologically*/
							display_donation();
							system("pause");
							break;
							
						case '2':
							/*User can display the distribution record in following ways
								- Ascending order of available quantity
								- Descending order of available quantity
								- Default i.e. chronologically*/
							display_distribution();
							system("pause");
							break;
							
						default:
							printf("\nInvalid choice.");
							break;
					}
					break;
				}
				
			case '5':
				{
					//Exits the program
					return '0';
				}
			
			default:
				{
					//Loops back to the menu
					printf("invalid choice");
					break;
				}
		}
	}
}

void add_new_donation()
{
	struct donation new_dona[20];
	int i=0,total;
	int index;
	fflush(stdin);
	printf("\nEnter the number of donations you want to enter:");
	scanf("%d",&total);
	for(i=0;i<total;i++)
	{
		printf("\nEnter the supply code:");
		scanf("%s",&new_dona[i].supply_code);
		//check if supply code exist
		index = search_donation(new_dona[i].supply_code);
		if(index>=0)
		{
			printf("Supply code already exists\n");
			continue;
		}
		
		printf("\nEnter the name of supply:");
		scanf("%s",&new_dona[i].Name_of_supply);
		printf("\nEnter the donator:");
		scanf("%s",&new_dona[i].donator);
		printf("\nEnter number of shipments:");
		scanf("%d",&new_dona[i].no_of_shipment);
		printf("\nEnter the quantity recieved in millions:");
		scanf("%f",&new_dona[i].quantity_recieved);
		new_dona[i].quantity_distributed = 0;
		write_to_donation(new_dona[i]);
	}
}


void update_donation()
{
	char new_record;
	char update_supply_code[5];
	float update_qty;
	char add_or_remove;
	fflush(stdin);
	printf("Enter the supply code:");
	scanf("%s",&update_supply_code);
	//checks if supply code exist
	if(search_donation(update_supply_code) >=0 )
	{
		fflush(stdin);
		printf("\n1.Add Donation[a]\t2.Remove Donation[r]");
		printf("\nDo you want to add or remove donation?[a/r]:");
		scanf("%c",&add_or_remove);
		printf("Enter the quantity to add/remove:");
		scanf("%f",&update_qty);
		update(update_supply_code,update_qty,add_or_remove);
	}
	else
	{
		fflush(stdin);
		printf("\nSupply code doesn't exist");
		printf("\nAdd new record to inventory [y/n]: ");
		scanf("%c",&new_record);
		if(new_record == 'y' || new_record == 'Y')
		{
			add_new_donation();
		}
	}
}

void update_distribute()
{
	int i=0,total;
	int index;
	fflush(stdin);
	printf("\nEnter the number of records you want to enter:");
	scanf("%d",&total);
	for(i=0;i<total;i++)
	{
		printf("\nEnter the supply code:");
		scanf("%s",&dist[i].supply_code);
		//Checks if supply code exist
		index = search_donation(dist[i].supply_code);
		if(index<0)
		{
			printf("\nThe donation you are trying to distribute is not available.");
			continue;
		}
		printf("\nEnter the quantity distributed in millions:");
		scanf("%f",&dist[i].quantity_distributed);
		
		//Checks if there is enough quantity to distribute
		if(dona[index].quantity_recieved-dist[i].quantity_distributed>=0)
		{
			strcpy(dist[i].Name_of_supply,dona[index].Name_of_supply);
			printf("\nEnter the reciever:");
			scanf("%s",&dist[i].reciever);
			printf("\nEnter number of shipment:");
			scanf("%d",&dist[i].no_of_shipment);
			update(dist[i].supply_code,dist[i].quantity_distributed,'d');
			write_to_distribution(dist[i]);
		}
		else
		{
			printf("\nNot enough quantity");
		}
	}
}

void delete_donation()
{
	char check[10];
	int i=0,size_donation=0;
	size_donation = read_donation();
	//clears the file
	clear_donation();
	fflush(stdin);
	printf("\nEnter the supply code:");
	scanf("%s",&check);
	//Enters all the donation and skips the one to be deleted
	for(i=0;i<size_donation;i++)
	{
		if(strcmp(check,dona[i].supply_code) != 0)
		{
			write_to_donation(dona[i]);
		}
	}
	printf("\nRecord Deleted!!\n");
}



void display_donation()
{
	char sort_choice;
	int i,size,j;
	char search_code[5];
	int index;
	struct donation temp;//temp is a temporary structure
	size = read_donation();
	if(size<0)
	{
		printf("\nThe file is empty\n");
		return;
	}
	printf("\n1.Quantity Ascending\t2.Quantity Descending");
	printf("\n3.Search Donation\t4.Default Display");
	printf("\nChoose your option\n>>");
	fflush(stdin);
	scanf("%c",&sort_choice);
	switch(sort_choice)
	{
		case '1': //Sort available quantity in ascending order
			for(i=0;i<size;i++)
			{
				for(j=i+1;j<size;j++)
					{
						if(dona[i].quantity_recieved>dona[j].quantity_recieved)
						{
							temp = dona[j];
							dona[j] = dona[i];
							dona[i] = temp;
						}
					}
			}
			break;
			
		
		case '2'://Sort available quantity in descending order
			for(i=0;i<size;i++)
			{
				for(j=i+1;j<size;j++)
					{
						if(dona[i].quantity_recieved<dona[j].quantity_recieved)
						{
							temp = dona[j];
							dona[j] = dona[i];
							dona[i] = temp;
						}
					}
			}
			break;
		
		case '3'://Searches and displays a donation and exists the function directly
			printf("Enter the supply code:");
			scanf("%s",&search_code);
			index = search_donation(search_code);
			printf(" |--------------------------|-------------|------------------|");
			printf("----------------|---------------------|----------------------|\n");
			printf(" |      Name of Supply      | Supply Code |      Donator     |");
			printf(" No of Shipment |  Quantity Available | Quantity Distributed |\n");
			printf(" |--------------------------|-------------|------------------|");
			printf("----------------|---------------------|----------------------|\n");
			printf(" | %-25s| %-12s| %-17s| %-15d| %-20.3f| %-21.3f|\n",dona[index].Name_of_supply,
			dona[index].supply_code,dona[index].donator,dona[index].no_of_shipment,
			dona[index].quantity_recieved, dona[index].quantity_distributed );
			printf(" |--------------------------|-------------|------------------|");
			printf("----------------|---------------------|----------------------|\n");
			return;
			
		case '4':
			break;
			
			
		default:
			printf("\nInvalid Choice\n");
			return;
	}
	printf(" |--------------------------|-------------|------------------|");
	printf("----------------|---------------------|----------------------|\n");
	printf(" |      Name of Supply      | Supply Code |      Donator     |");
	printf(" No of Shipment |  Quantity Received  | Quantity Distributed |\n");
	printf(" |--------------------------|-------------|------------------|");
	printf("----------------|---------------------|----------------------|\n");
	for(i=0;i<size;i++)
	{
		printf(" | %-25s| %-12s| %-17s| %-15d| %-20.3f| %-21.3f|\n",dona[i].Name_of_supply,
		dona[i].supply_code, dona[i].donator,dona[i].no_of_shipment,
		dona[i].quantity_recieved, dona[i].quantity_distributed );
	}
	printf(" |--------------------------|-------------|------------------|");
	printf("----------------|---------------------|----------------------|\n");
	
}

void display_distribution()
{
	char sort_choice;
	int i,size,j;
	size = read_distribution();
	struct distribute temp;//temp is a temporary structure
	if(size<0)
	{
		printf("\nThe file is empty\n");
		return;
	} 
	printf("\n1.Quantity Ascending\t2.Quantity Descending\n3.Default Display");
	printf("\nChoose your option\n>>");
	fflush(stdin);
	scanf("%c",&sort_choice);
	switch(sort_choice)
	{
		case '1'://Sort available quantity in ascending order
			for(i=0;i<size;i++)
			{
				for(j=i+1;j<size;j++)
					{
						if(dist[i].quantity_distributed>dist[j].quantity_distributed)
						{
							temp = dist[j];
							dist[j] = dist[i];
							dist[i] = temp;
						}
					}
			}
			break;
			
		case '2'://Sort available quantity in descending order
			for(i=0;i<size;i++)
			{
				for(j=i+1;j<size;j++)
					{
						if(dist[i].quantity_distributed<dist[j].quantity_distributed)
						{
							temp = dist[j];
							dist[j] = dist[i];
							dist[i] = temp;
						}
					}
			}
			break;	
		case '3':
			break;
			
		default:
			printf("\nInvalid Choice\n");
			return;
	}
	printf(" |--------------------------|-------------|------------------|");
	printf("----------------|----------------------| \n");
	printf(" |      Name of Supply      | Supply Code |     Reciever     |");
	printf(" No of Shipment | Quantity Distributed | \n");
	printf(" |--------------------------|-------------|------------------|");
	printf("----------------|----------------------| \n");
	for(i=0;i<size;i++)
	{
		printf(" | %-25s| %-12s| %-17s| %-15d| %-21.3f|\n",dist[i].Name_of_supply,
		dist[i].supply_code, dist[i].reciever,dist[i].no_of_shipment,dist[i].quantity_distributed);
	}
	printf(" |--------------------------|-------------|------------------|");
	printf("----------------|----------------------| \n");
}





/* Functions below does not require user interaction.*/

//reads the contents of donation file to an array of structure dona
int read_donation()
{
	int i=0,size=0;
	fp = fopen("donation.txt","r");
	if(fp == NULL)
	{
		printf("\nCan't open file");
	}
	else
	{
		if(fgetc(fp) !=EOF)
		{
			
			rewind(fp);
			while (!feof(fp)) 
				{
					fscanf(fp,"%s %s %s %d %f %f\n",&dona[i].Name_of_supply,&dona[i].supply_code, 
					&dona[i].donator, &dona[i].no_of_shipment, &dona[i].quantity_recieved,
					&dona[i].quantity_distributed);
					i++;//will increase the value one last time before exiting
					size=i;	
				}
		}
		else
		{
			return -1;
		}
	}
	fclose(fp); 
	return size;
}


//reads the contents of distribution file to an array of structure dist
int read_distribution()
{
	int i=0,size=0;
	fd = fopen("dist.txt","r");
	if(fd == NULL)
	{
		printf("\nCan't open file");
	}
	else
	{
		if(fgetc(fd) !=EOF)
		{
			
			rewind(fd);
			while (!feof(fd)) 
				{
					fscanf(fd,"%s %s %s %d %f\n",&dist[i].Name_of_supply,&dist[i].supply_code, 
					&dist[i].reciever, &dist[i].no_of_shipment, &dist[i].quantity_distributed);
					i++;//will increase the value one last time before exiting
					size=i;	
				}
		}
		else
		{
			return -1;
		}
	}
	fclose(fd); 
	return size;
}


//clears the contents of donation file
void clear_donation()
{
	fp = fopen("donation.txt","w");
	if(fp == NULL)
	{
		printf("\nCan't open file");
	}
	fclose(fp);
}

//writes contents to donation file from array of structure dona
void write_to_donation(struct donation d)
{
	fp = fopen("donation.txt","a+");
	if(fp == NULL)
	{
		printf("\nCan't open file");
	}
	else
	{
		fprintf(fp,"%s %s %s %d %f %f\n",d.Name_of_supply,d.supply_code, d.donator,
		d.no_of_shipment, d.quantity_recieved,d.quantity_distributed);
	}
	fclose(fp);
}

//writes contents to distribution file from array of structure dist
void write_to_distribution(struct distribute d)
{
	fd = fopen("dist.txt","a+");
	if(fd == NULL)
	{
		printf("\nCan't open file");
	}
	else
	{
		fprintf(fd,"%s %s %s %d %f\n",d.Name_of_supply,d.supply_code, d.reciever,
		d.no_of_shipment, d.quantity_distributed);
	}
	fclose(fd);
}

//Searches a donation using supply_code
int search_donation(char search_code[10])
{
	int i=0,size;
	size = read_donation();
	for(i=0;i<size;i++)
	{
		if(strcmp(dona[i].supply_code,search_code) == 0)
		{
			return i;
		}
	}
	return -1;
	
}

/*updates the contents of donation file
	- runs with update_donation() & update_distribution
	- rec_get tells the function what action needs to be taken
		a - adds to quantity recieved
		r - removes from quantity recieved
		d - removes from quantity_recieved & adds to quantity_ distributed*/
int update(char check[5],float update_qty,char rec_get)
{
	int i=0,size=0;
	size = read_donation();
	int index;
	index = search_donation(check);
	switch(rec_get)
	{
		case 'a'://add qty	
			dona[index].quantity_recieved = dona[index].quantity_recieved + update_qty;
			dona[index].no_of_shipment++;
			printf("\nRecords Updated\n");
			break;
			
		case 'r'://remove qty
			if(dona[index].quantity_recieved - update_qty>=0)
			{
				dona[index].quantity_recieved = dona[index].quantity_recieved - update_qty;
				printf("\nRecords Updated!!\n");
			}
			else
			{
				printf("\nInvalid Quantity.\n");
			}
			break;
			
		case 'd': //distribute
			dona[index].quantity_recieved = dona[index].quantity_recieved - update_qty;
			dona[index].quantity_distributed += update_qty;
			printf("\nRecords Updated!!\n");	
			break;
		default:
			printf("\nInvalid Choice.\n");
			return 0;
	}
		
		clear_donation();
		for(i=0;i<size;i++)
		{
			write_to_donation(dona[i]);
		}
}


