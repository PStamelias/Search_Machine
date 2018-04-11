struct keimeno{
	int id;
	char *symbols;
};
struct vision{
	int grammi_keimenou;
	int fores_emfanisis;
	struct vision* next;
};
struct posting_list{
	int counter; 
	int came;
	struct vision * beg;
};
struct gramma{
	char xaraktiras;
	struct gramma * next;
	struct gramma * paidi;
	struct posting_list * my_list;
};