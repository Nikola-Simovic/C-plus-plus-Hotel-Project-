#include<iostream>
#include<time.h>
#include<cstdlib>
#include<string>

using namespace std;


/*Hi, my name is Nikola Simovic, and in the final hotel project, I'm aiming for a 5.
The project was done in accordance with all of the requirements, but i have also added aditional functionalities to it to make it seem more like an actual hotel.
At the start of the program, the hotel rooms are filled up to 20% to make it seem a bit more realistic
The program itself works as a Hotel program where the user gets the option to book a room,
The user can decide on their own room or get the program to decide it, they can see the prices of the rooms before hand if they wish
There is also an option to check out which makes the room that got checked out of available for the next person to book.
Lastly there is a reservation checker, which tells the person if there is a valid reservation for the hotel room and booking code,
after which if their reservation is valid, they can print an Invoice or choose not to. */


struct Customer {                                                                               //The customer structure
	string name;                                                                                //name of the customer
	int room_number;																			//their room number
	int reservation;																			//the customers booking number
	int nights_staying;																			//number of nights they wish to stay
	int room_type;																				//the type of room they prefer
};

struct Room {
	int room_type;																				//to show if its a single or double room
	int room_number;																			//shows the room number
	int price;																					//shows the price of the room(depends on if its a single or double room)
	bool is_available = true;                                                                   //starts off as a fully empty hotel
	int discount = 55;                                                                          //random starting value for error checking
	string customersName = "Yug0slavia";														//the default customer name, shows up if the room isnt booked
	int booked_number = 9999;																		//the booking number of the room,its 4 digits by default which isnt valid if its booked
	int nights = 0;																			    //holds the information on how many nights the room has been booked for
};


bool Any_available_rooms(Room rooms[])                                                          //before the user can select a room or book, this function checks if there are any rooms in the hotel
{																								//and the customer wont be able to book a room if the hotel is full later in the code
	int available_rooms = 0;
	for (int i = 0; i < 70; i++)
	{
		if (rooms[i].is_available == true)
			available_rooms++;
	}
	if (available_rooms == 0)
		return false;
	else return true;
}



int singleOrDouble()                                                                             //this function is used to get the information on whether the customer wants to book a single or a double room
{
	int selectedNm;
	bool reason = true;

	while (reason) {                                                                             //the main while loop will run untill the user has put in acceptable input, aka. 1 or 2 depending on the desired room type

		cout << "For a single room, type 1, for a double room type 2:  ";
		cin >> selectedNm;

		while (cin.fail() || selectedNm < 1 || selectedNm>2)                                     //this is used to check the input and will run until the user has put in either 1 or 2

		{
			cout << "Remember to put in a number, and 1 for a single or 2 for a double room! Now try again:  ";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> selectedNm;
		}


		if (selectedNm == 1)
		{
			return 1;
			reason = false;
		}
		else if (selectedNm == 2)
		{
			return 2;
			reason = false;
		}

	}
}

int fillDiscount(Room rooms[])                                                                   //this function goes through the array of rooms and gives every room a discount value that will be used later
{

	for (int i = 0; i < 70; i++)
	{
		int randNum = (rand() % 3) + 1;
		rooms[i].discount = randNum;
	}

	return 0;
}

void fillHotel(Room rooms[])                                                                      //this function fills the hotel at around 20% capacity at the start of the program to make it seem like its a real hotel where some rooms are booked beforehand
//it also enumerates the rooms, adds the price into them and assigns them a type(single or double)
{
	int roomFiller;
	for (int i = 0; i < 70; i++)
	{
		roomFiller = (rand() % 10) + 1;

		if (roomFiller == 1 || roomFiller == 2)
		{
			rooms[i].is_available = false;
		}

		rooms[i].room_number = i + 1;

		if (i % 2 == 1)
		{
			rooms[i].room_type = 1;
			rooms[i].price = 100;
		}
		else
		{
			rooms[i].room_type = 2;
			rooms[i].price = 150;
		}
	}
}

void menu_option_3()                                                                             //this function simply prints out the third menu option, aka. if the customer wants to see the price of the rooms beforehand

{
	cout << "\nThe prices are as follows:\nFor single rooms, the price is 100e per night." << endl
		<< "For double rooms, the price is 150e per night.\nBut depending on the room, you might get offered as much as a 20 % discount at checkout!\n\n";
}



int bookingNumber()                                                                               //the function that creates the booking/reservation number that will be used throughout the program
{
	int booking_number;

	booking_number = 10000 + (rand() % 100000);

	return booking_number;
}

