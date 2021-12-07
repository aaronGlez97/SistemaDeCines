#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include<time.h>


//#include<time.h>

//#include <windows.h>
#define VALOR_CENTINELA -1
struct empleado{

    int idEmpleado;
    char nombreEmpleado[100];
    char apellidosEmpleado[100];
    char usuarioEmp[100];
    char password[100];


};



struct peliculas{
      int idPelicula;
      char nombrePelicula[100];
      char sinopsis[300];
      char clasificacion[40];
     char director[40];


};


struct ventas{
	
	int idVenta;
	int cantidadBoletos;
	int total;
	char peliculaVista[100];
	int sala;
	int turno;

};


struct corteGeneral{
	
	
	int idCorteGen;
	int totalBoletosVendi;
	int totalVentas;
	
	
	
};


struct salas{
	
	int idSala;
	char peliculaProy[100];
	char sinopPel[100];
	char clasificacion[100];
	
	int asDisponibles;
	int asOcupados;
	int turnoProyeccion;
	

};



//variable global para validar el inicio de sesion y manipular los menus principales 
int resul=0;

int elim_buscar_id;

void menuPrincipal();

int imprimirCartelera();

void mostrarIdYPelisRegis();

int validarIdPeli(int idIngresado);

void opcionesPeliculas();

char eliminacionFisica();         
char eliminarLogica();

int iniciarSesion(char usuario1[], char password1[]);

void registrarEmpleado();

int mostrarEmpleados();

void menuInicial();

void mostrarIdOcupados();

void asignarSala();

struct peliculas buscarPelicula(int idBuscar);

void imprimirSalas();


void imprimirSala2();

void imprimirSala1();

void modificarAsientosSala1();

void modificarAsientosSala2();
void ModificarPelicula();



int validarQueExistenPeliculasEnLaSala1();

int validarQueExistenPeliculasEnLaSala2();


void registrarVentasDelDia();

void imprimirVentas();



int validarIdSala(int idSala1);

int validarIdVenta(int idIngresado1);



void venderBoletos();



struct corteGeneral realizarElCorteDia1();



void imprimirCorteGeneral();


void registrarVentasDel(){
	
	

	
}



void imprimirCorteGeneral(){
	
	
	struct corteGeneral corte5;
	
	FILE *ptrCorte3=NULL;
	
	
	ptrCorte3= fopen("corteGeneral.dat", "rb");
	
	
	
	printf("\t ----   Corte General   ----------  \n");
	printf("\t  IDCORTEGENERAL  ----    Total de boletos vendidos -----  Total de ventas      \n");
	
	
	if(ptrCorte3 != NULL){
       
       fread(&corte5, sizeof(corte5), 1, ptrCorte3);
       
	   while(!feof(ptrCorte3)){
	   	 
	   	 
	   	    printf("\t  %5d    %5d      %5d  \n", corte5.idCorteGen, corte5.totalBoletosVendi, corte5.totalVentas);
	   	
	   	
	   	     fread(&corte5, sizeof(corte5), 1, ptrCorte3);
	   	
	   }
	   
	   	
	   fclose(ptrCorte3);	   	
		
	}else{
		
		printf("\t ERROR \n");
	}
	
	
	
}



struct corteGeneral realizarElCorteDia1(){
	
	//tenemos que generar un archivo binario donde se almacene el corte del dia 
	//TENEMOS QUE VALIDAR QUE EXISTEN VENTAS SI EXISTEN VENTAS SE RECORREN TODAS LAS VENTAS SE VAN
	//SUMANDO PARA DESPUES GENERAR EL CORTE GENERAL
	
	struct corteGeneral corte1;
	
	struct ventas ventaDia;
	
	
	
	FILE *ptrVenta=NULL;
	
	ptrVenta= fopen("ventasDia.dat", "rb");
	
	 corte1= {0, 0, 0 };
	
	if(ptrVenta != NULL ){
		
		
		fread(&ventaDia, sizeof(ventaDia), 1, ptrVenta );
		
		
		while(!feof(ptrVenta)){
          
          
          corte1.totalBoletosVendi = corte1.totalBoletosVendi + ventaDia.cantidadBoletos;
          
		   corte1.totalVentas =  corte1.totalVentas + ventaDia.total;
		  
		   
		  		
		
		
		  fread(&ventaDia, sizeof(ventaDia), 1, ptrVenta );	
		}
		
		fclose(ptrVenta);
		
		
	}else{
	  
	  printf("\t ERROR   \n");	
	  
		
		
	}
	
	corte1.idCorteGen=1;
	
	printf("\t -------- Corte general ---------- \n ");
	printf("\t Id corte : %d  \n", corte1.idCorteGen);
	printf("\t Total de boletos vendidos: %d  \n", corte1.totalBoletosVendi);
	printf("\t Total de ventas : %d  \n", corte1.totalVentas);
	
	

	
	
	return corte1;

	
	
	
	
	
	
	
}

void realizarCorteCompleto(struct corteGeneral corte1){
	
	
	FILE *ptrCorte=NULL;
	
	struct corteGeneral corte7;
	
	
	printf("\t Datos recibidos  \n");
	printf("\t %d,   %d   %d \n", corte1.idCorteGen, corte1.totalBoletosVendi, corte1.totalVentas);
	
	
	printf("\t Ingresa el id del corte :  ");
	scanf("%d", &corte7.idCorteGen);
	
	corte7.totalBoletosVendi= corte1.totalBoletosVendi;
	corte7.totalVentas = corte1.totalVentas;
		
	ptrCorte= fopen("corteGeneral.dat", "ab");
	
	if(ptrCorte!=NULL){
        printf("\t Corte realizado con exito  \n");
        
        fwrite(&corte7, sizeof(corte7), 1, ptrCorte);
     	
     	
     	
		 remove("ventasDia.dat");	
		
	}
	
	fclose(ptrCorte);
	
	
}


int validarIdVenta(int idIngresado1){


   struct ventas venta3;
   
   int idVentaIgual=0;
   
   FILE *ptrVenta= fopen("ventasDia.dat", "rb");
   
   
   if(ptrVenta!= NULL){

     fread(&venta3, sizeof(venta3),1, ptrVenta);
	 
	 while(!feof(ptrVenta)){
       
	    if(venta3.idVenta == idIngresado1 ){
		
		   idVentaIgual=1;
		   
		   return idVentaIgual;
		
		}else{
			
			idVentaIgual=0;
			
			
		}
			 	
	 	
	 	  fread(&venta3, sizeof(venta3),1, ptrVenta);
	 	
	
	 }   
   
      fclose(ptrVenta);
   
   
   }else {
   
   
     printf("\t   Error, no existen ventas registradas   \n");
   
   }
   
   

   	   return idVentaIgual;







}





int validarIdSala1(int idSala1){
	
	
	struct salas sala1;
	
	int idIgualSala;
	
	FILE *ptrSala1= NULL;
	
	
	ptrSala1= fopen("sala1.dat", "rb");
	
	fread(&sala1, sizeof(sala1), 1, ptrSala1);
	
	
	
	if(ptrSala1!=NULL){
		
		
			fread(&sala1, sizeof(sala1), 1, ptrSala1);
		
		while(!feof(ptrSala1)){
			
			
			if(sala1.idSala == idSala1){
				
				idIgualSala=1;
				
				return idIgualSala;
				
			}else{
				
				idIgualSala=0;
				printf("\t ------ EL id no es igual ----- \n");
			}
			
		
		 	fread(&sala1, sizeof(sala1), 1, ptrSala1);
			
		}
		
		
	   fclose(ptrSala1);
		
		
	}else {
		
		
		printf("\t  Error  \n");
		
		
	}
	
	
	return idIgualSala;
	
	
}

int validarQueExistenPeliculasEnLaSala1(){
	
	
	struct salas sala1;
	
	int cont11;
	
	FILE *ptrSala9=NULL;
	
	ptrSala9= fopen("sala1.dat","rb");
	
	//ptrSala2= fopen("sala2.dat","rb");
	   
   if(ptrSala9!=NULL){
        
      fread(&sala1 , sizeof(sala1), 1, ptrSala9);
     
     while(!feof(ptrSala9)){
                            
        
	         
                      
					           
                               
             
           fread(&sala1 , sizeof(sala1), 1, ptrSala9); 
		   
		   return 1;    
     }
   
     fclose(ptrSala9);
     
     
   
        
   }else{
     
       return 0;      
         
        
   }
         
   
   printf("\t----------------------------------------- \n");

	
    
	
	
	
	
	
	
	
	
	
}


