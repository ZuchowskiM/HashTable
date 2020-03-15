#include<iostream>
#include<string>
#include<fstream>

using std::string;
using std::cout;
using std::endl;

class Hashtable;

class Hashobj
{
	friend class Hashtable;
private:
	long key;
	string chain;

	Hashobj()
	{
		key = 0;
	}

	Hashobj(long key_p, char* chain_p)
	{
		key = key_p;
		chain = chain_p;
	}

	~Hashobj()
	{
		//EMPTY
	}

public:
	const long getKey() const
	{
		return key;
	}

	const string& getChain() const
	{
		return chain;
	}


};

class Hashtable
{
private:
	Hashobj* tab;
	int size;

	int HashFunction(long key_p)
	{
		return key_p % size;
	}

public:
	Hashtable()
	{
		size = 0;
		tab = nullptr;
	}

	~Hashtable()
	{
		delete[] tab;
	}

	/*void fillTheGaps2(long p_key, int miejsceUsuniecia)
	{
		int dokatSprawdzac = HashFunction(p_key);

		int i = miejsceUsuniecia + 1;
		if (i == size)
			i = 0;

		bool sprawdzonoTablice = false;

		if (i == dokatSprawdzac)
			sprawdzonoTablice = true;

		while (sprawdzonoTablice == false)
		{

			if (HashFunction(tab[i].key) == HashFunction(p_key))
			{
				tab[miejsceUsuniecia].chain = tab[i].chain;
				tab[miejsceUsuniecia].key = tab[i].key;

				tab[i].chain.clear();
				tab[i].key = 0;

				miejsceUsuniecia = i;
				i++;
			}
			else
			{
				i++;
			}


			

			if (i == size)
				i = 0;

			if (i == dokatSprawdzac)
				sprawdzonoTablice = true;

		}


	}*/
	
	void fillTheGaps(int miejsceUsuniecia)
	{
		int dokatSprawdzac = miejsceUsuniecia;

		int i = miejsceUsuniecia + 1;
		if (i == size)
			i = 0;

		bool sprawdzonoTablice = false;

		if (i == dokatSprawdzac)
			sprawdzonoTablice = true;

		int gdzieJestMojeMiejsce;

		while (!sprawdzonoTablice)
		{
			gdzieJestMojeMiejsce = HashFunction(tab[i].key);

			while (gdzieJestMojeMiejsce != i)
			{
				if (tab[gdzieJestMojeMiejsce].key == 0)
				{
					tab[gdzieJestMojeMiejsce].key = tab[i].key;
					tab[gdzieJestMojeMiejsce].chain = tab[i].chain;

					tab[i].key = 0;
					tab[i].chain = "";
				}

				gdzieJestMojeMiejsce++;

				if (gdzieJestMojeMiejsce == size)
					gdzieJestMojeMiejsce = 0;
			}

			i++;

			if (i == size)
				i = 0;

			if (i == dokatSprawdzac)
				sprawdzonoTablice = true;
		}

	}

	const int getSize() const
	{
		return size;
	}

	const Hashobj& getTab(int index) const
	{
		return tab[index];
	}

	void setSize(int size_p)
	{
		this->size = size_p;
		delete[] tab;
		tab = new Hashobj[size_p];
	}

	void addToTable(string chain, long key)
	{
		bool wstawieniePowiodloSie = false;
		int i = HashFunction(key);

		if (tab[i].key == 0)
		{
			tab[i].chain = chain;
			tab[i].key = key;
		}
		else
		{
			i++;
			while (wstawieniePowiodloSie == false)
			{
				if (i != size)
				{
					if (tab[i].key == 0)
					{
						tab[i].chain = chain;
						tab[i].key = key;
						wstawieniePowiodloSie = true;
					}
					else
					{
						i++;
					}
					
				}
				else
				{
					i = 0;
					if (tab[i].key == 0)
					{
						tab[i].chain = chain;
						tab[i].key = key;
						wstawieniePowiodloSie = true;
					}
					else
					{
						i++;
					}
				}

				
			}
		}
		
	}

	void deleteFromTable(long p_key)
	{
		int i = HashFunction(p_key);
		bool znaleziono = false;

		while (znaleziono == false)
		{
			if (i != size)
			{
				if (tab[i].key == p_key)
				{
					tab[i].chain.clear();
					tab[i].key = 0;
					znaleziono = true;
				}
				else
				{
					i++;
				}

			}
			else
			{
				i = 0;
				if (tab[i].key == p_key)
				{
					tab[i].chain.clear();
					tab[i].key = 0;
					znaleziono = true;
				}
				else
				{
					i++;
				}
			}
		}

		fillTheGaps(i);
		
		
	}

	
};

int main()
{
	std::fstream plik;
	plik.open("testForPauli.txt");

	int liczbaPrzypadkow;
	plik >> liczbaPrzypadkow;

	bool zakonczPrzypadek = false;
	std::string polecenie;
	long zmiennaKeySize;
	std::string zmiennaCiag;

	for (int i = 0; i < liczbaPrzypadkow; i++)
	{
		Hashtable* h = new Hashtable();
		zakonczPrzypadek = false;

		while (!zakonczPrzypadek)
		{
			plik >> polecenie;
			

			if (polecenie == "size")
			{
				plik >> zmiennaKeySize;
				h->setSize(zmiennaKeySize);
				
			}
			else if (polecenie == "add")
			{
				plik >> zmiennaKeySize;
				plik >> zmiennaCiag;
				h->addToTable(zmiennaCiag, zmiennaKeySize);
				
			}
			else if (polecenie == "delete")
			{
				plik >> zmiennaKeySize;
				h->deleteFromTable(zmiennaKeySize);
				
			}
			else if (polecenie == "print")
			{
				for (int i = 0; i < h->getSize(); i++)
				{
					if (h->getTab(i).getKey() != 0)
					{
						cout << i << " " << h->getTab(i).getKey() << " " << h->getTab(i).getChain() << endl;
					}
				}
				cout << endl;
				
			}
			else if (polecenie == "stop")
			{
				zakonczPrzypadek = true;
				
			}
		}

		delete h;
	}
	
	plik.close();
	return 0;
}