int Price(Customer customers[], int customer_number)												  //this function looks at the nights stayed and room type to return the price of the stay
{
	int price;
	if (customers[customer_number].room_type == 1)
		price = customers[customer_number].nights_staying * 100;
	else price = customers[customer_number].nights_staying * 150;
	return price;
}

int booking()                                                                                     //this function checks if the user wants to confirm the booking or cancel it completely
{
	string yesOrNo;
	string a = "yes";
	string b = "no";

	cout << "\nTo proceed with the booking, type:\n'yes' if you would like to book the room\n'no' if you would like to cancel the booking and go back to the main menu. ";

	cin.clear();
	cin.ignore(256, '\n');
	cin >> yesOrNo;

	while (true)                                                                                  //input check, that will only accept "yes" or "no" as options
	{
		if (yesOrNo == a)
			return 0;
		else if (yesOrNo == b)
			return 1;
		else cout << "\nUnfortunately, you can only choose 'yes' or 'no'.\nIf you want to cancel the booking or return to the main menu, please type 'no'.\nOtherwise to confirm the booking type 'yes' ";
		cin >> yesOrNo;
	}
}


string Invoice(Customer customers[], Room rooms[], int RoomNumber)                                   //The function that prints out the Invoice if the room is booked and the client asks for it
{

	string name = rooms[RoomNumber - 1].customersName;
	int discount_percentage;

	string room_type_string;
	if (rooms[RoomNumber - 1].room_type == 1)
	{
		room_type_string = "Double";
	}
	else room_type_string = "Single";



	cout << "\n--------------------------------------------------------" << endl
		<< "INVOICE \nThe Posseidon Thessaloniki\nThemistokli Sofouli 82 \nThessaloniki" << endl
		<< "\nCustomer: " << rooms[RoomNumber - 1].customersName << "     Booking number: " << rooms[RoomNumber - 1].booked_number << endl
		<< "Room number: " << RoomNumber << "      Room type: " << room_type_string << "      Nights: " << rooms[RoomNumber - 1].nights
		<< endl << endl << "SUBTOTAL: " << rooms[RoomNumber - 1].price << " euros.";

	if (rooms[RoomNumber - 1].discount == 1)                                                       //code that will give the discount a percentage value based on the type of discount the room recieved
	{
		discount_percentage = 0;
	}
	else if (rooms[RoomNumber - 1].discount == 2)
	{
		discount_percentage = 10;
	}
	else if (rooms[RoomNumber - 1].discount == 3)
	{
		discount_percentage = 20;
	}
	else cout << "Something unexpected happened,please contact an administrator.\n";               //a fallback in case something unexpected goes wrong


	cout << endl << "DISCOUNT: " << discount_percentage << "%"
		<< endl << "TOTAL: " << (rooms[RoomNumber - 1].price) - (rooms[RoomNumber - 1].price * discount_percentage / 100) << " euros" << endl
		<< "--------------------------------------------------------\n" << endl;



	return "success";


}

void checkReservation(Room rooms[], Customer customers[])                                           //checks whether there is a valid reservation after recieving the room number and booking number and also
{                                                                                                  //prints the invoice for the customer if they have a valid reservation and ask for it
																								   //returns to main menu if the reservation isnt found
	int roomNumberGiven;
	int bookingNumber;
	string asked_for_the_invoice;
	string default_invoice = "invoice";

	cout << "\nTo check your reservation, first type in your room number: ";
	cin >> roomNumberGiven;

	while (cin.fail() || roomNumberGiven > 70 || roomNumberGiven < 1)                              //checks if the user gave a valid room number
	{
		cout << "Thats not a valid room number! \nPlease Try again: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> roomNumberGiven;
	}

	cout << "Now please put in your booking number: ";
	cin >> bookingNumber;

	while (cin.fail() || bookingNumber <= 10000 || bookingNumber > 100000)                         //checks if the user gave a valid booking number
	{
		cout << "Thats not a valid booking number!\nBooking numbers are between 10000 and 100000. \nPlease Try again: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> bookingNumber;
	}

	if (rooms[roomNumberGiven - 1].booked_number == bookingNumber)
	{
		cout << "\nThere is a valid reservation for this room under the name: " << rooms[roomNumberGiven - 1].customersName << endl;

		cout << "\nIf you would like to recieve the invoice, type invoice.\nTyping anything else will bring up the main menu. ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> asked_for_the_invoice;

		while (true)
		{
			if (asked_for_the_invoice == default_invoice)
			{
				Invoice(customers, rooms, roomNumberGiven);
				break;
			}
			else
			{
				cout << "\n\nReturning to main menu...\n\n";
				break;
			}
		}

	}
	else
	{
		cout << "\nThere is no valid reservation with this info.\nCheck if the room number and reservation number are correct and try again if you wish.\n";
	}

}