int validarQueExistenPeliculasEnLaSala2(){
	
	
		struct salas sala2;
	
	int cont11;
	
	FILE *ptrSala10=NULL;
	
	ptrSala10= fopen("sala2.dat","rb");
	
	//ptrSala2= fopen("sala2.dat","rb");
	
    
   
   if(ptrSala10!=NULL){
        
      fread(&sala2 , sizeof(sala2), 1, ptrSala10);
     
     while(!feof(ptrSala10)){
                            
        
		                 
             
                      
					           
                               
             
           fread(&sala2 , sizeof(sala2), 1, ptrSala10); 
		   
		   return 1;    
     }
   
     fclose(ptrSala10);
     
     
        
   }else{
     
    return 0;
        
   }
         
   
   printf("\t----------------------------------------- \n");

	
    
    
  
	
	
	
	
}




//pasar los argumentos de la pelicula a registrar
int generarIdPeliculas(){
	
	struct peliculas peliLeer, peli33;
	
	
	
	FILE *ptrPeli33=NULL;
	
	ptrPeli33= fopen("peliculas.dat", "rb+");
	
	int idGenerado=1;
	
	
	if(ptrPeli33 != NULL){
		
		fread(&peliLeer, sizeof(peliLeer), 1, ptrPeli33);
		
		while(!feof(ptrPeli33)){

            if(peliLeer.idPelicula){
             idGenerado = peliLeer.idPelicula+1;
		
			//fwrite(&peli1, sizeof(peli1), 1, ptrPeli33);			
			
			//printf("\t El registro se a guardado con exito \n");
			
			 return  idGenerado;
			
		   }
		}
		
		
	}else{
		
		//genera el nuevo archivo
		
		//printf("\t Error \n");
		
		idGenerado=1;
		return idGenerado;
		

	}
	
	
	
	
}

void ModificarPelicula(){
	struct peliculas pelicula1;
	
	FILE *ptrArchivo=NULL;
	
	//aqui se apertura el archivo para leer los datos en modo lectura con el argumento rb
    ptrArchivo= fopen("peliculas.dat", "r+b");
	if(ptrArchivo)
        
        fread(&pelicula1, sizeof(pelicula1),1, ptrArchivo);
        
        while(!feof(ptrArchivo)){
            printf("\n");
            printf("---------------------------------------- \n");
            printf("\n Escriba el id de la pelicula a modificar\n");
            int buscar_id;
            scanf("%d",&buscar_id);
            if (buscar_id==pelicula1.idPelicula){
                printf("datos de la pelicula seleccionada");
                printf("Id pelicula: %d \n",pelicula1.idPelicula );
                printf("Nombre pelicula: %s \n", pelicula1.nombrePelicula);
                printf("Sinopsis: %s \n",pelicula1.sinopsis);
                printf("Director: %s \n", pelicula1.director );
                printf("Clasificacion:  %s \n", pelicula1.clasificacion);
                
                printf("\ncambiando los datos\n");
                printf("escribe los nuevos datos los cuales sustituiran a los anterirores de ese id\n");
                
                printf("\nombre pelicula: ");
                scanf(" %[^\n]%*c", pelicula1.nombrePelicula);
                printf("\nSinopsis: ");
                scanf(" %[^\n]%*c", pelicula1.sinopsis);
                printf("\nDirector: ");
                scanf(" %[^\n]%*c", pelicula1.director);
                printf("\nClasificacion: ");
                scanf(" %[^\n]%*c", pelicula1.clasificacion);
                printf("---------------------------------------- \n");
                int pos=ftell(ptrArchivo)-sizeof(pelicula1);
                fseek(ptrArchivo,pos,SEEK_SET);
                fwrite(&pelicula1, sizeof(pelicula1),1, ptrArchivo );
                printf("Se han cambiado los datos con exito\n");
           break;
            }
		   	  fread(&pelicula1, sizeof(pelicula1),1, ptrArchivo);
		   	
		   }
		   
		  fclose(ptrArchivo);
}






void modificarAsientosSala1(){
	
	struct salas sala1;
	
	int asientoComprar;
	
	imprimirSala1();
	
	FILE *ptrSala1= NULL;
	
	ptrSala1= fopen("sala1.dat", "wb");
	
	printf("\t");
	
	
	printf("\t Elige el asiento a comprar:");
	scanf("%d", &asientoComprar);
	
	
	//se tienen que abrir el archivo de las salas , y modificar el
	//arreglo de asientos para modificarlo
	
	
}


void modificarAsientosSala2(){
	
	
}

void imprimirSala2(){
	
	
	
	struct salas sala2;
	
	int cont11;
	
	FILE *ptrSala10=NULL;
	
	ptrSala10= fopen("sala2.dat","rb");
	
	//ptrSala2= fopen("sala2.dat","rb");
	
    printf(" \t  ------- SALA 2 ------  \n");	
    
    
    
    printf("\t  ID SALA - Pelicula a proyectar -- Sinopsis ------- Clasificacion-------Turno  ---- Asientos disponibles--- Asientos ocupados ---     \n");
   
   if(ptrSala10!=NULL){
        
      fread(&sala2 , sizeof(sala2), 1, ptrSala10);
     
     while(!feof(ptrSala10)){
                            
         printf("\t %5d            %5s             %5s                %5s      %5d                    %5d              %5d \n",sala2.idSala, sala2.peliculaProy, sala2.sinopPel, sala2.clasificacion, sala2.turnoProyeccion  , sala2.asDisponibles , sala2.asOcupados);  
	
		                 
                    
        printf("\n");  
		printf("\n");         
                      
					           
                               
             
           fread(&sala2 , sizeof(sala2), 1, ptrSala10);     
     }
   
     fclose(ptrSala10);
     
     
        
   }else{
     
     printf("\n");
     
     printf("\t  --------- No existen peliculas asignadas en la SALA 2  -------      \n");
     
     printf("\n");      
         
        
   }
         
   
   printf("\t----------------------------------------- \n");

	
    
    
  
	
	
	
}

void imprimirSala1(){
	
	struct salas sala1;
	
	int cont11;
	
	FILE *ptrSala9=NULL;
	
	ptrSala9= fopen("sala1.dat","rb");
	
	//ptrSala2= fopen("sala2.dat","rb");
	
    printf(" \t  ------- SALA 1 ------  \n");	
    
    
    
    printf("\t  ID SALA - Pelicula a proyectar -- Sinopsis ------- Clasificacion    -------   Turno    ----  Asientos disponibles--- Asientos ocupados ---     \n");
   
   if(ptrSala9!=NULL){
        
      fread(&sala1 , sizeof(sala1), 1, ptrSala9);
     
     while(!feof(ptrSala9)){
                            
         printf("\t %d     %5s             %5s                %5s      %5d          %5d              %5d \n",sala1.idSala, sala1.peliculaProy, sala1.sinopPel, sala1.clasificacion, sala1.turnoProyeccion , sala1.asDisponibles , sala1.asOcupados);  
		
         printf("\n");

		                 
                    
        printf("\n");  
	         
                      
					           
                               
             
           fread(&sala1 , sizeof(sala1), 1, ptrSala9);     
     }
   
     fclose(ptrSala9);
     
     
   
        
   }else{
     
     printf("\n");
     
     printf("\t  --------- No existen peliculas asignadas en la SALA 1 -------      \n");
     
     printf("\n");      
         
        
   }
         
   
   printf("\t----------------------------------------- \n");

	
    
    
  
    
    
}

void comprarAsientos(){
	
	
	int asientSel=0;
	
	printf(" \t   Selecciona un asiento por el numero \n");
	scanf("%d", &asientSel);
	
	for(int k=0; k<=20; k++){
		
		
		if(asientSel==k){
         // asiento[k]=1;
		 
		 			
			
		}
		
	}
	
	printf("Asiento seleccionado: %d ", asientSel);
	
	printf("\n");
	
	
	
	
	
	
	
	
	
}


