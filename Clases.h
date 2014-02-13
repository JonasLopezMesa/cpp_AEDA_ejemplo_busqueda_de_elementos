#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;


//CLASE VECTOR


class vectorT
{
private:
	int * v_;
	int sz_;
public:
	vectorT();
	vectorT(const vectorT& v);
	~vectorT();
	bool read (ifstream & is);
	void write();
	int buscar(int x);
	void OR(int i, int d);
	int showsz();
private:
	int buscar1(int i, int d, int x);
	int partir(int primero, int ultimo);
};

vectorT::vectorT() : v_(NULL), sz_(0) {}
vectorT::~vectorT()
{
	if (v_ != NULL) {
		delete [] v_;
		v_ = NULL;
	}
	sz_ = 0;
}
vectorT::vectorT(const vectorT& v)
{
	sz_=v.sz_;
	
	v_= new int [sz_];
	
	for(int i=0;i< sz_;i++)
		v_[i]=v.v_[i];
}
int vectorT::showsz()
{
	return sz_;
}

bool vectorT::read(ifstream & is)
{
	//cout << endl;
	//cout << "Leyendo..." << endl;
	//cout << "-------------------------" << endl;
	if (is.eof()){
		//cout << "-Fin de la linea" << endl;
		return false;
	}
	int sz;
	is >> sz;
	//cout << "SZ: " << sz << endl;
	if (! is.good()){
		//cout << "-Archivo en mal estado " << endl;
		return false;
	}
	if (v_ != NULL) {
		//cout << "-Vector nulo " << endl;
		delete[]v_;
		v_ = NULL;
	}
	sz_ = sz;
	//cout << "SZ_: " << sz_ << endl;
	//cout << "Tamaño:   ";
	//cout << sz_ << endl;
	v_ = new int[sz];
	for (int i = 0; i < sz_; i++) {
		is >> v_[i];
	}
	//for (int i = 0; i < sz_; i++) {
	//	cout << v_[i] << "  ";
	//}
	return true;
}
void vectorT::write(void)
{
	cout << sz_ << endl;
	cout << "------------------------------" << endl;
	for (int i = 0; i < sz_; i++) {
		cout << v_[i] << "  ";
	}
	cout << endl;
}
int vectorT::buscar(int x)
{
	return buscar1(0, sz_-1,x);
}

int vectorT::buscar1(int i, int d, int x)
{
	int centro;
	if (i <= d) {
		centro = (i + d) / 2;
		if (v_[centro] == x){
			return centro;
		}
		else {
			if (v_[centro] > x)
				return buscar1(i, centro - 1, x);
			else {
				return buscar1(centro + 1, d, x);
			}
		}
	}
	else {
		return -1;
	}
}



void vectorT::OR(int i, int d)
{
	int pos_pivote;
	if (i < d) {
		//particionamos v
		pos_pivote = partir(i, d);
		//ordenaro primera mitad
		OR(i, pos_pivote - 1);
		//ordenar segunda mitad
		OR(pos_pivote + 1, d);
	}
}

int vectorT::partir(int primero, int ultimo)
{
	int i, d;
	int val_pivote;
	//hacemos pivote primer elemento
	val_pivote = v_[primero];
	i = primero +1;
	d = ultimo;
	do {
		while ((i <= d) && (v_[i] <= val_pivote)) {
			i++;
		}
		while ((i <= d) && (v_[d] > val_pivote)) {
			d--;
		}
		if (i < d) { //intercambio
			swap(v_[i], v_[d]);
			i++;
			d--;
		}
	} while (i <= d);
		
	swap(v_[primero], v_[d]);
	return d;
}
		


	
//CLASE SLL_ITEM

class sll_item
{
private:
	sll_item* next_;
	vectorT dato_;
public:
	sll_item(const vectorT & dato);
	~sll_item();
	void write();
	void setnext(sll_item* n);
	sll_item* getnext();
	void setDato(vectorT d);
	vectorT& getDato();
	int buscar(int x);
	void ordenar();
	
	
};

sll_item::sll_item(const vectorT & dato) : dato_(dato), next_(NULL) {}
//destructor
sll_item::~sll_item()
{
	next_ = NULL;	
}

void sll_item::setnext(sll_item* n)
{
	next_ = n;
}

sll_item* sll_item::getnext()
{
	return next_;
}

void sll_item::setDato(vectorT d)
{
	dato_ = d;
}

vectorT& sll_item::getDato()
{
	return dato_;
}

void sll_item::write()
{
	getDato().write();
}
int sll_item::buscar(int x)
{
	return dato_.buscar(x);
}
void sll_item::ordenar()
{
	dato_.OR(0, dato_.showsz() - 1);
}


//CLASE SLL

class sll
{
private:
	sll_item* inicio_;
public:
	sll();
	~sll();
	void read(const char* file);
	void imprimir();
	void buscar(int x);
	void insert_b(sll_item* i);
	void ordenar();
	
};

sll::sll() : inicio_(NULL) {}

sll::~sll() 
{
	sll_item* aux = NULL;
	while (inicio_ != NULL) {
		aux = inicio_;
		inicio_ = inicio_->getnext();
		delete aux;
	}
}
void sll::insert_b(sll_item* i)					//insertar por el principio
{
	i->setnext(inicio_);
	inicio_ = i;
}
void sll::read(const char* name)
{
	ifstream is(name);
	//cout << name << endl;
	//cout << is << endl;
	if (is.is_open()){
		bool correcto = true;
		vectorT v;
		do {
			correcto = v.read(is);
			if(correcto) {
				sll_item* nodo = new sll_item(v);
				insert_b(nodo);
			}
			else {
				//cout << "ERROR2: No se ha podido escribir en la lista. " << endl;
			}

		} while (correcto);
	}
	else {
		cout << "ERROR0: No se ha podido abrir el archivo" << endl;
	}

	is.close();
}
			
void sll::imprimir()
{
		sll_item* aux = inicio_;
		while (aux != NULL) {
			cout << "TAMAÑO:                    ";
			aux->write();
			cout << "------------------------------" << endl;
			aux = aux->getnext();
		}		
}

void sll::buscar(int x)
{
	int mod = 0;
	int i = 0;
	cout << "El elemento seleccionado se encuentra en los siguientes puntos: " << endl;
	cout << "----------------------" << endl;
	sll_item* aux = inicio_;
	while (aux != NULL) {
		
		cout << "Vector número:......" << i << endl << "Posición:...........";
		if (aux->buscar(x) == -1) {
			cout << "no existe";
		}
		else {
		cout << aux->buscar(x);
		}
		if (aux->buscar(x) > mod) {
			mod = aux->buscar(x);
		}
		cout << endl;
		aux = aux->getnext();
		i++;
	}
	cout << "La posición mayor es: " << mod << endl;
	
}
	
	
void sll::ordenar()
{
	sll_item* aux = inicio_;
	while (aux != NULL) {
		aux->ordenar();
		aux = aux->getnext();
	}
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	
	
	
	
	
	
	
	
	