int AutomaticSelection(Room rooms[], int type, string PersonsName)                                  //this selects the room automatically and returns the room number and tells it to the customer
//it functions by picking a random number and checing if the type of room is appropriate and available
{                                                                                                   //it also assigns the customers name to the booked room for further use
	int random_room_number;

	if (type == 1)
	{
		while (true)
		{
			random_room_number = 1 + (rand() % 70);

			if (rooms[random_room_number].is_available == true)
			{
				if (random_room_number % 2 == 1)
				{
					cout << "\nYour room number is " << random_room_number << endl;
					rooms[random_room_number - 1].is_available = false;                             //changes the room to not available
					rooms[random_room_number - 1].customersName = PersonsName;                      //assigns the persons name to the room
					return random_room_number;
					break;
				}
			}

		}


	}
	else if (type == 2)
	{
		while (true)
		{
			random_room_number = 1 + (rand() % 70);

			if (rooms[random_room_number].is_available == true)
			{
				if (random_room_number % 2 == 0)
				{
					cout << "\nYour room number is " << random_room_number << endl;
					rooms[random_room_number - 1].is_available = false;                                //changes the room to not available
					rooms[random_room_number - 1].customersName = PersonsName;                         //assigns the persons name to the room

					return random_room_number;
					break;
				}
			}

		}


	}
	else cout << "Unexpected Error. Please try again later.";                                         //backup if something unexpected goes wrong



}

int ManualSelection(Room rooms[], Customer customers[], int customer_number)                         //this function lets the user decide on a room number themselves,checks the input, and whether the room type they want is possible to get or not
{                                                                                                    //if the room isnt available or is the wrong type, it asks the customer if they want to keep trying or let the machine decide for them
	int counter = 0;
	int available_rooms = 0;
	int secondary_selection;
	int somenm;
	int desired_type = customers[customer_number].room_type;
	string PersonsName = customers[customer_number].name;
	bool break_command = true;

	cout << "Please select the desired room number(1-70)  ";

	cin >> somenm;
	while (cin.fail() || somenm > 70 || somenm < 1)                                                  //checks whether the room number input is okay
	{
		cout << "Thats not a valid room number! \nPlease Try again: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> somenm;
	}
	for (counter; counter < 70; counter++)                                                           //the loop goes through all of the rooms, to see if the room type is available or not
	{
		if (desired_type == 1)
		{
			if (rooms[counter].is_available == true)
			{
				if (counter % 2 == 1) {
					available_rooms++;
				}
			}
		}
		else if (desired_type == 2)
		{
			if (rooms[counter].is_available == true)
			{
				if (counter % 2 == 0)
				{
					available_rooms++;
				}
			}
		}
	}

	if (available_rooms == 0)                                                                        //if there are no available rooms of that type, it says that to the user and returns a clearly false value
	{
		cout << "Unfortunately there are no desired rooms of that type.";
		return 999;
	}

	else
	{
		while (break_command)                                                                        //this loop checks if the room is available or not and gives the secondary options if it isnt or assigns the values if it is
		{
			if ((rooms[somenm - 1].is_available == true) && (rooms[somenm - 1].room_type != desired_type))
			{
				cout << "\nCongratulations! That room is available.\n";
				customers[customer_number].room_number == somenm;
				break_command = false;
				rooms[somenm - 1].is_available = false;                                                //makes the room not available anymore since its been booked
				rooms[somenm - 1].customersName = PersonsName;                                         //assigns the customer to the room
				return somenm;
			}
			else
			{
				cout << "\nUnfortunately, the desired room is not available,or the wrong type.\n\nWould you like to:\n(1)Choose a different room number \n(2)Let the program choose the room number for you? ";
				cin >> secondary_selection;

				while (cin.fail() || secondary_selection > 2 || secondary_selection < 1)                //input check for the secondary selection
				{
					cout << "Thats not a valid room number! \nPlease Try again: ";
					cin.clear();
					cin.ignore(256, '\n');
					cin >> secondary_selection;
				}

				if (secondary_selection == 1)
				{
					cout << "Please select a different room number. ";
					cin >> somenm;

					while (cin.fail() || somenm > 70 || somenm < 1)                                       //another input check for the secondary room selection
					{
						cout << "Thats not a valid room number! \nPlease Try again: ";
						cin.clear();
						cin.ignore(256, '\n');
						cin >> somenm;
					}
				}
				else
				{
					return AutomaticSelection(rooms, customers[customer_number].room_type, PersonsName);     //returns an automatic room number if the user asks for it
					break_command = false;
				}
			}

		}
	}

}


