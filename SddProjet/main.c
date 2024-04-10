#include <stdio.h>
#include <gtk/gtk.h>

struct Customer {
  int customerNumber;
  char *surname;
  char *firstName;
  char *address;
  char *telephone;
  struct Item *itemList;
  struct Customer *nextCustomer;
};

struct Item { 
  int itemCode;
  int quantity;
  float unitPrice;
  struct Item *nextItem;
};

void addCustomer(struct Customer **head, int customerNumber, char *surname, char *firstName, char *address, char *telephone) {
  struct Customer *newCustomer = malloc(sizeof(struct Customer));
  newCustomer->customerNumber = customerNumber;
  newCustomer->surname = surname;
  newCustomer->firstName = firstName;
  newCustomer->address = address;
  newCustomer->telephone = telephone;
  newCustomer->itemList = NULL;
  newCustomer->nextCustomer = *head;
  *head = newCustomer;
}

void addItem(struct Customer *customer, int itemCode, int quantity, float unitPrice) {
  struct Item *newItem = malloc(sizeof(struct Item));
  newItem->itemCode = itemCode;
  newItem->quantity = quantity;
  newItem->unitPrice = unitPrice;
  newItem->nextItem = customer->itemList;
  customer->itemList = newItem;
}

void printCustomers(struct Customer *head) {
  while (head != NULL) {
    printf("Customer number: %d\n", head->customerNumber);
    printf("Surname: %s\n", head->surname);
    printf("First name: %s\n", head->firstName);
    printf("Address: %s\n", head->address);
    printf("Telephone: %s\n", head->telephone);
    printf("Items ordered:\n");
    struct Item *item = head->itemList;
    while (item != NULL) {
      printf("Item code: %d\n", item->itemCode);
      printf("Quantity: %d\n", item->quantity);
      printf("Unit price: %.2f\n", item->unitPrice);
      item = item->nextItem;
    }
    printf("\n");
    head = head->nextCustomer;
  }
}



int main(int argc, char *argv[]) {
  GtkWidget *window;
  GtkWidget *label;
  GtkWidget *textBox;
  GtkWidget *button;

  gtk_init(&argc, &argv);

  /* Create a window */
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Customer and Item Management System");

  /* Create a label */
  label = gtk_label_new("Welcome to the Customer and Item Management System!");

  /* Create a text box */
  textBox = gtk_entry_new();

  /* Create a button */
  button = gtk_button_new_with_label("Add Customer");

  /* Connect the button to the add customer function */
  g_signal_connect(button, "clicked", G_CALLBACK(addCustomer), window);

  /* Add the label to the window */
  gtk_container_add(GTK_CONTAINER(window), label);

  /* Add the text box to the window */
  gtk_container_add(GTK_CONTAINER(window), textBox);

  /* Add the button to the window */
  gtk_container_add(GTK_CONTAINER(window), button);

  /* Show the window */
  gtk_widget_show_all(window);

  /* Start the main loop */
  gtk_main();

  return 0;
}