void imprimirSalas(){

   struct salas salaImp1, salaImp2;
   
   int cont55;
   
   FILE *ptrSala1=NULL;
   
   FILE *ptrSala2=NULL;
   
   ptrSala1= fopen("sala1.dat", "rb");
   
   ptrSala2=fopen("sala2.dat", "rb");
   
   printf("\n\n");
   printf("\t ---- SALAS  ------------------  \n");
   printf("\n\n");
   printf("\t ---------SALA 1------------------ \n");
   printf("\n\n");
   
   printf("  ID SALA - Pelicula a proyectar -------------------- Sinopsis ------------------ Clasificacion---- Turno ----- Asientos disponibles--- Asientos ocupados ---     \n");
   
   if(ptrSala1!=NULL){
        
      fread(&salaImp1 , sizeof(salaImp1), 1, ptrSala1);
     
     while(!feof(ptrSala1)){
    printf("\n\n");                        
	printf(" %5d       %5s                     %s                          %3s                %3d         %3d                     %d \n",salaImp1.idSala, salaImp1.peliculaProy, salaImp1.sinopPel, salaImp1.clasificacion, salaImp1.turnoProyeccion , salaImp1.asDisponibles , salaImp1.asOcupados);  
		 printf("\n");
		 
		                 
                    
        printf("\n");  
		printf("\n");         
                      
					           
                               
             
           fread(&salaImp1 , sizeof(salaImp1), 1, ptrSala1);     
     }
   
     fclose(ptrSala1);
   
        
   }else{
     
     printf("\n\n");
     
     printf("\t  --------- No existen peliculas asignadas en la SALA 1  -------      \n");
     
     printf("\n");      
         
         
   }
         
   printf("\n\n");
   printf("\t----------------------------------------- \n");


    printf("\n\n");
    printf("\t ---------SALA 2------------------ \n");
    printf("\n\n");
    printf("  ID SALA - Pelicula a proyectar -------------------- Sinopsis ------------------ Clasificacion---- Turno ----- Asientos disponibles--- Asientos ocupados ---     \n");
   
   
   
   if(ptrSala2!=NULL){
        
     fread(&salaImp2 , sizeof(salaImp2), 1, ptrSala2);
     
     while(!feof(ptrSala2)){
    printf("\n\n");                     
    printf("  %5d       %5s                     %s                          %3s                %3d         %3d                     %d \n",salaImp2.idSala, salaImp2.peliculaProy, salaImp2.sinopPel, salaImp2.clasificacion, salaImp2.turnoProyeccion  , salaImp2.asDisponibles , salaImp2.asOcupados);                   
                    
                    
         printf("\n");
	
		
		 
                
        printf("\n");  
        printf("\n");  
		                     
                               
             
           fread(&salaImp2 , sizeof(salaImp2), 1, ptrSala2);     
     }
   
     fclose(ptrSala2);
   
        
   }else{
     
     printf("\n\n");
     
     printf("\t  --------- No existen peliculas asignadas en la SALA 2  -------      \n");
     
     printf("\n");      
         
         
   }

     
}




struct peliculas  buscarPelicula(int idBuscar){

    struct peliculas peli3;


    FILE *ptrPelicula=NULL;
    
    
    ptrPelicula=fopen("peliculas.dat", "rb");
    
    
    if(ptrPelicula==NULL){
    printf("\n\n");     
    printf("\t   ------  ERROR  No hay peliculas registradas  ---------\n");
    printf("\t ------- Es necesario registrar peliculas antes --------\n");
    
    
    }else{
          
          
          
             //printf("\t Id pelicula ----Nombre pelicula------ Sinopsis ----- Horario ---- Clasificacion --- \n");
          
        while(!feof(ptrPelicula)){
                                  
                                 
          
          fread(&peli3, sizeof(peli3), 1 , ptrPelicula);
          
          if(peli3.idPelicula==idBuscar){
              
                //printf(" \t %d      %s      %s        %s        %s \n", peli3.idPelicula, peli3.nombrePelicula, peli3.sinopsis, peli3.horario,peli3.clasificacion);
                
                return peli3;
          
          
          
          
          }
          
        }
    }
   
    return peli3;
     
}

