//UNIVERSIDAD AUTÓNOMA DE AGUASCALIENTES
//Ing. en Sistemas Computacionales
//Segundo Semestre Grupo C
//Materia: Programación I
//Docente: Blanca Estrada Rentería
//Integrantes:
//Paola Alba Bugarín
//Paulo Antonio Benard Olvera

#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<windows.h>
#include<conio.h>
#include<ctime>

using namespace std;
//Estructura para los tiempos referentes al cronómetro
struct TTiempo{ 
	int hora;
	int min;
	int seg;
};
//Estructura para guardar hora normal con AM y PM incluidos
struct THoraN{ 
	int horas;
	int mins;
	int segs;
	int meridiano; //Se guarda un 1 si es AM o un 2 si es PM
};
//Estructura para guardar las 10 alarmas
struct TAlarm{
	THoraN alar[10];
};

void cascaronAlarma(); 
void cascaronCronom(); 
THoraN obtenerHora(); 
THoraN digital(THoraN HoraAc); 
void cronometro(); 
void impresionCrono(); 
void eliminarCrono(int cod); 
void despertador();
void impresionAlarm(); 
void alta(); 
void eliminarAlarm(int num); 
void modificar(int num); 
void ayuda(); 

int main(){
	int opc, opc2, num1, num2;
	do{
		system("cls");
		cout<<endl<<"\n\t\tBIENVENIDO AL PROGRAMA RELOJ";
		cout<<endl<<endl<<"\t1...Crear cascaron";
		cout<<endl<<"\t2...Reloj digital";
		cout<<endl<<"\t3...Reloj analogico";
		cout<<endl<<"\t4...Cronometro";
		cout<<endl<<"\t5...Tiempos del cronometro guardados";
		cout<<endl<<"\t6...Alarmas para el despertador";
		cout<<endl<<"\t7...Despertador";
		cout<<endl<<"\t8...Ayuda con el programa";
		cout<<endl<<"\t9...Salir";
		cout<<endl<<endl<<"(Seleccionar 1 si es tu primera vez utilizando el programa o si quieres reiniciarlo)";
		cout<<endl<<endl<<"Seleccione una opcion: ";
		cin>>opc;
		switch(opc){
			case 1:
				//Cascarones para los archivos binarios
				cascaronAlarma();
				cascaronCronom();	
				break;
			case 2: 
				//RELOJ DIGITAL
				THoraN HoraAct; //Variable para guardar la hora actual
				HoraAct=obtenerHora();
				digital(HoraAct);
				break;
			case 3:
				//RELOJ ANALOGICO
				system("reloj.exe"); //Se ejecutan los gráficos del reloj
				break;
			case 4:
				//CRONÓMETRO
				cronometro();
				break;
			case 5:
				//Registros del cronómetro
				impresionCrono();
				break;
			case 6: 
				do{
					system("cls");
					cout<<endl<<"\tALARMAS PROGRAMADAS (CUPO MAX DE 10)\n";
					impresionAlarm();
					cout<<endl<<endl<<"\tMENU";
					cout<<endl<<"1...Dar de alta una alarma";
					cout<<endl<<"2...Eliminar una alarma";
					cout<<endl<<"3...Modificar una alarma";
					cout<<endl<<"4...Salir del menu de alarmas";
					cout<<endl<<endl<<"Seleccione una opcion: ";
					cin>>opc2;
					switch(opc2){
						case 1:
							alta();
							break;
						case 2:
							cout<<endl<<"Ingrese el numero de la izquierda de la alarma a eliminar: ";
							cin>>num1;
							eliminarAlarm(num1);
							break;
						case 3:
							cout<<endl<<"Ingrese el numero de la izquierda de la alarma a modificar: ";
							cin>>num2;
							modificar(num2);
							break;
						case 4:
							break;
						default:
							cout<<endl<<"Opcion erronea, vuelve a intentarlo";
							system("pause");
							break;
					}
				}while(opc2!=4);
				break;
			case 7: //DESPERTADOR
				despertador();
				break;
			case 8: 
				//MANUAL DE USUARIO
				ayuda();
				break;
			case 9:
				cout<<endl<<"\tGracias por usar el programa";
				cout<<endl<<"\tHasta la proxima"<<endl<<endl;
				system("pause");
				break;
			default:
				cout<<endl<<"Opcion erronea, vuelve a intentarlo"<<endl;
				system("pause");
				break;
		}
	}while(opc!=9);
}

