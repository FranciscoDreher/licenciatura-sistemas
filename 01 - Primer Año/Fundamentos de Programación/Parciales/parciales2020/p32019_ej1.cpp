#include <iostream>
#include <string>
using namespace std;
/*Ejercicio 1 (40 puntos)
Un vivero recibe mercader�a de diversos proveedores, los cuales codifican sus productos de diversas maneras. Por este motivo, ha decidido optar
por una codificaci�n personal, diferente a estos c�digos. La forma en que codifica sus productos es mediante un c�digo alfanum�rico compuesto
por 3 letras y 3 n�meros, por ej.: AAA100. Tiene un total de 3.500 productos que son provistos por 3 proveedores.
Al inicio se cargan los siguientes datos de los 3.500 productos que comercializa: C�DIGO PRODUCTO( ej.: AAA100), DESCRIPCI�N, PRECIO UNITARIO DE VENTA.
Luego ingresa las compras realizadas a los proveedores en el mes en curso: CODIGO PRODUCTO PROVEEDOR (ver observaci�n), CANTIDAD COMPRADA,
PRECIO UNITARIO DE COMPRA. El fin est� dado por  CODIGO PRODUCTO PROVEEDOR ="XX".
Se desea:
1) Obtener un listado actualizado con los siguientes datos: 
C�D. PRODUCTO (*)	DESCRIPCI�N	CANTIDAD COMPRADA	PRECIO VTA ANTERIOR    PRECIO VTA NUEVO
XXXX			XXXXXXXXXXXX		XXXX			XXX,XX		XXX,XX

2) Cantidad de productos en los cuales el precio nuevo se increment� en m�s de un 30%.

OBSERVACI�N: El  CODIGO PRODUCTO PROVEEDOR var�a entre los distintos proveedores. Pero siempre comienzan con 4 d�gitos, contin�an con 3 letras y
3 n�meros (los usados para el c�digo propio del vivero), luego un gui�n - y letras, que pueden ser entre 3 y 6. Por ejemplo: 4578AQS300-PLANTA
Implementar las siguientes funciones:
- Una funci�n que devuelva el c�digo utilizado por el vivero. Dicha funci�n recibe de par�metro el c�digo producto del proveedor.
- Una funci�n de tipo void que reciba el precio unitario de compra y devuelva el nuevo precio de venta. �ste se obtiene al incrementar el
precio de compra en un 12% (ganancia del vivero). 
- Una funci�n que reciba de par�metro una matriz (una columna precio viejo y la otra columna precio nuevo) y devuelva por par�metro por
valor la cantidad de productos que aumentaron m�s de un 30%. 
*/

/*LEER:
deber�an ser 3500 productos. para probar, ser�n 5
Entonces, genero una variable producto, para que sea facil cambiar 
de 3500 a 5, o a cualquier otro valor
Lo declaro en la zona de variables globales, para que sea valido en las funciones*/
int productos=3;

string EXTRAE_COD(string codi); //funci�n que devuelve el c�digo utilizado por el vivero.
int BUSCA_COD(string codi, string DATOS[][2]); //no la pedia, se podi�a buscar en el while
void PRECIONUEVO(float PRE[][3]);//Una funci�n de tipo void que reciba el precio unitario de compra y devuelva el nuevo precio de venta.
int SUP30(float PRE[][3]);//devuelva por par�metro por valor la cantidad de productos que aumentaron m�s de un 30%. 