void asignarSala(){
	
	//Se generaran 2 archivos de salas , uno donde se registraran las peliculas para la sala 1 y otro para la sala 2
	
	struct salas sala1, sala2;
	int asientosDisponibles=20;
	
	struct peliculas peliEncontrada;
	
	FILE *ptrSala1=NULL;
	FILE *ptrSala2=NULL;
	
	int idPelicula=0, selecSala=0, selecTurno=0;
	
	int validarSala1=0;

	int idSalaIng;

	
	int existenPeliculas= imprimirCartelera();
	
	
	
	//generar una funcion para que se limite la asignacion de salas 
	
	
	if( existenPeliculas != 1 ){
		printf("\n\n");
		printf("\t -------  NO SE PUEDEN ASIGNAR LAS SALAS POR QUE NO HAY PELICULAS REGISTRADAS ------- \n ");
	  
	
	}else {
		
		
		
		

	
	printf("\t   -----   ASIGNACION DE SALAS  ------------ \n");
	printf("\t ------ Asignar pelicula ------\n");
	
	printf("\t   Ingrese el id de la pelicula para asignarle una sala: ");
	scanf("%d", &idPelicula);
	
	


    //le asigno a una variable de tipo struct pelicula el contenido de la pelicula buscada 	
    peliEncontrada = buscarPelicula(idPelicula);
	
	
	 
     printf("\t Id pelicula ----Nombre pelicula------ Sinopsis ----- Director ---- Clasificacion --- \n");
     printf(" \t %d      %s      %s        %s        %s \n", peliEncontrada.idPelicula, peliEncontrada.nombrePelicula, peliEncontrada.sinopsis, peliEncontrada.director ,peliEncontrada.clasificacion);
     
     
     //aqui se registran los datos para asignarle a una pelicula una sala a proyectar 
     
     printf("\t Seleccionar la sala a asignarle la pelicula  \n"); 
   	 printf("\t 1.- SALA 1   2.- SALA 2  \n");
     printf("\t Ingresa un opcion numerica: ");
     scanf("%d", &selecSala);
     printf("\t Seleccionar el turno de la pelicula  \n");
     printf("\t 1.- Matutino(Hora de la proyeccion : 10:00 am)  2.-Vespertino(Hora de la proyeccion : 5:00 pm ) \n");
     printf("\t Ingresa un opcion numerica: ");
     scanf("%d", &selecTurno);
     
     
     
     if(selecSala==1  && selecTurno==1){
                      
          printf("\t Se ha seleccionada la SALA 1 , en el turno matutino (Hora de la proyeccion : 10:00 am) \n");
          
          printf("Ingrese el id de la sala: ");

          /*
          scanf("%d",&idSalaIng);
          
          validarSala1= validarIdSala1(idSalaIng);
		    
		  while(validarSala1){
		  	  printf("\t ERROR El id ingresado ya existe , por favor ingrese otro  \n");
              printf("Ingresar id sala : ");			  
			  scanf("%d",&idSalaIng);		  			  	
		 
		     validarSala1= validarIdSala1(idSalaIng);
		  }  
		    
		  sala1.idSala= idSalaIng; 
           */

		   srand(time(NULL));
		  sala1.idSala= rand()%101; 
		    
          sala1.asDisponibles=20;
          
          strcpy(sala1.peliculaProy, peliEncontrada.nombrePelicula );
           strcpy(sala1.clasificacion ,  peliEncontrada.clasificacion );
            strcpy( sala1.sinopPel, peliEncontrada.sinopsis );
           
          
          sala1.asOcupados=0;
        
          
          
          //el turno numero 1 es matutino y el numero 2 vespertino
          
          sala1.turnoProyeccion=selecTurno;
          
          
          //Aqui se genera el arreglo de los asientos que se manipulara para vender asientos
          
		 

          
          
          printf(" \t  --------- SALA 1 ----------       \n");
          printf("\t Id sala : %d \n", sala1.idSala);
          printf("\t  Pelicula a proyectar: %s  \n", sala1.peliculaProy );
          printf("\t Clasificacion: %s  \n", sala1.clasificacion );
          printf("\t Sinopsis: %s \n", sala1.sinopPel );
          printf("\t Turno: %d  \n", sala1.turnoProyeccion);
         
          printf("\t Asientos disponibles: %d \n", sala1.asDisponibles);
          printf("\t Asientos ocupados: %d  \n", sala1.asOcupados);
         
          //imprimiendo la lista de los asientos 
          
         
          
          printf("\n ");
          
          ptrSala1=fopen("sala1.dat", "ab");
          
          if(ptrSala1!=NULL){
          
              fwrite(&sala1, sizeof(sala1), 1, ptrSala1);
                             
          }
          
          fclose(ptrSala1);
          
          printf("\t Se ha registrado con exito \n");
          
        
    }else if(selecSala==1  && selecTurno==2){
    	
    	 printf("\t Se ha seleccionada la SALA 1 , en el turno vespertino(Hora de la proyeccion : 5:00 pm ) \n");
    	
    	  
        


		  //generar numero aleatorio del id de la sala 

		  srand(time(NULL));
		  sala1.idSala= rand()%101;
          
          //validarSala1 = validarIdSala1(sala1.idSala);
		 
    	
    	
    	
    	
    	 sala1.asDisponibles=20;
          
          strcpy(sala1.peliculaProy, peliEncontrada.nombrePelicula );
           strcpy(sala1.clasificacion ,  peliEncontrada.clasificacion );
            strcpy( sala1.sinopPel, peliEncontrada.sinopsis );
           
          
          sala1.asOcupados=0;
          
          
          
          //el turno numero 1 es matutino y el numero 2 vespertino
          
          sala1.turnoProyeccion=selecTurno;
          
          
          //Aqui se genera el arreglo de los asientos que se manipulara para vender asientos
          
		 

          
          
          printf(" \t  --------- SALA 1 ----------       \n");
          printf("\t Id sala : %d \n", sala1.idSala);
          printf("\t  Pelicula a proyectar: %s  \n", sala1.peliculaProy );
          printf("\t Clasificacion: %s  \n", sala1.clasificacion );
          printf("\t Sinopsis: %s \n", sala1.sinopPel );
          printf("\t Turno: %d  \n", sala1.turnoProyeccion);
        
          printf("\t Asientos disponibles: %d \n", sala1.asDisponibles);
          printf("\t Asientos ocupados: %d  \n", sala1.asOcupados);
         
          //imprimiendo la lista de los asientos 
          
         
          
          printf("\n ");
          
          ptrSala1=fopen("sala1.dat", "ab");
          
          if(ptrSala1!=NULL){
          
              fwrite(&sala1, sizeof(sala1), 1, ptrSala1);
                             
          }
          
          fclose(ptrSala1);
          
          printf("\t Se ha registrado con exito \n");
          
        
    	
    	
    	
    	
	
                    
                      
     }else if(selecSala==2 && selecTurno==1){
           
           
        printf("\t Se ha seleccionada la SALA 2 , en el turno matutino (Hora de la proyeccion : 10:00 am) \n");   
        
        
        sala2.asDisponibles=20;
        
        strcpy(sala2.peliculaProy, peliEncontrada.nombrePelicula );
           strcpy(sala2.clasificacion ,  peliEncontrada.clasificacion );
            strcpy( sala2.sinopPel, peliEncontrada.sinopsis );
           
       
          sala2.asOcupados=0;
          srand(time(NULL));
		  sala2.idSala= rand()%101;
          
          sala2.turnoProyeccion=1;

                    
          printf(" \t  --------- SALA 2 ----------       \n");
          printf(" Id sala : %d \n", sala2.idSala);
          printf("  Pelicula a proyectar: %s  \n", sala2.peliculaProy );
          printf(" Clasificacion: %s  \n", sala2.clasificacion );
          printf(" Sinopsis: %s \n", sala2.sinopPel );
           printf("\t Turno: %d  \n", sala2.turnoProyeccion);
        
          printf(" Asientos disponibles: %d \n", sala2.asDisponibles);
          printf(" Asientos ocupados: %d  \n", sala2.asOcupados);
          printf("\n ");
          
          
          
          
          
          printf("\n ");
          
           ptrSala2=fopen("sala2.dat", "ab");
          
          if(ptrSala2!=NULL){
          
              fwrite(&sala2, sizeof(sala2), 1, ptrSala2);
                             
          }
          
          fclose(ptrSala2);
          
          printf("\t Se ha registrado con exito \n");
          
     
     }else if( selecSala==2 && selecTurno==1    ){
     	
     	printf("\t Se ha seleccionada la SALA 2 , en el turno vespertino(Hora de la proyeccion : 5:00 pm ) \n"); 
		 
		 
		    sala2.asDisponibles=20;
        
        strcpy(sala2.peliculaProy, peliEncontrada.nombrePelicula );
           strcpy(sala2.clasificacion ,  peliEncontrada.clasificacion );
            strcpy( sala2.sinopPel, peliEncontrada.sinopsis );
           
          
          sala2.asOcupados=0;

          srand(time(NULL));
		  sala2.idSala= rand()%101;


          sala2.turnoProyeccion=2;

                    
          printf(" \t  --------- SALA 2 ----------       \n");
          printf(" Id sala : %d \n", sala2.idSala);
          printf("  Pelicula a proyectar: %s  \n", sala2.peliculaProy );
          printf(" Clasificacion: %s  \n", sala2.clasificacion );
          printf(" Sinopsis: %s \n", sala2.sinopPel );
           printf("\t Turno: %d  \n", sala2.turnoProyeccion);
     
          printf(" Asientos disponibles: %d \n", sala2.asDisponibles);
          printf(" Asientos ocupados: %d  \n", sala2.asOcupados);
          printf("\n ");
          
          
          
          
          
          printf("\n ");
          
           ptrSala2=fopen("sala2.dat", "ab");
          
          if(ptrSala2!=NULL){
          
              fwrite(&sala2, sizeof(sala2), 1, ptrSala2);
                             
          }
          
          fclose(ptrSala2);
          
          printf("\t Se ha registrado con exito \n");
           
	 
	 
	 
	 
	 
	 
     
     }else{
           
        printf("\t Error opcion numerica no valida \n");
           
     }
        

	
	
	
	
  }	
	
	
	
	
}

void menuInicial(){

	int opcion2;
	
	char usuario1[100];
	char password1[100];
    
    int validarReg=0;
    int passAdmin=0;
	int validar=0;
	printf("\n");
	printf("\n");		
	printf("----------------- Sistema de Venta de Boletos CINESOFT------------------ \n");
	printf("\n");
	printf("\t ---- Por favor registre un empleado -----\n");
	printf("\t ---- Para empezar a usar el sistema -------\n");
	printf("\n");
	printf("\t 1.-Iniciar el sistema \n");
	printf("\n");
	printf("\t 2.-Registrar empleado \n");
	printf("\n");
	printf("\t 3.-Visualizar empleados registrados \n");
	printf("\t 4.-Salir del sistema  \n");
	
	
	printf("\n\t Ingrese una opcion numerica: ");
    validar= scanf("%d", &opcion2);


	

	
	while(!validar){
       printf("\t Error opcion no valida, por favor ingrese una opcion numerica dentro del rango del 1 al 3 \n");
       fflush(stdin);
	   getchar();

	   printf("\n\t Ingrese una opcion numerica: ");
       validar= scanf("%d", &opcion2);

   
	}


	



    printf("\n");
	printf("------------------------------------------------------------------------\n");


	switch(opcion2){


		case 1:


			






			//Agregar la funcion para que se validen que existe un usuario registrado
			printf("----------------- Sistema de Venta de Boletos CINESOFT------------------ \n");
			printf("\n");
			printf("\t -----Iniciar Sesion -----\n");
			printf("\n");
			printf("\t Nombre usuario: ");
			scanf(" %[^\n]%*c", usuario1);
			printf("\n");
			printf("\t Password: ");
			scanf("%[^\n]%*c", password1);
			
		

	        
		    resul=iniciarSesion(usuario1, password1);
            
            //printf("hOLA MUNDO   \n");
		
		    
		       
			  if(resul==1){
			  	
			  	printf("\n");
			  	printf("\n");
			  	printf("------------------------------------------------------------------------\n");
				printf("\t ---- Inicio de sesion correcto ------\n");
				printf("\n");
			  	printf("\n");
			    printf("\t ---------------------   Iniciando el sistema  ----------\n");
				
				menuPrincipal();
		        
		      }else {
		      	printf("\n");
		      	printf("\n");
		        printf("\t ---  Error el Usuario y password ingresados son incorrectos   ----- \n");
		        printf("\n");
			  	printf("\n");
		        printf("\t ---  Nota:  Es necesario registrar un empleado antes de iniciar el sistema  ----- \n");
		        
		        
		      }


			break;


		case 2:
			printf("\n");
		    printf("\n");
			printf(" \t   --- Sistema de Venta de Boletos ------ \n");
			printf("\n");
		    printf("\n");
		    printf("2.-Registrar empleado \n");

		    registrarEmpleado();

		    //mostrarEmpleados();
		  break;
		  
		case 3:
			printf("\n\n");
			printf("\t 3.-Visualizar empleados registrados \n");
		   
		    printf("\t Ingrese la contraseÃ±a de administrador: ");
		    scanf("%d", &passAdmin);
		    
		    
			if(passAdmin==9999){
			
			 mostrarEmpleados();
			
				
			}else{
				
				printf("\t Error password del administrador incorrecto   \n");
				
			}
				
				

		
		   break;

		case 4:

           printf("\t Ha salido del sistema  \n");
           exit(-1);       
		   break;   
		     


		default:
			printf("Error opcion numerica no valida \n");


	}



}