//Función para crear un cascarón en blanco para el archivo binario donde se guardan las alarmas
void cascaronAlarma(){
	int i;
	fstream archivo2;
	archivo2.open("alarmas.dat", ios::binary|ios::out);
	if(!archivo2){ //Verifica el vínculo con el archivo
		cout<<endl<<"Error de apertura. No se puede generar cascaron"<<endl;
		system("pause");
		exit(0);
	}
	for(i=0; i<=10; i++){ //cupo para 10 alarmas
		THoraN blanco={0,0,0,0};
		archivo2.write(reinterpret_cast<char*>(&blanco), sizeof(THoraN));
	}
	archivo2.close();
}

//Función para crear un cascarón en blanco para el archivo binario donde se guardan los registros del cronómetro
void cascaronCronom(){
	int i;
	fstream archivo;
	archivo.open("cronometro.dat", ios::binary|ios::out);
	if(!archivo){ //Verifica el vínculo con el archivo
		cout<<endl<<"Error de apertura. No se puede generar cascaron"<<endl;
		system("pause");
		exit(0);
	}
	for(i=0; i<=30; i++){ //cupo para 30 tiempos de cronómetro
		TTiempo blanco={0,0,0};
		archivo.write(reinterpret_cast<char*>(&blanco), sizeof(TTiempo));
	}
	archivo.close();
	cout<<endl<<"Cascarones creados con exito"<<endl;
	system("pause");
}

//Función que obtiene y retorna la hora actual
THoraN obtenerHora(){
	THoraN horaA;
	time_t tSac=time(NULL); 			//Función para conocer
	struct tm* tmP=localtime(&tSac); 	//la hora actual
	if(tmP->tm_hour<12){
		horaA.horas=tmP->tm_hour;
		horaA.meridiano=1;
	}else{
		horaA.horas=(tmP->tm_hour)-12;
		horaA.meridiano=2;
	}
	horaA.mins=tmP->tm_min;
	horaA.segs=tmP->tm_sec;
	return (horaA); //La hora actual se guarda en una variable tipo estructura y la retorna 
}

//Función que imprime un reloj digital en formato HH:MM:SS AM/PM
THoraN digital(THoraN HoraAc){
	bool reloj=true;
	char tecla;
	while(reloj){
    	system("cls");
    	cout<<endl<<"\n\t\tRELOJ DIGITAL";
    	cout<<endl<<"\t\t-------------\n";
		if(HoraAc.meridiano==1){
			printf("\n\n\n\t\t%.2d:%.2d:%.2d  AM",HoraAc.horas,HoraAc.mins,HoraAc.segs);	
		}else{
			printf("\n\n\n\t\t%.2d:%.2d:%.2d  PM",HoraAc.horas,HoraAc.mins,HoraAc.segs);
		}
		cout<<endl<<"\n\n\n\tPresione ENTER para salir\n";
		Sleep(1000);
		HoraAc.segs++;
		if(HoraAc.segs==60){
			HoraAc.mins++;
			HoraAc.segs=0;
		}
		if(HoraAc.mins==60){
			HoraAc.horas++;	
			HoraAc.mins=0;
			Beep(2500, 2000); //Cuando cambia la hora suenan pitidos
			Beep(2500, 1000);
		}
		if(HoraAc.horas>12){ //Paso de AM a PM
			if(HoraAc.meridiano==1){
				HoraAc.meridiano=2;
			}else{
				HoraAc.meridiano=1;
			}
		}
        if(kbhit()){
        	fflush(stdin);
        	char tecla=getch();
            if(tecla==13||tecla==10){
            	break;
			}	             
        }    	         
    }  
}