void checkout(Room rooms[])                                                                                //allows the person to check out of the hotel,it removes their information from the room and makes the room available again
{                                                                                                          //if the information isnt valid, it goes back to the main menu

	int roomnumber;
	int bookingNumber;

	cout << "\nTo checkout, you will need to input your Room number and Booking number.\nWhat is your room number? ";
	cin >> roomnumber;

	while (cin.fail() || roomnumber > 70 || roomnumber < 1)                                                 //input check to see if the room number is valid
	{
		cout << "\nThats not a valid room number!\nThe rooms are numbered from 1 to 70. \nPlease Try again: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> roomnumber;
	}

	cout << "Please input your booking number:(number between 10000 and 100000): ";
	cin >> bookingNumber;

	while (cin.fail() || bookingNumber <= 10000 || bookingNumber > 100000)                                  //input check to see if the booking number is valid
	{
		cout << "\nThats not a valid booking number!\nBooking numbers are between 10000 and 100000. \nPlease Try again: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> bookingNumber;
	}

	if (rooms[roomnumber - 1].booked_number == bookingNumber)                                                //if the customer gave the correct information, it checks them out and clears their information from the room
	{
		rooms[roomnumber - 1].is_available = true;
		rooms[roomnumber - 1].customersName = "Yug0slavia";
		rooms[roomnumber - 1].booked_number = 9999;
		cout << "\nYou have successfully checked out! \nHope you had a pleasant stay at Poseidon, and we hope to see you again one day!\n";
	}
	else
	{
		cout << "\nThe booking number doesnt seem to match the room number.\nThe program will return to the main menu after which you can try again.\n";
	}

}