int  iniciarSesion(char usuario1[], char password1[]){

	//printf("%s   %s \n", usuario1, password1);

	struct empleado emp5;

	int cont=0, inicioExitoso;
	FILE *ptrArchivo5=NULL;

	ptrArchivo5=fopen("empleados.dat", "rb");


    
       
        if(ptrArchivo5==NULL){
        	printf("\n");
			printf("\n");
        	printf("\t No se pudo abrir el archivo \n");
		}else {
			
			while(!feof(ptrArchivo5)){
            //printf("SI esta leyendo el archivo \n");

		   fread(&emp5, sizeof(emp5), 1, ptrArchivo5);


		     if((strcmp(emp5.usuarioEmp, usuario1)== 0) && (strcmp(emp5.password, password1)==0) )  {
		     	printf("\n");
				 printf("\n");

		 	  printf("\t  Inicio de sesion exitoso \n");
		 	  printf("\n\n");
		 	  inicioExitoso=1;
		 	  
		 	  return inicioExitoso;
		 	  
		 	  

		     }else {
		     	
		     	 //printf("\t El usuario y password no son iguales \n");
		     	
				 //el usuario y la contraseÃ±a no son iguales 
				 inicioExitoso=0;
			 }
		 
            
	           
	     }
	     
			
			
			
			
		}
        
            
	fclose(ptrArchivo5);
        
    
     
   
	  return inicioExitoso;   
	 




}


int  mostrarEmpleados(){

	struct empleado emp3;
	int cont22;

	FILE *ptrArchivo4=NULL;


	ptrArchivo4= fopen("empleados.dat", "rb");
	printf("\n");
	 printf("\n");




	printf("\t  IdEmpleado  Nombre   Apellidos    Usuario  Password ----\n ");

	if(ptrArchivo4!=NULL){

		fread(&emp3, sizeof(emp3),1, ptrArchivo4);

		while(!feof(ptrArchivo4)){

         printf("\n");
         printf("\n");
		 printf("\n");
         printf("\t %d    %s    %s    %s    %s", emp3.idEmpleado, emp3.nombreEmpleado, emp3.apellidosEmpleado, emp3.usuarioEmp, emp3.password);

          //return 1; 
         printf("\n"); 

		fread(&emp3, sizeof(emp3),1, ptrArchivo4);


		}

	   fclose(ptrArchivo4);
	}else{
		
		printf("\n");
		printf("\t ----- No existen empleados registrados ------------\n");
	    printf("\n");
	    
	    //return 0;
	}


     return 1;
    
}


void registrarEmpleado(){

	 struct empleado emp2;


	 FILE *ptrArchivo2=NULL;


    int validar2=0;




	 //printf("\t  2.-Registrar empleado \n");
	 printf("\n");
	 printf("\n");
	 printf("\tIngresa el id del empleado: ");
	 validar2= scanf("%d", &emp2.idEmpleado);


     


	

	
	while(!validar2){
       printf("\t Error , por favor ingrese un id numerico valido \n");
       fflush(stdin);
	   getchar();

       printf("\tIngresa el id del empleado: ");
	   validar2= scanf("%d", &emp2.idEmpleado);
	   

   
	}






	 printf("\n");
	 printf("\n");
	 printf("\tIngresa el nombre empleado: ");
	 scanf(" %[^\n]%*c", emp2.nombreEmpleado);
	 printf("\n");
	 printf("\n");
	 printf("\tIngresa el apellido: ");
	 scanf(" %[^\n]%*c", emp2.apellidosEmpleado);
	 printf("\n");
	 printf("\n");
	 printf("\tngresa el nombre de usuario: ");
	 scanf(" %[^\n]%*c", emp2.usuarioEmp);
	 printf("\n");
	 printf("\n");
	 printf("\tIngresa la contraseÃ±a de usuario:");
	 scanf(" %[^\n]%*c", emp2.password);


    //validar los datos del registro de los empleados 
	

   


	  ptrArchivo2=fopen("empleados.dat", "ab");


	 if(ptrArchivo2!=NULL){
	 	printf("\n");
		 printf("\n");

	 	printf("Archivo creado correctamente \n");

	 	fwrite(&emp2, sizeof(emp2), 1 ,ptrArchivo2);
	 }
	 printf("\n");
	 printf("\n");

	 printf(" \t  ---- empleado registrado con exito -------- \n");

	 fclose(ptrArchivo2);




}



void opcionesPeliculas(){

	struct peliculas pelicula1;

	FILE *ptrArchivo=NULL;


   int opcionPelicula;
   
     int validarID=0;


   printf("---------------------------------------------------------------");
   printf("\n\n");
   printf(" \t 1.-Registrar pelicula a proyectar \n");
   printf(" \t 2.-Modificar datos de pelicula a proyectar \n");
   printf(" \t 3.-Consultar cartelera \n");
   printf(" \t 4.-Asignar peliculas a las salas \n");
   printf(" \t 5.-Eliminar pelicula \n ");
   printf("\n\n");
   printf(" \t Eliga una opcion numerica :  ");
   scanf("%d",&opcionPelicula);
   printf("\n");
   
   switch(opcionPelicula){

    case 1:

    	
    	
          
		  ptrArchivo=fopen("peliculas.dat", "ab");
    	   
    	    
    	  printf(" -----Registrar pelicula a proyectar --------- \n");
    	  printf("\n\n");

        
    	  printf("Id pelicula: ");
		  scanf("%d",&pelicula1.idPelicula);
        
		   validarID=  validarIdPeli(pelicula1.idPelicula);
		  
		  
		   
		  
		   
		   
	        
			
		    
		  
		  
		  
		  
		  while(validarID==1){
		  	printf("\n\n");
		  	printf("\n -------- El id ingresado ya exite ------\n");
		  	printf("---- Ingresa otro \n");
		  	printf("\n\n");
		  	printf("Id pelicula: ");
		    scanf("%d",&pelicula1.idPelicula );
		    
		     validarID=  validarIdPeli(pelicula1.idPelicula);
     
            
		  }
		  
		  
		  printf("\n\n");
		  printf("Nombre pelicula: ");
		  scanf(" %[^\n]%*c", pelicula1.nombrePelicula);
		  printf("\n\n");
		  printf("Sinopsis: ");
		  scanf(" %[^\n]%*c", pelicula1.sinopsis);
		  printf("\n\n");
		  printf("Director de la pelicula : ");
		  scanf(" %[^\n]%*c", pelicula1.director);
		  printf("\n\n");
		   printf("Clasificacion: ");
		   scanf(" %[^\n]%*c", pelicula1.clasificacion);


           
          // leerIdPeliculas(pelicula1);

           
		   if(ptrArchivo!=NULL){
		   	printf("\n\n");
		   	printf(" Archivo creado correctamente \n");


		   	//aqui se guarda la informacion insertada en el archivo binario
		   	fwrite(&pelicula1, sizeof(pelicula1),1, ptrArchivo );


		   }



		   fclose(ptrArchivo);
		    printf("\n\n");
		    printf("   !!!!! Se ha registrado con exito Â¡Â¡Â¡Â¡Â¡ \n");

           


		   /*

		   printf("---------------------------------------- \n");
		   printf("Id pelicula: %d \n",pelicula1.idPelicula );
		   printf("Nombre pelicula: %s \n", pelicula1.nombrePelicula);
		   printf("Sinopsis: %s \n",pelicula1.sinopsis);
		   printf("Horario: %s \n", pelicula1.horario );
		   printf("Clasificacion:  %s \n", pelicula1.clasificacion);

		   */

		   printf("---------------------------------------- \n");

		break;

	case 2:
		printf("\n\n");
    	printf("\t ----- Modificar datos de pelicula a proyectar ------ \n");
	    ModificarPelicula();  
	    
	    
	      
       
        break;
	    
	case 3:
		printf("\n\n");
		printf("\t --------Consultar cartelera ------ \n");
	   
	   imprimirCartelera();
	   
	
	    break;  
		
	case 4:
		printf("\t 4.- AsIGnar peliculas a las salas \n");
		
		asignarSala();
	
	    break;	
        
    case 5:
    	/*
          FILE *ptrArchivo, *ptrArchivoAux;
            struct peliculas pelicula1;
            ptrArchivoAux=fopen("peliculas_aux.dat","wb");
            ptrArchivo=fopen("peliculas.dat","rb");

            if(!ptrArchivo){
                printf("Empty\n");
                
            }
            else{

                 int buscar_id;
                 printf("\n\n");
                printf("Escriba el id de la pelicula a eliminar \t");
                scanf("%d",&buscar_id);
                //Recibe los mismo parametros que fwrite
                while(fread(&pelicula1, sizeof(pelicula1),1, ptrArchivo)){

                   // if (!strcmp(pelicula1.idPelicula,buscar_id))
                   if (buscar_id==pelicula1.idPelicula){
                    fwrite(&pelicula1, sizeof(pelicula1),1, ptrArchivoAux);
                     fclose(ptrArchivoAux);
                     free(ptrArchivoAux);
                }
                ptrArchivoAux=fopen("peliculas_aux.dat","rb");
                ptrArchivo=fopen("peliculas.dat","wb");
                while(fread(&pelicula1, sizeof(pelicula1),1, ptrArchivoAux)){

                    fwrite(&pelicula1, sizeof(pelicula1),1, ptrArchivo);
                }//break;
            }

            fclose(ptrArchivo);
           
            
        }*/
        printf("Escriba el id de la pelicula a eliminar \t");
        scanf("%d",&elim_buscar_id);
        eliminacionFisica();         
		eliminarLogica();
         
         break;      

    default:
    	printf("!!! Error ingrese una opcion numerica valida Â¡Â¡Â¡ \n");



   }

}

