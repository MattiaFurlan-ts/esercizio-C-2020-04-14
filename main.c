#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 64
#define PHONE_LEN 20

typedef struct
{
   int id; // id numerico del contatto (valore univoco)
   char name[NAME_LEN + 1]; // nome della persona
   char phone[PHONE_LEN + 1]; // numero di telefono
} contact_type;

contact_type *create_contact (char *name, char *phone)
{
    contact_type *c = malloc (sizeof (contact_type));
    if (!c)
    	perror ("malloc");

    static int counter = 0;
    c->id = counter++;
    strncpy (c->name, name, NAME_LEN + 1);
    strncpy (c->phone, phone, PHONE_LEN + 1);
    return c;
}

void print_contact (contact_type *person)
{
    printf ("person: id=%d, name='%s', phone='%s'\n", person->id, person->name, person->phone);
}

#define ADDRESS_BOOK_SIZE 256

contact_type *address_book[ADDRESS_BOOK_SIZE];

int compare_contacts (contact_type *c1, contact_type *c2)
{
	if (!c1 || !c2)
		return -1;
	if (!strcmp (c1->name, c2->name) && !strcmp (c1->phone, c2->name))
		return 0;
	return strcmp (c1->name, c2->name);
}

int add_to_address_book (contact_type *c)
{
	for (int i = 0; i < ADDRESS_BOOK_SIZE; i++)
		if (!address_book[i])
		{
			address_book[i] = c;
			return i;
		}
	return -1;
}

int search_in_address_book (contact_type *c)
{
	for (int i = 0; i < ADDRESS_BOOK_SIZE; i++)
		if (address_book[i] && !compare_contacts (address_book[i], c))
			return i;
	return -1;
}

int remove_from_address_book (contact_type *c)
{
	int pos = search_in_address_book (c);
	return pos > 0 ? (address_book[pos] = NULL, pos) : -1;
}

void sort_by_name ()
{
	for (int i = 0; i < ADDRESS_BOOK_SIZE; i++)
	{
		if (!address_book[i])
			continue;
		for (int j = i + 1; j < ADDRESS_BOOK_SIZE; j++)
		{
			if (address_book[j] && compare_contacts (address_book[i], address_book[j]) > 0)
			{
				contact_type *buffer = address_book[i];
				address_book[i] = address_book[j];
				address_book[j] = buffer;
			}
		}
	}
}

void print_address_book ()
{
	printf ("Rubrica:\n");
	for (int i = 0; i < ADDRESS_BOOK_SIZE; i++)
		if (address_book[i])
			print_contact (address_book[i]);
}

int main ()
{
	char *names[] = {"dino", "filippo", "barbara", "antonio", "enrico", "chiara"};
	char *phones[] = {"+391237", "+391239", "+391235", "+391234", "+391238", "+391236"};

	for (int i = 0; i < sizeof (names) / sizeof (names[0]); i++)
		add_to_address_book (create_contact (names[i], phones[i]));

	contact_type *antonio = create_contact ("antonio", "+391238");
	remove_from_address_book (antonio);
	add_to_address_book (create_contact ("pino", "+399999"));
	print_address_book ();
	add_to_address_book (antonio);
	sort_by_name ();
	print_address_book ();
	return 0;
}
