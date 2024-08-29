#include <allegro.h>
#include <math.h>
#include <time.h>

/* Funciones utilizadas */
void Var();
void Funciones();
int Grafico(int ancho, int alto);
void Reloj(int x, int y, int radio, int grados, int grados2, int grados3);
void Tiempo(int segundos, int minutos, int horas, int* grados, int* grados2, int* grados3);

/* Variables globales */

void Var()
{
}

void Funciones()
{
	allegro_init();
	install_keyboard();
}

/* Devuelve 0 si no hay error al inicializar los graficos */
int Grafico(int ancho, int alto)
{
	if(set_gfx_mode(GFX_SAFE, ancho, alto, 0, 0) != 0) // DECLARACIÓN DE LA PANTALLA VISUAL GRÁFICA
	{
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("No se ha logrado entrar a modo grafico\n%s\n", allegro_error);
		return 1;
	}
	return 0;
}



void Reloj(int x, int y, int radio, int grados, int grados2, int grados3)
{
    //ROTACIÓN DE MANECILLAS CON BASE EN LOS GRADOS
	int h = radio - 30, h2 = radio - 50, h3 = radio - 80;
	int x2 = h*cos(grados*(M_PI/180)), y2 = h*sin(grados*(M_PI/180)); /* segundero */
	int x22 = h2*cos(grados2*(M_PI/180)), y22 = h2*sin(grados2*(M_PI/180)); /* minutero */
	int x222 = h3*cos(grados3*(M_PI/180)), y222 = h3*sin(grados3*(M_PI/180)); /* hora */

	clear_bitmap(screen);
	circlefill(screen, x, y, radio, palette_color[18]);
	text_mode(-1);
	//COLOR DE MANECILLAS, TAMAÑO.//
	line(screen, x, y, x+x2, y+y2, palette_color[2]);
	line(screen, x, y, x+x22, y+y22, palette_color[3]);
	line(screen, x, y, x+x222, y+y222, palette_color[4]);
	textout(screen, font, "12", x-5, (y-radio)+5, palette_color[5]);
	textout(screen, font, "3", (x+radio)-10, y-2, palette_color[6]);
	textout(screen, font, "6", x-2, (y+radio)-10, palette_color[7]);
	textout(screen, font, "9", (x-radio)+10, y-2, palette_color[8]);
}

void Tiempo(int segundos, int minutos, int horas, int* grados, int* grados2, int* grados3)
{
	int auxiliar;

	auxiliar = (segundos-15)*6;
	if(auxiliar <= 0)
	*grados = auxiliar+360;
	else
	*grados = auxiliar;

	auxiliar = (minutos-15)*6;
	if(auxiliar <= 0)
	*grados2 = auxiliar+360;
	else
	*grados2 = auxiliar;

	auxiliar = (horas-15)*6;
	if(auxiliar <= 0)
	*grados3 = auxiliar+360;
	else
	*grados3 = auxiliar;
}

void Obtener_Hora(int *segundos, int *minutos, int *horas)
{
	time_t tSac = time(NULL); // instante actual

	struct tm* pt1 = localtime(&tSac);

	tm tm2 = *gmtime(&tSac); // deferencia y asignación

	*segundos = tm2.tm_sec;
	*minutos = tm2.tm_min;
	*horas = ((tm2.tm_hour+1)-6)*5;//DETERMINACIÓN DE LA HORA
}

int main()
{
	int minutos = 0, segundos = 0, horas = 0, grados = 0, grados2 = 0, grados3 = 0;

	Var();
	Funciones();
	Grafico(700,700);//TAMAÑO DE LA VENTANA

	do
	{
		Obtener_Hora(&segundos, &minutos, &horas);
		Tiempo(segundos, minutos, horas, &grados, &grados2, &grados3);
		Reloj(300,300, 200, grados, grados2, grados3);

		rest(100);
	}while(keypressed() == 0);
}
END_OF_MAIN();