//Función que muestra un cronómetro y cuando se detiene por completo permite guardar o no el tiempo marcado 
void cronometro(){
	fstream archivo;
	TTiempo reg;
	char tecla;
	int aux=1;
	int op, x, y, z;
	int hr=0; //horas
	int mn=0; //minutos
	int sg=0; //segundos
	bool reloj=true;
	cout<<endl<<"Para iniciar el cronometro presione ENTER";
	getch();
	while(reloj){
    	system("cls");
    	cout<<endl<<"\t\t      CRONOMETRO";
    	cout<<endl<<"\t\t      ----------";
		printf("\n\n\n\t\t       %.2d:%.2d:%.2d",hr,mn,sg);
		cout<<endl<<endl<<"\n\n\t  Presione cualquier tecla para pausar \n";
		cout<<"\to ENTER para detener y guardar el tiempo\n";
		Sleep(1000);
		sg++;
		if(sg==60){
			mn++;
			sg=0;
		}
		if(mn==60){
			hr++;
			mn=0;
		}
        if(kbhit()){ //para pausar el cronometro con cualquier tecla
        	tecla=getch();
           	if(tecla==13||tecla==10){ //detiene el cronometro con Enter y guarda los datos del tiempo transcurrido
          	  	x=hr;
				y=mn;
				z=sg-1;
				break;	
			}	             
    	    else
    	   		system("Pause>null");
   	    }  	         
    }  
	cout<<endl<<endl<<"Desea guardar el tiempo del cronometro? Si=0, No=1"<<endl;
	cin>>op;
	if(op==0){
		int i;
		archivo.open("cronometro.dat", ios::binary|ios::in|ios::out);
		if(!archivo){ //Verifica el vínculo con el archivo
			cout<<endl<<"Error de apertura."<<endl;
			exit(0);
		}
		//El registro del cronometro se guarda en el archivo binario
		for(aux=1; aux<=30; aux++){
			archivo.seekg((aux-1)*sizeof(TTiempo), ios::beg); 
			archivo.read(reinterpret_cast<char*>(&reg), sizeof(TTiempo));
			if(reg.hora==0 && reg.min==0 && reg.seg==0){ //Si el registro esta en blanco para llenarlo
				TTiempo crono={x, y, z};
				archivo.seekp((aux-1)*sizeof(TTiempo), ios::beg); 
				archivo.write(reinterpret_cast<char*>(&crono), sizeof(TTiempo));
				//Con seekp y write se guardan las modificaciones en el archivo binario
				cout<<endl<<"Datos almacenados correctamente\n";
				system("pause");
				break;
			}
		}
		archivo.close();
	}
}

/*Función que muestra las marcas guardadas anteriormente del cronómetro y una vez que se muestran aparece un 
submenú que le permite al usuario eliminar una marca o salir de la impresión de registros*/
void impresionCrono(){
	fstream archivo;
	TTiempo reg;
	int opcion, cod;
	int n=1, k=0;
	system("cls");
	archivo.open("cronometro.dat", ios::binary|ios::in);
	if(!archivo){ //Verifica el vínculo con el archivo
		cout<<endl<<"Error de apertura"<<endl;
		exit(0);
	}
	while(!archivo.eof() && archivo.read(reinterpret_cast<char*>(&reg), sizeof(TTiempo))){ //Para que no lea dos veces el último registro 
		if(reg.hora!=0 || reg.min!=0 || reg.seg!=0){ //Si el registro tiene datos lo imprime
			printf("\n\t%d... %.2d:%.2d:%.2d\n",n,reg.hora,reg.min,reg.seg);
			n++;
			k=1;
		}
	}
	if(k==0){ 
	//Un mensaje se muestra en caso de que no haya registros y no muestra el submenú, ya que no tiene caso si no hay registros
		cout<<endl<<"No hay registros"<<endl;
		system("Pause");
		archivo.close();
	}else{
	//Si hay registros se muestra el submenú
		cout<<endl<<endl;
		archivo.close();
		//Submenú para poder eliminar un registro del cronómetro o salir de la vista de los registros
		do{
			cout<<endl<<endl<<"1...Eliminar un registro";
			cout<<endl<<"2...Regresar al menu";
			cout<<endl<<"Seleccione una opcion: ";
			cin>>opcion;
			switch(opcion){
				case 1:
					cout<<endl<<"Ingrese el numero de la izquierda del registro a eliminar: ";
					cin>>cod;
					eliminarCrono(cod);
					break;
				case 2:
					break;
				default:
					cout<<endl<<"Opcion erronea, vuelve a intentarlo";
					system("pause");
					break;
			}
		}while(opcion!=2);
		archivo.close();
	}
}

