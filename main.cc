/*
Lire README.md

Fr�d�ric Faure.

11 octobre 2016.
Demande de Malik d' etudier les ensemble de notes.


Commande de compilation:
g++ -std=c++11 main.o  -o main

Lire README.md
 */



/*


OBJET :
====
Un objet est une suite de n notes.

Par exemple les n=4 notes suivantes   C D F# G
Elles sont cod�es par la suite binaire    101000110000
o�  une suite de 12 bits correspond � la gamme chromatique C,C# ,.. B
et 1 veut dire que la note est presente, 0 absente.

cette suite binaire (en commancant la lecture par la gauche) correspond en ecriture d�cimale au chiffre v=197
Je l'appelle donc l'objet de valeur v=197.

La periode de l'objet est le nombre de transpositions a effectuer pour obtenir les meme notes.
Ici c'est T=12.



remarque:
--------------
Comme on travaille modulo  transposition, cet objet v=197 est en fait equivalent � 12 autres suites  de notes:
par exemple  C C# F# G# (valeur 323)  ou  D D# G# A# (valeur 1292) . On decide que C D F# G est le representant d'apr�s le crit�re "il a le plus de notes basses".
Le vrai crit�re et que sa valeur est la plus faible, ici  c'est v=197.



Exemples d'objets
================================
on donne ici leur valeur (i.e. representant minimal)

Gamme majeur: v=1387, T=12
------------
Notes=C D E F G A B 
      101011010101
    val=2741

    decalage=11
Notes=C C# D# F F# G# A# 
      110101101010
    val=1387


Gamme mineur melodique: v=1371, T=12
---------------
Notes=C D D# F G A B 
      101101010101
    val=2733
    decalage=11
Notes=C C# D# E F# G# A# 
      110110101010
    val=1371


Gamme mineur harmonique: v=859, T=12
---------------------
Notes=C D D# F G G# B 
      101101011001
    val=2477
    decalage=11
Notes=C C# D# E F# G# A 
      110110101100
    val=859



ST Majeur M: v=355, T=12
--------------------
Notes=C E F G B 
      100011010001
    val=2225 Periode T=12
    decalage=11
Notes=C C# F F# G# 
      110001101000
    val=355


ST mineur melodique m1 v=333, T=12
---------------------------
Notes=C D# F A B 
      100101000101
    val=2601 Periode T=12
    decalage=9
Notes=C D D# F# G# 
      101100101000
    val=333

ST mineur melodique m2 v=341, T=12
---------------------------
Notes=D# F G A B 
      000101010101
    val=2728 Periode T=12
    decalage=3
Notes=C D E F# G# 
      101010101000
    val=341


ST mineur melodique m3 v=101, T=12
---------------------------
Notes=D D# A B 
      001100000101
    val=2572 Periode T=12
    decalage=9
Notes=C D F F# 
      101001100000
    val=101



ST mineur harmonique h1 v=153, T=12
---------------------------
Notes=C D# G# B 
      100100001001
    val=2313 Periode T=12
    decalage=8
Notes=C D# E G 
      100110010000
    val=153


ST mineur harmonique h2 v=51, T=12
---------------------------
Notes=C G G# B 
      100000011001
    val=2433 Periode T=12
    decalage=7
Notes=C C# E F 
      110011000000
    val=51

ST mineur harmonique h3 v=147, T=12
---------------------------
Notes=D G G# B 
      001000011001
    val=2436 Periode T=12
    decalage=7
Notes=C C# E G 
      110010010000
    val=147


Toutes les 15+2  gammes symetriques (periode T<12)
=================================================

Objet  v=0	    000000000000   periode T=1, 
Objet  v=65	    100000100000   periode T=6, 	C F# 
Objet  v=195	110000110000   periode T=6, 	C C# F# G
Objet  v=273	100010001000   periode T=4, 	C E G#
Objet  v=325	101000101000   periode T=6, 	C D F# G#
Objet  v=455	111000111000   periode T=6, 	C C# D F# G G#             : MATL M5
Objet  v=585	100100100100   periode T=3, 	C D# F# A
Objet  v=715	110100110100   periode T=6, 	C C# D# F# G A
Objet  v=819	110011001100   periode T=4, 	C C# E F G# A 
Objet  v=845	101100101100   periode T=6, 	C D D# F# G# A 
Objet  v=975	111100111100   periode T=6, 	C C# D D# F# G G# A        : MATL M4
Objet  v=1365	101010101010   periode T=2, 	C D E F# G# A#             : MATL M1, gamme par tons
Objet  v=1495	111010111010   periode T=6, 	C C# D E F# G G# A#        : MATL M6
Objet  v=1755	110110110110   periode T=3, 	C C# D# E F# G A A#        : MATL M2, gamme diminuee
Objet  v=1911	111011101110   periode T=4, 	C C# D E F F# G# A A#      : MATL M3
Objet  v=2015	111110111110   periode T=6, 	C C# D D# E F# G G# A A#   : MATL M7
Objet  v=4095	111111111111   periode T=1, 	C C# D D# E F F# G G# A A# B : gamme chromatique



OBJETS VOISINS
=============

pour un objet donn�, on s'interesse aux "objets voisins" c'est � dire
qui ont une note de plus ou une note de moins.

Par exemple pour

Objet  v=199    111000110000   periode T=12,     C C# D F# G
 nombre de notes n=5


il a  plusieurs voisins dont le voisin avec une note de plus:
    v=455    111000111000   periode T=6,     C C# D F# G G#

et le voisin avec une note de moins:
    v=135    111000010000   periode T=12,     C C# D G
il a aussi le voisin avec une note de moins:
    v=99    011000110000   periode T=12,     C# D F# G  (decalage de p=1)
o� l'information "decalage de p=1" signifie que cet objet de valeur v=99 est en fait la suite binaire
 110001100000   obtenue par un decalage de p=1 vers la droite.




BILAN (present� en fin de fichier)
======

Il y a 352 objets dont:
335   objets de periode T=12.
9   objets de periode T= 6.
3   objets de periode T= 4.
2   objets de periode T= 3.
1   objets de periode T= 2.
2   objets de periode T= 1.

Et Il y a 291 objets de periode T=12 et ayant des voisins qui sont tous  de periode T=12. Ce sont des objets "d'identit� A et de filiation A". Leur valeur est:
3 5 7 9 11 13 15 19 21 23 25 27 29 31 33 35 37 39 41 43 45 47 49 51 53 55 57 59 61 63 71 75 77 79 83 85 87 89 91 93 95 99 101 103 105 107 109 111 113 115 117 119 121 123 125 127 133 135 137 139 141 143 145 147 149 151 153 155 157 159 163 165 167 169 171 173 175 177 179 181 183 185 187 189 191 197 201 205 207 209 213 215 217 219 221 223 229 231 233 235 237 239 241 243 245 247 249 251 253 255 279 283 285 287 291 293 295 297 299 301 303 309 311 313 315 317 319 329 331 335 339 343 345 347 349 351 355 359 361 363 365 367 371 373 375 377 379 381 383 397 399 403 405 407 411 413 415 421 423 425 427 429 431 435 437 439 441 443 445 447 457 459 461 467 469 473 475 477 479 485 489 491 493 495 499 501 503 505 507 509 511 591 595 597 599 603 605 607 613 615 619 621 623 627 629 631 635 637 639 661 663 667 669 671 679 683 685 687 691 693 695 699 701 703 717 723 725 727 733 735 743 749 751 755 757 759 763 765 767 821 829 831 853 855 859 863 871 875 879 885 891 893 895 925 927 939 941 943 949 951 957 959 981 983 987 989 1003 1005 1013 1015 1019 1021 1023 1371 1375 1387 1391 1403 1407 1455 1463 1467 1471 1499 1519 1531 1535 1775 1783 1791 1983

 */


