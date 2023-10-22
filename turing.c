#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definesc structura nodurilor din coada
typedef struct queue_node
{
  char data[100];
  struct queue_node *next;
} queue_node;

// Definesc coada, cu doua noduri, head si tail, pentru a extrage din coada
// noduri si pentru a putea insera noduri in coada
typedef struct queue
{
  queue_node *head;
  queue_node *tail;
} queue;

// Definesc structura nodurilor din lista dublu inlantuita
typedef struct node
{
  struct node *prev;
  char data;
  struct node *next;
} node;

// Definesc banda magica, cu doua noduri, head si finger, pentru a putea stii
// inceputul listei si pentru a retine pozitia curenta
typedef struct list
{
  node *head;
  node *finger;
} list;

// Definesc structura nodurilor din stive
typedef struct stiva_nod
{
  node *data;
  struct stiva_nod *prev;
} stiva_nod;

// Definesc stiva, cu un singur nod tail, pentru a putea insera si extrage noduri
// in stiva
typedef struct stiva
{
  stiva_nod *tail;
} stiva;

// Functia de inceput de program, care initializeaza stivele coada si lista cu NULL
void init_program(queue *q, stiva *s, stiva *r, list *l)
{
  q->head = NULL;
  q->tail = NULL;
  s->tail = NULL;
  r->tail = NULL;

  l->head = malloc(sizeof(node));
  l->head->next = NULL;
  l->head->prev = NULL;
  l->head->data = '-';

  node *new_node = malloc(sizeof(node));
  new_node->next = NULL;
  new_node->prev = l->head;
  new_node->data = '#';

  l->head->next = new_node;
  l->finger = new_node;
}

// Functie care adauga un nod nou in coada, ce contine comenzile inainte sa se
// dea EXECUTE
void enqueue(queue *q, char *data)
{
  queue_node *new_node = malloc(sizeof(queue_node));
  strcpy(new_node->data, data);
  new_node->next = NULL;

  if (q->head == NULL)
  {
    q->head = new_node;
    q->tail = new_node;
  }
  else
  {
    q->tail->next = new_node;
    q->tail = new_node;
  }
}

// Functie care adauga un nod nou in stiva, ce contine noduri din lista
void putu(stiva *u, node *n)
{
  stiva_nod *new = malloc(sizeof(stiva_nod));
  new->data = n;
  new->prev = u->tail;
  u->tail = new;
}

// Functie care arata toata banda, si incadreaza nodul curent intre "|"
void show(list *l, FILE *out_file)
{
  node *current_node = l->head->next;
  while (current_node != NULL)
  {
    if (current_node != l->finger)
    {
      fprintf(out_file, "%c", current_node->data);
      current_node = current_node->next;
    }
    else
    {
      fprintf(out_file, "|%c|", current_node->data);
      current_node = current_node->next;
    }
  }
  fprintf(out_file, "\n");
}

// Functie care arata valoarea nodului curent din banda
void show_current(list *l, FILE *out_file)
{
  fprintf(out_file, "%c\n", l->finger->data);
}

// Functie care schimba valoarea nodului curent din badnda
void scrie(list *l, char date)
{
  l->finger->data = date;
}

// Functie care misca nodul curent cu o pozitie inspre stanga, iar daca nu
// exista un nod in stanga nu face nimic
void move_left(list *l, stiva *u)
{
  if (l->finger->prev != l->head)
  {
    putu(u, l->finger);
    l->finger = l->finger->prev;
  }
}

// Functie care misca nodul curent cu o pozitie inspre dreapta, iar daca nu
// exista nod in dreapta, creeaza unul cu valoarea "#"
void move_right(list *l, stiva *u)
{
  if (l->finger->next != NULL)
  {
    putu(u, l->finger);
    l->finger = l->finger->next;
  }
  else
  {
    putu(u, l->finger);
    node *new_node = malloc(sizeof(node));
    new_node->data = '#';
    new_node->prev = l->finger;
    new_node->next = NULL;
    l->finger->next = new_node;
    l->finger = l->finger->next;
  }
}

// Functie care adauga un nod nou in stanga nodului actual din banda, iar daca
// nodul curent este primul nod din banda afiseaza "ERROR"
void insert_left(list *l, char date, FILE *out_file)
{
  if (l->finger->prev == l->head)
  {
    fprintf(out_file, "ERROR\n");
  }
  if (l->finger != l->head->next)
  {
    node *new_node = malloc(sizeof(node));
    new_node->data = date;

    new_node->prev = l->finger->prev;
    new_node->next = l->finger;
    l->finger->prev->next = new_node;
    l->finger->prev = new_node;

    l->finger = new_node;
  }
}

// Functie care adauga un nod nou in dreapta nodului actual din banda
void insert_right(list *l, char date)
{
  if (l->finger->next == NULL)
  {
    node *new_node = malloc(sizeof(node));
    new_node->data = date;
    new_node->next = NULL;
    l->finger->next = new_node;
    new_node->prev = l->finger;
    l->finger = new_node;
  }
  if (l->finger->next != NULL)
  {
    node *new_node = malloc(sizeof(node));
    new_node->data = date;
    new_node->next = l->finger->next;
    new_node->next->prev = new_node;
    new_node->prev = l->finger;
    l->finger->next = new_node;
    l->finger = new_node;
  }
}