/*Función que complementa a la anterior al momento de elegir eliminar registro, aquí se elimina la marca que el
usuario había elegido*/
void eliminarCrono(int cod){
	int aux;
	fstream archivo;
	TTiempo reg;
	archivo.open("cronometro.dat", ios::binary|ios::in|ios::out);
	if(!archivo){ //Verifica el vínculo con el archivo
		cout<<endl<<"Error de apertura"<<endl;
		exit(0);
	}
	archivo.seekg((cod-1)*sizeof(TTiempo), ios::beg); 
	archivo.read(reinterpret_cast<char*>(&reg), sizeof(TTiempo));
	printf("\n\t%.2d:%.2d:%.2d \n",reg.hora,reg.min,reg.seg);
	cout<<endl<<"Deseas darlo de baja? si=0, no=1\n";
	cin>>aux;
	if(aux==0){
		TTiempo blanco={0,0,0};
		archivo.seekp((cod-1)*sizeof(TTiempo), ios::beg); 
		archivo.write(reinterpret_cast<char*>(&blanco), sizeof(TTiempo));
		//Con seekp y write se guardan las modificaciones en el archivo binario
		cout<<endl<<"Registro dado de baja\n";
		system("pause");
	}
	else{
		cout<<endl<<"Los datos no se eliminaron\n";
		system("pause");
	}
	archivo.close();
}

//Función que corre un reloj digital y según las alarmas programadas van a sonar pitidos a las horas marcadas
void despertador(){
	fstream archivo;
	TAlarm lista; //variable que servirá para guardar las alarmas
	//El vector se inicializa en ceros para evitar complicaciones
	for(int i=0; i<10; i++){ 
		lista.alar[i].horas=0;
		lista.alar[i].mins=0;
		lista.alar[i].meridiano=0;
	}
	//Se abre el archivo binario con las alarmas y se graban en el vector anterior
	THoraN reg;
	int aux;
	archivo.open("alarmas.dat", ios::binary|ios::in);
	if(!archivo){ //Verifica el vínculo con el archivo
		cout<<endl<<"Error de apertura"<<endl;
		exit(0);
	}
	for(aux=1; aux<=10; aux++){ 
		archivo.seekg((aux-1)*sizeof(THoraN), ios::beg); 
		archivo.read(reinterpret_cast<char*>(&reg), sizeof(THoraN));
		if(reg.horas!=0 || reg.mins!=0 || reg.segs!=0 || reg.meridiano!=0){ 
		//Si el registro tiene datos lo guarda en el vector de alarmas
		lista.alar[aux-1].horas=reg.horas;
		lista.alar[aux-1].mins=reg.mins;
		lista.alar[aux-1].meridiano=reg.meridiano;
		}
	}
	archivo.close();
	THoraN clock; //Variable para guardar la hora actual
	clock=obtenerHora(); //Se obtiene la hora actual
	bool reloj=true;
	int i;
	int stop=1;
	char tecla;
	//Inicio del reloj despertador
	while(reloj){
    	system("cls");
    	cout<<endl<<"\n\t\tDESPERTADOR\n";
		if(clock.meridiano==1){
			printf("\n\n\n\t\t%.2d:%.2d:%.2d  AM",clock.horas,clock.mins,clock.segs);	
		}else{
			printf("\n\n\n\t\t%.2d:%.2d:%.2d  PM",clock.horas,clock.mins,clock.segs);
		}
		cout<<endl<<"\n\n\tPresione ENTER para salir\n";
		cout<<endl<<"\tPresione ESC para apagar la alarma\n";
		Sleep(1000);
		clock.segs++;
		if(kbhit()){
        	fflush(stdin);
        	char tecla=getch();
            if(tecla==13||tecla==10){
            	break;
			}	             
        } 
		if(clock.segs==60){
			clock.mins++;
			clock.segs=0;
		}
		if(clock.mins==60){
			clock.horas++;	
			clock.mins=0;
		}
		if(clock.horas>12){ //Paso de AM a PM
			if(clock.meridiano==1){
				clock.meridiano=2;
			}else{
				clock.meridiano=1;
			}
		}
		if(kbhit()){
        	fflush(stdin);
        	char tecla=getch();
            if(tecla==27){
            	stop=0;
			}	             
       	} 
       	/*Si alguna alarma guardada en el vector coincide con la hora actual suenan pitidos y se muestran mensajes
		de DESPIERTA, se puede desactivar al presionar la tecla ESC hasta que deje de sonar*/
		if(stop==1){
			for(i=0; i<10; i++){
				if(lista.alar[i].horas==clock.horas && lista.alar[i].mins==clock.mins && lista.alar[i].meridiano==clock.meridiano){
					Beep(2500, 2000);
					cout<<endl<<endl<<"\tDESPIERTA!!!";
					Beep(2500, 2000);
					cout<<endl<<endl<<"\tDESPIERTA!!!";
				}	
			}
		}   	         
    }  
}

