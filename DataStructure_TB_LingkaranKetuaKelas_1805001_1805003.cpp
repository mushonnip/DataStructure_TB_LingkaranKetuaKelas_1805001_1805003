/*
Author	: Abu Mushonnip, Ade Irawan
*/

#include <iostream>
#include <cstdio>

using namespace std;

typedef struct
{
	int nim;
} nilaiMatkul;

typedef struct elmt *alamatelmt;

typedef struct elmt
{
	nilaiMatkul kontainer;
	alamatelmt next;
} elemen;

typedef struct
{
	elemen *first;
} list;

void createList(list *L)
{
	(*L).first = NULL;
}

int countElement(list L)
{
	int hasil = 0;

	if (L.first != NULL)
	{

		elemen *bantu;

		bantu = L.first;

		while (bantu != NULL)
		{
			hasil = hasil + 1;

			bantu = bantu->next;
		}
	}
	return hasil;
}

void addFirst(int nim, list *L)
{
	elemen *baru;

	baru = new elemen;
	baru->kontainer.nim = nim;

	if ((*L).first == NULL)
	{

		baru->next = NULL;
	}
	else
	{

		baru->next = (*L).first;
	}
	(*L).first = baru;
	baru = NULL;
}

void addAfter(elemen *prev, int nim)
{
	if (prev != NULL)
	{
		elemen *baru;
		baru = new elemen;
		baru->kontainer.nim = nim;

		if (prev->next == NULL)
		{

			baru->next = NULL;
		}
		else
		{
			baru->next = prev->next;
		}
		prev->next = baru;
		baru = NULL;
	}
}

void addLast(int nim, list *L)
{
	//karena hanya mengubah nilai elemen tanpa melempar nilai, maka menggunakan void

	if ((*L).first == NULL)
	{
		//proses jika list masih kosong
		addFirst(nim, L);
	}
	else
	{
		//proses jika list telah berisi elemen
		//kita harus mencari elemen terakhir
		//inisialisasi elemen last dari awal first
		elemen *last = (*L).first;

		while (last->next != NULL)
		{ //dicari sampai ketemu null
			//iterasi sampai ketemu null
			last = last->next;
		}
		//dilakukan proses penambahan add after dari last yang sudah ditemukan
		addAfter(last, nim);
	}
}

void delFirst(list *L)
{
	if ((*L).first != NULL)
	{
		elemen *hapus = (*L).first;

		if (countElement(*L) == 1)
		{
			(*L).first = NULL;
		}
		else
		{
			(*L).first = (*L).first->next;
		}

		hapus->next = NULL;
		delete hapus;
	}
	else
	{
		printf("list kosong\n");
	}
}

void delAfter(elemen *prev)
{
	if (prev != NULL)
	{
		elemen *hapus = prev->next;

		if (hapus != NULL)
		{
			if (hapus->next == NULL)
			{
				prev->next = NULL;
			}
			else
			{
				prev->next = hapus->next;
			}

			hapus->next = NULL;
			delete hapus;
		}
	}
}

void delLast(list *L)
{
	if ((*L).first != NULL)
	{
		if (countElement(*L) == 1)
		{

			delFirst(L);
		}
		else
		{
			elemen *last = (*L).first;
			elemen *before_last;

			while (last->next != NULL)
			{
				before_last = last;
				last = last->next;
			}

			delAfter(before_last);
		}
	}
	else
	{
		printf("list kosong\n");
	}
}

void delAll(list *L)
{
	int i;
	if (countElement(*L) != 0)
	{
		for (i = countElement(*L); i >= 1; i--)
		{
			delLast(L);
		}
	}
}

void printElement(list L)
{
	if (L.first != NULL)
	{

		elemen *bantu = L.first;
		int i = 1;
		while (bantu != NULL)
		{
			printf("%d ", bantu->kontainer.nim);
			bantu = bantu->next;
			i = i + 1;
		}
	}
	else
	{
		printf("list kosong\n");
	}
}

void lempar(list *L, int x)
{
	list terhapus;
	createList(&terhapus);

	elemen *pemilih = L->first;

	while (countElement(*L) > 1)
	{
		elemen *terpilih = pemilih;
		elemen *sebelum;

		for (int i = 0; i < x; i++)
		{
			sebelum = terpilih;

			if (terpilih->next != NULL)
			{
				terpilih = terpilih->next;
			}
			else
			{
				terpilih = L->first;
			}
		}

		// printf("pemilih = %d\n", pemilih->kontainer.nim);
		// printf("terpilih = %d\n", terpilih->kontainer.nim);
		pemilih = terpilih->next;
		if (pemilih == NULL) //jika pemilih melebihi batas countElement
		{
			pemilih = L->first;
		}

		//menghapus elemen yang terpilih
		addLast(terpilih->kontainer.nim, &terhapus); //menambahkan elemen terpilih ke List *terhapus
		if (sebelum->next != NULL)
		{
			//printf("Sebelum = %d\n", sebelum->kontainer.nim);
			delAfter(sebelum);
		}
		else
		{
			delFirst(L); //jika sebelum melebihi batas countElement maka yang dihapus elemen pertama dari list L
		}
	}

	printf("Mahasiswa yang keluar\t\t: ");
	printElement(terhapus);
	printf("@\n");
	printf("Ketua kelas\t\t\t: ");
	printElement(*L);
	printf("\n\n");
}

int main()
{
	list L;
	createList(&L); //membuat list untuk memuat ketua kelas terpilih

	int t, n, x = 0; //inisialisasi variabel {testcase, jumlah mahasiswa, posisi yang ditunjuk}
	printf("Program Untuk Menentukan Ketua Kelas");
	printf("\n");
	printf("Masukkan jumlah test case\t: ");
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{
		//TESTCASE t
		printf("Masukkan jumlah mahasiswa\t: ");
		scanf("%d", &n);
		printf("Posisi yang ditunjuk\t\t: ");
		scanf("%d", &x);

		for (int i = 1; i <= n; ++i)
		{
			addLast(i, &L);
		}
		lempar(&L, x); //operasi untuk melakukan pelemparan ketua kelas
		delAll(&L);	//menghapus seluruh elemen list L setelah iterasi test case 
	}

	return 0;
}