/* ELiminación lógica de un registro */
char eliminarLogica()
{
    
	FILE *ptrArchivo;
	FILE *auxiliar;
	struct peliculas pelicula1;
	char elimina;
 
	/* Abre el archivo para leer */
	ptrArchivo = fopen("peliculas.dat", "r+b");	/* Modo lectura/escritura. Si el ptrArchivo no existe, es creado */
 
	if (ptrArchivo == NULL) { /* Si no se pudo abrir el ptrArchivo, el valor de ptrArchivo es NULL */
		elimina = 0;
 
	} else {
		/* Se busca el registro que se quiere borrar. Cuando se encuentra, se sitúa en esa posición mediante la 
		función fseek y luego se modifica el campo clave de ese registro mediante algún valor centinela, eso se logra 
		con fwrite. Hasta allí se ha logrado una eliminación LÓGICA. Porque el registro sigue ocupando espacio en el ptrArchivo físico */
 
		elimina = 0;
		fread(&pelicula1, sizeof(pelicula1), 1, ptrArchivo);
		while (!feof(ptrArchivo)) {
			if (pelicula1.idPelicula == elim_buscar_id) {
				fseek(ptrArchivo, ftell(ptrArchivo) - sizeof(pelicula1), SEEK_SET);
				pelicula1.idPelicula = VALOR_CENTINELA;
				fwrite(&pelicula1, sizeof(pelicula1), 1, ptrArchivo);
				elimina = 1;
				printf("\t   ------ Se ha eliminado la pelicula con exito  ------    \n");
				
				break;
			}
			fread(&pelicula1, sizeof(pelicula1), 1, ptrArchivo);
		}
 
		/* Cierra el ptrArchivo */
		fclose(ptrArchivo);
	}
 
	return elimina;
}
 
char eliminacionFisica()
{
	FILE *ptrArchivo;
	FILE *temporal;
	struct peliculas pelicula1;
	char elimina = 0;
 
	ptrArchivo = fopen("peliculas.dat", "rb");
	temporal = fopen("temporal.dat", "wb");
 
	if (ptrArchivo == NULL || temporal == NULL) {
		elimina = 0;
	} else {
		/* Se copia en el ptrArchivo temporal los registros válidos */
		fread(&pelicula1, sizeof(pelicula1), 1, ptrArchivo);
		while (!feof(ptrArchivo)) {
			if (pelicula1.idPelicula != elim_buscar_id) {
				fwrite(&pelicula1, sizeof(pelicula1), 1, temporal);

				printf("\t   ------ Se ha eliminado la pelicula con exito  ------    \n");
			}
			fread(&pelicula1, sizeof(pelicula1), 1, ptrArchivo);
		}
		/* Se cierran los ptrArchivos antes de borrar y renombrar */
		fclose(ptrArchivo);
		fclose(temporal);
 
		remove("peliculas.dat");
		rename("temporal.dat", "peliculas.dat");
 
		elimina = 1;
	}
 
	return elimina;
}


void mostrarIdYPelisRegis(){






}



void mostrarIdOcupados(){
	
	FILE *ptrPel=NULL;
	
	struct peliculas peli3;
	
	ptrPel= fopen("peliculas.dat", "rb");
	
	
	
	       printf("-----  Id de peliculas ocupados---- \n");

	  	  while(!feof(ptrPel)){

	  	  	fread(&peli3, sizeof(peli3), 1, ptrPel);

            
	  	  	    printf("%d---",peli3.idPelicula);
	  	        

			}

	        fclose(ptrPel);
	        
	        printf("\n");

	
}







int validarIdPeli(int idIngresado){

 	 //struct peliculas pelicula4;

 	 int idPeliculaComparar;
 	 int idNoIgual=0 , idIgual=0;

 	 struct peliculas peli1;

 	 FILE *ptrArchivo3=NULL;

 	 ptrArchivo3=fopen("peliculas.dat","rb");



       if(ptrArchivo3!=NULL){
	   
	   
	   
	   
	  	  //printf("-----  Id de peliculas ocupados---- \n");

          	fread(&peli1, sizeof(peli1), 1, ptrArchivo3);

            
	  	  while(!feof(ptrArchivo3)){

	  	  
	  	  	    //printf("%d---",peli1.idPelicula);
	  	        

	  	  	   if(peli1.idPelicula == idIngresado){
	  	  	      
	  	  	       idIgual=1;
					  
	  	  		   return idIgual;


				}else{
					
					 idIgual=0;
				}

               	fread(&peli1, sizeof(peli1), 1, ptrArchivo3);
		   }

	        fclose(ptrArchivo3);
        }else{
        	
        	printf("Error ");
		}
 	
 	
 	
 	
 	
 	
 	
      return idIgual;



}


int imprimirCartelera(){

	struct peliculas pelicula2;

	FILE *ptrArchivo2=NULL;


	//aqui se apertura el archivo para leer los datos en modo lectura con el argumento rb
	ptrArchivo2= fopen("peliculas.dat", "rb");
	
	printf("\n\n");
	//printf("Id pelicula ----Nombre pelicula----------------------------------- Sinopsis ---------------------------------- Director ---------------------------- Clasificacion --- \n");
	 printf("Id pelicula\tNombre pelicula\t\t\tSinopsis\t\t\tDirector\t\t\tClasificacion\n");

	if(ptrArchivo2 != NULL){

		   fread(&pelicula2, sizeof(pelicula2),1, ptrArchivo2);
		   while(!feof(ptrArchivo2)){
    printf("\n\n");
    //printf("%d              %5s                                                 %5s                                         %12s                                  %12s", pelicula2.idPelicula, pelicula2.nombrePelicula, pelicula2.sinopsis, pelicula2.director ,pelicula2.clasificacion);
	printf("%d\t%5s\t\t\t%5s\t\t\t%12s\t\t\t%12s", pelicula2.idPelicula, pelicula2.nombrePelicula, pelicula2.sinopsis, pelicula2.director ,pelicula2.clasificacion);	   
		   //printf("Id pelicula: %d \n",pelicula2.idPelicula );
		   //printf("Nombre pelicula: %s \n", pelicula2.nombrePelicula);
		   //printf("Sinopsis: %s \n",pelicula2.sinopsis);
     		 //  printf("---------------------------------------- \n");
     		 
		   //printf("Horario: %s \n", pelicula2.horario );
		   //printf("Clasificacion:  %s \n", pelicula2.clasificacion);

		   //printf("---------------------------------------- \n");

		       printf("\n");

		   	  fread(&pelicula2, sizeof(pelicula2),1, ptrArchivo2);

		   }
printf("\n\n");
		   printf("\t ----------------------------------------------- \n");
printf("\n\n");
		  fclose(ptrArchivo2);


	}else{
		
		printf("\n");
		printf("\t -------   No existen peliculas registradas , es necesario registrar peliculas ----- \n");
		printf("\n");
		
		return 0;
		
	}
	
	
	return 1;


}




