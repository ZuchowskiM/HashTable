#include<iostream>
#include<string>

using std::string;
using std::cout;
using std::endl;

class Hashobj
{
public:
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



};

class Hashtable
{
public:
	Hashobj* tab;
	int size;

	Hashtable()
	{
		size = 0;
		tab = nullptr;
	}

	Hashtable(int size_p)
	{
		this->size = size_p;
		tab = new Hashobj[size_p];
	}

	~Hashtable()
	{
		delete[] tab;
	}

	int HashFunction(long key_p)
	{
		return key_p % size;
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

	void deleteFromTable(int p_key)
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

		fillTheGaps(p_key, i);
		
		
	}

	void fillTheGaps(int p_key, int miejsceUsuniecia)
	{
		int dokatSprawdzac = HashFunction(p_key);
		int i = miejsceUsuniecia + 1;
		bool sprawdzonoTablice = false;

		if (i == dokatSprawdzac)
			sprawdzonoTablice = true;

		while(sprawdzonoTablice == false)
		{
			
			if (i != size)
			{
				if (HashFunction(tab[i].key) == HashFunction(p_key))
				{
					tab[miejsceUsuniecia].chain = tab[i].chain;
					tab[miejsceUsuniecia].key = tab[i].key;

					tab[i].chain.clear();
					tab[i].key = 0;
					
					miejsceUsuniecia = i;
				}
				else
				{
					i++;
				}
			}
			else
			{
				i = 0;
				if (HashFunction(tab[i].key) == HashFunction(p_key))
				{
					tab[miejsceUsuniecia].chain = tab[i].chain;
					tab[miejsceUsuniecia].key = tab[i].key;

					tab[i].chain.clear();
					tab[i].key = 0;

					miejsceUsuniecia = i;
				}
				else
				{
					i++;
				}
			}

			if (i == dokatSprawdzac)
				sprawdzonoTablice = true;
			
		}

		
	}

};

int main()
{
	Hashtable h1(3);

	h1.addToTable("ala", 13);
	h1.addToTable("ola", 22);
	h1.addToTable("basia", 4);

	h1.deleteFromTable(4);

	
	for (int i = 0; i < 3; i++)
	{
		cout << "index: " << i << " lancuch: " << h1.tab[i].chain << endl;
	}

	return 0;
}