// Functie care misca nodul curent la stanga pana cand gaseste un nod cu aceeasi
// valoare ca cea data, iar daca nu gaseste, afiseaza ERROR si nu se muta
void move_left_char(list *l, char date, stiva *u, FILE *out_file)
{
  putu(u, l->finger);
  node *new_node = l->finger;
  while (l->finger->prev != l->head && l->finger->data != date)
    l->finger = l->finger->prev;
  if (l->finger->data != date)
  {
    fprintf(out_file, "ERROR\n");
    l->finger = new_node;
  }
}

// Functie care misca nodul curent la dreapta pana cand gaseste un nod cu aceeasi
// valoare ca cea data, iar daca nu gaseste, creeaza unul nou cu valoarea "#"
void move_right_char(list *l, char date, stiva *u)
{
  putu(u, l->finger);
  while (l->finger->next != NULL && l->finger->data != date)
    l->finger = l->finger->next;
  if (l->finger->data != date)
  {
    node *new_node = malloc(sizeof(node));
    new_node->data = '#';
    new_node->prev = l->finger;
    new_node->next = NULL;
    l->finger->next = new_node;
    l->finger = l->finger->next;
  }
}

// Functie de undo la pasii precedenti pe care ii facem in banda(doar de miscare)
// si adauga in stiva redo pasii facuti
void undo(list *l, stiva *u, stiva *r)
{
  if (u->tail != NULL)
  {
    putu(r, l->finger);
    stiva_nod *man = u->tail;
    l->finger = u->tail->data;
    u->tail = u->tail->prev;
    free(man);
  }
}

// Functie de redo la pasii facuti in undo, si adauga in stiva undo pasii facuti
void redo(list *l, stiva *u, stiva *r)
{
  if (r->tail != NULL)
  {
    putu(u, l->finger);
    stiva_nod *man = r->tail;
    l->finger = r->tail->data;
    r->tail = r->tail->prev;
    free(man);
  }
}

// Functie care goleste o stiva de toate elementele din ea
void clear(stiva *s)
{
  while (s->tail != NULL)
  {
    stiva_nod *man = s->tail;
    s->tail = s->tail->prev;
    free(man);
  }
}

// Functia execute, care citeste prima comanda din coada si o executa
void execute(list *l, queue *q, stiva *u, stiva *r, FILE *out_file)
{
  if (strncmp(q->head->data, "MOVE_LEFT_CHAR", 14) == 0)
    move_left_char(l, q->head->data[15], u, out_file);
  else if (strncmp(q->head->data, "MOVE_LEFT", 9) == 0)
    move_left(l, u);
  if (strncmp(q->head->data, "MOVE_RIGHT_CHAR", 15) == 0)
    move_right_char(l, q->head->data[16], u);
  else if (strncmp(q->head->data, "MOVE_RIGHT", 10) == 0)
    move_right(l, u);
  if (strncmp(q->head->data, "INSERT_RIGHT", 12) == 0)
    insert_right(l, q->head->data[13]);
  if (strncmp(q->head->data, "INSERT_LEFT", 11) == 0)
    insert_left(l, q->head->data[12], out_file);
  if (strncmp(q->head->data, "WRITE", 5) == 0)
  {
    scrie(l, q->head->data[6]);
    clear(u);
    clear(r);
  }
  queue_node *man = q->head;
  q->head = q->head->next;
  free(man);
}

// Functia de sfarsit de program, care da free la stive, lista si la coada si
// care inchide fisierele
void end_program(list *l, queue *q, stiva *u, stiva *r, FILE *out_file, FILE *in_file)
{
  clear(u);
  clear(r);
  fclose(in_file);
  fclose(out_file);
  while (q->head != NULL)
  {
    queue_node *man1 = q->head;
    q->head = q->head->next;
    free(man1);
  }
  while (l->head != NULL)
  {
    node *man2 = l->head;
    l->head = l->head->next;
    free(man2);
  }
}

int main()
{
  FILE *in_file = fopen("tema1.in", "r");
  FILE *out_file = fopen("tema1.out", "w");
  int n, i;
  char buffer[100];
  queue q;
  stiva u;
  stiva r;
  list l;
  init_program(&q, &u, &r, &l);
  fscanf(in_file, "%d", &n);
  fgets(buffer, 100, in_file);
  for (i = 0; i < n; i++)
  {
    fgets(buffer, 100, in_file);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strncmp(buffer, "SHOW_CURRENT", 12) == 0)
      show_current(&l, out_file);
    else if ((strncmp(buffer, "SHOW", 4) == 0))
      show(&l, out_file);
    if ((strncmp(buffer, "EXECUTE", 7) != 0) &&
        (strncmp(buffer, "SHOW_CURRENT", 12) != 0) &&
        (strncmp(buffer, "SHOW", 4) != 0) &&
        (strncmp(buffer, "UNDO", 4) != 0) &&
        (strncmp(buffer, "REDO", 4) != 0))
      enqueue(&q, buffer);
    if (strncmp(buffer, "EXECUTE", 7) == 0)
      execute(&l, &q, &u, &r, out_file);
    if ((strncmp(buffer, "UNDO", 4) == 0))
      undo(&l, &u, &r);
    if ((strncmp(buffer, "REDO", 4) == 0))
      redo(&l, &u, &r);
  }
  end_program(&l, &q, &u, &r, out_file, in_file);
  return 0;
}