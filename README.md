Turing Machine

Am implementat programul folosind o lista dublu inlantuita, care reprezinta 
"banda magica", o coada, doua stive si functii de write, show, move, insert,
undo si redo pentru lista.

Am definit structura "queue" care este folosita la implementarea cozii si are 
doua noduri: "head", care este folosit la extragerea informatiilor din coada si
"tail" care este folosit la inserarea informatiilor in coada

Am definit structura "queue_node" care reprezinta nodurile din coada, care au in
componenta "data" care este un vector care retine comenzile pe care programul le 
va executa la comanda "EXECUTE" si "next" care retine adresa urmatorului nod din 
coada

Am definit structura "list" care este folosita la implementarea "benzii magice"
si are doua noduri: "head", care este folosit la retinerea santinelei listei
pentru a afisa mai tarziu toate elementele din banda si "finger" care este folosit
la retinerea aresei nodului curent

Am definit structura "node" care reprezinta nodurile din lista, care au in 
componenta "data" care stocheaza caracterele din lista, si "prev" si "next" care
stocheaza adresele nodurilor vecine

Am defini structura "stiva" care este folosita la implementarea comenzilor "UNDO"
si "REDO" si are un nod "tail", care este necesar atat pentru extragerea cat si 
pentru inserarea de informatie in stiva

Am definit strucutra "stiva_nod" care reprezinta nodurile din stiva, care au in
componenta "data" care stocheaza penultima adresa a degetului si "tail" care 
stocheaza adresa urmatorului nod din stiva

Am definit functia "init_program" care initializeaza coada, stivele, creeaza 
santinela listei cat si primul nod, care stocheaza automat valoarea "#"

Am definit functia "enqueue" care insereaza un nod nou in coada

Am definit functia "putu" care insereaza un nod nou in stiva

Am definit functia "show" care afiseaza intreaga lista si incadreaza nodul la 
care pointeaza degetul cu "|"

Am definit functia "show_current" care afiseaza doar caracterul din nodul curent

Am definit funtia "scrie" care schimba caracterul din nodul curent cu un caracter 
indicat dupa comanda

Am definit functia "move_left" care muta pozitia degetului cu un nod inspre stanga
in cazul in care exista un nod in stanga, iar daca nu exista nu se modifica nimic

Am definit functia "move_right" care muta pozitia degetului cu un nod inspre dreapta
in cazul in care exista un nod in dreapta, iar daca nu exista creeaza unul care 
stocheaza caracterul "#"

Am definit functia "insert_left" care insereaza la stanga nodului curent un nod
nou in care se stocheaza valoarea indicata de dupa comanda, in cazul in care 
nodul curent nu este primul nod din banda, iar daca este primul nod se afiseaza 
"ERROR"

Am definit functia "insert_right" care insereaza la dreapta nodului curent un nod
nou in care se stocheaza valoarea indicata de dupa comanda, chiar daca e sau nu
ultimul nod din lista

Am definit functia "move_left_char" care muta degetul de la pozitia curenta spre 
stanga pana la prima aparitie(de la deget) a caracterului de dupa comanda, iar 
in cazul in care nu este nici una, se afiseaza "ERROR" si nu se intampla nimic

Am definit functia "move_right_char" care muta degetul de la pozitia curenta spre 
dreapta pana la prima aparitie(de la deget) a caracterului de dupa comanda, iar 
in cazul in care nu este nici una, se creeaza un nod nou ce contine caracterul 
"#"

Am definit functia "undo" care insereaza in stiva redo adresa curenta a degetului
apoi extrage din stiva undo adresa ultimului nod si duce degetul acolo

Am definit functia "redo" care insereaza in stiva undo adresa curenta a degetului
apoi extrage din stiva redo adresa ultimului nod si duce degetul acolo, si este 
operatia inversa a functiei "undo"

Am definit functia "clear" care "curata" o stiva data

Am definit functia "execute" care executa functia potrivita pentru fiecare comanda
data de utilizator, preluata din coada si apoi o elibereaza

Am definit functia "end_program" care inchide fisierele, curata stivele de undo
si redo, curata coada si lista

In functia main deschid fisierul "tema.in" din care extrag informatiile necesare:
numarul de comenzi pe care il introduc in variabila n si toate comenzile pe care 
cu ajutorul vectorului de caractere "buffer" le introduc in coada sau le rulez
(doar EXECUTE, UNDO, REDO, SHOW, SHOW_CURRENT) si fisierul "tema.out" in care 
afisez rezultatele 