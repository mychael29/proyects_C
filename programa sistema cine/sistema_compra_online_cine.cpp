#include<stdio.h>
#include<iostream>
#include<fstream>
#include<conio.h>
#include<time.h>
#include <stdlib.h>
#include <Windows.h> 

/**
 * Created by Maycol Meza.
 */

using namespace std;
string getNumPelicula(int i, int peli1, int peli2, int peli3, int peli4, int peli5, int peli6);
string getPelicula(char c);
void PeliculasVistas();
void registrar_entradas (int a);
void buscar_entradas();
void lista_entradas();
void liquidacion();
bool compare(string s1, string s2);
char* convertirStringaChar(string s);

bool verficarPeliculaPeli1 = true,verficarPeliculaPeli2 = true,verficarPeliculaPeli3 = true,verficarPeliculaPeli4 = true,verficarPeliculaPeli5 = true,
	verficarPeliculaPeli6 = true,verficarPeliculaPeli7 = true; 

void colores(int c){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

struct boleto{
	char nombres[50];
	float precio;
	int codigo,dni;
	char asiento[2];
};

int main(){

	int opcion, salir=0, cantidad;
	char k;
	
	
	while(salir==0){
		colores(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	    cout<<"\n\n \t|||||||||||||||||||||||||||||||||| CINEPOLIS SANTA ANITA ||||||||||||||||||||||||||||||||||||||||||||"<<endl;
	    colores(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	    cout<<"\t======================================= CARTELERA ==================================================="<<endl;
	
	    cout<<"\n\tA. "; colores(FOREGROUND_INTENSITY | FOREGROUND_BLUE); cout<<"La cuidad perdida "; colores(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); 
	    cout<<"|| B. "; colores(FOREGROUND_INTENSITY | FOREGROUND_BLUE); cout<<"Spider-man: de regreso a casa "; colores(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); 
	    cout<<"|| C. "; colores(FOREGROUND_INTENSITY | FOREGROUND_BLUE);  cout<<"Transformers: el ultimo caballero "; colores(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); 
	    cout<<"\n\tD. "; colores(FOREGROUND_INTENSITY | FOREGROUND_BLUE);  cout<<"Fate stay night: heaven's feel "; colores(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	    cout<<" || E. "; colores(FOREGROUND_INTENSITY | FOREGROUND_BLUE); cout<<"koe no katachi "; colores(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); 
	    cout<<"|| F. "; colores(FOREGROUND_INTENSITY | FOREGROUND_BLUE); cout<< "Sword art online: ordinal scale"<<endl; colores(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	    cout<<"\n\t1> Generar Entrada\n\t2> Verificar Entrada \n\t3> Lista de Entradas vendidas \n\t4> Cantidad y Monto recaudado\n\t5> Salir"<<endl;
	    cout<<"\n\tElija Opcion: ";
		k='s'; 
		cin>>opcion;
		cout<<endl;
		if(opcion==1) {
			while(k != 'N'){
				cout<<"\tIngrese cantidad de personas: ";
				cin>>cantidad;
				registrar_entradas (cantidad);
				cout<<"\n\tContinuar S/N? : ";
				cin>>k;
				cout<<endl;
				cout<<"\t-------------------------------------------------------------------------";
				cout<<endl;
			}
		}
		if(opcion==2) buscar_entradas();
		if(opcion==3) {
			while(k!='N'){
				lista_entradas();
				cout<<"\n\tContinuar S/N? : ";
				cin>>k;
				cout<<endl;
				cout<<"\t--------------------------------------------------------------------------";
				cout<<endl;
		    }
		}
		if(opcion==4){
			liquidacion();
			cout<<"\n\tContinuar S/N? : ";
			cin>>k;
		}
		if(opcion==5)salir=1;
		system("cls");	
	}
	return 0;	
}

void PeliculasVistas(){
	FILE* archivo_entradas_peliculas;
	boleto entradaPelicula;
	
	archivo_entradas_peliculas=fopen("registro_entradas.bin","rb+"); 
	
	if(archivo_entradas_peliculas==NULL){ 
		cout<<"\tNo existe archivo... "<<endl;
		cout<<"------------------------------------------------------------------------------------------";
		getch();
		return;
	}
	
	fseek(archivo_entradas_peliculas, 0 , SEEK_SET); 
	fread(&entradaPelicula,sizeof(boleto),1,archivo_entradas_peliculas); 
	
	int laciudadperdida=0, spiderman=0, transformers=0, fate=0, koenokatachi=0, sao=0;
	char dat;
	while(!feof(archivo_entradas_peliculas)){
		if(!strcmp(entradaPelicula.nombres, "La cuidad perdida")) laciudadperdida++;
		if(!strcmp(entradaPelicula.nombres, "Spiderman de regreso a casa")) spiderman++;
		if(!strcmp(entradaPelicula.nombres, "Transformers el ultimo caballero")) transformers++;
		if(!strcmp(entradaPelicula.nombres, "Fate stay night heaven's feel")) fate++;
		if(!strcmp(entradaPelicula.nombres, "koe no katachi")) koenokatachi++;
		if(!strcmp(entradaPelicula.nombres, "Sword art online ordinal scale")) sao++;
		fread(&entradaPelicula,sizeof(boleto),1,archivo_entradas_peliculas);
	}
	fclose(archivo_entradas_peliculas);
	
	int userMovie[5];
	int tempN,contMovie;
	
	userMovie[0] = laciudadperdida;
	userMovie[1] = spiderman;
	userMovie[2] = transformers;
	userMovie[3] = fate;
	userMovie[4] = koenokatachi;
	userMovie[5] = sao;
	
	contMovie=0;
	while(contMovie<5){
		contMovie++;
	    for(int i=0;i<5;i++){
		    if(userMovie[i] < userMovie[i+1]){
		    tempN =userMovie[i];
			userMovie[i] = userMovie[i+1];
			userMovie[i+1] = tempN;
		    }
		}
	}
	
	cout<<endl;
	cout<<"\tPeliculas mas vistas"<<endl;
	cout<<endl;
	cout<<getNumPelicula(userMovie[0],laciudadperdida,spiderman,transformers,fate,koenokatachi,sao)<<": "<<userMovie[0]<<endl;
	cout<<getNumPelicula(userMovie[1],laciudadperdida,spiderman,transformers,fate,koenokatachi,sao)<<": "<<userMovie[1]<<endl;
	cout<<getNumPelicula(userMovie[2],laciudadperdida,spiderman,transformers,fate,koenokatachi,sao)<<": "<<userMovie[2]<<endl;
	cout<<getNumPelicula(userMovie[3],laciudadperdida,spiderman,transformers,fate,koenokatachi,sao)<<": "<<userMovie[3]<<endl;
	cout<<getNumPelicula(userMovie[4],laciudadperdida,spiderman,transformers,fate,koenokatachi,sao)<<": "<<userMovie[4]<<endl;
	cout<<getNumPelicula(userMovie[5],laciudadperdida,spiderman,transformers,fate,koenokatachi,sao)<<": "<<userMovie[5]<<endl;	
}

string getNumPelicula(int i, int peli1, int peli2, int peli3, int peli4, int peli5, int peli6){

	string movieNum;
	
	if(i == peli1 && verficarPeliculaPeli1){
	   movieNum = "\tLa cuidad perdida                   ";
	   verficarPeliculaPeli1 = false;
		return movieNum; // acaba la funcion con el return
	}
	if(i == peli2 && verficarPeliculaPeli2){
	   movieNum = "\tSpider-man de regreso a casa        ";
	   verficarPeliculaPeli2 = false;
			return movieNum;	
	}
	if(i == peli3 && verficarPeliculaPeli3){
	   movieNum = "\tTransformers el ultimo caballero    ";
	   verficarPeliculaPeli3 = false;
			return movieNum;	
	}
	if(i == peli4 && verficarPeliculaPeli4){
	   movieNum = "\tFate stay night heaven's feel       ";
	   verficarPeliculaPeli4 = false;
			return movieNum;	
	}
	if(i == peli5 && verficarPeliculaPeli5){
	   movieNum = "\tkoe no katachi                      ";
	   verficarPeliculaPeli5 = false;
			return movieNum;
	}
	if(i == peli6 && verficarPeliculaPeli6){
	   movieNum = "\tSword art online ordinal scale      ";
	   verficarPeliculaPeli6 = false;
			return movieNum;	
	}

	return "\tERROR";
}

string getPelicula(char c){
	
	string mov;
	
	switch(c){
		case 'A':
			mov = "La cuidad perdida";
			return mov; 
			break;
		case 'B':
			mov = "Spider-man de regreso a casa";
			return mov;
			break;
		case 'C':
			mov = "Transformers el ultimo caballero";
			return mov;
		    break;
		case 'D':
			mov = "Fate stay night heaven's feel";
			return mov;
		    break;
		case 'E':
			mov = "koe no katachi";
			return mov;
		    break;
		case 'F':
			mov = "Sword art online ordinal scale";
			return mov;
		    break;    
	}
	
	return NULL;
}

void registrar_entradas (int a){ 
    float precio; 
    string movie;
	char pelicula;

	colores(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	cout<<"\tPelicula : ";
	colores(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	
	cin>>pelicula;  
	
	cout<<endl;
	
	movie = getPelicula(pelicula); 

	cout<<"\tHD : S/ 15"<<endl;
    cout<<"\tHD 3D : S/ 25"<<endl;
    cout<<"\tHD 4D : S/ 40"<<endl;
    
    colores(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
    cout<<"\tA> HD DOB | B> HD 3D DOB | C> HD 4D DOB "<<endl;
    colores(FOREGROUND_INTENSITY | FOREGROUND_GREEN  | FOREGROUND_BLUE);
    cout<<"\t>> ";
    colores(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    
    char calidadPelicula;
    
    cin>>calidadPelicula;
    
    cout<<endl;
    
    switch(calidadPelicula){
		case 'A':
			precio = 15;
			break;
		case 'B':
			precio = 25;
			break;
		case 'C':
			precio = 40;
		    break;    
	}
    
    
    fflush(stdin);
    
	string nombreArchivo =  calidadPelicula + movie + ".txt";

	fflush(stdin);
    char *archTxt =  convertirStringaChar(nombreArchivo);
    char archivoTxT[80];
	
	fflush(stdin);
	for(int r = 0; r<80; r++){
		 archivoTxT[r] = archTxt[r]; 	    		
	}
	
	
	
    ifstream leer;
  	leer.open(archivoTxT, ios::in);

  	string asiento[100];
  	char asientoCharOpc[2];
  	
  	string asientoOrdenados[100];
  	int n = 0;	
  	
  	if (leer.is_open()){
  		
    	fflush(stdin);
    	leer.getline(asientoCharOpc,80,'\n');
    	asiento[n] = asientoCharOpc;
		while (!leer.eof()){
            n++;
            
            leer.getline(asientoCharOpc,80,'\n');
            asiento[n] = asientoCharOpc;    
        }   
    }
    leer.close();
    cout<<endl;
    
    const int fila = 10;
    const int columna = 10;
    
    string sopa[fila][columna] =
	{
		"A1","B1","C1","D1","E1","F1","G1","H1","I1","J1",
		"A2","B2","C2","D2","E2","F2","G2","H2","I2","J2",
		"A3","B3","C3","D3","E3","F3","G3","H3","I3","J3",
		"A4","B4","C4","D4","E4","F4","G4","H4","I4","J4",
		"A5","B5","C5","D5","E5","F5","G5","H5","I5","J5",
		"A6","B6","C6","D6","E6","F6","G6","H6","I6","J6",
		"A7","B7","C7","D7","E7","F7","G7","H7","I7","J7",
		"A8","B8","C8","D8","E8","F8","G8","H8","I8","J8",
		"A9","B9","C9","D9","E9","F9","G9","H9","I9","J9",
		"A10","B10","C10","D10","E10","F10","G10","H10","I10","J10",
	};
	
    int p = 0;
    
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			
			for(int m=0;m<=n;m++){
				
		        if(sopa[i][j] == asiento[m]){  
		        	
			        asientoOrdenados[p] = sopa[i][j];
			        p++;
		        }
            }  
				      
		}
    }
 
    p=0;
    for(int i=0;i<10;i++){
		    for(int j=0;j<10;j++){
		    	
			    if(sopa[i][j] == asientoOrdenados[p]){
			    	colores(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
				    cout << "\t" << sopa[i][j];
				    p++;
		
			    }else{
			        colores(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				    cout << "\t" << sopa[i][j];	
			    }
		    }
		cout<<endl<<endl;
	}
	
	long int aleatorio=0; 
	string asientoIngresado;
	
	FILE* archivo_entradas; 
	boleto entrada[a]; 
	archivo_entradas = fopen("registro_entradas.bin","ab");
	if(archivo_entradas==NULL){
		archivo_entradas=fopen("registro_entradas.bin","a+b");
	}
	
	ofstream escribir;
	escribir.open(archivoTxT,ios::app); 
	if(escribir==NULL){
		cout<<endl<<"\tNo existe un archivo...";
		cout<<"\tCree un archivo txt con al menos un dato guardado"; 
		return;
	}
	
	string asientoIngresadoAux[10]; 
	int contAsientoIngresadoAux = 0;
	
	for(int i=0; i<a ;i++){ 
	    bool comprobar = true;
	    bool comprobar2 = false;
	    
	    cout<<endl;
	    colores(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	    
	    cout<<"\tEscoge su asiento : ";
	    colores(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	    cin>>asientoIngresado;
	    
	    cout<<endl;
	    
		while(comprobar){
	        char charAsientoVerificar[2];
	        char charAsientonuevoIngresado[2];
	        for(int v=0; v<n; v++){
	
	        	if(asientoIngresado==asiento[v]){
	        		comprobar2 = true;
	        		v=n;
				}else{
					comprobar2 = false;
				}
			}
			if(comprobar2){
				cout<<"\tEl asiento ya esta reservada.."<<endl;
				colores(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	        		cout<<endl;
	                cout<<"\tEscoge su asiento : ";
	                colores(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	                cin>>asientoIngresado;
	                
			}else{
				for(int u = 0; u <= 10; u++ ){
					if(asientoIngresadoAux[u]==asientoIngresado){
						
					cout<<"\tEl asiento ya esta reservada.."<<endl;
				    colores(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	        		cout<<endl;
	                cout<<"\tEscoge su asiento : ";
	                colores(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	                cin>>asientoIngresado;
	                u=11;
	                comprobar = true;
				    }else{
					comprobar = false;
				    }
					
				}
				
			}	
		}
	
		escribir<<asientoIngresado<<"\n";
		asientoIngresadoAux[contAsientoIngresadoAux] = asientoIngresado;
		contAsientoIngresadoAux++;
	    
	    char *movieChar =  convertirStringaChar(movie);
	    for(int h = 0; h<50; h++){
			 entrada[i].nombres[h] = movieChar[h];   		
		}
		
	    colores(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		fflush(stdin);
		cout<<" \tDNI : ";
		colores(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cin>>entrada[i].dni; 
		cout<<endl;
		char *asientoChar =  convertirStringaChar(asientoIngresado);  
	    for(int r = 0; r<5 ; r++){
			 entrada[i].asiento[r] = asientoChar[r];	    		
		}
		
		entrada[i].precio = precio;
		
		srand(time(NULL)); 
		aleatorio = rand()%(87654)+12345; 
		entrada[i].codigo = aleatorio; 
	}
	escribir.close();
	colores(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN );
	
	cout<<"\tPrecio cobrado: "<<" S/" << precio * a <<endl; 
	colores(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	fwrite(&entrada,sizeof(boleto),a,archivo_entradas);
	
	fclose(archivo_entradas); 

	getch(); 
	return; 
}

char* convertirStringaChar(string s){
	
	char* c = new char [s.size()];	
		
	strcpy(c, s.c_str()); 
		
	return c;
}


void buscar_entradas(){
    
	int codigo; 
	FILE* archivo_entradas;
	boleto entrada;
	
	archivo_entradas=fopen("registro_entradas.bin","rb+"); 
	
	if(archivo_entradas==NULL){ 
		cout<<"\tNo existe archivo... "<<endl;
		cout<<"------------------------------------------------------------------------------------------";
		getch();
		return;
	}
	
	cout<<"\tIngrese Codigo de Boleto: "; 
	cin>>codigo; 
	int cont =0;
	
	fseek(archivo_entradas, 0 , SEEK_SET); 
	fread(&entrada,sizeof(boleto),1,archivo_entradas); 
	
	char dat;
	while(!feof(archivo_entradas)){
		
		if(entrada.codigo==codigo){ 
		    string a;
		    
			cout<<endl;
			cout<<"\t====================================================================================="<<endl;
			cout<<"\tCodigo de Boleto: "<<entrada.codigo<<endl;
			cout<<"\tAsistente: "<<entrada.nombres<<endl;
			cout<<"\tDNI: "<<entrada.dni<<endl;
			cout<<"\tAsiento: "<<entrada.asiento<<endl;
			cout<<"\t============================================"<<endl;
			string nombreMovie = entrada.nombres;
			a = entrada.asiento;
			
			colores(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			cout<<"\tMODIFICAR (M) o SALIR(Presione cualquier tecla): ";
			colores(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cin>>dat;
			
			if(dat=='M'){
				string asientoAcambiar;
				printf("\tIngrese nuevos datos..\n\n");
	            
	    
	            fflush(stdin);
	            cout<<"\tNuevo asiento : ";
	            cin>>entrada.asiento;
	            cout<<"\tDNI : ";
	            cin>>entrada.dni;
	            
			    asientoAcambiar = entrada.asiento;
			    
				fseek(archivo_entradas,ftell(archivo_entradas)-sizeof(entrada),SEEK_SET);
				
			    fwrite(&entrada,sizeof(entrada),1,archivo_entradas);   
			    fclose(archivo_entradas);
			    
			    
			    ifstream leerAsientosImprimir;
	            ifstream leerAsientos;
	            ofstream escribirAsientoNuevos;

	            string archivoTxTAux;
	            string archivoTxTAuxTemp;

	            char calidad;
	
	            if(entrada.precio == 15) calidad = 'A';
	            if(entrada.precio == 25) calidad = 'B';
	            if(entrada.precio == 40) calidad = 'C';
	
	            archivoTxTAux = calidad+nombreMovie+".txt";
	            archivoTxTAuxTemp = calidad+nombreMovie+" Temp"+".txt";

	            char *archivoCharB =  convertirStringaChar(archivoTxTAux);  
	            char nombreArchivoTxtMod[80];
	            for(int r = 0; r<80; r++){
	            nombreArchivoTxtMod[r]= archivoCharB[r]; 	    		
	            }
	
	             char *archivoCharBTemp =  convertirStringaChar(archivoTxTAuxTemp);  
	             char nombreArchivoTxtModTemp[80];
	             for(int r = 0; r<80; r++){
	              nombreArchivoTxtModTemp[r]= archivoCharBTemp[r];	    		
	              }
	
                 leerAsientosImprimir.open(nombreArchivoTxtMod,ios::in);
  	             leerAsientos.open(nombreArchivoTxtMod,ios::in);
  	             escribirAsientoNuevos.open(nombreArchivoTxtModTemp,ios::out);
  	
			    
			     char asientoAcambiarChar[2];
			     char *asientoCharMod =  convertirStringaChar(a);
			    
		         asientoAcambiarChar[0] = asientoCharMod[0];

		         asientoAcambiarChar[1] = asientoCharMod[1];
				 
		         cout<<endl;
		        
		        
			     char asientoCharOpcModificar[2];
			    
  	            if (leerAsientos.is_open()){
    	            leerAsientos.getline(asientoCharOpcModificar,80,'\n');
		            while (!leerAsientos.eof()){
		            	
     	            fflush(stdin);
		            
			            if(!strcmp(asientoCharOpcModificar, asientoAcambiarChar)){
				            escribirAsientoNuevos<<asientoAcambiar<<"\n";
				            
			             }else{
			           	
				            escribirAsientoNuevos<<asientoCharOpcModificar<<"\n";
				            
			             }    
			             leerAsientos.getline(asientoCharOpcModificar,80,'\n');
                    
				         }
                     }
            
                 leerAsientos.close();
                 escribirAsientoNuevos.close();
    
                 remove(nombreArchivoTxtMod);
                 rename(nombreArchivoTxtModTemp,nombreArchivoTxtMod);
                
			     printf("\tModificado.\n\n");   
			     }
			
			     printf("\tPresione cualquier tecla para salir\n");
			     getch();
			     return; 
		         }
			
		         fread(&entrada,sizeof(boleto),1,archivo_entradas); 
	             }
	
	             cout<<endl;
	             cout<<"\tNo se encontro Boleto..."<<endl; 
	             cout<<"\t----------------------------------------------------------------------";
	             getch();
                  return; 
                  
                 }
                 


void lista_entradas(){
	ifstream leer;
  	leer.open("asientos.txt",ios::in);

  	string asiento[100];
  	char asientoCharOpc[2];
  	string asientoOrdenados[100];
  	int n = 0;	
  	if (leer.is_open()){
  		
    	fflush(stdin);
    	leer.getline(asientoCharOpc,80,'\n');
    	asiento[n] = asientoCharOpc;
        
		while (!leer.eof()){
            n++;
            leer.getline(asientoCharOpc,80,'\n');
            asiento[n] = asientoCharOpc;
            
        }
    }
    
	
    leer.close();
    
    
	FILE* archivo_entradas;
	boleto entrada;
	archivo_entradas=fopen("registro_entradas.bin","rb"); 
	if(archivo_entradas==NULL){ 
		cout<<endl;
		cout<<"\tNo existe archivo... "<<endl;
		cout<<"\t------------------------------------------------------------------";
		getch();
		return;
	}
	
	rewind(archivo_entradas); 
	int t = 0;
	fread(&entrada,sizeof(boleto),1,archivo_entradas);
	colores(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	while(!feof(archivo_entradas)){ 
		
		cout<<"\tCodigo de Boleto: "<<entrada.codigo<<endl;
		cout<<"\t"<<entrada.nombres<<" - DNI: "<<entrada.dni<<" - S/."<<entrada.precio<<" - Asiento: "<<entrada.asiento<<endl; //asiento[t]  ...EN VEZ DE PONER entrada.asiento ponemos asiento[T] por eso la declaracion de la variable t.
		
		cout<<"\t================================================================"<<endl;
		t++;
		fread(&entrada,sizeof(boleto),1,archivo_entradas);
	}
	
	colores(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fclose(archivo_entradas);
	getch();
	return;	
}


void liquidacion(){
	int numeroRegistros,monto_total=0,aux;
	
	FILE* archivo_entradas;
	boleto entrada;
	archivo_entradas=fopen("registro_entradas.bin","rb");
	if(archivo_entradas==NULL){ 
		cout<<endl;
		cout<<"\tNo existe archivo... "<<endl;
		cout<<"\t------------------------------------------------------------------";
		getch();
		return;
	}
	
	fseek(archivo_entradas, 0, SEEK_END); 
	
	numeroRegistros = ftell(archivo_entradas)/sizeof(entrada);
	
	rewind(archivo_entradas);
	 
	fread(&entrada,sizeof(boleto),1,archivo_entradas);
	
	while(!feof(archivo_entradas)){
		aux = entrada.precio; 
		monto_total = monto_total + aux; 
		fread(&entrada,sizeof(boleto),1,archivo_entradas);
	}
	
	colores(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN );
	
	cout<<"\tTotal de entradas vendidas: "<< numeroRegistros <<endl;
	PeliculasVistas();
	cout<<endl;
	cout<<"\tMonto total recaudado: "<<"S/."<< monto_total <<endl;
	colores(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fclose(archivo_entradas);
	getch();
	
	return;
}