void imprimirVentas(){
	
	
	struct ventas ventas2;
	
	FILE *ptrVentas2=NULL;
	
	
	
	
	
	ptrVentas2=fopen("ventasDia.dat", "rb");
	
	printf("\t  ID VENTA  ------ Pelicula ------ Sala ----- Turno -----  Cantidad de boletos ----- Total ---   \n");
	
	  
	
	
	
	
	if(ptrVentas2!=NULL){
		
		
			fread(&ventas2, sizeof(ventas2),1, ptrVentas2);
	
	    while(!feof(ptrVentas2)){
		
		
		printf(" \t %d   %s      %3d        %3d     %3d      %3d    \n", ventas2.idVenta, ventas2.peliculaVista, ventas2.sala,  ventas2.turno, ventas2.cantidadBoletos, ventas2.total);
		
		
		
		
		fread(&ventas2, sizeof(ventas2),1, ptrVentas2);
		
	   }
	}else{
		
		printf("\t No existen ventas registradas , es necesarion realizar ventas    \n");
	    	
	 }
		fclose(ptrVentas2);

	
	printf("\n");
	
	
	
	
	
}



void venderBoletos(){
	   
	   int opcion3=0, opcionSala=0,  	existePeliAsig1=0, opcionTurno=0, numAsie=0, validarIdVen=0, existePeliAsig2=0;
	
	      /*
          srand(time(NULL));
		  sala1.idSala= rand()%101;
          */

		 


	
	 printf("\n");
		    printf("\t ------- Administrar y registrar venta de boletos ----- \n");
		    printf("\t 1.-Vender Boletos  \n");
		    printf("\t 2.- Venta de boletos del dia  \n");
			printf("\t 3.- Realizar corte general \n ");
			printf("\t 4.- Consultar cortes de caja realizados \n");		    
		    printf("\t ---------------- \n");
	        printf("\t Ingresa una opcion numerica :");
	        scanf("%d", &opcion3);
	        
	        switch(opcion3){
	        		
	        	case 1:
	        		
	        		
	        	   
	        		
	        		
	        		printf("\t Vender boletos   \n");
	        		printf("\t Â¿ De que sala deseas vender boletos ?  \n");
	        		printf("\t 1.-SALA 1   2.- SALA 2  \n ");
	        		printf("\t Ingresa una opcion numerica : ");
	        		scanf("%d", &opcionSala);
	        		
	        		existePeliAsig1= validarQueExistenPeliculasEnLaSala1();
	        		
	        		
	        		
	        		if(opcionSala==1 ){
	        			
	        			printf("\t ----- Selecciona el turno de los boletos a comprar para  la pelicula --------- \n");
	        			printf("\t 1.-Matutino (Horario de proyeccion: 10:00 AM) \n");
	        			printf("\t 2.-Vespertino(Horario de proyeccion: 3:00 PM) \n");
	        			printf("\t Ingresa una opcion numerica : ");
	        			scanf("%d", &opcionTurno);
	        			
	        			
	        			
	        			//se tiene que generar una funcion para validar el turno de la sala y para despues ir manipulando los datos 
	        			//se busca la sala a vender boletos aperturando el archivo y se trae aqui
	        			
	        		
						
					
	        			
	        			
	        			   if(existePeliAsig1==1){
						 
						 
						      printf("\t ------- SALA 1 ------- \n");
	        			
	        			      imprimirSala1();
	        			
	        			
	        			
	        			
	        			       printf("\n");
	        			       printf("\t Costo de boletos en general: $35.00   \n");
	        			       printf("\t Â¿ Cuantos boletos deses comprar ? ");
	        			     scanf("%d", &numAsie);
	        			     
	        			     
	        			     
	        			     //generar funcion de ventas de boletos del dia 
	        			     //el costo total de la venta sera igual a el costoBoleto*asientos a comprar 
	        			
	        				
	        				//aqui se llama a la funcion seleccionar asientos
	        				//se necesita apertura el archivo de la sala 1 y manipular el arreglo de 
	        				//los asientos para que al momento de comprar cambie el estado a 1 
	        				
	        		//se tienen que apertura la estructura de la sala 1 y generar una copia de esa estrucutura una vez que
	        		//ya realizamos esa modificacion guardamos la copia del stuct en el archivo binario 
                         
                          struct salas sala1, salaCopia;
                          
                          FILE *ptrSalaCom1=NULL;
                          
                          ptrSalaCom1= fopen("sala1.dat", "rb+");
                          
                             printf("\t  ID SALA - Pelicula a proyectar -- Sinopsis ------- Clasificacion    -------   Turno   ----  Asientos disponibles--- Asientos ocupados ---     \n");
                          
       				    
                           if(ptrSalaCom1!=NULL){
                                                 
                               fread(&sala1, sizeof(sala1), 1, ptrSalaCom1);                  
                                
                                 while(!feof(ptrSalaCom1)){
                                 	   
                                 	   if(sala1.turnoProyeccion==opcionTurno){
										
										
										  printf("\t   Sala encontrada en el turno especifico \n");
										  printf("\t %d  %s  %s  %s  %d     %d   %d  \n", sala1.idSala, sala1.peliculaProy, sala1.sinopPel, sala1.clasificacion, sala1.turnoProyeccion,  sala1.asDisponibles, sala1.asOcupados);
										  //printf();
										  
										  printf("\t ------------------------------------------- \n ");
										  
										  
										  
                                      sala1.asDisponibles=sala1.asDisponibles-numAsie;
                                      sala1.asOcupados=  sala1.asOcupados+numAsie;
                                      
                                      printf("\t   Id pelicula: %d  \n", sala1.idSala);
                                      printf("\t  Pelicula a proyectar:  %s   \n", sala1.peliculaProy);
                                      printf("\t  Sinopsis :  %s      \n", sala1.sinopPel);
                                      printf("\t  Clasificacion : %s   \n", sala1.clasificacion);
                                    
                                      printf("\t  Asientos disponibles : %d  \n", sala1.asDisponibles);
                                      printf("\t Asientos ocupados: %d \n", sala1.asOcupados);
                                           
									
										   
									salaCopia.idSala= sala1.idSala;
									
									//printf("Ingrese el id de la sala: ");
									//scanf("%d", salaCopia.idSala);
									
									
									strcpy(salaCopia.peliculaProy, sala1.peliculaProy);
									strcpy(salaCopia.sinopPel, sala1.sinopPel);
								    strcpy(	salaCopia.clasificacion,  sala1.clasificacion);
							
							        salaCopia.turnoProyeccion= sala1.turnoProyeccion;
								
									salaCopia.asDisponibles= sala1.asDisponibles;
									salaCopia.asOcupados= sala1.asOcupados;                     
                                     
									 
									 fseek(ptrSalaCom1, ftell(ptrSalaCom1)- sizeof(salaCopia), SEEK_SET);
									 fwrite(&salaCopia, sizeof(salaCopia), 1, ptrSalaCom1);
									 printf("\t Se ha modificado el archivo \n");
									 
									 
									 
									 //aqui se tiene que crear el struct ventas , generar el 
									 
									 struct ventas ventasDia;
									 
									 FILE *ptrVentas= NULL;
									 
									 
									 
									     ptrVentas=fopen("ventasDia.dat","ab");
									     
									     /*
										 printf("\t Ingresa el id de la venta : ");
									     scanf("%d", &ventasDia.idVenta);

                                         */
                                         srand(time(NULL));
		                                 ventasDia.idVenta= rand()%101;

									     

										 /*
									     validarIdVen= validarIdVenta(ventasDia.idVenta);
									      
									      while(validarIdVen==1){
										     
										    
		  	                              printf("\t ERROR El id ingresado ya existe , por favor ingrese otro  \n");
                                          printf("Ingresar id venta : ");			  
			                              scanf("%d",  &ventasDia.idVenta);		  			  	
		 
		                                  
										    validarIdVen= validarIdVenta(ventasDia.idVenta); 
										  
										  }

										  */
										  
									     
									     
									     
										 strcpy(ventasDia.peliculaVista , salaCopia.peliculaProy);
									     ventasDia.sala= opcionSala;
									     ventasDia.turno = salaCopia.turnoProyeccion;
									     ventasDia.total= numAsie*35;
									     ventasDia.cantidadBoletos=numAsie;
									     
										 if(ptrVentas!=NULL){
											 
											 printf("\t Archivo creado con exito   \n");
											 
											 fwrite(&ventasDia, sizeof(ventasDia), 1, ptrVentas);
											 
											 
									     	
									     	
									     	
									     	
									     	
										 }else{
										 	printf("\t No se pudo crear el archivo de ventas  \n");
										 	
										 	
										 }
									     fclose(ptrVentas);
										 printf("   !!!!! Se ha registrado con exito Â¡Â¡Â¡Â¡Â¡ \n");
										 
									 
									 
									 
										
										  break;
										
										}
										else{
											
											printf("\t No se ha encontrado la sala   \n");
											
										}
                                       
                                      
									  fread(&sala1, sizeof(sala1), 1, ptrSalaCom1);  
                                       /*
                                  
									 
								     break;  
									 
									 */                 
                                 }
                                
								   fclose(ptrSalaCom1);		    
                          }    
                       
	        				
	        				
	        			
	                     	
						
						
					  }else {
						
						  printf("\t Error no se pueden comprar boletos , no existe una pelicula asignada en la SALA 1     \n");
						
						
					  }
						
						
	        			
	        						
	        			
						
	
					}else if(opcionSala==2){
						
						
						existePeliAsig2= validarQueExistenPeliculasEnLaSala2();
						
						if(existePeliAsig2==1){
							
							printf("\t ------- SALA 2 ------- \n");
	        			   imprimirSala2();
	        			
	        			
	        			
	        				printf("\n");
	        			printf("\t Â¿ Cuantos asientos deses comprar ? ");
	        			scanf("%d", &numAsie);
	        			
	        				
	        				//aqui se llama a la funcion seleccionar asientos
	        				//se necesita apertura el archivo de la sala 1 y manipular el arreglo de 
	        				//los asientos para que al momento de comprar cambie el estado a 1 
	        				
	        		//se tienen que apertura la estructura de la sala 1 y generar una copia de esa estrucutura una vez que
	        		//ya realizamos esa modificacion guardamos la copia del stuct en el archivo binario 
                         
                          struct salas sala2, salaCopia2;
                          
                          FILE *ptrSalaCom2=NULL;
                          
                          ptrSalaCom2= fopen("sala2.dat", "rb+");
                          
       				    
                           if(ptrSalaCom2!=NULL){
                                                 
                               fread(&sala2, sizeof(sala2), 1, ptrSalaCom2);                  
                                
                                 while(!feof(ptrSalaCom2)){
                                 	
                                 	 if(sala2.turnoProyeccion == opcionTurno ){
                                 	 	
                                 	 	
                                 	 	 printf("\t   Sala encontrada en el turno especifico \n");
										  printf("\t %d  %s  %s  %s  %d       %d   %d  \n", sala2.idSala, sala2.peliculaProy, sala2.sinopPel, sala2.clasificacion, sala2.turnoProyeccion, sala2.asDisponibles, sala2.asOcupados);
										  //printf();
										  
										  printf("\t ------------------------------------------- \n ");
										
                                 
								     break; 
									 
									 
									}else{
										
										printf("\t No se ha encontrado la pelicula \n");
									}
									 
									 fread(&sala2, sizeof(sala2), 1, ptrSalaCom2); 	
										                  
                                 }
                                
								   fclose(ptrSalaCom2);		    
                          }    
                       
	        				
	        			
	        			
	        			  
							
							
						}else{
						
						
						   printf("\t Error no se pueden comprar boletos , no existe una pelicula asignada en la SALA 2    \n");
						  
						
						}
                     
                       	   
                          
                    }else {
                    	
                    	printf("\t  ------ Error opcion numerica no valida \n");
                          
                          
                    }
	        		
	
	         
	        		break;
	        		
	        	case 2:
	        		
	        		 printf("\t 2.- Venta de boletos del dia  \n");
	        		 imprimirVentas();
				    
					break;	
					
				case 3:
					
				       struct corteGeneral corte33;  
					  corte33 = realizarElCorteDia1();
					  
				     realizarCorteCompleto(corte33);
				    
				 
				 
	              break;	
	            case 4:
	               imprimirCorteGeneral();
				   			
				break;
				
					
	        	
			}   
	
	
	
}