int main() {
	string DATOS[3500][2], cod, auxcod;
	float PRECIOS[3500][3];
	int CANTC[3500];
	int i, j, pos, supera;
	
	
	
	supera=0;
	
	//for(i=0; i<3500; i++)  dejo este for comentado para que se vea como debi�a hacerse
	for(i=0; i<productos; i++)
	{
		for(j=0; j<3; j++)
		{
			PRECIOS[i][j]=0;  // Siempre pongo en 0. Si un producto no se actualiza, queda en 0
		}
		CANTC[i]=0; //pongo en 0 vector de cantidades comparadas
	}
	
	/*l inicio se cargan los siguientes datos de los 3.500 productos que comercializa: C�DIGO PRODUCTO( ej.: AAA100), DESCRIPCI�N, 
	PRECIO UNITARIO DE VENTA.*/
	cout<<endl<<"CARGA DE LOS 3500 PRODUCTOS DEL VIVERO..."<<endl;
	for(i=0; i<productos; i++)
	{
		cout<<"C�digo: ";
		getline(cin,DATOS[i][0]);//codigo producto, interno del vivero
		cout<<"Descripci�n: ";
		getline(cin,DATOS[i][1]);//descripcion
		cout<<"Precio unitario: ";
		cin>>PRECIOS[i][0];// precio unitario de venta
		cin.get();
	}
	
	/*Luego ingresa las compras realizadas a los proveedores en el mes en curso: CODIGO PRODUCTO PROVEEDOR (ver observaci�n), CANTIDAD COMPRADA,
	PRECIO UNITARIO DE COMPRA. El fin est� dado por  CODIGO PRODUCTO PROVEEDOR ="XX".*/
	cout<<endl<<"CARGA DATOS DE LAS COMPRAS EFECTUADAS..."<<endl;
	cout<<"C�digo del PROVEEDOR: ";
	getline(cin, cod);//4578AQS300-PLANTA
	while(cod!="XX")
	{
		auxcod= EXTRAE_COD(cod);
		pos= BUSCA_COD(auxcod,DATOS);
		cout<<"Cantidad del producto "<<auxcod<<": ";
		cout<<pos<<endl;
		cin>>CANTC[pos]; //Cantidad comprada
		cout<<"Precio unitario compra: ";
		cin>>PRECIOS[pos][1]; //precio unitario de compra		
		cin.get();
		cout<<"C�digo del PROVEEDOR: ";
		getline(cin, cod);
	}
	//con los datos cargados, llamar� a la funci�n encargada de calcular el precio nuevo
	PRECIONUEVO(PRECIOS);
	/*1) Obtener un listado actualizado con los siguientes datos: 
	C�D. PRODUCTO (*)	DESCRIPCI�N	CANTIDAD COMPRADA	PRECIO VTA ANTERIOR    PRECIO VTA NUEVO
	XXXX			XXXXXXXXXXXX		XXXX			XXX,XX		XXX,XX*/
	cout<<endl<<"C�D. PROD.   DESC. 	CANT.COMPRADA	PREC.VTA ANTERIOR    PREC.VTA NUEVO"<<endl;
	for(i=0;i<productos;i++)
		cout<<DATOS[i][0]<<" "<<DATOS[i][1]<<"  "<<CANTC[i]<<"  "<<PRECIOS[i][0]<<"  "<<PRECIOS[i][2]<<endl;
	
	//2) Cantidad de productos en los cuales el precio nuevo se increment� en m�s de un 30%.
	supera= SUP30(PRECIOS);
	cout<<endl<<"Cantidad de productos en los cuales el precio nuevo se increment� en m�s de un 30%= "<<supera<<endl;
	
	return 0;
}

string EXTRAE_COD(string codi)
{
	string aux;//4578AQS300-PLANTA
	
	aux=codi.substr(4,6);
	return(aux);
}

int BUSCA_COD(string codi, string DATOS[][2])
{
	int p,f;
	
	for(f=0; f<productos; f++)
	{
		if(codi==DATOS[f][0])
		{
			p=f;
			f=productos;
		}
	}
	return (p);
}

void PRECIONUEVO(float PRE[][3])
{
	//nuevo precio de venta. �ste se obtiene al incrementar el	precio de compra en un 12% (ganancia del vivero). 
	int f;
	for(f=0; f<productos; f++)
		PRE[f][2]=PRE[f][1]*1.12;
}

int SUP30(float PRE[][3])
{
	int c,f;
	float sub;
	c=0;
	
	for(f=0; f<productos; f++)
	{
		sub=PRE[f][0]*1.3;
		if(PRE[f][2]>=sub)
			c++;
	}
	return(c);
}
