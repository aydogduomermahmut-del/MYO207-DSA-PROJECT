#include <stdio.h>
#include <stdlib.h>

// Ad SOYAD: Ömer Mahmut Aydoğdu
// Öğrenci Numaranız: 2420161020
// BTK Akademi Sertifika Bağlantınız (https://www.btkakademi.gov.tr/portal/certificate/validate?certificateId= ZA1Urdy1Z0 )
struct Node {
	int veri;
	struct Node *next;
};

typedef struct Node Dugum;

void dizi_yazdir(int dizi[], int BOYUT) {
	int i;
	for (i=0; i<BOYUT; i++) {
		printf("%3d", dizi[i]);
	}
	printf("\n");
}

void takas(int *ap, int *bp) {
	int swap;
	swap = *ap;
	*ap = *bp;
	*bp = swap;
}

void sirala(int dizi[], int BOYUT) {
	int i, j;
	int takas_oldu;
	
	printf("iter.  0: ");
	dizi_yazdir(dizi, BOYUT);
	
	for (i=1; i<BOYUT; i++) {
		takas_oldu = 0;
		for (j=0; j<BOYUT-1; j++) {
			if (dizi[j] > dizi[j+1]) {
				takas(dizi+j, dizi+j+1);
				takas_oldu = 1;
			}
		}
		printf("iter.%2d: ", i);
		dizi_yazdir(dizi, BOYUT);
		
		if (takas_oldu == 0) {
			break;
		}
	}
}

int ara(int dizi[], int BOYUT, int search, int ilk_ind, int son_ind) {
	int orta_ind = (ilk_ind + son_ind) / 2;
	
	if (search == dizi[orta_ind]) {
		return orta_ind;
	}
	else if (search > dizi[orta_ind] && (son_ind-ilk_ind) > 0) {
		return ara(dizi, BOYUT, search, orta_ind+1, son_ind);
	}
	else if (search < dizi[orta_ind] && (son_ind-ilk_ind) > 0) {
		return ara(dizi, BOYUT, search, ilk_ind, orta_ind-1);
	}
	else {
		return -1;
	}
}

Dugum* liste_olustur(int dizi[], int BOYUT) {
	int i;
	Dugum *head = NULL;
	Dugum *yeni, *p;
	
	head = (Dugum*) malloc(sizeof(Dugum));
	if (head == NULL) {
		return NULL;
	}
	head->veri = dizi[0];
	head->next = NULL;
	
	p = head;
	
	for (i=1; i<BOYUT; i++) {
		yeni = (Dugum*) malloc(sizeof(Dugum));
		if (yeni == NULL) {
			return NULL;
		}
		yeni->veri = dizi[i];
		yeni->next = NULL;
		
		p->next = yeni;
		p = yeni;
	}
	
	return head;
}

void liste_dolas(Dugum *p) {
	while (p != NULL) {
		printf("%d --> ", p->veri);
		p = p->next;
	}
	printf("NULL\n");
}

void liste_temizle(Dugum *head) {
	Dugum *p;
	while (head != NULL) {
		p = head;
		head = head->next;
		free(p);
	}
}

int main() {
	int A[] = {12, 47, 55, 8, 7, 15, 3, 99, 25, 32};
	int N = sizeof(A) / sizeof(A[0]);
	int aranan, sonuc;
	int *dizi_dinamik;
	Dugum *head;
	
	printf("Orijinal Dizi:\n");
	dizi_yazdir(A, N);
	
	dizi_dinamik = (int*) malloc(N * sizeof(int));
	if (dizi_dinamik == NULL) {
		printf("Bellek ayrilamadi!\n");
		return 1;
	}
	
	int i;
	for (i=0; i<N; i++) {
		dizi_dinamik[i] = A[i];
	}
	
	printf("\n");
	sirala(dizi_dinamik, N);
	
	printf("\nSiralanmis Dizi:\n");
	dizi_yazdir(dizi_dinamik, N);
	
	printf("\nBaglantili Liste:\n");
	head = liste_olustur(dizi_dinamik, N);
	if (head != NULL) {
		liste_dolas(head);
	}
	
	printf("\nAramak istediginiz deger: ");
	scanf("%d", &aranan);
	
	sonuc = ara(dizi_dinamik, N, aranan, 0, N-1);
	
	if (sonuc == -1) {
		printf("Aradiginiz deger %d, dizide bulunamadi!\n", aranan);
	}
	else {
		printf("Aradiginiz deger %d, dizi %d. icinde bulundu!\n", aranan, sonuc);
	}
	
	free(dizi_dinamik);
	liste_temizle(head);
	
	return 0;
}