void menuPrincipal(){

	int opcion=0;
	printf("\n");
	
	
	
	
	
	
	
	
	
	///imprimirCartelera();
	
	/*
	printf("\t ----- Sala 1 -------- ------ | -----------Sala 2 --------------- \n ");
	printf("\t |                            |                                  | \n");
	printf("\t |   Nombre pelicula:         |  Nombre pelicula:                | \n");
	printf("\t |   Sinopsis:                |  Sinopsis:                       | \n");
	printf("\t |   Clasificacion:           |  Clasificacion:                  | \n");
	printf("\t |   Precio boletos--         |  Precios boletos---              | \n");
	printf("\t |   Adulto= $60              |  Adulto= $60                     | \n");
	printf("\t |   NiÃ±o= $30                |  NiÃ±o= $30                       | \n");
	printf("\t |                            |                                  | \n");
	printf("\t |                            |                                  | \n");
	printf("\t |____________________________|__________________________________|\n ");
	printf("\n");
	
	*/
	 printf("\t  Turnos para la proyeccion de peliculas  \n");
	 printf("\t 1.- Matutino(Hora de la proyeccion : 10:00 am)  2.-Vespertino(Hora de la proyeccion : 5:00 pm ) \n");
	
	imprimirSalas();
	

		int opcionSala, opcion3,numAsie,cont=1;
		
		
				struct salas salaP1;
	        				
		        FILE *ptrSalaP1=NULL;			
				ptrSalaP1=fopen("sala1.dat","rb");
				
				    int asientoComprar=0; 
					
					int existePeliAsig1=0, existePeliAsig2=0, opcionTurno=0;
					
					
					 int validarIdVen=0;	
	
	
	printf("\t ---------  Sistema de ventas de boletos Cine Morelos --------\n ");
	printf(" \t 1.-Administrar y registrar peliculas a proyectar \n");
	printf("\t 2.-Administrar y registrar venta de boletos \n");
	printf("\t 3.- Salir del sistema \n");
	printf("\t Elige una opcion numerica: ");
	scanf("%d", &opcion);
    printf("\n");


	switch(opcion){


		case 1:
			 printf("\n");
			 printf("\t ----- Administrar y registrar peliculas a proyectar --------------- \n");
			 printf("\n");
			 opcionesPeliculas();
			break;
	
		case 2:
			
	
		     venderBoletos();
	        
	
            printf("\n");
		    break;

		case 3:
			printf("\n");

			printf("\t ---- Ha salido del sistema -------  \n");
			exit(1);
			break;
			
			
		default:
			printf("\n");
			printf("\t !!! Error eliga una opcion numerica valida !!!\n");
	}



}



int main(){

//Cambiando color y letra
	system("COLOR F1");

    int decision=0, validarDatos=0;


    do {



       //se tiene que agregar una funcion para que se mantega la sesion del usuario, y no te pida iniciar sesion a cada rato
       
       
         //imprimirSalas();
        //printf("Resul = %d \n", resul);
        
	    //imprimirVentas();
		
		
		
		
		
		if(resul==1){
          
          menuPrincipal();             
                     
        }
        
        if(resul==0){
           
            menuInicial();    
          
        }  
        
        
        
        
        
        
	  //esta funcion sirve para que se pause el sistema y no termina la ejecucion del programa antes de tiempo	
      fflush(stdin);
	  getchar();


       printf("\n");
       printf("\n");
       printf("\t Desea continuar 1.-Si 2.-No \n");
       printf("\t Ingresa una opcion numerica: ");
        scanf("%d", &decision);
        
		
		//la variable valida los datos capturados en la funcion 
       //validarDatos=scanf("%d", &decision);
       
       if(decision!=1){
	   printf("\n");
	   printf("\t Error opcion no valida \n");
	   
	   
	   }
	   
        
       
    }while(decision==1  );
    printf("\n");
    printf("\t ---- Ha salido del sistema ----- \n");





}