//Función que imprime las alarmas registradas al seleccionar en el menú principal "Alarmas para el despertador"
void impresionAlarm(){
	fstream archivo2;
	THoraN reg;
	int n=1, k=0;
	archivo2.open("alarmas.dat", ios::binary|ios::in);
	if(!archivo2){ //Verifica el vínculo con el archivo
		cout<<endl<<"Error de apertura"<<endl;
		exit(0);
	}
	while(!archivo2.eof() && archivo2.read(reinterpret_cast<char*>(&reg), sizeof(THoraN))){ //Para que no lea dos veces el último registro 
		if(reg.horas!=0 || reg.mins!=0 || reg.segs!=0 || reg.meridiano!=0){ //Si el registro tiene datos lo imprime
			if(reg.meridiano==1){
				printf("\n\t%d... %.2d:%.2d  AM",n,reg.horas,reg.mins);
				n++;
				k=1;	
			}else{
				printf("\n\t%d... %.2d:%.2d  PM",n,reg.horas,reg.mins);
				n++;
				k=1;
			}	
		}
	}
	if(k==0){ 
	//Un mensaje se muestra en caso de que no haya registros
		cout<<endl<<"No hay registros"<<endl;
		archivo2.close();
	}
	archivo2.close();
}

/*Función que permite dar de alta nuevas alarmas dadas por el usuario donde solo se pide la hora, los minutos y si es
AM o PM */
void alta(){
	fstream archivo;
	THoraN reg, nuevaAlarm;
	int aux;
	archivo.open("alarmas.dat", ios::binary|ios::in|ios::out);
	if(!archivo){ //Verifica el vínculo con el archivo
		cout<<endl<<"Error de apertura."<<endl;
		exit(0);
	}
	for(aux=1; aux<=10; aux++){
		archivo.seekg((aux-1)*sizeof(THoraN), ios::beg); 
		archivo.read(reinterpret_cast<char*>(&reg), sizeof(THoraN));
		if(reg.horas==0 && reg.mins==0 && reg.segs==0 && reg.meridiano==0){ //Si el registro esta en blanco para llenarlo
			cout<<endl<<"Nueva alarma";
			cout<<endl<<endl<<"Ingrese la hora (en formato 12 hrs): ";
			cin>>nuevaAlarm.horas;
			cout<<endl<<"Ingrese los minutos: ";
			cin>>nuevaAlarm.mins;
			do{ //Se valida que el usuario ponga 1 o 2 
				cout<<endl<<"Ingrese si es AM=(1) o PM=(2): ";
				cin>>nuevaAlarm.meridiano;
			}while(nuevaAlarm.meridiano!=1 && nuevaAlarm.meridiano!=2);
			archivo.seekp((aux-1)*sizeof(THoraN), ios::beg); 
			archivo.write(reinterpret_cast<char*>(&nuevaAlarm), sizeof(THoraN));
			//Con seekp y write se guardan las modificaciones en el archivo binario
			cout<<endl<<"Alarma guardada correctamente\n";
			system("pause");
			break;
		}
	}		
	archivo.close();
}

