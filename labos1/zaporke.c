#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char lozinka[255],master[255],lista[255],zahtjev,nova_lozinka[255];							
int adresa,adrese[1000];

int main(void){
	FILE *ulaz=fopen("popis.txt","r+w");										//putanja do dokumenta

	if(fscanf(ulaz,"%s",&master)==1){										//čitamo prvi redak dokumenta(kriptirana master lozinka)
		for(int m=0;master[m]!='\0';m++){						
			master[m]=master[m]-70;										//dekriptiramo master lozinku
			if(master[m]<33)
				master[m]=master[m]+94;
		}
		printf("Unesi svoju master lozinku\n");									//klijent unosi svoju master lozinku
		scanf("%s",&lozinka);
		if(strcmp(master,lozinka)==0){										//provjeravamo je li master lozinka ispravna
			printf("Unijeli ste tocnu master lozinku\n");
			
				printf("Za unos neke nove lozinke u bazu pritisnite n,a za pregled stare s\n");		//tražimo od klijenta da izabere zahtjev
				scanf("%s",&zahtjev);
				if(zahtjev =='n'){									//ako je zahtjev n unosimo novu lozinku u bazu
					printf("Unesi novu lozinku u bazu\n");	
					scanf("%s",&nova_lozinka);							//klijent unosi novu lozinku u bazu
					int k=0;
					while(fscanf(ulaz,"%s",&lista)==1){						//određujemo adresu na kojoj će se spremiti lozinka						
						k++;
					}
					k=k/3;
					int b=0,c=0,zbroj,x1=nova_lozinka[0],x2,osiguranje;
					for(;nova_lozinka[b]!='\0';b++,c++){						//iteriramo po elementima lozinke
						if(master[c]=='\0')
							c=0;
						int ind1=master[c];
						int ind2=nova_lozinka[b];
						zbroj=ind1+ind2;							//zbrajamo slova lozinke sa slovima master lozinke->kriptiramo
						x2=nova_lozinka[b];
						if(zbroj>126)
							zbroj=zbroj-94;
						nova_lozinka[b]=zbroj;							//kriptiramo elemente lozinke
					}
					osiguranje=x1+x2;								//postavljamo osiguranje u slucaju napada zamjenom
					if(osiguranje>126)						
						osiguranje=osiguranje-127;
					nova_lozinka[b]=osiguranje;
					fprintf(ulaz,"\n%d : %s",k,&nova_lozinka);					//upisujemo kriptiranu lozinku
					printf("Unijeli ste novu lozinku na adresu %d\n",k);
				}
				if(zahtjev =='s'){									//ako je zahtjev s tražimo stare zozinke
					printf("Unesi adresu stare lozinke koju zelis pogedat\n");
					scanf("%d",&adresa);								//klijent unosi adresu lozinke koju želi pogledati
					int i=0,nasli=0,napad=0,y1,y2,y3;
					while(fscanf(ulaz,"%s",&lista)==1){						//učitavamo elemente dokumenta
						if(adresa==i/3 && i%3==2){						//uvjet pronalaska elementa sa adrese
				      			int b=0,c=0,razlika;
							for(;lista[b+1]!='\0';b++,c++){    				//iteriramo po elementima pronađene lozinke
								if(master[c]=='\0')
									c=0;
								int ind1=master[c];
								int ind2=lista[b];
								razlika=ind2-ind1;					//od slova lozinke oduzimamo slova master lozinke->dekriptiramo
								if(razlika<33)
									razlika=razlika+94;
								lista[b]=razlika;					//dekriptiramo elemente lozinke
								nasli++;						//postavljamo zastavicu na 1 jer smo pronašli lozinku
							}
							y1=lista[0];
							y2=lista[b-1];
							y3=lista[b];
							if(y1+y2>126)
								y3=y3+127;
							if(y1+y2==y3){							//provjeravamo je li sustav napadnut metodom zamjene
								for(b=0;lista[b+1]!='\0';b++)
									printf("%c",lista[b]);				//ispisujemo traženu lozinku
								printf("\n");
							}
							else{
								printf("Sustav napadnut zamjenom\n");
								nasli++;
							}
						}
						i++;
					}
					if(nasli==0)									//ako je zastavica ostala 0 znači da ta adresa ne postoji
						printf("Lozinka na toj adresi ne postoji\n");
				}

				
			fclose(ulaz);
			return 0;
		}
		else{													//ako je unešena kriva master lozinka zaustavlja se program
			printf("Unijeli ste krivu master lozinku\n");
			fclose(ulaz);
			return 0;
		}	
	}		

	printf("Postavi master lozinku\n");										//ako je dokument prazan traži se od klijenta da unese svoju master lozinku
	scanf("%s",&master);
	printf("Postavili ste master zaporku %s\n",master);

	for(int m=0;master[m]!='\0';m++){										//iteriramo po elementima master lozinke
		master[m]=master[m]+70;											//kriptiramo elemente master lozinke
		if(master[m]>126)
			master[m]=master[m]-94;
	}
	
	fprintf(ulaz,"%s",&master);
	fclose(ulaz);
return 0;
}