int main()                                        //the main function will be the one that runs the code controls the main menu, decides on the options the user takes
{                                                 //and calls the appropriate functions
	int option;
	int nights;
	bool continuation = true;
	int booking_number;
	char name[30];
	int discount_recieved = 0;


	int customer_number = 0;

	Customer customers[70];
	Room rooms[70];

	srand(time(NULL));                                                                                     //ties the random numbers generated to the time, so they wouldnt be the same every time the program runs

	fillDiscount(rooms);                                                                                   //this and the following line start up the hotel,
	fillHotel(rooms);                                                                                      //giving the rooms default values


	while (continuation) {
		cout << "\n--------------------------------------------------------" << endl;                      //the main menu of the program runs inside of this while loop
		cout << "Welcome to the Poseidon Thessaloniki! Would you like to:\n(1)Book a room \n(2)Check your reservation\n(3)See the prices\n(4)Check out\n(5)Exit?  ";
		cin >> option;

		while (cin.fail() || option < 1 || option>5)                                                       //checks if the users input is valid or not
		{
			cout << "\nThe options are numbered from 1 to 5, please put in the desired option number again:  ";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> option;
		}


		if (option == 1)                                                                                   //runs the code required to book a room
		{
			cout << "\nWhats your name?(Your name may contain a maximum of 30 characters.)  \n";
			cin.clear();
			cin.ignore(256, '\n');
			cin.getline(name, 30);

			customers[customer_number].name = name;
			customers[customer_number].reservation = bookingNumber();

			cout << "\nWelcome to the Poseidon booking services " << name << "!\n";

			if (!Any_available_rooms(rooms))                                                               //if there are no available rooms, the customer can not proceed to book one
			{
				cout << "\nUnfortunately there are no available rooms at the moment, please try booking our hotel at a different time.";
			}
			else
			{
				customers[customer_number].room_type = singleOrDouble();

				bool room_select = true;
				while (room_select) {

					int selection;
					cout << "\nIt's time to select a room.\nTo select the room number yourself, type 1.\nTo let the program decide the room for you, type 2:  ";
					cin >> selection;

					while (cin.fail() || selection < 1 || selection>2)                                      //another input check, to see if the user wants to manually choose a number or let the program do it
					{
						cout << "\nPlease pick 1 or 2 depending on the room type! Try again:  ";
						cin.clear();
						cin.ignore(256, '\n');
						cin >> selection;
					}

					if (selection == 1)
					{
						customers[customer_number].room_number = ManualSelection(rooms, customers, customer_number);
						room_select = false;

					}
					else if (selection == 2)
					{

						customers[customer_number].room_number = AutomaticSelection(rooms, customers[customer_number].room_type, customers[customer_number].name);
						room_select = false;
					}

				}

				cout << "\nHow many nights do you plan to stay at our hotel?  ";
				cin >> nights;
				while (cin.fail() || nights < 1 || nights>90)                                             //the customers can not book the hotel for less than 1 night or more than 90 nights (our hotel policy)
				{
					cout << "\nThere are a few rules when choosing how many nights your staying:\n-Remember to put in an integer number\n-You can not stay at the hotel for less than one night(Hotel policy)" << endl;
					cout << "-You can not stay in the hotel for more than three months(90 days) at a time!(Hotel policy)\nNow try again:  ";
					cin.clear();
					cin.ignore(256, '\n');
					cin >> nights;
				}

				customers[customer_number].nights_staying = nights;
				rooms[customers[customer_number].room_number - 1].nights = nights;



				if (rooms[customers[customer_number].room_number - 1].discount == 1)                      //within this if statement is the discount explainer, it tells why the rooms are discounted and how much
				{
					cout << "\nRoom number " << customers[customer_number].room_number << " is a room with a sea view, so there is no discount.\n";
				}
				else if (rooms[customers[customer_number].room_number - 1].discount == 2)
				{
					cout << "\nRoom number " << customers[customer_number].room_number << " is a room with a seaview but not directly, so the discount is 10 % \n";
				}
				else cout << "\nRoom number " << customers[customer_number].room_number << " is a room with a garden view, the discount on it is 20 % \n";



				if (rooms[customers[customer_number].room_number - 1].discount == 1)                        //gives the discounts a value that can be used in calculations
				{
					discount_recieved = 0;
				}
				else if (rooms[customers[customer_number].room_number - 1].discount == 2)
				{
					discount_recieved = 10;
				}
				else if (rooms[customers[customer_number].room_number - 1].discount == 3)
				{
					discount_recieved = 20;
				}
				else cout << "\n\nSomething unexpected happened,please contact an administrator.\n\n";



				cout << "The price of your stay after the discount would be: " << Price(customers, customer_number) - (Price(customers, customer_number) * discount_recieved / 100) << " euros." << endl;;



				rooms[customers[customer_number].room_number - 1].price = Price(customers, customer_number);  //assigns the price to the room

				int isBooked;
				isBooked = booking();
				if (isBooked == 0)                                                                            //here we are checking if the customer decided to book the room or canceled before booking it
				{
					int booking_number = bookingNumber();

					customers[customer_number].reservation = booking_number;

					cout << "\n\nBooking successful!\n\nYour booking number is :" << booking_number << "\nYour room number is " << customers[customer_number].room_number << endl;
					cout << "\nPlease remember this information as it is necessairy to check your reservation and checkout! \n";

					rooms[customers[customer_number].room_number - 1].booked_number = booking_number;


					Invoice(customers, rooms, customers[customer_number].room_number);


					if (customer_number < 70)                                                                 //for every customer, since there are 70 rooms in the hotel, it assigns a value, to store their information inside of an array
					{                                                                                         //while its less than 70, the number goes up and when it reaches the maximum ammount, it starts from the beginning again
						customer_number++;
					}
					else customer_number = 0;
				}
				else                                                                                          //if the customer doesnt proceed with the booking,the room is returned to default values so it can be booked by someone else
				{                                                                                             //it also doesnt change the customer number since the booking was cancelled and the sot wasnt taken
					rooms[customers[customer_number].room_number - 1].is_available = true;
					rooms[customers[customer_number].room_number - 1].customersName = "Yug0slavia";
					rooms[customers[customer_number].room_number - 1].booked_number = 9999;
				}


			}
		}
		else if (option == 2)                                                                                 //the following code just calls the remaining menu options
		{
			checkReservation(rooms, customers);
		}
		else if (option == 3)
		{
			menu_option_3();
		}
		else if (option == 4)
		{
			checkout(rooms);
		}
		else if (option == 5)
		{
			cout << "\nThanks for using Poseidon services, have a nice day!\n";
			continuation = false;
		}
		else {
			cout << "Oopsie, that wasnt the correct input, lets try again.";
		}



	}
}