//Función que permite eliminar una alarma según la posición (num) dada por el usuario antes de llamar a esta función 
void eliminarAlarm(int num){
	int aux;
	fstream archivo;
	THoraN reg;
	archivo.open("alarmas.dat", ios::binary|ios::in|ios::out);
	if(!archivo){ //Verifica el vínculo con el archivo
		cout<<endl<<"Error de apertura"<<endl;
		exit(0);
	}
	archivo.seekg((num-1)*sizeof(THoraN), ios::beg); 
	archivo.read(reinterpret_cast<char*>(&reg), sizeof(THoraN));
	if(reg.meridiano==1){
			printf("\n\t%.2d:%.2d  AM",reg.horas,reg.mins);	
	}else{
			printf("\n\t%.2d:%.2d  PM",reg.horas,reg.mins);
	}
	cout<<endl<<endl<<"Deseas darlo de baja? si=0, no=1\n";
	cin>>aux;
	if(aux==0){
		THoraN Blanco={0,0,0,0};
		archivo.seekp((num-1)*sizeof(THoraN), ios::beg); 
		archivo.write(reinterpret_cast<char*>(&Blanco), sizeof(THoraN));
		//Con seekp y write se guardan las modificaciones en el archivo binario
		cout<<endl<<"Alarma dada de baja\n";
		system("pause");
	}
	else{
		cout<<endl<<"La alarma no fue eliminada\n";
		system("pause");
	}
	archivo.close();
}

//Función que permite modificar una alarma según la posición (num) dada por el usuario antes de llamar a esta función
void modificar(int num){
	int aux;
	fstream archivo;
	THoraN reg;
	archivo.open("alarmas.dat", ios::binary|ios::in|ios::out);
	if(!archivo){ //Verifica el vínculo con el archivo
		cout<<endl<<"Error de apertura"<<endl;
		exit(0);
	}
	//Con el número dado por el usuario se lee especificamente dentro del archivo binario con la funcion seekg 
	archivo.seekg((num-1)*sizeof(THoraN), ios::beg); 
	archivo.read(reinterpret_cast<char*>(&reg), sizeof(THoraN));
	//Se imprime el tiempo para confirmar si fue el que se escogió
	if(reg.meridiano==1){
			printf("\n\t%.2d:%.2d  AM",reg.horas,reg.mins);	
	}else{
			printf("\n\t%.2d:%.2d  PM",reg.horas,reg.mins);
	}
	cout<<endl<<endl<<"Deseas modificarlo? si=0, no=1\n";
	cin>>aux;
	if(aux==0){
		cout<<endl<<"Ingrese la nueva hora (en formato 12 hrs): ";
		cin>>reg.horas;
		cout<<endl<<"Ingrese los nuevos minutos: ";
		cin>>reg.mins;
		do{ //Se valida que el usuario ponga 1 o 2 
			cout<<endl<<"Ingrese si es AM=(1) o PM=(2):  ";
			cin>>reg.meridiano;
		}while(reg.meridiano!=1 && reg.meridiano!=2);
		archivo.seekp((num-1)*sizeof(THoraN), ios::beg); 
		archivo.write(reinterpret_cast<char*>(&reg), sizeof(THoraN));
		//Con seekp y write se guardan las modificaciones en el archivo binario
		cout<<endl<<endl<<"Alarma modificada\n";
		system("pause");
	}
	else{
		cout<<endl<<"La alarma no fue modificada\n";
		system("pause");
	}
	archivo.close();
}

//Función que imprime de un archivo de texto un manual de usuario para poder utilizar el programa si se ocupa ayuda
void ayuda(){
	system("cls");
	fstream archivo;
	char c;
	archivo.open("AyudaPrograma.txt", ios::in); //abre el archivo de texto con las instrucciones del programa
	if(!archivo){ //Verifica el vínculo con el archivo
		cerr<<"Lo sentimos, no se pudo abrir el archivo :("<<endl;
		exit(0);
	}else{
		//Imprime el archivo de texto, caracter por caracter 
		cout<<endl;
		while(!archivo.eof()){
			archivo.get(c);
			cout<<c;
		}
		cout<<endl;
	}
	system("pause");
	archivo.close();
}
