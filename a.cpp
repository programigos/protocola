#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;


void print5x5(int (*mat)[5]){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			if ((*(*mat+i)+j) == 0) cout << "-";
			else cout << (*(*mat+i)+j) << " ";
		}
		cout << endl;
	}
}

int rdtsc(){
	__asm__ __volatile__("rdtsc");
}

class Carta{
public:
	char palo;
	int numero;
	Carta(char letra, int num){
		this -> palo = letra;
		this -> numero = num;
	}
};

vector<int> MakeVector(int n){
	vector<int> v;
	for (int i = 1; i <= n; i++)
		v.push_back(i);
	return v;
}

bool verificar(vector<int> numeros, int numero){
	for(int i = 0; i < numeros.size(); i++){
		if(numeros[i] == numero){
			return true;
		}
	}
	return false;
}

vector<Carta> unir(vector<Carta> A, vector<Carta> B){
	vector<Carta>C;
	for(int i = 0; i < A.size(); i++){
		C.push_back(A[i]);
	}
	for(int j = 0; j < B.size(); j++){
		C.push_back(B[j]);
	}
	return C;
}

vector<Carta> partir(vector<Carta> numero,int posicion, int numeros){
	vector <Carta> resultado;
	for(int i = 0; i < numeros; i++){
		resultado.push_back(numero[posicion]);
		posicion++;
	}
	return resultado;
}

const int n = 75;

class Dado{
public:
	int caras;
	Dado(int a){caras=a;}
	int operator()(){
		return rand()%caras + 1;
	}
};

class bola{
public:
	int num;
	char letra;
	bola(){}
	bola(int a, char b){num=a;letra=b;}
};

bool buscar_bola(vector<bola> nam, int a, char b){
	for(int i=0;i<nam.size();i++){
		if((nam[i].num==a)&&(nam[i].letra==b))
			return true;
	}
	return false;
}

class Bolillero{
private:
	vector<bola> bolillas;
public:
	int x;
	int sacadas;
	Bolillero(int a){x=a;sacadas=0;}
	void operator()(){
		if(sacadas<=(x*5)-1){
			char bingo[5] = {'B','I','N','G','O'};
			int letra=rand()%5;
			int numero=rand()%x+1;
			bola retornar((x*letra)+numero,bingo[letra]);
			while(buscar_bola(bolillas,retornar.num,retornar.letra)){
				letra=rand()%5;
				numero=rand()%x+1;
				retornar=bola((x*letra)+numero,bingo[letra]);
			}
			bolillas.push_back(retornar);
			sacadas++;
			cout << retornar.letra << "-" << retornar.num << endl;
		}
		else
		   cout<<"No hay mas bolillas"<<endl;
	}
};

class Cartilla{
private:
	int numOfBalls;
public:
	Cartilla(int n){
		this->numOfBalls = n;
	}
	void operator()(int n){
		for (int carts = 0; carts < n; carts++){
			int num, gap;
			int (*cart)[5];
			for(int i = 0; i < 5; i++){
				for(int j = 0; j < 5; j++){
					
					do{
						num = rand() % gap;
					}while(num);
					//(*(*cart+j)+i) = num;
					cart[j][i] = num;
				}
			}
			(cart[2][2]) = 0;
			print5x5(cart);
		}
	}
};

class Cartillas{
private:
	int bolillas;
public:
	Cartillas(int a){
		this -> bolillas = a;
	}
	operator()(int num){ ///numero de cartillas
		int resultado;
		for(int i = 0; i < num; i++){
			vector<int> comprobacion;
			cout << " B  I  N  G  O" << endl;
			for(int j = 0; j < 5; j++){
				for(int k=0;k<5;k++){
					if(j==2&&k==2){
						cout<<"XX ";
						continue;
					}
					resultado = rand()%bolillas+(k*bolillas)+1;
					while(verificar(comprobacion,resultado)){
						resultado = rand()%bolillas+(k*bolillas)+1;
					}
					if(resultado<10)
									cout<<" ";
					comprobacion.push_back(resultado);
					cout<<resultado<<" ";
				}
				cout<<endl;
			}
			cout<<endl<<endl;
		}
	}
};

class Baraja{
private:
	vector<Carta> espadas;
	vector<Carta> corazones;
	vector<Carta> diamantes;
	vector<Carta> treboles;
	vector<Carta> baraja;
	
public:
	Baraja(){
		for(int j = 1; j <= 13; j++){
			espadas.push_back(Carta(3,j));
			corazones.push_back(Carta(4,j));
			diamantes.push_back(Carta(5,j));
			treboles.push_back(Carta(6,j));
		}
		this -> baraja = unir(unir(espadas,corazones),unir(diamantes,treboles));
	}
	operator()(int mesclas){
		int izquierda=0;
		int derecha=0;
		for(int i = 0; i < mesclas; i++){
			vector<Carta> resultado;
			izquierda=0;
			derecha=0;
			while(izquierda<25&&derecha<25){
				for(int i=0;i<(rand()%(26-izquierda)+1);i++,izquierda++)
					resultado.push_back(baraja[izquierda]);
				for(int i=0;i<(rand()%(26-derecha)+1);i++,derecha++)
					resultado.push_back(baraja[derecha+26]);
			}
			if(izquierda!=26){
				for(;izquierda<26;izquierda++)
					resultado.push_back(baraja[izquierda]);
			}
			if(derecha!=26){
				for(;derecha<26;derecha++)
					resultado.push_back(baraja[derecha+26]);
			}
			baraja=resultado;
			
		}
	}
	void imprimir(){
		for(int i = 0; i < baraja.size(); i++){
			cout << baraja[i].palo << baraja[i].numero << " ";
		}
	}
};


int main(int argc, char *argv[]){
	srand(time(NULL));
	cout << "--------------------------------------------" << endl;
	Dado A(19);
	for(int i=0;i<10;i++)
		cout << "Dado| salio el lado " << A() << endl;
	cout << "--------------------------------------------" << endl;
	Bolillero B(15);
	for (int i = 0; i < 100; i++){
		B();
	}
	cout << "--------------------------------------------" << endl;
	Cartillas Bingo(15);
	Bingo(5);
	cout << "--------------------------------------------" << endl;
	Baraja cartas;
	cartas(11);
	cartas.imprimir();
	return 0;
}

