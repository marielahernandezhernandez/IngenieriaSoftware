  #include <stdio.h>

typedef struct{
char nombre[30];
int bonus;
int vigencia;
}Cancion;


typedef struct{
const char nombre[30];
int popularidad;
int energia;
int energia_max;
int fans;
Cancion *cancion;
}Idol;


typedef struct{
char nombre[30];
Idol miembros[4];
int n;
Idol *lider;
}Grupo;



void mostrar(const Idol *i){
if (i == NULL){
return;
}
else{
printf("Nombre:%s\n", i-> nombre);
printf("Popularidad:%d\n", i-> popularidad);
printf("Energia:%d\n", i-> energia);
printf("Energia_max:%d\n", i-> energia_max);
printf("Fans:%d\n", i-> fans);
}
}


int limitar(int valor, int minimo, int maximo){
if(valor<minimo) return minimo;
if(valor>maximo) return maximo;;
return valor;
}


void ensayar(Idol *i){
if(i==NULL){
return;
}

i->popularidad = limitar(i->popularidad + 5, 0, i->energia_max);
i->energia = limitar(i->energia - 20, 0, i->energia_max);
}


void descansar(Idol *i){
if(i==NULL){
return;
}
i->energia = limitar(i->energia + 30, 0, i->energia_max);
}


int esta_activa(const Idol *i){
if(i->energia>0){
return 1;
}
else{
return 0;
}
}


int colaboracion(Idol *a, Idol *b){
if(a==NULL || b==NULL || a==b){
return 0;
}

a->popularidad += 10;
b->popularidad += 10;

a->energia= limitar(a->energia -15, 0, a->energia_max);
b->energia= limitar(b->energia -15, 0, b->energia_max);

printf("%s y %s hicieron colaboracion\n", a->nombre, b->nombre);
return 1;
}


void asignar_cancion(Idol *i, Cancion *c){
if(i==NULL){
return;
 }
 i->cancion=c;
}




int popularidad_total(const Idol *i){
if(i==NULL){
return 0;
}

int total = i->popularidad;

if(i->cancion != NULL && i->cancion->vigencia > 0){
total += i->cancion->bonus;
}
return total;
}



int cambiar_lider(Grupo *g, Idol *nueva) {
 if (g == NULL || nueva == NULL) {
 return 0;
 }

 for (int i = 0; i < g->n; i++) {
 if (nueva == &g->miembros[i]) {
 g->lider = nueva;
 return 1;
  }
 }

return 0;
}


void mostrar_grupo(const Grupo *g) {
 if (g == NULL) {
 printf("Grupo NULL\n");
return;
}

printf("Grupo: %s\n", g->nombre);

for (const Idol *p = g->miembros; p < g->miembros + g->n; p++) {
 printf("%s\n", p->nombre);
}

 printf("Recorrido inverso:\n");

for (const Idol *p = g->miembros + g->n; p > g->miembros; ) {
 p--;
printf("%s\n", p->nombre);
 }
}


int contar_activas(const Grupo *g) {
if (g == NULL) {
return 0;
}

int activas = 0;

for (const Idol *p = g->miembros;
p < g->miembros + g->n; p++) {
if (p->energia > 0) {
activas++;
 }
}
return activas;
}


Idol *idol_mas_cansada(Grupo *g) {
if (g == NULL || g->n == 0) {
return NULL;
}

Idol *menor = &g->miembros[0];

for (int i = 1; i < g->n; i++) {
if (g->miembros[i].energia < menor->energia) {
menor = &g->miembros[i];
 }
}

return menor;
}


void dar_concierto(Grupo *g) {
if (g == NULL) {
return;
}

for (int i = 0; i < g->n; i++) {
Idol *p = &g->miembros[i];

if (p->energia > 0) {

p->fans += popularidad_total(p) * 10;


 p->energia = limitar(p->energia - 15, 0, p->energia_max);

if (p->cancion != NULL && p->cancion->vigencia > 0) {
p->cancion->vigencia--;

if (p->cancion->vigencia == 0) {
printf("La cancion %s ya no esta vigente.\n",
p->cancion->nombre);
    }
   }
  }
 }
}

void mostrar_cancion_lider(const Grupo *g) {

 if (g == NULL) {
 printf("El grupo no existe.\n");
 return;
 }


 if (g->lider == NULL) {
 printf("El grupo no tiene lider.\n");
 return;
 }


if (g->lider->cancion == NULL) {
printf("La lider %s no tiene cancion.\n",g->lider->nombre);
return;
}

printf("Cancion de la lider: %s\n",g->lider->cancion->nombre);
}


