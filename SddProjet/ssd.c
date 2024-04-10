#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Article
{
    int code;
    int quantite;
    double prixUnitaire;
    struct Article *nextArticle;
} Article;

typedef struct Client
{
    int matricule;
    char nom[50];
    char adresse[100];
    char telephone[20];
    Article *articles;
    struct Client *nextClient;
} Client;

void ajouterClient(Client **head, int matricule, char *nom, char *adresse, char *telephone)
{
    Client *newClient = (Client *)malloc(sizeof(Client));
    newClient->matricule = matricule;
    strcpy(newClient->nom, nom);
    strcpy(newClient->adresse, adresse);
    strcpy(newClient->telephone, telephone);
    newClient->articles = NULL;
    newClient->nextClient = (*head);
    (*head) = newClient;
}

void afficherClient(Client *head, int matricule)
{
    Client *current = head;
    while (current != NULL)
    {
        if (current->matricule == matricule)
        {
            printf("Matricule: %d\n", current->matricule);
            printf("Nom: %s\n", current->nom);
            printf("Adresse: %s\n", current->adresse);
            printf("Telephone: %s\n", current->telephone);
            // Afficher les articles ici
            return;
        }
        current = current->nextClient;
    }
    printf("Client non trouve\n");
}

// Ajouter un article à la liste des articles d'un client donné par son matricule.
void ajouterArticle(Client *head, int matricule, int code, int quantite, double prixUnitaire)
{
    Client *current = head;
    while (current != NULL)
    {
        if (current->matricule == matricule)
        {
            Article *newArticle = (Article *)malloc(sizeof(Article));
            newArticle->code = code;
            newArticle->quantite = quantite;
            newArticle->prixUnitaire = prixUnitaire;
            newArticle->nextArticle = current->articles;
            current->articles = newArticle;
            return;
        }
        current = current->nextClient;
    }
    printf("Client non trouve\n");
}