#include <iostream>
using namespace std;

#include <vector>
#include <math.h>
#include <bitset>
#include <algorithm>
#include <tuple>
#include <fstream>
#include <sstream>
vector<string> notes={"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
//======================

class Objet
{
public:
	int v; //valeur de l'objet (12 bits)
	int T; //periode
	int n;//nbre de notes (bits 1)

	vector< tuple<int , int, int > > L_up, L_down; // liste des valeurs ayant une note de plus (val, shift p, index i)

	vector<tuple<int,int> > L_sym; // liste des valeurs symetriques (v2,p) (T<12) t.q. v est inclu dans v2 avec decalage p 
};


vector<Objet> L_o; //Liste d'objets

//===========
/*
entree: val: valeur
sortie nbre de bits 1 parmi les 12 premiers
ex: val = 0b 1011 renvoit n=3



rem: utiliser plutot biset.count()
 */
int nbre_notes(int val)
{
	int n=0;
	for(int t=1;t<=12;t++)
	{
		n += val%2; //ajout du bit faible
		val = val/2 + (val%2)* (1<<11); //permuttation circulaire de k
	}
	return n;
}

//===================
/*
renvoit 0,1 la valeur du bit a la position pos >=0
ex: val = 0b 1011,  pos=2 renvoit b = 0
 */
int GetBit(int val, int pos)
{
	return (val>>pos)%2;
}

//===================
/*
Met le bit pos a 1 dans le nombre val
ex: val 0b 1011, pos = 2 renvoit val = 0b 1111
 */
int SetBit(int val, int pos)
{
	return val | (1<<pos);
}

//==================
/*
entree 
    entier n < 2^12 
sortie
    p=0 si n est le plus petit de toutes ses permutations circulaires 
	p: nbre de right shift a faire pour obtenir le plus petit
    n : representant le + petit
    
 */
int Test_permut_circ(int &n, int opt_affiche=0)
{
	int n0=n;
	int p=0, pmin=0;
	int k=n; // nombre � permutter
	//	cout<<"k="<<bitset<12>(k)<<endl;
	
	for(p = 1; p<=11; p++)
	{
		k=k/2 + (k%2)* (1<<11); //permuttation circulaire droite de k
		//	cout<<"k="<<bitset<12>(k)<<endl;

		if(k < n)
		{
			pmin=p;
			n = k;
		}
		//cout<<"n0="<<n0<<", "<<bitset<12>(n0)<<" p="<<p<<" k="<<k<<" "<<bitset<12>(k)<<" n="<<n<<" pmin="<<pmin<<endl;

	}

	if(opt_affiche)
		cout<<"On donne n="<<n0<<", "<<bitset<12>(n0)<<". Alors avec decalage  p="<<pmin<<" n="<<n<<" "<<bitset<12>(n)<<endl;

	return pmin;
}

//================
/*
  input val, k
  output: right shift of val by k shifts on 12 bits
*/
int Right_shift(int v, int p)
{
//	return v;
	for(int k = 1; k<=p; k++)
		v = v/2 + (v%2)* (1<<11);
	return v;
}

//===========
/*
input v
output reverse value on first 12 bit
 */
int Reverse(int v)
{
	int r=0;
	for(int b=0;b<12;b++)
	{
		r=r*2;
		r+= v%2;
		v=v/2;
	}
	return r;
}
/*=========================
input: val : value
output: index of the objet with this value . -1: if not found
 */
int index_Lo(int val)
{
	int i=0;
	int test=0;
	
	for(i=0;i<L_o.size(); i++)
		if (L_o[i].v == val)
		{
			test=1;
			break;
		}
	if(test==0)
		return -1; // pas trouve
	else
		return i;
}


/*=========================
input: val : value
output: index of the objet with this value. -1: if not found
 */
int index_L_up(int val, vector<tuple<int,int,int>> &L_up)
{
	int i=0;
	int test=0;
	
	for(i=0;i<L_up.size(); i++)
		if (get<0>(L_up[i]) == val)
		{
			test=1;
			break;
		}
	if(test==0)
		return -1; // pas trouve
	else
		return i;
}

//================
/*
Periode d'un objet
 */
int Periode(int v)
{
	int T=0;
	int k=v;
	for(int t=1;t<=12;t++)
	{
		k=k/2 + (k%2)* (1<<11); //permuttation circulaire de k
		if(k==v)
		{
			T=t;
			break;
		}
	}
	return T;
}

/*===========================
  input v
  output:
  liste de notes correspondantes

  ex: v = 010110111111

  -> C# D# E F# G G# A A# B
*/
string Notes(int v)
{
	string s;
	for(int b=11;b>=0;b--)
	{
		if(GetBit(v,b))
		{
			s+= notes[11-b] + " ";
		}
	}
	return s;
}


/*======================
input : v1, v2  values of objet

output: p \in {0,11}: decalage de v1 pour qu'il soit inclu dans v2
        p=-1 si v1 n'est pas inclu dans v2 (pour tout decalage) 
    

cad Right_shift(v1,p) est inclu dans v2
 */
int Inclusion(int v1,int v2)
{
	int test=0;
	int p=0;
	for(p=0; p<12;p++)
	{

		if (((v1)&(~v2))==0) // then v1 is  included in v2
		{
			test=1;
			break;
		}
		
		v1=Right_shift(v1,1);
	}
	if(test==0)
		p=-1;
	return p;
}
//=================
/*
sortie:
liste de nombre en base deux, avec 12 bits,    0,1 
class�s par ordre croissant,
et tels que il y a un seul representant par classe  d'equivalence:
deux nombre sont equivalents si egaux apres une permutation circulaire.
 */
void fabrique_liste_objets()
{

	for(int i=0; i< (1<<12) ; i++)
	{
		
		//.. on parcourt les 12 permutation et on teste si i est plus petit que toutes
		int k=i;
		int test = Test_permut_circ(k);

		if(test != 0)
			continue;

        //--- ici, i est un nouvel objet

		//.. calcul de sa periode T et nbre de notes n

		
		int T=0, n=0;
		k=i;
		test=0;
		for(int t=1;t<=12;t++)
		{
			n += k%2; //ajout du bit faible
			k=k/2 + (k%2)* (1<<11); //permuttation circulaire de k
			if(test==0 && k==i)
			{
				T=t;
				test=1;
			}
		}

		
		Objet o;
		o.v=i;
		o.T=T;
		o.n=n;
		L_o.push_back(o);


	}

	
}
//===========================
/*
  Parcourt tous les objets
  Pour chaque objet, cherche les objets voisins (i.e. qui differente que de +/- une note)
  et construit les listes: L_up, L_down
*/
void Recherche_liens()
{
	
	for(int i=0;i<L_o.size();i++)
	{
		//	Objet o  = L_o[i];
		
		//.. rajoute une note ,ie bit b...
		for(int b=0; b<12; b++)
		{
			if(GetBit(L_o[i].v,b)==0) 
			{
				int val2 = SetBit(L_o[i].v,b); // nouvel objet
				
				int p=Test_permut_circ(val2); // -> val2: representant minimal apres right shift de p
				if( index_L_up(val2, L_o[i].L_up) == -1) //test si val2 est nouveau dans la liste L_up
				{
					int j = index_Lo(val2); //index de l'objet de valeur val2
					
					L_o[i].L_up.push_back(make_tuple(val2, p, j)); // le rajoute dans liste L_up


				
					//... rajoute aussi a la liste L_down
				
					L_o[j].L_down.push_back(make_tuple(L_o[i].v, (12-p)%12, i)); // le rajoute dans liste L_up
					
					//cout<<" L_o[i].v = "<<L_o[i].v<<" val2="<<val2<<endl;


				}
			}
		}
	}
}

/*===============================
Etabli pour chaque objet v1 non sym (T==12), la liste des valeurs v2 symetriques (1<T<12)
t.q. v1 est inclu dans v2 modulo decalage p
 */
void Liste_inclusions_sym()
{
	for(int i=0;i<L_o.size();i++)
	{
		if (L_o[i].T<12)
			continue;

		for(int j=0;j<L_o.size();j++)
		{
			if (L_o[j].T==12)
				continue;
			if (L_o[j].T==1)
				continue;
			

			int p= Inclusion(L_o[i].v, L_o[j].v);
			if(p>=0) // v1 est inclu dans v2
			{
				L_o[i].L_sym.push_back(make_tuple(L_o[j].v,p)); // rajoute a la liste
			}
		}
	}


	
}

//===============
// affiche le resultat sur le flux de sortie o
void Affiche_objets(ostream & o)
{
	//--- affichage
	o<<"================================="<<endl;
	o<<" Liste des objets et de leur propri�t�s."<<endl;
	o<<" Le bilan se trouve en fin de fichier."<<endl;
	o<<"================================="<<endl;
	o<<endl;

	int n12=0,n6=0,n4=0,n3=0,n2=0,n1=0;
	for(int i=0; i<L_o.size(); i++)
	{
		//	if (L_o[i].T==12)			continue; // saute les periodes T=12
	
		int v = L_o[i].v;
		int v2= Reverse(v);
		o<<"-------------------"<<endl;
		o<<"Objet  v="<<v<<"\t"<<bitset<12>(v2)<<"   periode T="<<L_o[i].T<<", \t"<<Notes(v2)<<endl;
		o<<" nombre de notes n="<<L_o[i].n<<endl<<endl;


		
		o<<"   objets voisins avec une note de plus:"<<endl;
		for(auto nt : L_o[i].L_up)
		{
			int val = get<0>(nt), p =get<1>(nt), j=get<2>(nt);
			int val2 = Right_shift(val,(12-p)%12); // decalage
			val2 = Reverse(val2);
			o<<" \tv="<<val<<"\t"<<bitset<12>(val2);
			o<<"   periode T="<<L_o[j].T;
			o<<", \t"<<Notes(val2);
			if (p !=0)
				o<<"  \t (decalage de p="<<p<<")";
			o<<endl;

		}


		o<<endl<<endl;

		o<<"   objets voisins avec une note de moins:"<<endl;
		for(auto nt : L_o[i].L_down)
		{
			int val = get<0>(nt), p =get<1>(nt), j=get<2>(nt);
			int val2 = Right_shift(val,(12-p)%12); // decalage
			val2 = Reverse(val2);
			o<<" \tv="<<val<<"\t"<<bitset<12>(val2);
			o<<"   periode T="<<L_o[j].T;
			o<<", \t"<<Notes(val2);
			if (p !=0)
				o<<"  \t (decalage de p="<<p<<")";
			o<<endl;

		
		}

		o<<endl<<endl;

		
		if(L_o[i].T==12)
			n12++;
		if(L_o[i].T==6)
			n6++;
		if(L_o[i].T==4)
			n4++;
		if(L_o[i].T==3)
			n3++;
		if(L_o[i].T==2)
			n2++;
		if(L_o[i].T==1)
			n1++;

	}


	//----- liste des inclusions
	int Nis=0, Nis2=0;
	
	o<<endl<<endl;
	o<<"Liste des inclusions"<<endl;
	o<<"-------------------"<<endl;
	for(int i=0; i<L_o.size(); i++)
	{
		Nis2++;
		if(L_o[i].L_sym.size()>0)
		{
			Nis++;
			o<<endl;
			o<<"objet v1="<<L_o[i].v<<"=\t"<<bitset<12>(Reverse(L_o[i].v))<<"=\t"<<Notes(Reverse(L_o[i].v))<<" est inclu dans les objets symetriques suivants: "<<endl;
			for(int j=0; j<L_o[i].L_sym.size(); j++)
			{
				int v2=get<0>(L_o[i].L_sym[j]);
				int p=get<1>(L_o[i].L_sym[j]);
				int v3=Right_shift(v2, (12- p)%12);
				o<<"objet v2="<<v2<<"=\t"<<bitset<12>(Reverse(v3))<<"=\t"<<Notes(Reverse(v3))<<endl;
			}
			o<<endl;
		}
	}

	o<<endl<<endl;


	int Nis3=0;
	o<<"Liste des objets non symetriques non inclus dans des objets symetriques"<<endl;
	o<<" c'est a dire de l'ensemble I"<<endl;
	o<<"-------------------"<<endl;

	vector<int> N_sym (13,0); // pour comptage, N_sym[n] = nombre d'objets de I ayant n notes.

	
	for(int i=0; i<L_o.size(); i++)
	{
		
		if(L_o[i].T ==12)
			if(L_o[i].L_sym.size()==0)
			{
				Nis3++;
				o<<endl;
				o<<"objet v="<<L_o[i].v;
				//o<<"=\t"<< bitset<12>(Reverse(L_o[i].v));
				o<<"=\t"<<Notes(Reverse(L_o[i].v))<<endl;
				o<<"    n ="<<L_o[i].n<<endl;
				N_sym[L_o[i].n]= N_sym[L_o[i].n]+1;// comptage
				
				//... Liste des objets v' de meme type obtenus en rajoutant une note
				int cpt=0;
				for(int j=0; j< L_o[i].L_up.size(); j++) // parcourt les objets ayant une note de plus
				{

					int k = get<2>(L_o[i].L_up[j]); // index
				
					if(L_o[k].L_sym.size()==0)
					{
						int v2 = L_o[k].v;
						int p2 = get<1>(L_o[i].L_up[j]);
						int v2_dec =Right_shift(v2, (12- p2)%12);
						o<<"   -> v="<<v2<<",";
						//	o<<" p="<<p2;
						o<<"\t"<<Notes(Reverse(v2_dec))<<endl;
//						o<<" n="<<L_o[k].n<<" p="<<get<1>(L_o[i].L_up[j])<<endl;
						cpt++;
					}
				}
//				if(cpt==0)					o<<"   MAXIMAL."<<endl;
				//... Liste des objets v' de meme type obtenu en enlevant une note
				cpt=0;
				for(int j=0; j< L_o[i].L_down.size(); j++) // parcourt les objets ayant une note de plus
				{
					int k = get<2>(L_o[i].L_down[j]);
				
					if(L_o[k].L_sym.size()==0)
					{
						int v2 = L_o[k].v;
						int p2 = get<1>(L_o[i].L_down[j]);
						int v2_dec =Right_shift(v2, (12- p2)%12);
						o<<"   <- v="<<v2<<",";
						//o<<" n="<<L_o[k].n<<endl;
						o<<"\t"<<Notes(Reverse(v2_dec))<<endl;
						cpt++;
					}
				
				}
//				if(cpt==0)					o<<"   MINIMAL."<<endl;
			}
	}



	
	//-----Bilan ---------------------------------
	o<<"==============="<<endl;
	o<<"BILAN"<<endl;
	o<<"==============="<<endl;
	o<<"Il y a "<<L_o.size()<<" objets dont:"<<endl;
	o<<n12<<"   objets de periode T=12."<<endl;
	o<<n6<<"   objets de periode T= 6."<<endl;
	o<<n4<<"   objets de periode T= 4."<<endl;
	o<<n3<<"   objets de periode T= 3."<<endl;
	o<<n2<<"   objets de periode T= 2."<<endl;
	o<<n1<<"   objets de periode T= 1."<<endl;

	o<<endl;
	o<<endl;
	o<<"Il y a "<<Nis<<" objets non symetriques inclus dans des objets symetriques"<<endl;
	o<<"   et  "<<Nis2-Nis<<" objets non symetriques inclus seulement dans des objets non symetriques."<<endl; 
	o<<"==============="<<endl;

	o<<endl<<endl;
	o<<"====================="<<endl;
	o<<" Ensemble I: des objets non sym non inclus dans objets symetriques,"<<endl;
	o<<"  il y a:"<<endl;
	int sum=0;
	for(int n=1; n<=12; n++)
	{
		if(N_sym[n]>0)
			o<<"    "<<N_sym[n]<<" objets de I ayant "<<n<<" notes."<<endl;
		sum+= N_sym[n];
	}
	o<<" Soit, "<<sum<<" objets dans I"<<endl;
	o<<"====================="<<endl;
	
}
//================
/*
 on entre une gamme, il renvoit la valeur et les notes.
 */
void Test()
{
	while(1)
	{
	cout<<"Objet sous forme suite de 12 bits 0,1 =?"<<flush;
	string n;
	cin>>n;
	int n2 = bitset<12>(n).to_ulong();
	n2=Reverse(n2);
	cout<<"Notes="<<Notes(Reverse(n2))<<endl;
	cout<<"      "<<bitset<12>(Reverse(n2))<<endl;
	cout<<"    val="<<n2<<" Periode T="<<Periode(n2)<<endl;
	
	
	int p=	Test_permut_circ(n2);
	cout<<"    decalage="<<p<<endl;
	cout<<"Notes="<<Notes(Reverse(n2))<<endl;
	cout<<"      "<<bitset<12>(Reverse(n2))<<endl;
	cout<<"    val="<<n2<<endl;
	}	
}
//=============
int main()
{

	fabrique_liste_objets(); // -> L_o

	Recherche_liens(); // -> complete L_o
	
	Liste_inclusions_sym(); // -> liste L_sym
	
	Affiche_objets(cout); // affiche a l'ecran

	ofstream f("objets_de_Malik.txt");
	Affiche_objets(f); // ecrit dans fichier

	
	return 0;
}