void preparar_presentacion(Grupo *g) {
 if (g == NULL) {
return;
 }

 Idol *cansada = idol_mas_cansada(g);

if (cansada != NULL) {
 descansar(cansada);
 }

 dar_concierto(g);

 printf("\nResumen de presentacion\n");
    mostrar_grupo(g);

 printf("Integrantes activas: %d\n", contar_activas(g));
mostrar_cancion_lider(g);
}






int main(void){

Idol jennie = {"jennie", 50, 100, 100, 12000, NULL};
Idol rose = {"rose", 45, 90, 100, 10000, NULL};


Cancion discos[2]={
{"Starlight", 10, 3},
{"Nova", 5, 6}
};


//Hu14//
printf("\nAsignar canciones\n");
asignar_cancion(&jennie, &discos[0]);
asignar_cancion(&rose, &discos[0]);

printf("%s tiene la cancion: %s\n",
jennie.nombre, jennie.cancion->nombre);

printf("%s tiene la cancion: %s\n",
rose.nombre, rose.cancion->nombre);

asignar_cancion(&jennie, NULL);

if (jennie.cancion == NULL) {
printf("Jennie ya no tiene cancion asignada\n");
}



// HU-15: Probar con canción vigente //
discos[0].vigencia = 3;

asignar_cancion(&jennie, &discos[0]);
asignar_cancion(&rose, &discos[0]);

printf("\nCancion vigente:\n");
printf("Jennie: %d\n", popularidad_total(&jennie));
printf("Rose: %d\n", popularidad_total(&rose));

// Probar sin canción//
asignar_cancion(&jennie, NULL);
printf("jennie sin cancion: %d\n", popularidad_total(&jennie));

//Probar canción compartida con vigencia 0//
asignar_cancion(&jennie, &discos[0]);
discos[0].vigencia = 0;
printf("Cancion compartida con vigencia 0:\n");
printf("Jennie: %d\n", popularidad_total(&jennie));
printf("Rose: %d\n", popularidad_total(&rose));



//Hu16//
Grupo blackpink = {
    "BLACKPINK",
    {
{"jennie", 50, 100, 100, 12000, NULL},
{"rose", 45, 90, 100, 10000, NULL},
{"lisa", 40, 85, 100, 9000, NULL}
 },
 3,
 NULL
};

blackpink.lider = &blackpink.miembros[0];

printf("\nGrupo: %s\n", blackpink.nombre);
printf("Integrantes: %d\n", blackpink.n);
printf("Lider: %s\n", blackpink.lider->nombre);


//Hu17//
printf("\nCambiar lider\n");
if (cambiar_lider(&blackpink, &blackpink.miembros[1])) {
printf("Nuevo lider: %s\n", blackpink.lider->nombre);
}
else {
 printf("No se pudo cambiar el lider\n");
}

//Casos de rechazo //
Idol externa = {"rose", 45, 90, 100, 10000, NULL};
printf("Rechazo persona externa: %d\n",cambiar_lider(&blackpink, &externa));
printf("Rechazo puntero NULL: %d\n",cambiar_lider(&blackpink, NULL));

printf("Fans del lider: %d\n", blackpink.lider->fans);


//Hu18//
mostrar_grupo(NULL);
mostrar_grupo(&blackpink);


//Hu19//
blackpink.miembros[2].energia = 0;
printf("\nIdols activas: %d\n", contar_activas(&blackpink));
printf("Grupo NULL: %d\n", contar_activas(NULL));


//Hu20//
printf("\nIdol mas cansada\n");
Idol *cansada = idol_mas_cansada(&blackpink);
if (cansada != NULL) {
printf("Idol: %s\n", cansada->nombre);
printf("Energia antes de descansar: %d\n", cansada->energia);
descansar(cansada);
printf("Energia despues de descansar: %d\n", cansada->energia);
}

printf("Grupo NULL: %p\n", (void *)idol_mas_cansada(NULL));

Grupo vacio = {"Vacio", {
{"", 0, 0, 0, 0, NULL}
}, 0, NULL};
printf("Grupo vacio: %p\n", (void *)idol_mas_cansada(&vacio));


//*Hu21*//
Cancion cancion_concierto = {"Starlight", 10, 5};

for (int i = 0; i < blackpink.n; i++) {
    blackpink.miembros[i].energia = 100;
}

blackpink.miembros[0].cancion = &cancion_concierto;
blackpink.miembros[1].cancion = &cancion_concierto;

for (int vuelta = 1; vuelta <= 3; vuelta++) {
    printf("\nConcierto %d\n", vuelta);

    dar_concierto(&blackpink);

    printf("Fans de Jennie: %d\n", blackpink.miembros[0].fans);
    printf("Energia de Jennie: %d\n",
           blackpink.miembros[0].energia);
    printf("Vigencia de la cancion: %d\n",
           cancion_concierto.vigencia);
}

dar_concierto(NULL);

//Hu23//
//Escenario 1//
blackpink.lider->cancion = &cancion_concierto;
mostrar_cancion_lider(&blackpink);

// Escenario 2 //
blackpink.lider->cancion = NULL;
mostrar_cancion_lider(&blackpink);

// Escenario 3 //
Idol *lider_anterior = blackpink.lider;
blackpink.lider = NULL;
mostrar_cancion_lider(&blackpink);

blackpink.lider = lider_anterior;

mostrar_cancion_lider(NULL);



//Hu24//
// Preparar presentaciones//
for (int vuelta = 1; vuelta <= 3; vuelta++) {
    printf("\nPresentacion %d\n", vuelta);
    preparar_presentacion(&blackpink);

 for (int i = 0; i < blackpink.n; i++) {
 if (blackpink.miembros[i].energia < 0 ||
 blackpink.miembros[i].energia >
 blackpink.miembros[i].energia_max) {
 printf("ERROR: energia fuera de rango\n");
    }
  }
}


Idol *lider_guardado = blackpink.lider;
blackpink.lider = NULL;
preparar_presentacion(&blackpink);
blackpink.lider = lider_guardado;

Cancion *cancion_guardada = blackpink.lider->cancion;
blackpink.lider->cancion = NULL;
preparar_presentacion(&blackpink);
blackpink.lider->cancion = cancion_guardada;


//Hu02//
Idol *p = &jennie;
printf("%d\n", jennie.fans);
printf("%d\n", (*p).fans);
printf("%d\n", p->fans);

printf("%p %p \n", (void *)p, (void *)&jennie);

//HU03//
mostrar(&jennie);

//Hu04//
printf("\n\nPrueabas de limitar\n");
printf("Prueba 1: %d\n", limitar(-5, 0, 100));
printf("Prueba 2: %d\n", limitar(150, 0, 100));
printf("Prueba 3: %d\n", limitar(40, 0, 100));
printf("Prueba 3: %d\n", limitar(0, 0, 100));
printf("Prueba 3: %d\n\n", limitar(100, 0, 100));

//Hu05//
mostrar(&jennie);
for(int i=0; i<20;i++){
ensayar(&jennie);

}

mostrar(&jennie);

//Hu06//
for(int i=0; i<20;i++){
descansar(&jennie);
}
mostrar(&jennie);


//Hu07//
if(esta_activa(&jennie)){
printf("\njennie esta activa\n");
}
else{
printf("\njennie no esta activa\n");
}


//Hu09//
printf("\nColaboracion\n");
printf("Misma idol: %d\n",colaboracion(&jennie, &jennie));
printf("Apuntador NULL: %d\n", colaboracion(NULL, &rose));
printf("Colaboracion valida: %d\n", colaboracion(&jennie, &rose));


//Hu10//
printf("\nDinamica por turnos\n");
Idol *turno = &jennie;
Idol *otra = &rose;
Idol *temporal;

while(esta_activa(turno) && esta_activa(otra)){
    ensayar(turno);

    temporal = turno;
    turno = otra;
    otra = temporal;
}

if(esta_activa(turno)){
    printf("%s\nconserva energia.\n", turno->nombre);
}
else if(esta_activa(otra)){
    printf("%s\n conserva energia.\n", otra->nombre);
}
else{
    printf("\nAmbas integrantes se quedaron sin energia.\n");
}



//*Hu22*//
printf("\nArreglos y apuntadores\n");
printf("&miembros[0] = %p\n", (void *)&blackpink.miembros[0]);
printf("miembros + 0 = %p\n", (void *)(blackpink.miembros + 0));
printf("&miembros[1] = %p\n", (void *)&blackpink.miembros[1]);
printf("miembros + 1 = %p\n", (void *)(blackpink.miembros + 1));


/*Explicacion:
El nombre del arreglo representa la direccion de su primer
elemento.
&miembros[i] y miembros + i representan la misma direccion.
Sumar 1 a un apuntador avanza una Idol completa, no un byte.*/


return 0;
}