void supprimerClient(Client **head, int matricule)
{
    Client *previous = NULL;
    Client *current = *head;

    while (current != NULL)
    {
        if (current->matricule == matricule)
        {
            if (previous == NULL)
            {
                *head = current->nextClient;
            }
            else
            {
                previous->nextClient = current->nextClient;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->nextClient;
    }

    printf("Client non trouve\n");
}

// 5. Modifier l'adresse ou le téléphone d'un client
void modifierClient(Client *head, int matricule, char *nouvelleAdresse, char *nouveauTelephone)
{
    Client *current = head;
    while (current != NULL)
    {
        if (current->matricule == matricule)
        {
            strcpy(current->adresse, nouvelleAdresse);
            strcpy(current->telephone, nouveauTelephone);
            return;
        }
        current = current->nextClient;
    }

    printf("Client non trouve\n");
}

void editerFacture(Client *head, int matricule)
{
    Client *current = head;
    while (current != NULL)
    {
        if (current->matricule == matricule)
        {
            double total = 0.0;
            Article *currArticle = current->articles;
            while (currArticle != NULL)
            {
                double cost = currArticle->quantite * currArticle->prixUnitaire;
                total += cost;

                printf("\nArticle Code: %d\n", currArticle->code);
                printf("Quantite: %d\n", currArticle->quantite);
                printf("Prix Unitaire: %.2f\n", currArticle->prixUnitaire);
                printf("Cout Total de l'Article: %.2f\n", cost);

                currArticle = currArticle->nextArticle;
            }

            printf("\nCout Total de la Commande: %.2f\n", total);
            return;
        }
        current = current->nextClient;
    }
    printf("Client non trouve\n");
}

// 11. Afficher tous les clients
void afficherTousClients(Client *head)
{
    Client *current = head;
    while (current != NULL)
    {
        printf("Matricule: %d\n", current->matricule);
        printf("Nom: %s\n", current->nom);
        printf("Adresse: %s\n", current->adresse);
        printf("Telephone: %s\n", current->telephone);
        current = current->nextClient;
    }
}

// 10. Annuler toute la commande d'un client
void annulerCommande(Client *head, int matricule)
{
    Client *current = head;
    while (current != NULL)
    {
        if (current->matricule == matricule)
        {
            Article *currArticle = current->articles;
            while (currArticle != NULL)
            {
                Article *nextArticle = currArticle->nextArticle;
                free(currArticle);
                currArticle = nextArticle;
            }
            current->articles = NULL;
            return;
        }
        current = current->nextClient;
    }

    printf("Client non trouve\n");
}
// Annuler un article commandé par un client donné par son matricule.
void annulerArticle(Client *head, int matricule, int code)
{
    Client *current = head;
    while (current != NULL)
    {
        if (current->matricule == matricule)
        {
            Article *prevArticle = NULL;
            Article *currArticle = current->articles;
            while (currArticle != NULL)
            {
                if (currArticle->code == code)
                {
                    if (prevArticle == NULL)
                    {
                        current->articles = currArticle->nextArticle;
                    }
                    else
                    {
                        prevArticle->nextArticle = currArticle->nextArticle;
                    }
                    free(currArticle);
                    return;
                }
                prevArticle = currArticle;
                currArticle = currArticle->nextArticle;
            }
            printf("Article non trouve\n");
            return;
        }
        current = current->nextClient;
    }
    printf("Client non trouve\n");
}

// Changer la quantité commandée d'un article d'un client donné par son matricule.
void changerQuantite(Client *head, int matricule, int code, int nouvelleQuantite)
{
    Client *current = head;
    while (current != NULL)
    {
        if (current->matricule == matricule)
        {
            Article *currArticle = current->articles;
            while (currArticle != NULL)
            {
                if (currArticle->code == code)
                {
                    currArticle->quantite = nouvelleQuantite;
                    return;
                }
                currArticle = currArticle->nextArticle;
            }
            printf("Article non trouve\n");
            return;
        }
        current = current->nextClient;
    }
    printf("Client non trouve\n");
}

// Afficher la liste des articles commandés par un client donné par son matricule.
void afficherArticles(Client *head, int matricule)
{
    Client *current = head;
    while (current != NULL)
    {
        if (current->matricule == matricule)
        {
            Article *currArticle = current->articles;
            while (currArticle != NULL)
            {
                printf("Code: %d\n", currArticle->code);
                printf("Quantite: %d\n", currArticle->quantite);
                printf("Prix Unitaire: %.2f\n", currArticle->prixUnitaire);
                currArticle = currArticle->nextArticle;
            }
            return;
        }
        current = current->nextClient;
    }
    printf("Client non trouve\n");
}

void ajouterClient(Client **head, int matricule, char *nom, char *adresse, char *telephone);
void afficherClient(Client *head, int matricule);
void ajouterArticle(Client *head, int matricule, int code, int quantite, double prixUnitaire);
void annulerArticle(Client *head, int matricule, int code);
void changerQuantite(Client *head, int matricule, int code, int nouvelleQuantite);
void afficherArticles(Client *head, int matricule);
void supprimerClient(Client **head, int matricule);
void modifierClient(Client *head, int matricule, char *nouvelleAdresse, char *nouveauTelephone);
void afficherTousClients(Client *head);
void annulerCommande(Client *head, int matricule);
void editerFacture(Client *head, int matricule);

int obtenirChoix();

int main()
{
    int choix;
    Client *clients = NULL;

    do
    {
        choix = obtenirChoix();

        int matricule;
        char nom[50];
        char adresse[100];
        char telephone[20];
        int code;
        int quantite;
        double prixUnitaire;

        switch (choix)
        {
        case 1:
            printf("Entrez le matricule: ");
            scanf("%d", &matricule);

            printf("Entrez le nom: ");
            scanf("%s", nom);

            printf("Entrez l'adresse: ");
            scanf("%s", adresse);

            printf("Entrez le telephone: ");
            scanf("%s", telephone);

            ajouterClient(&clients, matricule, nom, adresse, telephone);
            break;

        case 2:
            printf("Entrez le matricule: ");
            scanf("%d", &matricule);

            afficherClient(clients, matricule);
            break;

        case 4:
            printf("Entrez le matricule: ");
            scanf("%d", &matricule);

            editerFacture(clients, matricule);
            break;

        case 6:
            printf("Entrez le matricule: ");
            scanf("%d", &matricule);

            printf("Entrez le code de l'article: ");
            scanf("%d", &code);

            printf("Entrez la quantite: ");
            scanf("%d", &quantite);

            printf("Entrez le prix unitaire: ");
            scanf("%lf", &prixUnitaire);

            ajouterArticle(clients, matricule, code, quantite, prixUnitaire);
            break;

        case 3:
            printf("Entrez le matricule: ");
            scanf("%d", &matricule);

            supprimerClient(&clients, matricule);
            break;

        case 5:
            printf("Entrez le matricule: ");
            scanf("%d", &matricule);

            printf("Entrez la nouvelle adresse: ");
            scanf("%s", adresse);

            printf("Entrez le nouveau telephone: ");
            scanf("%s", telephone);

            modifierClient(clients, matricule, adresse, telephone);
            break;

        case 10:
            printf("Entrez le matricule: ");
            scanf("%d", &matricule);

            annulerCommande(clients, matricule);
            break;

        case 11:
            afficherTousClients(clients);
            break;

        case 7:
            printf("Entrez le matricule: ");
            scanf("%d", &matricule);

            printf("Entrez le code de l'article: ");
            scanf("%d", &code);

            annulerArticle(clients, matricule, code);
            break;

        case 8:
            printf("Entrez le matricule: ");
            scanf("%d", &matricule);

            printf("Entrez le code de l'article: ");
            scanf("%d", &code);

            printf("Entrez la nouvelle quantite: ");
            scanf("%d", &quantite);

            changerQuantite(clients, matricule, code, quantite);
            break;

        case 9:
            printf("Entrez le matricule: ");
            scanf("%d", &matricule);

            afficherArticles(clients, matricule);
            break;

        case 12:
            printf("Au revoir!\n");
            break;
        default:
            printf("Option invalide, veuillez choisir une option valide.\n");
            break;
        }
    } while (choix != 12);

    return 0;
}

int obtenirChoix()
{
    int choix;

    printf("\n~~~~~~~~~~~\n");
    printf("Menu\n");
    printf("~~~~~~~~~\n\n");

    printf("1. Ajouter un client\n");
    printf("2. Afficher les informations d'un client\n");
    printf("3. Supprimer un client\n");
    printf("4. Editer la facture d'un client\n");
    printf("5. Modifier l'adresse ou le telephone d'un client\n");
    printf("6. Ajouter un article a la liste des articles d'un client\n");
    printf("7. Annuler un article commande par un client\n");
    printf("8. Changer la quantite commandee d'un article d'un client\n");
    printf("9. Afficher la liste des articles commandes par un client\n");
    printf("10. Annuler toute la commande d'un client\n");
    printf("11. Afficher tous les clients\n");
    printf("12. Quitter\n");
    printf("~~~~~~~~~\n");
    printf("Choisissez une option: ");

    scanf("%d", &choix);

    return choix;
}